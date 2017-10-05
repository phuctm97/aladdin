#include "GoUpState.h"
#include "GoRightState.h"
#include "core/GameManager.h"

GoUpState::GoUpState(ala::GameObject* gameObject)
  :IState(gameObject)
{
}

ala::IState* GoUpState::checkTransition()
{
  auto transform = getGameObject()->getTransform();

  if (transform->getPositionY() >= ala::GameManager::get()->getScreenHeight() / 2)
  {
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
  position.setY(position.getY() + 10);
  getGameObject()->getTransform()->setPosition(position);
}
