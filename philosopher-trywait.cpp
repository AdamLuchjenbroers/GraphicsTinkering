#include "philosopher/TryWaitCore.h"

int main( int argc, char* args[] ) { 
  PhilosopherCore *thisApp = new TryWaitCore();

  thisApp->appInit();

  while (thisApp->appMain()) { };
 
  delete thisApp;
  return 0;
}
