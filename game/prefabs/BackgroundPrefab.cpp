#include "BackgroundPrefab.h"

void BackgroundPrefab::doInstantiate( ala::GameObject* object ) {
  // ReSharper disable CppNonReclaimedResourceAcquisition
  const auto spriteRenderer = new ala::SpriteRenderer( object, "background.png" );

  object->setLayer( "Background" );
  auto transform = object->getTransform();

  transform->setPosition( ala::Vec2( spriteRenderer->getFrameSize().getWidth() / 2,
                                     spriteRenderer->getFrameSize().getHeight() / 2 )
    - ala::Vec2( ala::GameManager::get()->getScreenWidth() / 2,
                 ala::GameManager::get()->getScreenHeight() / 2 ) );
}
