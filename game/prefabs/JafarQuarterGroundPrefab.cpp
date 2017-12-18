#include "JafarQuarterGroundPrefab.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(JafarQuarterGroundPrefab, ala::PrefabV2)

void JafarQuarterGroundPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // constants
  const auto gameManager = GameManager::get();
  const auto visibleWidth = gameManager->getVisibleWidth();
  const auto visibleHeight = gameManager->getVisibleHeight();
  const auto halfVisibleWidth = visibleWidth / 2;
  const auto halfVisibleHeight = visibleHeight / 2;

  // components
  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto collider = new Collider( object, false, Vec2( 0, -72 ), Size( 634, 50 ) );

  // collider renderers
  new ColliderRenderer( collider );

  // configurations
  object->setTag( GROUND_TAG );
  object->setLayer( "Debug" );
}
