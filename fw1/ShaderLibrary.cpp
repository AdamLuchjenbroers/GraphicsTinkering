#include <glob.h>
#include <libgen.h>
#include <sys/stat.h>

#include "ShaderLibrary.h"
#include "fw1.h"

/*
 * Shader Library 
 */
ShaderLibrary::ShaderLibrary(char *basepath) {
    char search[64];
    glob_t files;
    int file_index;

    snprintf(search, 64, "%s/*", basepath);
    glob(search, 0, NULL, &files);
    
    Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_SHADERS, "Searching shader path %s - found %i files\n", search, files.gl_pathc);

    for(file_index=0; file_index < files.gl_pathc; file_index++) {
        char *path = NULL;
        GLSLVersion *ver = NULL;
        struct stat stat_data;
        
        Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_SHADERS, "Checking found file %s\n", files.gl_pathv[file_index]);
        lstat(files.gl_pathv[file_index], &stat_data);

        if (S_ISDIR(stat_data.st_mode)) {
            char *dirname = basename(files.gl_pathv[file_index]);

            ver = GLSLVersion::versionFromText(dirname);
            if ( ver != NULL ) {
                path = new char[ strlen(files.gl_pathv[file_index])+ 1 ];
                strcpy(path, files.gl_pathv[file_index]);
                 
                Logger::logprintf(Logger::LOG_INFO, Logger::LOG_SHADERS, "Added base shader path %s\n", path, files.gl_pathv[file_index]);
                versions[*ver] = path;
            }
        }
    }

};

ShaderLibrary *ShaderLibrary::library = NULL;

void ShaderLibrary::setLibraryPath(char *newpath) {
    if (library != NULL) {
        delete library;
    }

    library = new ShaderLibrary(newpath);
};

ShaderLibrary *ShaderLibrary::getLibrary() {
    if (library == NULL) {
        //Initialise with default library path
        char defaultPath[9] = "./shader";
        setLibraryPath(defaultPath);
    }

    return library;
};

Shader *ShaderLibrary::getShader(const char *name, GLuint stage) {
    std::map<GLSLVersion, char*>::iterator itr;
    GLSLVersion *context = GLSLVersion::getContextVersion();

    //Start at the highest version and work our way back
    for(itr = versions.end(); itr != versions.begin(); ) {
        itr--;
        
        if (itr->first <= *context) {
            char shaderPath[256];
            struct stat shaderStat;

            snprintf(shaderPath, 256, "%s/%s", itr->second, name);
            Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_SHADERS, "Checking for shader: %s\n", shaderPath);

            if (stat(shaderPath, &shaderStat) == 0) {
                Logger::logprintf(Logger::LOG_INFO, Logger::LOG_SHADERS, "Found shader %s\n", shaderPath);
                return new Shader(shaderPath, stage);
            }
        }
    }
     
    Logger::logprintf(Logger::LOG_WARN, Logger::LOG_SHADERS, "Failed to locate shader %s\n", name);
    return NULL;
};