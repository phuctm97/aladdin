#include "ThrowableApplePrefab.h"
#include "../scripts/ThrowableAppleController.h"

USING_NAMESPACE_ALA;

void ThrowableApplePrefab::doInstantiate( ala::GameObject* object ) const {
  // constants
  const auto gameManager = GameManager::get();
  const auto input = Input::get();

  const auto density = 3.0f;
  const auto throwVelocity = 150.0f;

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "aladdin.png" );
  const auto animator = new Animator( object, "apple", "aladdin.anm" );

  const auto body = new Rigidbody( object, PhysicsMaterial( density ), ALA_BODY_TYPE_DYNAMIC, 1.0f );
  const auto collider = new Collider( object, true, Vec2( 0, 0 ), Size( 4, 5 ) );
  const auto stateManager = new StateManager( object, "apple_left" );

  const auto controller = new ThrowableAppleController( object, "controller" );
  const auto transform = object->getTransform();

  // configurations
  object->setLayer( "Character" );

  // states

  new State( stateManager, "apple_explode",
             [=] {
               animator->setAction( "apple_explode" );
               body->setVelocity( Vec2( 0, 0 ) );
               body->setGravityScale( 0 );
             }, [=]( float dt ) {
               if ( !animator->isPlaying() ) {
                 object->release();
               }
             }
             , NULL );

  new State( stateManager, "apple_left",
             [=] {
               animator->setAction( "apple" );
               controller->resetCollidedWithGround();
               transform->setScaleX( -ABS(transform->getScale().getX()) );
             },NULL,NULL );

  new State( stateManager, "apple_right",
             [=] {
               animator->setAction( "apple" );
               controller->resetCollidedWithGround();
               transform->setScaleX( ABS(transform->getScale().getX()) );
             }, NULL, NULL );


  new StateTransition( stateManager, "apple_left", "apple_explode", [=] {
    return controller->isCollidedWithGround();
  } );

  new StateTransition( stateManager, "apple_right", "apple_explode", [=] {
    return controller->isCollidedWithGround();
  } );

}
