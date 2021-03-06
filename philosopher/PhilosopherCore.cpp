#include "PhilosopherCore.h"
#include <stdio.h>

PhilosopherCore::PhilosopherCore() {
    display = SDLDisplay::resizableDisplay("Dining Philosophers - Framework Test", 800, 800);

    _projection = Matrix4::fovHorizontal( 1.0f, 6.0f, 90.0f, display->aspectRatio());
}

PhilosopherCore::~PhilosopherCore() {
    delete display;

    if (_table) {
        delete _table;
    }
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
    
  int n = _table->numDiners();

  switch(key.sym) {
  case SDLK_a:
    if (n < 8) {
      setupTable(n+1);
      _table->startDinner();
    }
    break;
  case SDLK_z:
    if (n > 3) {
      setupTable(n-1);
      _table->startDinner();
    }
    break;
  }

  GLint loc = _shader.uniformLocation("num_philosophers");
  glUniform1i(loc, _table->numDiners());
}

void PhilosopherCore::appInit() {
   GLuint glerror;
   bool success = true;
   size_t buf_size;

   setupTable(7);

   if (!ShaderLibrary::isReady()) {
       ShaderLibrary::setLibraryPath("./shader"); 
   }

   success = _shader.addShader("philosopher-vertex.sdr", GL_VERTEX_SHADER);   
   success &= _shader.addShader("philosopher-geo.sdr", GL_GEOMETRY_SHADER);   
   success &= _shader.addShader("philosopher-fragment.sdr", GL_FRAGMENT_SHADER);   

   if (success == false) {
      Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Failed to build shader program, missing shader\n");

      appQuit();
      return;
   }

    success = _shader.linkProgram();

    if (success == false) {
        Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Unable to link rendering program: %s\n", gluErrorString(glerror));

        appQuit();
        return;
    }
    
    glUseProgram(_shader.programID());

    GLint loc = _shader.uniformLocation("num_philosophers");
    glUniform1i(loc, _table->numDiners());

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

    _table->startDinner();
}

void PhilosopherCore::setupTable(int diners) {
    if (_table) {
        delete _table;
    }

    _table = new TableState(diners);
    _table->seatDiners();
}

void PhilosopherCore::updateTable() {
    size_t buf_size;
    GLvoid *buf;
 
    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    buf = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    _table->writeState(buf);
    glUnmapBuffer(GL_ARRAY_BUFFER);
}

bool PhilosopherCore::appMain() {

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glVertexAttrib1f(0, _angle);
    _angle += 0.1f;
  
    updateTable();
    glDrawArrays(GL_POINTS, 0, 2 * _table->numDiners());

    display->swapBuffers();
    display->mainLoop(*this);

    return (_table != NULL);
}


void PhilosopherCore::appQuit() {
    Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "App Exit Received, terminating\n");

    if ( _table ) {
        delete _table;
    }
    _table = NULL;
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
