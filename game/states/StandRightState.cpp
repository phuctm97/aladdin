#include "StandLeftState.h"
#include "GoRightState.h"
#include "GoLeftState.h"
#include "StandRightState.h"
#include "DownRightState.h"

StandRightState::StandRightState(ala::GameObject * gameObject) :IState(gameObject)
{

}

ala::IState * StandRightState::checkTransition()
{
  if (ala::Input::get()->getKeyDown(ALA_KEY_RIGHT_ARROW))
  {
    return new GoRightState(getGameObject());
  }
  if (ala::Input::get()->getKeyDown(ALA_KEY_LEFT_ARROW))
  {
    return new GoLeftState(getGameObject());
  }
  if(ala::Input::get()->getKeyDown(ALA_KEY_DOWN_ARROW))
  {
    return new DownRightState(getGameObject());
  }
  return nullptr;
}

void StandRightState::onUpdate(const float dt)
{
}

void StandRightState::onStateEnter()
{
  auto animator = getGameObject()->getComponentT< ala::Animator>();
  animator->setAction("idle1");
}
