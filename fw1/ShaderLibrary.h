#pragma once

#include "fw1.h"

#include <string>
#include <map>

/** Manages a collection of shader script files and supplies the shader as requested. It expects the shader library
 *  to be organized with sub-folders for each GLSL version and will select the shader script file corresponding to
 *  the highest GLSL version supported by the current rendering context.
 *
 *  This class uses a singleton design patten.
 */
class ShaderLibrary {
public:
/** Retrieve a Shader object corresponding to the script name provided, selecting a version of the shader that
 *  is supported by the current rendering context.
 *  @param name The filename of the shader script (without directory)
 *  @param stage The GL pipeline stage for this shader.
 *  @return A Shader object created with the requested script and for the requested pipeline stage.
 */
    ShaderRef getShader(const std::string name, GLuint stage);

/** Gets the Shader Library object, or creates it if required using the default shader search path.
 *  @return A pointer to the shader library.
 */
    static ShaderLibrary *getLibrary();
/** Replaces the current Shader Library object with a new Shader Library based in the specified path
 *  @param newpath The new base search path for the shader library.
 */
    static void setLibraryPath(char *newpath);
private:
    static ShaderLibrary *library;

    ShaderLibrary(char *basepath);

    std::map<GLSLVersion, char*> _versions;
    std::map<std::string, Shader> _shaders;
};
