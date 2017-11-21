/*
* Created by phuctm97 on Sep 27th 2017
*/
#include "MyApp.h"
#include "MyResourceInitializer.h"
#include "../scenes/ExperimentalScene.h"
#include "../scenes/MenuScene.h"

USING_NAMESPACE_ALA;

MyApp::MyApp() : Application() {}

void MyApp::onPreInitialize() {
  // configurations
  setResolutionSize( 320, 256 );
  setScreenSize( 320 * 3, 256 * 3 );
  setTitle( "Aladdin" );
  setFps( 60 );
  Logger::setLogLevel( ALA_LOG_INFO );

  // resource initializers
  registerResourceInitializer( new MyResourceInitializer() );
}

void MyApp::onPostInitialize() {
  // starter scene
  startWithScene( new MenuScene() );
}
