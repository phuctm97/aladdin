#include "StairPrefab.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(StairPrefab, ala::Prefab)

void StairPrefab::doInstantiate( ala::GameObject* object ) const {
  // components
  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto collider = new Collider( object, false, Vec2(), Size( 0, 0 ), 1, 0 );
  collider->setTag( GROUND_TAG );

  // collider renderers
  new ColliderRenderer( collider );

  object->setTag( GROUND_TAG );
  object->setLayer( "Sub Background" );
}
