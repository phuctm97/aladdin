#include "RopePrefab.h"

USING_NAMESPACE_ALA;

void RopePrefab::doInstantiate( ala::GameObject* object ) const {
  // Constants
  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );
  const auto transform = object->getTransform();

  // Collider
  const auto collider = new Collider( object, true, Vec2(), Size( 0, 0 ), 1, 0, "Rope" );
  const auto colliderRenderer = new ColliderRenderer( collider );
}
