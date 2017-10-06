#include "GoDownState.h"
#include "GoLeftState.h"
#include "core/GameManager.h"
#include "2d/Animator.h"
#include "2d/SpriteRenderer.h"

GoDownState::GoDownState ( ala::GameObject* gameObject )
  :IState ( gameObject )
{
}

ala::IState* GoDownState::checkTransition ( )
{
  auto transform = getGameObject()->getTransform();

  auto spriteRenderer = getGameObject()->getComponentT<ala::SpriteRenderer>();

  if (transform->getPositionY() - spriteRenderer->getFrameSize (  ).getHeight (  )/2 <= -ala::GameManager::get()->getScreenHeight () / 2)
  {
    auto animator = getGameObject()->getComponentT< ala::Animator>();
    animator->setAction("Left");
    return new GoLeftState(getGameObject (  ));
  }
  else
  {
    return NULL;
  }
}

void GoDownState::onUpdate ( const float dt )
{
  auto position = getGameObject()->getTransform()->getPosition();
  position.setY(position.getY() - 10);
  getGameObject()->getTransform()->setPosition(position);
}
