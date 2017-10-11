#include "GoLeftState.h"
#include "GoRightState.h"
#include "StandLeftState.h"

GoLeftState::GoLeftState ( ala::GameObject* gameObject)
  :IState ( gameObject )
{
}

ala::IState* GoLeftState::checkTransition ( )
{

  if(ala::Input::get()->getKeyDown(ALA_KEY_RIGHT_ARROW))
  {
    return new GoRightState(getGameObject());
  }
  if (ala::Input::get()->getKeyUp(ALA_KEY_LEFT_ARROW))
  {
    return new StandLeftState(getGameObject());
  }
  return NULL;
}

void GoLeftState::onStateEnter()
{
  auto animator = getGameObject()->getComponentT< ala::Animator>();
  animator->setAction("run");
  getGameObject()->getTransform()->setScaleX(-1);
}


void GoLeftState::onUpdate ( const float dt )
{
  auto position = getGameObject()->getTransform()->getPosition (  );
  position.setX(position.getX() - 100 * dt);
  getGameObject()->getTransform()->setPosition(position);
}
