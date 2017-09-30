/*
* Created by phuctm97 on Sep 27th 2017
*/
#include "MyApp.h"
#include "../scenes/IntroScene.h"
#include "MyResourceInitializer.h"

USING_NAMESPACE_ALA;

MyApp::MyApp() : Application() {}

void MyApp::init() {
  // TODO: init application (size, title, fps, scene to start, log behaviors)
  setScreenSize( 800, 600 );
  setTitle( "Aladdin" );
  setAnimationInterval( 1000.0f / 60 );

  registerResourceInitializer(new MyResourceInitializer());
  startWithScene( new IntroScene() );
}

void MyApp::release() {
  // TODO: release my application
}
