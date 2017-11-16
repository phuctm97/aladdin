#include "GroundPrefab.h"

USING_NAMESPACE_ALA;

void GroundPrefab::doInstantiate( ala::GameObject* object ) const {
  // constants
  const auto gameManager = GameManager::get();
  const auto halfVisibleSize = Size( gameManager->getVisibleWidth() / 2, gameManager->getVisibleHeight() / 2 );
  const auto groundSize = Size( 500, 63 );

  // components
  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );
  const auto collider = new Collider( object, false, false, groundSize );
  const auto colliderRenderer = new ColliderRenderer( collider );
  const auto transform = object->getTransform();

  // configurations
  transform->setPosition( Vec2( - halfVisibleSize.getWidth() + groundSize.getWidth() / 2,
                                - halfVisibleSize.getHeight() + groundSize.getHeight() / 2 ) );
}
