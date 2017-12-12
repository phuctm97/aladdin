#include "RopePrefab.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

void RopePrefab::doInstantiate( ala::GameObject* object ) const {
  // components
  const auto transform = object->getTransform();

  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto collider = new Collider( object, true, Vec2(), Size( 0, 0 ), 1, 0, "Rope" );
  collider->setTag( ROPE_TAG );

  const auto colliderRenderer = new ColliderRenderer( collider );

  // configurations
  object->setLayer( "Sub Background" );
  object->setTag( ROPE_TAG );
}
