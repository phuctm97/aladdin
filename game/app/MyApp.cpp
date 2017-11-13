/*
* Created by phuctm97 on Sep 27th 2017
*/
#include "MyApp.h"
#include "MyResourceInitializer.h"
#include "../scenes/ExperimentalScene.h"

USING_NAMESPACE_ALA;

MyApp::MyApp() : Application() {}

void MyApp::onPreInitialize() {
  // configurations
  setScreenSize( 320, 256 );
  setTitle( "Aladdin" );
  setFps( 60 );
  Logger::setLogLevel( ALA_LOG_INFO );

  // resource initializers
  registerResourceInitializer( new MyResourceInitializer() );
}

void MyApp::onPostInitialize() {
  // starter scene
  startWithScene( new ExperimentalScene() );
}
