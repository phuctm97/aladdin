#include "ClimbableRopePrefab.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(ClimbableRopePrefab, ala::PrefabV2)

void ClimbableRopePrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto height = nextFloat( argsStream );
  const auto width = 4.0f;
  const auto topSize = 5.0f;
  const auto topPadding = 35.0f;
  const auto mainSize = height - topSize - topPadding;

  // components
  const auto transform = object->getTransform();

  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto mainOffset = -(topSize + topPadding + mainSize / 2);
  const auto collider = new Collider( object, true, Vec2( 0, mainOffset ), Size( width, mainSize ), 1, 0, "M" );
  collider->setTag( ROPE_TAG );
  collider->ignoreTag( ROPE_TAG );
  collider->ignoreTag( ENEMY_TAG );
  collider->ignoreTag( APPLE_TAG );
  collider->ignoreTag( SWORD_TAG );

  const auto topOffset = -(topSize / 2);
  const auto colliderT = new Collider( object, true, Vec2( 0, topOffset ), Size( width, topSize ), 1, 0, "T" );
  colliderT->ignoreTag( ROPE_TAG );
  colliderT->ignoreTag( ENEMY_TAG );
  colliderT->ignoreTag( APPLE_TAG );
  colliderT->ignoreTag( SWORD_TAG );

  // collider renderers
  new ColliderRenderer( collider );
  new ColliderRenderer( colliderT );

  // configurations
  object->setLayer( "Debug" );
  object->setTag( ROPE_TAG );
}
