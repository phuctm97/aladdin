#include "ThrowableApplePrefab.h"
#include "../scripts/CollisionTracker.h"
#include "../Define.h"
#include "../scripts/DirectionController.h"

USING_NAMESPACE_ALA;

void ThrowableApplePrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto dir = nextChar( argsStream );
  const auto impulseX = nextFloat( argsStream );
  const auto impulseY = nextFloat( argsStream );

  // constants
  const auto gameManager = GameManager::get();
  const auto input = Input::get();

  const auto density = 2.5f;

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "aladdin.png" );
  //audio
  const auto apple_explode_sound = new AudioSource(object, "Apple Splat.wav");

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
  if ( dir == 'L' ) direction->setLeft();
  else if ( dir == 'R' ) direction->setRight();

  const auto collisionTracker = new CollisionTracker( object );

  // helpers
  const auto transform = object->getTransform();

  // configurations
  object->setLayer( "Foreground" );
  object->setTag( ALADDIN_TAG );

  // states
  new State( stateManager, "initial",
             [=] {
               // animation effect
               {
                 animator->setAction( "apple" );
                 actionManager->play( new RotateBy( 360 * 15, 1 ) );

                 collisionTracker->reset();
               }

               // move
               {
                 body->addImpulse( Vec2( impulseX, impulseY ) );
               }
             }, NULL, NULL );

  new State( stateManager, "explode",
             [=] {
               // animation effect
               {
                 animator->setAction( "apple_explode" );
				 apple_explode_sound->play();
                 actionManager->stopAll();
                 transform->setRotation( 0 );
               }

               // move
               {
                 body->setVelocity( Vec2( 0, 0 ) );
                 body->setGravityScale( 0 );
               }
             },
             [=]( float dt ) {
               // release
               {
                 if ( !animator->isPlaying() ) {
                   object->release();
                 }
               }
             }, NULL );

  new StateTransition( stateManager, "initial", "explode", [=] {
    return collisionTracker->collided();
  } );
}
