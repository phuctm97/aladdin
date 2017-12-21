#include "DeathSceneControllerPrefab.h"
#include "../app/MyAppData.h"
#include "../scenes/AutoLoadScene.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(DeathSceneControllerPrefab, ala::PrefabV2)

void DeathSceneControllerPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // constants
  const auto gameManager = GameManager::get();

  const auto myAppData = static_cast<MyAppData*>(gameManager->getResource( "My App Data" ));

  const auto sceneFadeOutTransitionPrefab = gameManager->getPrefabV2( "Scene Fade Out Transition" );

  // components
  const auto timer = new Timer( object );

  const auto stateManager = new StateManager( object, "default" );

  // states
  new State( stateManager, "default",
             [=] { timer->start( 4.0f ); },
             [=]( float dt ) {
               if ( timer->isDone() ) {
                 if ( myAppData->getAladdinLives() > 0 ) {
                   myAppData->setAladdinLives( myAppData->getAladdinLives() - 1 );

                   if ( myAppData->getCurrentLevel() <= myAppData->getNumberOfLevels() ) {
                     std::stringstream args;
                     args << 0.5 << ' ' << myAppData->getSceneName( myAppData->getCurrentLevel() ) << '\n' << 1;
                     sceneFadeOutTransitionPrefab->instantiateWithArgs( args.str() );
                   }
                   else {
                     sceneFadeOutTransitionPrefab->instantiateWithArgs( "0.5 menu.scene\n0" );
                   }
                 }
                 else if ( myAppData->getRetryTimes() > 0 ) {
                   myAppData->setRetryTimes( myAppData->getRetryTimes() - 1 );

                   sceneFadeOutTransitionPrefab->instantiateWithArgs( "0.5 retry.scene\n0" );
                 }
                 else {
                   sceneFadeOutTransitionPrefab->instantiateWithArgs( "0.5 menu.scene\n0" );
                 }

                 timer->start( 1000.0f );
               }
             }, NULL );
}
