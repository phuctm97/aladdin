#include "PendalPrefab.h"
#include "../Define.h"
#include "../scripts/PendalController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(PendalPrefab, ala::PrefabV2)

void PendalPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // constants

  // components
  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_DYNAMIC, 0.f );

  const auto mainCollider = new Collider( object, false, Vec2(), Size( 37.0f, 9.0f ), 1, 0 );

  const auto stateManager = new StateManager( object, "idle" );

  const auto controller = new PendalController( object );

  const auto spriteRenderer = new SpriteRenderer( object, "items.png" );

  const auto animator = new Animator( object, "pendal_idle", "items.anm" );

  const auto timer = new Timer( object );

  const auto flags = COLLIDE_ALADDIN_FLAG | STANDABLE_FLAG;
  mainCollider->setFlags( flags );

  // collider renderers
  new ColliderRenderer( mainCollider );

  // configurations
  object->setLayer( "Foreground" );
  object->setTag( GROUND_TAG );

  // states
  new State( stateManager, "idle",
             [=] {
               animator->setAction( "pendal_idle" );
             }, NULL, NULL );

  new State( stateManager, "drop",
             [=] {
               timer->start( 0.5f );
             }, [=]( float delta ) {
               if ( timer->isDone() ) {
                 animator->setAction( "pendal_broken" );
                 mainCollider->setActive( false );
                 body->setGravityScale( 2.0f );
                 timer->start( 60 );
               }
             }, NULL );

  new State( stateManager, "disappear",
             [=] {
               object->release();
             }, NULL, NULL );
}
