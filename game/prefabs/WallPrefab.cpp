#include "WallPrefab.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(WallPrefab, ala::PrefabV2)

void WallPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto width = nextFloat( argsStream );
  const auto height = nextFloat( argsStream );
  const auto halfWidth = width / 2;

  // components
  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto collider = new Collider( object, false, Vec2( 0, 0 ), Size( width, height ), 1, 0, "Main" );
  collider->setTag( WALL_TAG );
  collider->ignoreTag( WALL_TAG );
  collider->ignoreTag( GROUND_TAG );

  const auto colliderL = new Collider( object, false, Vec2( -halfWidth - 0.5f, 0 ), Size( 1, height ), 1, 0, "L" );
  colliderL->ignoreTag( WALL_TAG );
  colliderL->ignoreTag( GROUND_TAG );

  const auto colliderR = new Collider( object, false, Vec2( halfWidth + 0.5f, 0 ), Size( 1, height ), 1, 0, "R" );
  colliderR->ignoreTag( WALL_TAG );
  colliderR->ignoreTag( GROUND_TAG );

  // collider renderers
  //  new ColliderRenderer( collider );
  //  new ColliderRenderer( colliderL );
  //  new ColliderRenderer( colliderR );

  // flags
  collider->setFlags( COLLIDE_ALADDIN_FLAG | COLLIDE_ENEMY_FLAG | COLLIDE_FREE_OBJECT_FLAG | STATIC_FLAG );
  colliderL->setFlags( COLLIDE_ALADDIN_FLAG | STATIC_FLAG );
  colliderR->setFlags( COLLIDE_ALADDIN_FLAG | STATIC_FLAG );
  collider->ignoreIfHasAnyFlags( STATIC_FLAG );
  colliderL->ignoreIfHasAnyFlags( STATIC_FLAG );
  colliderR->ignoreIfHasAnyFlags( STATIC_FLAG );

  // configurations
  object->setTag( WALL_TAG );
  object->setLayer( "Debug" );
}
