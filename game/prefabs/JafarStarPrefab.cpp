#include "JafarStarPrefab.h"
#include "../Define.h"
#include "../scripts/JafarStarController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(JafarStarPrefab, ala::PrefabV2)

void JafarStarPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // constants
  const auto gameManager = GameManager::get();

  const auto movingSpeed = 3.0f;

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "jafar.png" );

  const auto animator = new Animator( object, "star", "jafar.anm" );

  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto collider = new Collider( object, true, Vec2( 0, -1 ), Size( 17, 8 ) );

  const auto controller = new JafarStarController( object, movingSpeed );

  // helpers
  const auto transform = object->getTransform();

  // collider renderers
  //  new ColliderRenderer( collider );

  // configurations
  object->setLayer( "Foreground" );
  object->setTag( STAR_TAG );
}
