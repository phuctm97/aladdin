#include "2d/Animator.h"
#include "2d/SpriteRenderer.h"
#include "GoRightState.h"
#include "input/Input.h"
#include "GoLeftState.h"
#include "StandRightState.h"

GoRightState::GoRightState(ala::GameObject * gameObject)
	:IState(gameObject)
{
}

ala::IState * GoRightState::checkTransition()
{

  if(ala::Input::get()->getKeyDown(ALA_KEY_LEFT_ARROW))
  {
    return new GoLeftState(getGameObject());
  }
  if(ala::Input::get()->getKeyUp(ALA_KEY_RIGHT_ARROW))
  {
    return new StandRightState(getGameObject());
  }
  return NULL;
}

void GoRightState::onStateEnter()
{
  auto animator = getGameObject()->getComponentT< ala::Animator>();
  animator->setAction("run");
  getGameObject()->getTransform()->setScaleX(1);
}


void GoRightState::onUpdate(const float dt)
{
  auto position = getGameObject()->getTransform()->getPosition();
  position.setX(position.getX() + 100 * dt);
  getGameObject()->getTransform()->setPosition(position);
}
