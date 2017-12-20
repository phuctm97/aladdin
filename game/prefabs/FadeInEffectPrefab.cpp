#include "FadeInEffectPrefab.h"
#include "../scripts/CameraFollower.h"
#include "../scripts/FadeOutEffect.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(FadeInEffectPrefab, ala::PrefabV2)

void FadeInEffectPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto duration = nextFloat( argsStream );

  // constants
  const auto gameManager = GameManager::get();

  const auto visibleSize = Size( gameManager->getVisibleWidth(), gameManager->getVisibleHeight() );

  // components
  const auto rectRenderer = new RectRenderer( object, Vec2( 0, 0 ), visibleSize, Color( 0, 0, 0 ) );

  const auto cameraFollower = new CameraFollower( object );

  const auto fadeOut = new FadeOutEffect( object );

  const auto stateManager = new StateManager( object, "default" );

  // states
  new State( stateManager, "default",
             [=] {
               fadeOut->start( duration );
             },
             [=]( float dt ) {
               if ( !fadeOut->isRunning() ) {
                 object->release();
               }
             },
             NULL );


  // configurations
  object->setLayer( "UI" );
  rectRenderer->setZOrder( 90 );
}
