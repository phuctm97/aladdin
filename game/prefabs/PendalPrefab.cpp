#include "PendalPrefab.h"
#include "../Define.h"
#include "../scripts/PendalController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(PendalPrefab, ala::PrefabV2)

void PendalPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // constants

  // components
  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_DYNAMIC, 0.f );

  const auto collider = new Collider( object, false, Vec2(), Size( 37.0f, 9.0f ), 1, 0 );

  const auto stateManager = new StateManager( object, "idle" );

  const auto controller = new PendalController( object );

  // collider renderers
  new ColliderRenderer( collider );

  // configurations
  object->setLayer( "Foreground" );
  object->setTag( GROUND_TAG );

  // states

  new State( stateManager, "idle",
             NULL, NULL,
             [=] { } );

  new State( stateManager, "drop",
             [=] {
               body->setGravityScale( 1.0f );
             }, NULL, NULL );

  new State( stateManager, "disappear",
             [=] {
               object->release();
             }, NULL, NULL );
}
