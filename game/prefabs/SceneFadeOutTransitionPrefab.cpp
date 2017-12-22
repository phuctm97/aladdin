#include "SceneFadeOutTransitionPrefab.h"
#include "../scripts/CameraFollower.h"
#include "../scripts/FadeInEffect.h"
#include "../scenes/AutoLoadScene.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(SceneFadeOutTransitionPrefab, ala::PrefabV2)

void SceneFadeOutTransitionPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto duration = nextFloat( argsStream );
  const std::string scene = nextLine( argsStream );
  const auto useCameraController = nextBool( argsStream );

  // constants
  const auto gameManager = GameManager::get();

  const auto physicsManager = PhysicsManager::get();

  const auto camera = gameManager->getRunningScene()->getMainCamera();

  const auto visibleSize = Size( gameManager->getVisibleWidth(), gameManager->getVisibleHeight() );

  // components
  const auto rectRenderer = new RectRenderer( object, Vec2( 0, 0 ), visibleSize, Color( 0, 0, 0 ) );
  rectRenderer->setOpacity( 0 );

  const auto cameraFollower = new CameraFollower( object );

  const auto fadeIn = new FadeInEffect( object );

  const auto stateManager = new StateManager( object, "default" );


  // states
  new State( stateManager, "default",
             [=] {
               // deactive objects in scene
               for ( const auto o : gameManager->getAllObjects() ) {
                 if ( o != camera && o != object ) {
                   o->setActive( false );
                 }
               }
               physicsManager->setActice( false );

               rectRenderer->setOpacity( 0 );
               fadeIn->start( duration );
             },
             [=]( float dt ) {
               if ( !fadeIn->isRunning() ) {
                 physicsManager->setActice( true );

                 gameManager->replaceScene( new AutoLoadScene( scene, useCameraController ) );
               }
             },
             NULL );

  // configurations
  object->setLayer( "Overlay" );
  rectRenderer->setZOrder( 90 );
}
