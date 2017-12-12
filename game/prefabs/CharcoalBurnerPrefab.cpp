#include "CharcoalBurnerPrefab.h"
#include "../scripts/CharcoalBurnerController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

void CharcoalBurnerPrefab::doInstantiate( ala::GameObject* object ) const {
  // constants
  const auto gameManager = GameManager::get();
  const auto firePrefab = gameManager->getPrefab( "Fire" );

  // components
  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC, 0 );

  const auto collider = new Collider( object, true, Vec2(), Size( 90, 4 ) );
  collider->setTag( CHARCOAL_BURNER_TAG );
  collider->ignoreTag( CHARCOAL_BURNER_TAG );
  collider->ignoreTag( GROUND_TAG );

  const auto stateManager = new StateManager( object, "nothing" );

  const auto controller = new CharcoalBurnerController( object );

  // helpers
  const auto timer = new Timer( object );

  const auto transform = object->getTransform();

  // configurations
  object->setTag( CHARCOAL_BURNER_TAG );
  object->setLayer( "Background" );

  // states
  new State( stateManager, "nothing", NULL, NULL, NULL );

  new State( stateManager, "fire",
             [=] {
               timer->start( 0 );
             },
             [=]( float dt ) {
               if ( timer->isDone() ) {
                 const auto firePosition = Vec2( controller->getFiringX(), transform->getPositionY() + 21 );
                 firePrefab->instantiate( firePosition );
                 timer->start( 0.25f );
               }
             },
             NULL );

  new StateTransition( stateManager, "nothing", "fire", [=] {
    return controller->isTouchingAladdin();
  } );

  new StateTransition( stateManager, "fire", "nothing", [=] {
    return !controller->isTouchingAladdin();
  } );
}
