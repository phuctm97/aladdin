#include "DoubleStairsModeSwitcher.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(DoubleStairsModeSwitcher, ala::GameObjectComponent)

DoubleStairsModeSwitcher::DoubleStairsModeSwitcher( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _stairsStateManager( NULL ) {}

void DoubleStairsModeSwitcher::onTriggerEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  const auto selfCollider = collision.getColliderA() == otherCollider
                              ? collision.getColliderB()
                              : collision.getColliderA();

  if ( otherObject->getTag() == ALADDIN_TAG && otherCollider->getTag() == ALADDIN_TAG ) {

    if ( selfCollider->getName() == "B" ) {
      if ( otherObject->getTransform()->getPositionX() < getGameObject()->getTransform()->getPositionX()
        + selfCollider->getOffset().getX() ) {
        if ( _stairsStateManager->getCurrentStateName() == "OffOff" ) {
          _stairsStateManager->changeState( "OnOff" );
          return;
        }
        if ( _stairsStateManager->getCurrentStateName() == "OnOff" ) {
          _stairsStateManager->changeState( "OffOff" );
          return;
        }
      }
      if ( otherObject->getTransform()->getPositionX() > getGameObject()->getTransform()->getPositionX()
        + selfCollider->getOffset().getX() ) {
        if ( _stairsStateManager->getCurrentStateName() == "OnOn" ) {
          _stairsStateManager->changeState( "OnOff" );
          return;
        }
      }
    }

    if ( selfCollider->getName() == "U" ) {
      if ( otherObject->getTransform()->getPositionX() > getGameObject()->getTransform()->getPositionX()
        + selfCollider->getOffset().getX() ) {
        if ( _stairsStateManager->getCurrentStateName() == "OnOn" ) {
          _stairsStateManager->changeState( "OnOff" );
          return;
        }
        if ( _stairsStateManager->getCurrentStateName() == "OnOff" ) {
          _stairsStateManager->changeState( "OnOn" );
          return;
        }
      }
    }

	if (selfCollider->getName() == "S") {
		_stairsStateManager->changeState("OnOn");
		return;
	}
  }
}

void DoubleStairsModeSwitcher::onInitialize() {
  _stairsStateManager = getGameObject()->getComponentT<StateManager>();
}
