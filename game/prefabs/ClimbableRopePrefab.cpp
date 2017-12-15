#include "ClimbableRopePrefab.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(ClimbableRopePrefab, ala::PrefabV2)

void ClimbableRopePrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto height = nextFloat( argsStream );

  // components
  const auto transform = object->getTransform();

  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto collider = new Collider( object, true, Vec2(), Size( 3, height ) );
  collider->setTag( ROPE_TAG );
  collider->ignoreTag( ROPE_TAG );
  collider->ignoreTag( ENEMY_TAG );
  collider->ignoreTag( APPLE_TAG );

  const auto colliderRenderer = new ColliderRenderer( collider );

  // configurations
  object->setLayer( "Debug" );
  object->setTag( ROPE_TAG );
}
