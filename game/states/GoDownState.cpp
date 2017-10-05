#include "GoDownState.h"
#include "GoLeftState.h"
#include "core/GameManager.h"

GoDownState::GoDownState ( ala::GameObject* gameObject )
  :IState ( gameObject )
{
}

ala::IState* GoDownState::checkTransition ( )
{
  auto transform = getGameObject()->getTransform();

  if (transform->getPositionY() <= -ala::GameManager::get()->getScreenHeight () / 2)
  {
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
