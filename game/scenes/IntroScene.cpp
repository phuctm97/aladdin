/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "IntroScene.h"
#include "core/GameManager.h"
#include "core/StringMessageArg.h"

IntroScene::IntroScene() {}

void IntroScene::onPreInitialize() {
  ala::GameManager::get()->getPrefab( "Ball" )->instantiate();
  _ballDirectionChangedListener = ala::GameManager::get()->getGlobalMessenger()->subscribe("Ball Direction Changed", [=](ala::IMessageArg* arg)
  {
	  onBallDirectionChanged(arg);
  });
}

void IntroScene::onPreRelease ( )
{
	ala::GameManager::get()->getGlobalMessenger()->unsubscribe("Ball Direction Changed", _ballDirectionChangedListener);
}

void IntroScene::onBallDirectionChanged ( ala::IMessageArg* arg )
{
	// log to output in visual studio ._.
	OutputDebugString(static_cast < ala::StringMessageArg* > ( arg )->getPayload (  ).c_str (  ));
}
