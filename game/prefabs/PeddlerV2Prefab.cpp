#include "PeddlerV2Prefab.h"
#include "../Define.h"
#include "../scripts/PeddlerController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(PeddlerV2Prefab, ala::PrefabV2)

void PeddlerV2Prefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // constants
  const auto gameManager = ala::GameManager::get();

  // components
  const auto spriteRenderer = new ala::SpriteRenderer( object, "peddler.png" );

  const auto animator = new ala::Animator( object, "idle_1", "peddler.anm" );

  const auto body = new ala::Rigidbody( object, ala::PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto collider10 = new ala::Collider( object, true, ala::Vec2( 0, 0 ), ala::Size( 10, 20 ), 1, 0, "10" );

  const auto collider5 = new ala::Collider( object, true, ala::Vec2( -50, 0 ), ala::Size( 10, 20 ), 1, 0, "5" );

  const auto controller = new PeddlerController( object );

  const auto child = new ala::GameObject( object );

  const auto childSpriteRenderer = new ala::SpriteRenderer( child, "peddler.png" );
  childSpriteRenderer->setVisible( false );

  const auto childAnimator = new ala::Animator( child, "idle_1", "peddler.anm" );

  const auto childTransform = child->getTransform();
  childTransform->setPositionX( 50 );

  // collider renderers
  //  new ala::ColliderRenderer( collider5 );
  //  new ala::ColliderRenderer( collider10 );

  // flags
  collider10->setFlags( COLLIDE_ALADDIN_FLAG | STATIC_FLAG );
  collider10->ignoreIfHasAnyFlags( STATIC_FLAG );

  collider5->setFlags( COLLIDE_ALADDIN_FLAG | STATIC_FLAG );
  collider5->ignoreIfHasAnyFlags( STATIC_FLAG );

  // configurations
  object->setLayer( "Mass Character" );
}
