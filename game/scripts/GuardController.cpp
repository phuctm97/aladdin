#include "GuardController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(GuardController, ala::GameObjectComponent)

GuardController::GuardController( ala::GameObject* gameObject, const std::string& name ):
  GameObjectComponent( gameObject, name ),
  _minDistanceCouldAttack( 40 ),
  _maxDistanceCouldAttack( 70 ),
  _tooFarDistance( GameManager::get()->getVisibleWidth() * 0.7f ),
  _initialX( 0 ),
  _leftBoundX( 0 ), _rightBoundX( 0 ), _health( 2 ),
  _aladdinTransform( NULL ), _selfTransform( NULL ), _selfStateManager( NULL ), _selfDirection( NULL ),
  _enemyExplosionOnePrefab( NULL ), _enemyExplosionTwoPrefab( NULL ){}

void GuardController::onInitialize() {
  const auto gameManager = GameManager::get();

  _selfTransform = getGameObject()->getTransform();

  _selfTransform->setPositionX( _initialX );

  _selfDirection = getGameObject()->getComponentT<DirectionController>();

  _selfStateManager = getGameObject()->getComponentT<StateManager>();

  const auto aladdin = gameManager->getObjectByTag( ALADDIN_TAG );
  if ( aladdin != NULL ) {
    _aladdinTransform = aladdin->getTransform();
  }

  _enemyExplosionOnePrefab = gameManager->getPrefabV2( "Enemy Explosion 1" );

  _enemyExplosionTwoPrefab = gameManager->getPrefabV2( "Enemy Explosion 2" );
}

bool GuardController::isTooFarFromAladdin() const {
  const auto aladdinPosition = _aladdinTransform->getPosition();
  const auto selfPosition = _selfTransform->getPosition();
  return ABS(aladdinPosition.getX() - selfPosition.getX()) >= _tooFarDistance;
}

bool GuardController::isAbleToSeeAladdin() const {
  const auto aladdinPositionX = _aladdinTransform->getPositionX();
  const auto dist1 = ABS(aladdinPositionX - _leftBoundX);
  const auto dist2 = ABS(aladdinPositionX - _rightBoundX);

  return (aladdinPositionX >= _leftBoundX && aladdinPositionX <= _rightBoundX)
    || dist1 <= _maxDistanceCouldAttack
    || dist2 <= _maxDistanceCouldAttack;
}

char GuardController::getDirectionToGoToAttackAladdin() const {
  const auto aladdinPosition = _aladdinTransform->getPosition();
  const auto selfPosition = _selfTransform->getPosition();

  float options[] = {
    aladdinPosition.getX() - _minDistanceCouldAttack,
    aladdinPosition.getX() + _minDistanceCouldAttack,
    aladdinPosition.getX() - _maxDistanceCouldAttack,
    aladdinPosition.getX() + _maxDistanceCouldAttack
  };

  std::sort( options, options + 4, [=]( float a, float b ) {
    if ( a < _leftBoundX || a > _rightBoundX ) return false;
    if ( b < _leftBoundX || b > _rightBoundX ) return true;
    return ABS(a - selfPosition.getX()) < ABS(b - selfPosition.getX());
  } );

  const auto bestOption = options[0];
  if ( bestOption < selfPosition.getX() ) return 'L';
  return 'R';
}

char GuardController::getDirectionToFaceToAladdin() const {
  if ( _aladdinTransform->getPositionX() < _selfTransform->getPositionX() ) return 'L';
  return 'R';
}

bool GuardController::isAbleToAttackAladdin() const {
  const auto dist = ABS(_aladdinTransform->getPositionX() - _selfTransform->getPositionX());
  return dist >= _minDistanceCouldAttack && dist <= _maxDistanceCouldAttack;
}

bool GuardController::isAbleToGoLeft() const {
  return _selfTransform->getPositionX() > _leftBoundX;
}

bool GuardController::isAbleToGoRight() const {
  return _selfTransform->getPositionX() < _rightBoundX;
}

void GuardController::keepInBound() const {
  const auto selfTransform = _selfTransform;

  if ( selfTransform->getPositionX() < _leftBoundX ) {
    selfTransform->setPositionX( _leftBoundX );
  }
  if ( selfTransform->getPositionX() > _rightBoundX ) {
    selfTransform->setPositionX( _rightBoundX );
  }
}

float GuardController::getInitialX() const { return _initialX; }

void GuardController::setInitialX( const float initialX ) { _initialX = initialX; }

float GuardController::getLeftBoundX() const { return _leftBoundX; }

void GuardController::setLeftBoundX( const float leftBoundX ) { _leftBoundX = leftBoundX; }

float GuardController::getRightBoundX() const { return _rightBoundX; }

void GuardController::setRightBoundX( const float rightBoundX ) { _rightBoundX = rightBoundX; }

float GuardController::getMinDistanceCouldAttack() const { return _minDistanceCouldAttack; }

void GuardController::setMinDistanceCouldAttack( const float minDistanceCouldAttack ) {
  _minDistanceCouldAttack = minDistanceCouldAttack;
}

float GuardController::getMaxDistanceCouldAttack() const { return _maxDistanceCouldAttack; }

void GuardController::setMaxDistanceCouldAttack( const float maxDistanceCouldAttack ) {
  _maxDistanceCouldAttack = maxDistanceCouldAttack;
}

int GuardController::getHealth() const { return _health; }

void GuardController::setHealth( const int health ) { _health = health; }

void GuardController::onHit() {
  if ( _selfStateManager->getCurrentStateName() == "hit" ) return;

  const auto hitState = _selfStateManager->getState( "hit" );
  if ( hitState != NULL ) {
    _selfStateManager->changeState( hitState );
  }

  _health -= rand() % 2 + 1;
  if ( _health <= 0 ) {
    onDie();
  }
}

void GuardController::onDie( const int explosionType ) const {
  switch ( explosionType ) {
  case 1:
    _enemyExplosionOnePrefab->instantiate( _selfTransform->getPosition() );
    break;
  case 2:
    _enemyExplosionTwoPrefab->instantiate( _selfTransform->getPosition() );
    break;
  default:
    _enemyExplosionOnePrefab->instantiate( _selfTransform->getPosition() );
    break;
  }

  getGameObject()->release();
}

void GuardController::onTriggerEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  const auto selfCollider = collision.getColliderA() == otherCollider
                              ? collision.getColliderB()
                              : collision.getColliderA();

  if ( selfCollider->getTag() == ENEMY_TAG ) {
    if ( otherObject->getTag() == ALADDIN_TAG &&
      (otherCollider->getTag() == SWORD_TAG || otherCollider->getTag() == APPLE_TAG) ) {
      onHit();
    }
    else if ( otherObject->getTag() == SAVILA_TAG ) {
      onHit();
    }
  }
}
