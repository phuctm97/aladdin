#include "JafarStarController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(JafarStarController, ala::GameObjectComponent)

JafarStarController::JafarStarController( ala::GameObject* gameObject, const float movingSpeed,
                                          const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _movingSpeed( movingSpeed ),
    _aladdinTransform( NULL ), _selfTransform( NULL ), _explosionPrefab( NULL ) {}

const ala::Vec2& JafarStarController::getTargetPosition() const {
  return _targetPosition;
}

void JafarStarController::onTriggerEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  if ( otherObject->getTag() == ALADDIN_TAG ) {
    explode();
  }
}

void JafarStarController::onInitialize() {
  const auto gameManager = GameManager::get();

  _selfTransform = getGameObject()->getTransform();

  const auto aladdin = gameManager->getObjectByTag( ALADDIN_TAG );
  if ( aladdin != NULL ) {
    _aladdinTransform = aladdin->getTransform();
    _targetPosition = _aladdinTransform->getPosition();
  }

  _explosionPrefab = gameManager->getPrefabV2( "Jafar Star Explosion" );
}

void JafarStarController::onUpdate( const float delta ) {
  // move toward target
  const auto diff = _targetPosition - _selfTransform->getPosition();
  const auto diffLength = diff.getLength();
  if ( diffLength <= _movingSpeed ) {
    _selfTransform->setPosition( _targetPosition );

    // update target position
    _targetPosition = _aladdinTransform->getPosition();
  }
  else {
    const auto normalizedDiff = diff / diffLength;
    _selfTransform->setPosition( _selfTransform->getPosition() + normalizedDiff * _movingSpeed );
  }
}

void JafarStarController::explode() const {
  _explosionPrefab->instantiateWithArgs( "" )
                  ->getTransform()->setPosition( _selfTransform->getPosition() );

  getGameObject()->release();
}
