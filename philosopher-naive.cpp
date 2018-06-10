#include "philosopher/NaiveCore.h"

int main( int argc, char* args[] ) { 
  PhilosopherCore *thisApp = new NaiveCore();

  thisApp->appInit();

  while (thisApp->appMain()) { };
 
  delete thisApp;
  return 0;
}
