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
  const auto timer = new Timer( object );
  const auto stateManager = new StateManager( object, "apple" );

  const auto controller = new ThrowableAppleController( object, "controller" );
  const auto transform = object->getTransform();

  // configurations
  object->setLayer( "Character" );

  // states
  new State( stateManager, "apple",
             [=] {
               animator->setAction( "apple" );
               controller->resetCollidedWithGround();
				 if(controller->getDirection()=='L')
				 {
					 transform->setScaleX(-ABS(transform->getScale().getX()));
					 body->addImpulse(Vec2(-20000.0f, 1000.0f));
				 }
				 else
				 {
					 transform->setScaleX(ABS(transform->getScale().getX()));
					 body->addImpulse(Vec2(20000.0f, 1000.0f));
				 } 
             }, NULL, NULL );
  new State( stateManager, "apple_explode",
             [=] {
               animator->setAction( "apple_explode" );
               body->setVelocity( Vec2( 0, 0 ) );
               body->setGravityScale( 0 );
             }, [=](float dt) {
				 if (!animator->isPlaying()) {
					 object->release();
				 }
			 }
             ,  NULL);

  new StateTransition( stateManager, "apple", "apple_explode", [=] {
    return controller->isCollidedWithGround();
  } );
}
