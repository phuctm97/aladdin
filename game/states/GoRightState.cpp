#include "GoRightState.h"
#include "core/GameManager.h"
#include "GoDownState.h"
#include "2d/Animator.h"
#include "2d/SpriteRenderer.h"

GoRightState::GoRightState ( ala::GameObject* gameObject )
  :IState ( gameObject )
{
}

ala::IState* GoRightState::checkTransition ( )
{
  auto transform = getGameObject()->getTransform();

  auto spriteRenderer = getGameObject()->getComponentT<ala::SpriteRenderer>();

  if (transform->getPositionX() + spriteRenderer->getFrameSize (  ).getWidth (  )/2 >= ala::GameManager::get()->getScreenWidth() / 2)
  {
    auto animator = getGameObject()->getComponentT< ala::Animator>();
    animator->setAction("Front");
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
  position.setX(position.getX() + 100 * dt);
  getGameObject()->getTransform()->setPosition(position);
}
