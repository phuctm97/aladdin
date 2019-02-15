#include "FallingHalfOfApplePrefab.h"
#include "../scripts/DirectionController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(FallingHalfOfApplePrefab, ala::PrefabV2)

void FallingHalfOfApplePrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto dir = nextChar( argsStream );
  const auto impulseX = nextFloat( argsStream );
  const auto impulseY = nextFloat( argsStream );

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "items.png" );

  const auto animator = new Animator( object, "half_apple", "items.anm" );

  const auto body = new Rigidbody( object, PhysicsMaterial( 1, 0 ), ALA_BODY_TYPE_DYNAMIC, 1 );

  const auto collider = new Collider( object, true, Vec2(), Size( 5, 5 ) );

  const auto stateManager = new StateManager( object, "default" );

  const auto direction = new DirectionController( object );
  if ( dir == 'L' ) direction->setLeft();
  else if ( dir == 'R' ) direction->setRight();

  const auto transform = object->getTransform();

  // states
  new State( stateManager, "default",
             [=] {
               // move
               {
                 body->addImpulse( Vec2( impulseX, impulseY ) );
               }
             },
             [=]( float dt ) {
               // release
               if ( transform->getPositionY() < -200 ) {
                 object->release();
               }
             }, NULL );


  // configurations
  object->setLayer( "Second Foreground" );
}
