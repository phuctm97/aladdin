#include "PendalV2Prefab.h"
#include "../Define.h"
#include "../scripts/CollisionTracker.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(PendalV2Prefab, ala::PrefabV2)

void PendalV2Prefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto resetX = nextFloat( argsStream );
  const auto resetY = nextFloat( argsStream );

  // constants

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "items.png" );

  const auto animator = new Animator( object, "pendal_idle", "items.anm" );

  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_DYNAMIC, 0.0f );

  const auto collider = new Collider( object, false, Vec2(), Size( 37.0f, 9.0f ), 1, 0 );

  const auto collisionTracker = new CollisionTracker( object );

  const auto stateManager = new StateManager( object, "default" );

  const auto transform = object->getTransform();

  const auto timer = new Timer( object );

  // states
  new State( stateManager, "default",
             [=] {
               transform->setPosition( resetX, resetY );
             }, NULL, NULL );

  new State( stateManager, "fall",
             [=] {
               timer->start( 0.3f );
             },
             [=]( float dt ) {
               if ( body->getGravityScale() == 0 && timer->isDone() ) {
                 body->setGravityScale( 1.0f );
                 timer->start( 0.7f );
               }
               else if ( body->getGravityScale() > 0 ) {
                 if ( timer->isDone() ) {
                   animator->setAction( "pendal_broken" );
                   collider->setFlags( EMPTY_FLAG );
                   timer->start( 60.0f );
                 }

                 if ( collisionTracker->collidedWithColliderFlag( STATIC_FLAG ) ) {
                   std::stringstream stringBuilder;
                   stringBuilder << resetX << ' ' << resetY;
                   this->instantiateWithArgs( stringBuilder.str() );

                   object->release();
                 }
               }
             }, NULL );

  new StateTransition( stateManager, "default", "fall", [=] {
    return collisionTracker->collidedWithObjectTag( ALADDIN_TAG );
  } );

  // flags
  const auto flags = COLLIDE_ALADDIN_FLAG | COLLIDE_FREE_OBJECT_FLAG | STANDABLE_FLAG;
  collider->setFlags( flags );

  // configurations
  object->setLayer( "Second Background" );
}
