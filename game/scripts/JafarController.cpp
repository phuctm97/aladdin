#include "JafarController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(JafarController, ala::GameObjectComponent)

JafarController::JafarController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ), _mode( 1 ), _health( 100.0f ), _aladdinTransform( NULL ),
    _selfTransform( NULL ), _sceneFadeOutTransitionPrefab( NULL ) {}

char JafarController::getDirectionToFaceAladdin() const {
  if ( _aladdinTransform->getPositionX() < _selfTransform->getPositionX() ) return 'L';
  return 'R';
}

float JafarController::getHealth() const {
  return _health;
}

int JafarController::getMode() const {
  return _mode;
}

void JafarController::onTriggerEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  const auto selfCollider = collision.getColliderA() == otherCollider
                              ? collision.getColliderB()
                              : collision.getColliderA();

  if ( otherObject->getTag() == ALADDIN_TAG ) {
    if ( otherCollider->getTag() == APPLE_TAG || otherCollider->getTag() == SWORD_TAG ) {
      onHit();
    }
  }
}

void JafarController::onInitialize() {
  const auto gameManager = GameManager::get();

  _selfTransform = getGameObject()->getTransform();

  const auto aladdin = gameManager->getObjectByTag( ALADDIN_TAG );
  if ( aladdin != NULL ) {
    _aladdinTransform = aladdin->getTransform();
  }

  _sceneFadeOutTransitionPrefab = gameManager->getPrefabV2( "Scene Fade Out Transition" );
}

void JafarController::onHit() {
  _health -= 10;

  if ( _health <= 60 && _mode != 2 ) {
    _mode = 2;
  }

  if ( _health < 0 ) {
    _sceneFadeOutTransitionPrefab->instantiateWithArgs( "0.5 level_complete.scene\n0" );
  }
}
