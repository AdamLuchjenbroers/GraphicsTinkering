#include <glob.h>
#include <libgen.h>
#include <sys/stat.h>

#include "ShaderLibrary.h"
#include "fw1.h"

/*
 * Shader Library 
 */
ShaderLibrary::ShaderLibrary(const char *basepath) {
    char search[64];
    glob_t files;
    int file_index;

    snprintf(search, 64, "%s/*", basepath);
    glob(search, 0, NULL, &files);
    
    Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_SHADERS, "Searching shader path %s - found %i files\n", search, files.gl_pathc);

    for(file_index=0; file_index < files.gl_pathc; file_index++) {
        char *path = NULL;
        struct stat stat_data;
        
        Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_SHADERS, "Checking found file %s\n", files.gl_pathv[file_index]);
        lstat(files.gl_pathv[file_index], &stat_data);

        if (S_ISDIR(stat_data.st_mode)) {
            char *dirname = basename(files.gl_pathv[file_index]);
            GLSLVersion ver = GLSLVersion::versionFromText(dirname);

            if ( ver > GLSLVersion(0,0) ) {
                path = new char[ strlen(files.gl_pathv[file_index])+ 1 ];
                strcpy(path, files.gl_pathv[file_index]);
                 
                Logger::logprintf(Logger::LOG_INFO, Logger::LOG_SHADERS, "Added base shader path %s\n", path, files.gl_pathv[file_index]);
                _versions[ver] = path;
            }
        }
    }

};

ShaderLibrary *ShaderLibrary::library = NULL;

void ShaderLibrary::setLibraryPath(const char *newpath) {
    if (library != NULL) {
        delete library;
    }
    Logger::logprintf(Logger::LOG_INFO, Logger::LOG_SHADERS, "Initialising Shader Library with search path %s\n", newpath);

    library = new ShaderLibrary(newpath);
};

ShaderLibrary *ShaderLibrary::getLibrary() {
    if (library == NULL) {
        //Initialise with default library path
        Logger::logprintf(Logger::LOG_INFO, Logger::LOG_SHADERS, "No library loaded, initialising with default search path\n");
        char defaultPath[9] = "./shader";
        setLibraryPath(defaultPath);
    }

    return library;
};

ShaderRef ShaderLibrary::getShader(const std::string name, GLuint stage) {
    std::map<GLSLVersion, char*>::iterator itr;
    GLSLVersion context = GLSLVersion::getContextVersion();

    // First, check if we've already got this shader in memory.
    if ( _shaders[name].isValid() ) {
        Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_SHADERS, "getShader() retrieved %s from cache\n", name.c_str());
        return ShaderRef(_shaders[name]);
    }

    Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_SHADERS, "getShader() called to retrieve %s. Context supports up to GLSL %s\n", name.c_str(), context.getLogName());

    //Start at the highest version and work our way back
    for(itr = _versions.end(); itr != _versions.begin(); ) {
        itr--;
        
        if (itr->first <= context) {
            char shaderPath[256];
            struct stat shaderStat;

            snprintf(shaderPath, 256, "%s/%s", itr->second, name.c_str());
            Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_SHADERS, "Checking for shader: %s\n", shaderPath);

            if (stat(shaderPath, &shaderStat) == 0) {
                Logger::logprintf(Logger::LOG_INFO, Logger::LOG_SHADERS, "Found shader %s\n", shaderPath);
                _shaders[name].loadShader(shaderPath, stage);

                return ShaderRef(_shaders[name]);
            }
        }
    }
     
    Logger::logprintf(Logger::LOG_WARN, Logger::LOG_SHADERS, "Failed to locate shader %s\n", name.c_str());
    return ShaderRef();
};
