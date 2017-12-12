#include "ThrowableApplePrefab.h"
#include "../scripts/CollisionInfoTracker.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

void ThrowableApplePrefab::doInstantiate( ala::GameObject* object ) const {
  // constants
  const auto gameManager = GameManager::get();
  const auto input = Input::get();

  const auto density = 2.5f;

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "aladdin.png" );

  const auto animator = new Animator( object, "apple", "aladdin.anm" );

  const auto body = new Rigidbody( object, PhysicsMaterial( density ), ALA_BODY_TYPE_DYNAMIC, 1.0f );

  const auto collider = new Collider( object, true, Vec2( 0, 0 ), Size( 4, 5 ) );
  collider->setTag( APPLE_TAG );
  collider->ignoreTag( APPLE_TAG );
  collider->ignoreTag( ALADDIN_TAG );

  const auto stateManager = new StateManager( object, "left" );

  const auto collision = new CollisionInfoChecker( object );

  // helpers
  const auto transform = object->getTransform();

  // configurations
  object->setLayer( "Character" );
  object->setTag( ALADDIN_TAG );

  // states
  new State( stateManager, "left",
             [=] {
               animator->setAction( "apple" );
               transform->setScaleX( -ABS(transform->getScale().getX()) );
             }, NULL, NULL );

  new State( stateManager, "right",
             [=] {
               animator->setAction( "apple" );
               transform->setScaleX( ABS(transform->getScale().getX()) );
             }, NULL, NULL );

  new State( stateManager, "explode",
             [=] {
               animator->setAction( "apple_explode" );
               body->setVelocity( Vec2( 0, 0 ) );
               body->setGravityScale( 0 );
             },
             [=]( float dt ) {
               if ( !animator->isPlaying() ) {
                 object->release();
               }
             }, NULL );

  new StateTransition( stateManager, "left", "explode", [=] {
    return collision->collided();
  } );

  new StateTransition( stateManager, "right", "explode", [=] {
    return collision->collided();
  } );
}
