#include "GoUpState.h"
#include "GoRightState.h"
#include "core/GameManager.h"
#include "2d/Animator.h"
#include "2d/SpriteRenderer.h"

GoUpState::GoUpState(ala::GameObject* gameObject)
  :IState(gameObject)
{
}

ala::IState* GoUpState::checkTransition()
{
  auto transform = getGameObject()->getTransform();

  auto spriteRenderer = getGameObject()->getComponentT<ala::SpriteRenderer>();

  if (transform->getPositionY() + spriteRenderer->getFrameSize (  ).getHeight (  )/2 >= ala::GameManager::get()->getScreenHeight() / 2)
  {
    auto animator = getGameObject()->getComponentT< ala::Animator>();
    animator->setAction("Right");
    return new GoRightState(getGameObject());
  }
  else
  {
    return NULL;
  }
}

void GoUpState::onUpdate(const float dt)
{
  auto position = getGameObject()->getTransform()->getPosition();
  position.setY(position.getY() + 100*dt);
  getGameObject()->getTransform()->setPosition(position);
}
