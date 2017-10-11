#include "StandLeftState.h"
#include "input/Input.h"
#include "GoRightState.h"
#include "GoLeftState.h"
#include "2d/Animator.h"

StandLeftState::StandLeftState(ala::GameObject * gameObject):IState(gameObject)
{

}

ala::IState * StandLeftState::checkTransition()
{
  if(ala::Input::get()->getKeyDown(ALA_KEY_RIGHT_ARROW))
  {
    return new GoRightState(getGameObject());
  }
  if (ala::Input::get()->getKeyDown(ALA_KEY_LEFT_ARROW))
  {
    return new GoLeftState(getGameObject());
  }
  return nullptr;
}

void StandLeftState::onUpdate(const float dt)
{
}

void StandLeftState::onStateEnter()
{
  auto animator = getGameObject()->getComponentT< ala::Animator>();
  animator->setAction("idle1");
}
