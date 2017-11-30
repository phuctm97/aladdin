#include "GroundPrefab.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

void GroundPrefab::doInstantiate( ala::GameObject* object ) const {
  // constants
  const auto gameManager = GameManager::get();
  const auto halfVisibleSize = Size( gameManager->getVisibleWidth() / 2, gameManager->getVisibleHeight() / 2 );
  const auto groundSize = Size( 500, 63 );

  // components
  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto collider1 = new Collider( object, false, Vec2( 0, 0 ), groundSize, 1, 0, "firstGround" );
  collider1->setTag(GROUND_TAG);
  
  const auto colliderRenderer1 = new ColliderRenderer( collider1 );

  const auto collider2 = new Collider( object, false, Vec2( groundSize.getWidth(), -20 ),
                                       groundSize, 1, 0, "secondGround" );
  collider2->setTag(GROUND_TAG);

  const auto colliderRenderer2 = new ColliderRenderer( collider2 );

  const auto transform = object->getTransform();

  // configurations
  transform->setPosition( Vec2( - halfVisibleSize.getWidth() + groundSize.getWidth() / 2,
                                - halfVisibleSize.getHeight() + groundSize.getHeight() / 2 ) );
}
