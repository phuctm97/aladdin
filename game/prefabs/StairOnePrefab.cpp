#include "StairOnePrefab.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(StairOnePrefab, ala::Prefab)

void StairOnePrefab::doInstantiate( ala::GameObject* object ) const {
  // components
  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const std::vector<std::pair<Vec2, Size>> stairs = {
    std::make_pair( Vec2( 1015.5f, -46.0f ), Size( 45.0f, 8.0f ) ),
    std::make_pair( Vec2( 1055.5f, -36.0f ), Size( 42.0f, 7.0f ) ),
    std::make_pair( Vec2( 1096.0f, -28.5f ), Size( 42.0f, 6.0f ) ),
    std::make_pair( Vec2( 1136.0f, -21.5f ), Size( 45.0f, 7.0f ) ),
    std::make_pair( Vec2( 1176.0f, -12.5f ), Size( 43.0f, 6.0f ) ),
    std::make_pair( Vec2( 1215.0f, -5.5f ), Size( 43.0f, 7.0f ) ),
    std::make_pair( Vec2( 1286.0f, 2.5f ), Size( 106.0f, 7.0f ) )
  };

  for ( const auto& pair : stairs ) {
    const auto collider = new Collider( object, false, pair.first, pair.second, 1, 0 );
    collider->setTag( GROUND_TAG );

    new ColliderRenderer( collider );
  }

  object->setTag( GROUND_TAG );
  object->setLayer( "Sub Background" );
}