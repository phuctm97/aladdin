#include "BackgroundPrefab.h"

USING_NAMESPACE_ALA;

void BackgroundPrefab::doInstantiate( ala::GameObject* object ) const {
  // constants
  const auto gameManager = GameManager::get();

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "background.png" );
  auto transform = object->getTransform();

  // configurations
  object->setLayer( "Background" );

  const auto frameSize = spriteRenderer->getFrameSize();
  transform->setPosition( Vec2( frameSize.getWidth() / 2, frameSize.getHeight() / 2 )
    - Vec2( gameManager->getVisibleWidth() / 2,
            gameManager->getVisibleHeight() / 2 ) );
}
