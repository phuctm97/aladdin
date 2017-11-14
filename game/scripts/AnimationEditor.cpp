#include "AnimationEditor.h"

USING_NAMESPACE_ALA;

AnimationEditor::AnimationEditor( ala::GameObject* gameObject, const std::string& entryAction,
                                  ala::Animation* animation, const std::string& name )
  : GameObjectComponent( gameObject, name ) {
  _animation = static_cast<Animation*>(GameManager::get()->getResource(animationResourceName));
  _currentAction = _animation->getAction(entryAction);

  _frameIterator = _currentAction->getFrames().begin();

  auto spriteRenderer = getGameObject()->getComponentT<SpriteRenderer>();
  if (spriteRenderer != NULL)
  {
    spriteRenderer->setSprite(static_cast < Sprite* > (GameManager::get()->getResource(_currentAction->getTextureName())));
    spriteRenderer->setSourceRect(*_frameIterator);
  }
}

AnimationEditor::AnimationEditor( ala::GameObject* gameObject, const std::string& entryAction,
                                  const std::string& animationResourceName, const std::string& name )
  : GameObjectComponent( gameObject, name ) {}
