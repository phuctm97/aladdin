#include "ForegroundPrefab.h"

void ForegroundPrefab::doInstantiate( ala::GameObject* object ) {
  // ReSharper disable CppNonReclaimedResourceAcquisition
  const auto spriteRenderer = new ala::SpriteRenderer( object, "foreground.png" );

  object->setLayer( "Foreground" );
  auto transform = object->getTransform();
  auto frameSize = spriteRenderer->getFrameSize();

  transform->setPosition( ala::Vec2( spriteRenderer->getFrameSize().getWidth() / 2,
                                     spriteRenderer->getFrameSize().getHeight() / 2 )
    - ala::Vec2( ala::GameManager::get()->getVisibleWidth() / 2,
                 ala::GameManager::get()->getVisibleHeight() / 2 ) );
}
