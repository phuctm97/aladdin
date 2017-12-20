#include "AgrabahMarketStairsSixPrefab.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(AgrabahMarketStairsSixPrefab, ala::PrefabV2)

void AgrabahMarketStairsSixPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // constants

  vector<Vec2> position{
    Vec2( 4191.5f - 4214.5f, -82.0f + 76.5f ),
    Vec2( 4214.5f - 4214.5f, -76.5f + 76.5f ),
    Vec2( 4256.5f - 4214.5f, -70.5f + 76.5f ),
    Vec2( 4296.5f - 4214.5f, -62.0f + 76.5f ),
    Vec2( 4463.0f - 4214.5f, -52.5f + 76.5f )
  };

  vector<Size> size{
    Size( 21.0f, 4.0f ),
    Size( 43.0f, 5.0f ),
    Size( 43.0f, 5.0f ),
    Size( 43.0f, 5.0f ),
    Size( 296.0f, 5.0f )
  };

  // components
  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  std::vector<Collider*> colliders;
  for ( size_t i = 0; i < position.size(); i++ ) {
    const auto collider = new Collider( object, false, position[i], size[i], 1, 0 );

    colliders.push_back( collider );
  }

  // collider renderers
  for ( const auto collider : colliders ) new ColliderRenderer( collider );

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
