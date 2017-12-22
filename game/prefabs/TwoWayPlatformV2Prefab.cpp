#include "TwoWayPlatformV2Prefab.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(TwoWayPlatformV2Prefab, ala::PrefabV2)

void TwoWayPlatformV2Prefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto width = nextFloat( argsStream );
  const auto height = 5.0f;

  // components
  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto collider = new Collider( object, false, Vec2( 0, 0 ), Size( width, height ), 1, 0, "Aladdin" );
  collider->ignoreTag( PLATFORM_TAG );

  // collider renderers
  new ColliderRenderer( collider );

  // flags
  collider->setFlags(
    COLLIDE_ALADDIN_FLAG | STANDABLE_FLAG | COLLIDE_ENEMY_FLAG | COLLIDE_FREE_OBJECT_FLAG | STATIC_FLAG );
  collider->ignoreIfHasAnyFlags( STATIC_FLAG );

  // configurations
  object->setLayer( "Debug" );
}
