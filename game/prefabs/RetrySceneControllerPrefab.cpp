#include "RetrySceneControllerPrefab.h"
#include "../app/MyAppData.h"
#include "../scripts/DirectionController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(RetrySceneControllerPrefab, ala::PrefabV2)

void RetrySceneControllerPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // constants
  const auto gameManager = GameManager::get();

  const auto myAppData = static_cast<MyAppData*>(gameManager->getResource( "My App Data" ));

  const auto sceneFadeOutTransitionPrefab = gameManager->getPrefabV2( "Scene Fade Out Transition" );

  // components
  const auto timer = new Timer( object );

  const auto stateManager = new StateManager( object, "default" );

  // states
  new State( stateManager, "default",
             [=] { timer->start( 5.0f ); },
             NULL, NULL );

  new State( stateManager, "left",
             [=] {
               const auto aladdinAndAbu = gameManager->getObjectByName( "Aladdin And Abu" );
               aladdinAndAbu->getComponentT<Rigidbody>()->setVelocity( Vec2( 70, 0 ) );
               aladdinAndAbu->getComponentT<DirectionController>()->setLeft();
               aladdinAndAbu->getTransform()->setPositionX( 17 );
               timer->start( 2.9f );
             },
             [=]( float dt ) {
               if ( timer->isDone() ) {
                 sceneFadeOutTransitionPrefab->instantiateWithArgs( "0.5 menu.scene\n0" );
               }
             },
             NULL );

  new State( stateManager, "right",
             [=] {
               const auto aladdinAndAbu = gameManager->getObjectByName( "Aladdin And Abu" );
               aladdinAndAbu->getComponentT<Rigidbody>()->setVelocity( Vec2( 70, 0 ) );
               aladdinAndAbu->getComponentT<DirectionController>()->setRight();
               timer->start( 2.9f );
             },
             [=]( float dt ) {
               if ( timer->isDone() ) {
                 std::stringstream args;
                 args << 0.5 << ' ' << myAppData->getSceneName( myAppData->getCurrentLevel() ) << '\n' << 1;
                 sceneFadeOutTransitionPrefab->instantiateWithArgs( args.str() );
               }
             },
             NULL );

  new StateTransition( stateManager, "default", "left", [=] {
    return Input::get()->getKeyDown( ALA_KEY_LEFT_ARROW );
  } );

  new StateTransition( stateManager, "default", "right", [=] {
    return Input::get()->getKeyDown( ALA_KEY_RIGHT_ARROW ) || timer->isDone();
  } );
}
