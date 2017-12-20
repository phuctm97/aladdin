#include "HoldableBarPrefab.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(HoldableBarPrefab, ala::PrefabV2)

void HoldableBarPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto height = 3.0f;
  const auto width = nextFloat( argsStream );

  // components
  const auto transform = object->getTransform();

  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto offset = -width / 2;
  const auto collider = new Collider( object, true, Vec2( offset, 0 ), Size( width, height ), 1, 0 );
  collider->setTag( BAR_TAG );
  collider->ignoreTag( BAR_TAG );
  collider->ignoreTag( ENEMY_TAG );
  collider->ignoreTag( APPLE_TAG );
  collider->ignoreTag( SWORD_TAG );

  // collider renderers
  new ColliderRenderer( collider );

  // flags
  collider->setFlags( COLLIDE_ALADDIN_FLAG | STATIC_FLAG );
  collider->ignoreIfHasAnyFlags( STATIC_FLAG );

  // configurations
  object->setLayer( "Debug" );
  object->setTag( BAR_TAG );
}
