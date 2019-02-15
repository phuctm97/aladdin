#include "AgrabahMarketStairsFivePrefab.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(AgrabahMarketStairsFivePrefab, ala::PrefabV2)

void AgrabahMarketStairsFivePrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // constants

  vector<Vec2> position{
    Vec2( 3811.0f - 3811.0f, 124.5f - 124.5f ),
    Vec2( 3780.0f - 3811.0f, 119.5f - 124.5f ),
    Vec2( 3747.0f - 3811.0f, 111.5f - 124.5f ),
    Vec2( 3717.0f - 3811.0f, 102.5f - 124.5f ),
    Vec2( 3695.5f - 3811.0f, 93.5f - 124.5f ),
    Vec2( 3677.0f - 3811.0f, 85.5f - 124.5f )
  };

  vector<Size> size{
    Size( 32.0f, 6.0f ),
    Size( 32.0f, 6.0f ),
    Size( 32.0f, 6.0f ),
    Size( 32.0f, 6.0f ),
    Size( 32.0f, 6.0f ),
    Size( 32.0f, 6.0f ),
  };

  // components
  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  std::vector<Collider*> colliders;
  for ( size_t i = 0; i < position.size(); i++ ) {
    const auto collider = new Collider( object, false, position[i], size[i], 1, 0 );

    colliders.push_back( collider );
  }

  // collider renderers
//  for ( const auto collider : colliders ) new ColliderRenderer( collider );

  // flags
  const auto stairFlags = COLLIDE_ALADDIN_FLAG |
    COLLIDE_ENEMY_FLAG |
    COLLIDE_FREE_OBJECT_FLAG |
    STANDABLE_FLAG |
    STATIC_FLAG;
  for ( const auto collider : colliders ) {
    collider->setFlags( stairFlags );
    collider->ignoreIfHasAnyFlags( STATIC_FLAG );
  }

  // configurations
  object->setTag( GROUND_TAG );
  object->setLayer( "Debug" );
}
