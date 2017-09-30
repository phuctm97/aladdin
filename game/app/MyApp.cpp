/*
* Created by phuctm97 on Sep 27th 2017
*/
#include "MyApp.h"
#include "../scenes/IntroScene.h"

USING_NAMESPACE_ALA;

MyApp::MyApp() : Application() {}

void MyApp::init() {
  // TODO: init application (size, title, fps, scene to start, log behaviors)
  setScreenSize( 800, 600 );
  setTitle( "Aladdin" );
  setLoopInterval( 1000.0f / 30 );
  startWithScene( new IntroScene() );
}

void MyApp::release() {
  // TODO: release my application
}
