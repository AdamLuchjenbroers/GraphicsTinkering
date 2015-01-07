#include "SingleLightRig.h"
#include "Logger.h"


SingleLightRig::SingleLightRig() {
    writeValues(_light.position, 0.0f, 0.0f, 0.0f);
    _light.position[3] = 1.0f;

    writeValues(_light.color, 1.0f, 1.0f, 1.0f);
    writeValues(_light.ambient, 0.0f, 0.0f, 0.0f);
}

bool SingleLightRig::setPosition(int light, Vector3H pos) {
    if (light != 1) {
        //Addressing a light that does not exist
        Logger::logprintf(Logger::LOG_WARN, Logger::LOG_LIGHTING, "Unable to update position of light %i, single light rig in use\n", light);
        return false;
    }

    pos.writeTo(_light.position);
    return true;
}

void SingleLightRig::writeValues(GLfloat *buffer, GLfloat v1, GLfloat v2, GLfloat v3) {
    buffer[0] = v1;
    buffer[1] = v2;
    buffer[2] = v3;
}

bool SingleLightRig::setPosition(int light, GLfloat x, GLfloat y, GLfloat z) {
    if (light != 1) {
        //Addressing a light that does not exist
        Logger::logprintf(Logger::LOG_WARN, Logger::LOG_LIGHTING, "Unable to update color of light %i, single light rig in use\n", light);
        return false;
    }

    writeValues(_light.position, x, y, z);
    return true;
}

bool SingleLightRig::setColor(int light, GLfloat r, GLfloat g, GLfloat b) {
    if (light != 1) {
        //Addressing a light that does not exist
        Logger::logprintf(Logger::LOG_WARN, Logger::LOG_LIGHTING, "Unable to update color of light %i, single light rig in use\n", light);
        return false;
    }

    writeValues(_light.color, r, g, b);
    return true;
}


bool SingleLightRig::setAmbient(int light, GLfloat r, GLfloat g, GLfloat b) {
    if (light != 1) {
        //Addressing a light that does not exist
        Logger::logprintf(Logger::LOG_WARN, Logger::LOG_LIGHTING, "Unable to update color of light %i, single light rig in use\n", light);
        return false;
    }

    writeValues(_light.ambient, r, g, b);
    return true;
}

bool SingleLightRig::loadRig(ShaderProgram &program) {
    GLuint progID;
    GLint rigLoc;

    progID = program.programID();

    if ( !program.isLinked() ) {
        Logger::logprintf(Logger::LOG_WARN, Logger::LOG_LIGHTING, "Unable to load lighting uniform for program %i, program not yet linked.\n", progID);
        return false;
    }

    rigLoc = program.uniformBlockLocation("SingleLight");
    glUniformBlockBinding(progID, rigLoc, _rigBuffer);

    return updateBuffer();
}

bool SingleLightRig::updateBuffer() {
    glGenBuffers(1, &_rigBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, _rigBuffer);

    glBufferData(GL_UNIFORM_BUFFER, sizeof(_light), &_light, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, _binding, _rigBuffer);

    return true; 
}
