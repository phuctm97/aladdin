/*
* Created by phuctm97 on Sep 27th 2017
*/
#include "MyApp.h"
#include "../scenes/IntroScene.h"
#include "MyResourceInitializer.h"

USING_NAMESPACE_ALA;

MyApp::MyApp() : Application() {}

void MyApp::onInitialize() {
  // TODO: init application (size, title, fps, resources initializer, scene to start, log behaviors)
  setScreenSize( 800, 600 );
  setTitle( "Aladdin" );
  setFps( 60 );

  registerResourceInitializer( new MyResourceInitializer() );
  startWithScene( new IntroScene() );
}

void MyApp::onRelease() {
  // TODO: release my application
}
