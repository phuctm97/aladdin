#include "BackgroundPrefab.h"

USING_NAMESPACE_ALA;

void BackgroundPrefab::doInstantiate( ala::GameObject* object ) const {
  const auto gameManager = GameManager::get();

  // ReSharper disable CppNonReclaimedResourceAcquisition
  const auto spriteRenderer = new SpriteRenderer( object, "background.png" );

  object->setLayer( "Background" );
  auto transform = object->getTransform();

  transform->setPosition( Vec2( spriteRenderer->getFrameSize().getWidth() / 2,
                                spriteRenderer->getFrameSize().getHeight() / 2 )
    - Vec2( gameManager->getVisibleWidth() / 2,
            gameManager->getVisibleHeight() / 2 ) );
}
