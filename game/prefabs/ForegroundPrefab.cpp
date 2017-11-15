#include "ForegroundPrefab.h"

USING_NAMESPACE_ALA;

void ForegroundPrefab::doInstantiate( ala::GameObject* object ) const {
  // constants
  const auto gameManager = GameManager::get();

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "foreground.png" );
  auto transform = object->getTransform();

  // configurations
  object->setLayer( "Foreground" );

  const auto frameSize = spriteRenderer->getFrameSize();
  transform->setPosition( Vec2( spriteRenderer->getFrameSize().getWidth() / 2,
                                spriteRenderer->getFrameSize().getHeight() / 2 )
    - Vec2( gameManager->getVisibleWidth() / 2,
            gameManager->getVisibleHeight() / 2 ) );
}
