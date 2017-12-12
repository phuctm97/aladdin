#include "GuardController.h"
#include "../Define.h"


USING_NAMESPACE_ALA;

GuardController::GuardController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _couldAttackAladdin( false ), _couldSeeAladdin( false ), _onRightOfAladdin( false ), _tooFarFromAladdin( true ),
    _initialX( 0 ), _minX( 0 ), _maxX( 0 ) {}

bool GuardController::couldAttackAladdin() const {
  return _couldAttackAladdin;
}

bool GuardController::couldSeeAladdin() const {
  return _couldSeeAladdin;
}

bool GuardController::isOnRightOfAladdin() const {
  return _onRightOfAladdin;
}

bool GuardController::isTooFarFromAladdin() const {
  return _tooFarFromAladdin;
}

float GuardController::getInitialX() const {
  return _initialX;
}

void GuardController::setInitialX( const float initialX ) {
  _initialX = initialX;
}

void GuardController::onUpdate( const float delta ) {
  const auto aladdin = GameManager::get()->getObjectByTag( ALADDIN_TAG );
  if ( aladdin == NULL ) return;

  const auto visibleWidth = GameManager::get()->getVisibleWidth();
  const auto guardPosition = getGameObject()->getTransform()->getPosition();
  const auto aladdinPosition = aladdin->getTransform()->getPosition();

  const auto distanceToAladdin = ABS(guardPosition.getX() - aladdinPosition.getX());
  _couldSeeAladdin = distanceToAladdin < visibleWidth * 0.6f;
  _tooFarFromAladdin = distanceToAladdin > visibleWidth * 0.7f;
  _couldAttackAladdin = distanceToAladdin < 70;
  _onRightOfAladdin = aladdinPosition.getX() < guardPosition.getX();
}

void GuardController::onTriggerEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  if ( otherObject->getTag() == ALADDIN_TAG && otherCollider->getTag() == SWORD_TAG ) {
    onHit();
  }
}

void GuardController::onHit() {
  const auto stateManager = getGameObject()->getComponentT<StateManager>();
  const auto currentStateName = stateManager->getCurrentStateName();

  if ( currentStateName == "hit_left" || currentStateName == "hit_right" )
    return;

  if ( currentStateName.substr( currentStateName.length() - 4 ) == "left" ) {
    stateManager->changeState( "hit_left" );
  }
  else {
    stateManager->changeState( "hit_right" );
  }
}

float GuardController::getMinX() const { return _minX; }

void GuardController::setMinX( const float minX ) { _minX = minX; }

float GuardController::getMaxX() const { return _maxX; }

void GuardController::setMaxX( const float maxX ) { _maxX = maxX; }

void GuardController::set( const float initialX, const float minX, const float maxX ) {
  setInitialX( initialX );
  setMinX( minX );
  setMaxX( maxX );
}
