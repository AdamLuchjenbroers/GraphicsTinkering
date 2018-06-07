#include "philosopher/NaivePhilosophers.h"

int main( int argc, char* args[] ) { 
  FrameworkOneApp *thisApp = new NaiveCore();

  thisApp->appInit();

  while (thisApp->appMain()) { };
 
  delete thisApp;
  return 0;
}
