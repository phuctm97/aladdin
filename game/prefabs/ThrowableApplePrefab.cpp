#include "ThrowableApplePrefab.h"
#include "../scripts/CollisionInfoTracker.h"
#include "../Define.h"
#include "../scripts/DirectionController.h"

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
  collider->ignoreTag( CHARCOAL_BURNER_TAG );
  collider->ignoreTag( ALADDIN_TAG );

  const auto stateManager = new StateManager( object, "initial" );

  const auto actionManager = new ActionManager( object );

  const auto direction = new DirectionController( object );

  const auto collision = new CollisionInfoTracker( object );

  // helpers
  const auto transform = object->getTransform();

  // configurations
  object->setLayer( "Sub Character" );
  object->setTag( ALADDIN_TAG );

  // states
  new State( stateManager, "initial",
             [=] {
               animator->setAction( "apple" );
               actionManager->play( new RotateBy( 360 * 15, 1 ) );
             }, NULL, NULL );

  new State( stateManager, "explode",
             [=] {
               animator->setAction( "apple_explode" );
               actionManager->stopAll();
               transform->setRotation( 0 );

               body->setVelocity( Vec2( 0, 0 ) );
               body->setGravityScale( 0 );
             },
             [=]( float dt ) {
               if ( !animator->isPlaying() ) {
                 object->release();
               }
             }, NULL );

  new StateTransition( stateManager, "initial", "explode", [=] {
    return collision->collided();
  } );
}
