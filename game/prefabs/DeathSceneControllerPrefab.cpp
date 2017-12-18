#include "DeathSceneControllerPrefab.h"
#include "../app/MyAppData.h"
#include "../scenes/AutoLoadScene.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(DeathSceneControllerPrefab, ala::PrefabV2)

void DeathSceneControllerPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // constants
  const auto gameManager = GameManager::get();

  const auto myAppData = static_cast<MyAppData*>(gameManager->getResource( "My App Data" ));

  // components
  const auto timer = new Timer( object );

  const auto stateManager = new StateManager( object, "default" );

  // states
  new State( stateManager, "default",
             [=] { timer->start( 4.0f ); },
             [=]( float dt ) {
               if ( timer->isDone() ) {
                 if ( myAppData->getAladdinLives() > 0 ) {
                   switch ( myAppData->getCurrentLevel() ) {
                   case 1:
                     gameManager->replaceScene( new AutoLoadScene( "agrabah_market.scene", true ) );
                     break;
                   case 2:
                     gameManager->replaceScene( new AutoLoadScene( "jafar_quarter.scene", true ) );
                     break;
                   default:
                     gameManager->replaceScene( new AutoLoadScene( "menu.scene", false ) );
                     break;
                   }
                 }
                 else if ( myAppData->getRetryTimes() > 0 ) {
                   myAppData->setRetryTimes( myAppData->getRetryTimes() - 1 );

                   // TODO: replace with RetryScene
                   gameManager->replaceScene( new AutoLoadScene( "menu.scene", false ) );
                 }
                 else {
                   gameManager->replaceScene( new AutoLoadScene( "menu.scene", false ) );
                 }

                 timer->start( 1000.0f );
               }
             }, NULL );
}
