#include "MyApp.h"

#ifndef LOG_STREAM
#define LOG_STREAM 1
#endif

int WINAPI WinMain( HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int nCmdShow ) {
  MyApp app;
  app.run( hInstance,
           hPrevInstance,
           lpCmdLine,
           nCmdShow,
           LOG_STREAM );
  return 0;
}
