#include "GoRightState.h"
#include "core/GameManager.h"
#include "GoDownState.h"

GoRightState::GoRightState ( ala::GameObject* gameObject )
  :IState ( gameObject )
{
}

ala::IState* GoRightState::checkTransition ( )
{
  auto transform = getGameObject()->getTransform();

  if (transform->getPositionX() >= ala::GameManager::get()->getScreenWidth() / 2)
  {
    return new GoDownState(getGameObject());
  }
  else
  {
    return NULL;
  }
}

void GoRightState::onUpdate ( const float dt )
{
  auto position = getGameObject()->getTransform()->getPosition();
  position.setX(position.getX() + 10);
  getGameObject()->getTransform()->setPosition(position);
}
