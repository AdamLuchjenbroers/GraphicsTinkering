#include "philosopher/PhilosopherCore.h"

int main( int argc, char* args[] ) { 
  FrameworkOneApp *thisApp = new PhilosopherCore();

  thisApp->appInit();

  while (thisApp->appMain()) { };
 
  delete thisApp;
  return 0;
}
