#include "DeathScene.h"
#include "../app/MyAppData.h"
#include "MenuScene.h"
#include "AgrabahMarketScene.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(DeathScene, ala::Scene)

void DeathScene::onPreInitialize() {
  // constants
  const auto gameManager = GameManager::get();
  const auto myAppData = static_cast<MyAppData*>(gameManager->getResource( "My App Data" ));

  // objects
  const auto node = gameManager->getPrefabV2( "Sprite" )->instantiateWithArgs( "aladdin.png 1 aladdin.anm die" )
                               ->getTransform()
                               ->setPosition( -32, 0 )
                               ->getGameObject();

  gameManager->getPrefabV2( "Sprite" )->instantiateWithArgs( "abu.png 1 abu.anm fan" )
             ->getTransform()
             ->setPosition( 50, -40 );

  // navigation controller
  const auto timer = new Timer( node );
  const auto stateManager = new StateManager( node, "cutscene" );
  const auto animator = node->getComponentT<Animator>();

  new State( stateManager, "cutscene", NULL, NULL, NULL );

  new State( stateManager, "delay",
             [=] { timer->start( 1.0f ); },
             [=]( float dt ) {
               if ( timer->isDone() ) {
                 if ( myAppData->getAladdinLives() > 0 ) {
                   switch ( myAppData->getCurrentLevel() ) {
                   case 1:
                     gameManager->replaceScene( new AgrabahMarketScene() );
                     break;
                   case 2:
                     // TODO: replace with JafarQuarterScene
                     gameManager->exit();
                     break;
                   default:
                     gameManager->exit();
                     break;
                   }
                 }
                 else if ( myAppData->getRetryTimes() > 0 ) {
                   myAppData->setRetryTimes( myAppData->getRetryTimes() - 1 );

                   // TODO: replace with RetryScene
                   gameManager->replaceScene( new MenuScene() );
                 }
                 else {
                   gameManager->replaceScene( new MenuScene() );
                 }

                 timer->start( 10 );
               }
             }, NULL );

  new StateTransition( stateManager, "cutscene", "delay", [=] {
    return !animator->isPlaying();
  } );
}
