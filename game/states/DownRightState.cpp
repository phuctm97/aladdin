#include "GoLeftState.h"
#include "GoRightState.h"
#include "DownRightState.h"
#include "StandRightState.h"

DownRightState::DownRightState(ala::GameObject* gameObject)
  :IState(gameObject)
{
}

ala::IState* DownRightState::checkTransition()
{
  if (ala::Input::get()->getKeyUp(ALA_KEY_DOWN_ARROW))
  {
    return new StandRightState(getGameObject());
  }
  return NULL;
}

void DownRightState::onStateEnter()
{
  auto animator = getGameObject()->getComponentT< ala::Animator>();
  animator->setAction("sit");
}


void DownRightState::onUpdate(const float dt)
{
}
