#include "PhilosopherCore.h"
#include <stdio.h>

PhilosopherCore::PhilosopherCore() {
    display = SDLDisplay::resizableDisplay("Dining Philosophers", 600, 600);

    _projection = Matrix4::fovHorizontal( 1.0f, 6.0f, 90.0f, display->aspectRatio());
}

PhilosopherCore::~PhilosopherCore() {
    delete display;
}

void PhilosopherCore::resizeWindow(int newX, int newY) {
    _projection = Matrix4::fovHorizontal( 1.0f, 6.0f, 90.0f, display->aspectRatio());

    GLint proj_loc = _shader.uniformLocation("projection");
    glUniformMatrix4fv(proj_loc, 1, false, _projection.buffer());
}

void PhilosopherCore::keyEvent(SDL_Keysym &key, bool press) {
  if (!press) {
    return;
  }
    
  int n = tableState.num_diners();

  switch(key.sym) {
  case SDLK_a:
    if (n < 8) {
      tableState = TableState(n+1);
    }
    break;
  case SDLK_z:
    if (n > 3) {
      tableState = TableState(n-1);
    }
    break;
  }

  GLint loc = _shader.uniformLocation("num_philosophers");
  glUniform1i(loc, tableState.num_diners());
}

void PhilosopherCore::appInit() {
   GLuint glerror;
   bool success = true;
   size_t buf_size;

   if (!ShaderLibrary::isReady()) {
       ShaderLibrary::setLibraryPath("./shader"); 
   }

   success = _shader.addShader("philosopher-vertex.sdr", GL_VERTEX_SHADER);   
   success &= _shader.addShader("philosopher-geo.sdr", GL_GEOMETRY_SHADER);   
   success &= _shader.addShader("philosopher-fragment.sdr", GL_FRAGMENT_SHADER);   

   if (success == false) {
      Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Failed to build shader program, missing shader\n");

      tableState.stop_running();
      return;
   }

    success = _shader.linkProgram();

    if (success == false) {
        Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Unable to link rendering program: %s\n", gluErrorString(glerror));

       tableState.stop_running();
       return;
    }
    
    glUseProgram(_shader.programID());

    GLint loc = _shader.uniformLocation("num_philosophers");
    glUniform1i(loc, tableState.num_diners());

    glGenVertexArrays(1, &_vertexarray);
    glBindVertexArray(_vertexarray);

    glGenBuffers(1, &_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(GLint), NULL, GL_DYNAMIC_DRAW);
    checkGLError("Error encountering creating buffer: %s\n", Logger::LOG_ERROR);

    loc = _shader.attributeLocation("type");

    glVertexAttribIPointer(loc, 1, GL_INT, GL_FALSE, 0);
    glEnableVertexAttribArray(loc);    
    checkGLError("Error encountering setting up vertex array: %s\n", Logger::LOG_ERROR);

    GLint samp_loc = _shader.uniformLocation("tex_philosopher");
    _tx_philosopher = Texture::loadImage("textures/philosopher.png", GL_TEXTURE0);
    glUniform1i(samp_loc, 0);

    samp_loc = _shader.uniformLocation("tex_chopstick");
    _tx_chopstick = Texture::loadImage("textures/chopstick.png", GL_TEXTURE1);
    glUniform1i(samp_loc, 1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    tableState.start_dinner();
}

void PhilosopherCore::updateTable() {
    size_t buf_size;
    GLvoid *buf;
 
    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    buf = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    tableState.write_state(buf);
    glUnmapBuffer(GL_ARRAY_BUFFER);
}

bool PhilosopherCore::appMain() {

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glVertexAttrib1f(0, _angle);
    _angle += 0.1f;
  
    updateTable();
    glDrawArrays(GL_POINTS, 0, 2 * tableState.num_diners());

    display->swapBuffers();
    display->mainLoop(*this);

    return tableState.is_running();
}

bool PhilosopherCore::checkGLError(const char *errfmt, Logger::Level loglevel) {
    GLenum glerror;

    glerror = glGetError();

    if (glerror == GL_NO_ERROR) {
       return true;
    } else {
       Logger::logprintf(loglevel, Logger::LOG_APPLICATION, errfmt, gluErrorString(glerror));
       return false;
    }
}
