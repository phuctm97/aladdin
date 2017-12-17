#include "StairsModeSwitcher.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(StairsModeSwitcher, ala::GameObjectComponent)

StairsModeSwitcher::StairsModeSwitcher( ala::GameObject* gameObject, const char turnSide,
                                        const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _turnSide( turnSide ),
    _stairsStateManager( NULL ) {}

void StairsModeSwitcher::onTriggerEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();
  const auto selfCollider = collision.getColliderA() == otherCollider
                              ? collision.getColliderB()
                              : collision.getColliderA();

  if ( otherObject->getTag() == ALADDIN_TAG && otherCollider->getTag() == ALADDIN_TAG &&
    selfCollider->getName() == "S" ) {
    if ( (_turnSide == 'C')
      || (_turnSide == 'L' && collision.getNormal().getX() < 0)
      || (_turnSide == 'R' && collision.getNormal().getX() > 0) ) {

      if ( _stairsStateManager->getCurrentStateName() == "on" ) {
        _stairsStateManager->changeState( "off" );
      }
      else if ( _stairsStateManager->getCurrentStateName() == "off" ) {
        _stairsStateManager->changeState( "on" );
      }
    }
  }
}

void StairsModeSwitcher::onInitialize() {
  _stairsStateManager = getGameObject()->getComponentT<StateManager>();
}
