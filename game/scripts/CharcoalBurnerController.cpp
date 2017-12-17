#include "CharcoalBurnerController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

CharcoalBurnerController::CharcoalBurnerController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _touchingAladdin( false ),
    _firingMinX( 0 ), _firingMaxX( 0 ), _firingX( 0 ), _aladdinTransform( NULL ) {}

void CharcoalBurnerController::onTriggerEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  if ( otherObject->getTag() == ALADDIN_TAG && otherCollider->getTag() == ALADDIN_TAG ) {
    _touchingAladdin = true;
    updateFiringX();
  }
}

void CharcoalBurnerController::onTriggerStay( const ala::CollisionInfo& collision ) { }

void CharcoalBurnerController::onTriggerExit( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  if ( otherObject->getTag() == ALADDIN_TAG && otherCollider->getTag() == ALADDIN_TAG ) {
    _touchingAladdin = false;
  }
}

float CharcoalBurnerController::getFiringX() const {
  return _firingX;
}

bool CharcoalBurnerController::isTouchingAladdin() const {
  return _touchingAladdin;
}

void CharcoalBurnerController::onInitialize() {
  const auto gameManager = GameManager::get();
  const auto aladdin = gameManager->getObjectByTag( ALADDIN_TAG );
  if ( aladdin != NULL ) {
    _aladdinTransform = aladdin->getTransform();
  }

  const auto collider = getGameObject()->getComponentT<Collider>();
  if ( collider == NULL ) return;

  const auto colliderBox = collider->getBoundingRect();
  _firingMinX = colliderBox.getMinX();
  _firingMaxX = colliderBox.getMaxX();
  _firingX = (_firingMaxX + _firingMinX) / 2;
}

void CharcoalBurnerController::onUpdate( const float delta ) {
  if ( _touchingAladdin ) {
    updateFiringX();
  }
}

void CharcoalBurnerController::updateFiringX() {
  _firingX = MAX(MIN(_aladdinTransform->getPositionX(), _firingMaxX), _firingMinX);
}
