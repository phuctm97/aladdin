#include "JafarPalaceGroundPrefab.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(JafarPalaceGroundPrefab, ala::PrefabV2)

void JafarPalaceGroundPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
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
  //  new ColliderRenderer( collider );

  // flags
  const auto groundFlags = COLLIDE_ALADDIN_FLAG | COLLIDE_ENEMY_FLAG | COLLIDE_FREE_OBJECT_FLAG | STANDABLE_FLAG |
    STATIC_FLAG;
  collider->setFlags( groundFlags );
  collider->ignoreIfHasAnyFlags( STATIC_FLAG );

  // configurations
  object->setTag( GROUND_TAG );
  object->setLayer( "Debug" );
}
