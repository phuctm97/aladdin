#include "JafarStarController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(JafarStarController, ala::GameObjectComponent)

JafarStarController::JafarStarController( ala::GameObject* gameObject, const float movingSpeed,
                                          const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _movingSpeed( movingSpeed ), _jafarTransform( NULL ),
    _aladdinTransform( NULL ), _aladdinBody( NULL ), _aladdinController( NULL ),
    _selfTransform( NULL ),
    _explosionPrefab( NULL ), _myAppData( NULL ) {}

const ala::Vec2& JafarStarController::getTargetPosition() const {
  return _targetPosition;
}

void JafarStarController::onTriggerEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  if ( otherObject->getTag() == ALADDIN_TAG ) {
    if ( otherCollider->getTag() == ALADDIN_TAG ) {
      if ( _aladdinController != NULL ) {
        auto force = 6000.0f;
        auto delay = 0.5f;
        switch ( _myAppData->getDifficulty() ) {
        case 0:
          force = 2000.0f;
          delay = 0.2f;
          break;
        case 1:
          force = 4000.0f;
          delay = 0.35f;
          break;
        case 2:
          force = 6000.0f;
          delay = 0.5f;
          break;
        default: break;
        }

        if ( _aladdinTransform->getPositionX() < _jafarTransform->getPositionX() ) {
          _aladdinController->addDampVelocity( force, delay );
        }
        else {
          _aladdinController->addDampVelocity( -force, delay );
        }
      }
    }

    explode();
  }
}

void JafarStarController::onInitialize() {
  const auto gameManager = GameManager::get();

  _selfTransform = getGameObject()->getTransform();

  const auto aladdin = gameManager->getObjectByTag( ALADDIN_TAG );
  if ( aladdin != NULL ) {
    _aladdinTransform = aladdin->getTransform();

    _aladdinBody = aladdin->getComponentT<Rigidbody>();

    _aladdinController = static_cast<PlayableAladdinController*>(aladdin->getComponent( "Controller" ));

    _targetPosition = _aladdinTransform->getPosition();
  }

  const auto jafar = gameManager->getObjectByTag( BOSS_TAG );
  if ( jafar != NULL ) {
    _jafarTransform = jafar->getTransform();
  }

  _explosionPrefab = gameManager->getPrefabV2( "Jafar Star Explosion" );

  _myAppData = static_cast<MyAppData*>(gameManager->getResource( "My App Data" ));
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
