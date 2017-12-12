#include "GuardController.h"
#include "DirectionController.h"
#include "../Define.h"


USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(GuardController, ala::GameObjectComponent)

GuardController::GuardController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _state( 0 ),
    _initialX( 0 ), _minX( 0 ), _maxX( 0 ), _health( 2 ) {}

bool GuardController::isIdling() const {
  return _state == 0;
}

bool GuardController::isChasingAladdin() const {
  return _state == 1;
}

bool GuardController::isAttacking() const {
  return _state == 2;
}

void GuardController::onInitialize() {
  const auto transform = getGameObject()->getTransform();
  transform->setPosition( _initialX );
}

void GuardController::onUpdate( const float delta ) {
  const auto gameManager = GameManager::get();
  const auto aladdin = gameManager->getObjectByTag( ALADDIN_TAG );
  if ( aladdin == NULL ) return;

  const auto transform = getGameObject()->getTransform();
  const auto direction = getGameObject()->getComponentT<DirectionController>();
  const auto stateManager = getGameObject()->getComponentT<StateManager>();

  const auto visibleWidth = GameManager::get()->getVisibleWidth();
  const auto guardPosition = getGameObject()->getTransform()->getPosition();
  const auto aladdinPosition = aladdin->getTransform()->getPosition();
  const auto distanceToAladdin = ABS(guardPosition.getX() - aladdinPosition.getX());

  // keep in bound
  if ( guardPosition.getX() < _minX ) {
    transform->setPositionX( _minX );
  }
  else if ( guardPosition.getX() > _maxX ) {
    transform->setPositionX( _maxX );
  }

  // direction
  const auto onRightOfAladdin = aladdinPosition.getX() < guardPosition.getX();
  if ( onRightOfAladdin ) direction->setLeft();
  else direction->setRight();

  // attack
  const auto couldAttackAladdin = distanceToAladdin < 70;
  if ( couldAttackAladdin ) {
    _state = 2;
    return;
  }

  // chase
  const auto couldSeeAladdin = distanceToAladdin < visibleWidth * 0.6f;

  if ( couldSeeAladdin &&
    ((guardPosition.getX() < _maxX && !onRightOfAladdin) ||
      (guardPosition.getX() > _minX && onRightOfAladdin)) ) {
    _state = 1;
  }
  else {
    _state = 0;

    const auto tooFarFromAladdin = distanceToAladdin > visibleWidth * 0.7f;
    if ( tooFarFromAladdin ) {
      transform->setPositionX( _initialX );
    }
  }
}

void GuardController::onTriggerEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  if ( otherObject->getTag() == ALADDIN_TAG &&
    (otherCollider->getTag() == SWORD_TAG || otherCollider->getTag() == APPLE_TAG) ) {
    onHit( rand() % 2 + 1 );
  }
}

void GuardController::onHit( const int damage ) {
  const auto stateManager = getGameObject()->getComponentT<StateManager>();
  if ( stateManager->getCurrentStateName() == "hit" )
    return;

  if ( stateManager->getState( "hit" ) != NULL ) {
    stateManager->changeState( "hit" );
  }

  _health -= damage;
  if ( _health <= 0 ) {
    const auto object = getGameObject();

    GameManager::get()->getPrefab( "Enemy Explosion" )->instantiate( object->getTransform()->getPosition() );
    object->release();
  }
}

float GuardController::getInitialX() const {
  return _initialX;
}

float GuardController::getMinX() const { return _minX; }

float GuardController::getMaxX() const { return _maxX; }

int GuardController::getHealth() const {
  return _health;
}

void GuardController::set( const float initialX, const float minX, const float maxX ) {
  _initialX = initialX;
  _minX = minX;
  _maxX = maxX;
}

void GuardController::setHealth( const int health ) {
  _health = health;
}
