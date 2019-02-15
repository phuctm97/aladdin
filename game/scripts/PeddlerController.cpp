#include "PeddlerController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(PeddlerController, ala::GameObjectComponent)

PeddlerController::PeddlerController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ), _aladdinTransform( NULL ), _aladdinController( NULL ),
    _selfTransform( NULL ),
    _selfSpriteRenderer( NULL ),
    _selfAnimator( NULL ), _childSpriteRenderer( NULL ), _childAnimator( NULL ),
    _collider5( NULL ), _collider10( NULL ), _peddlerTextPrefab( NULL ) {}

void PeddlerController::onInitialize() {
  const auto aladdin = GameManager::get()->getObjectByTag( ALADDIN_TAG );
  _aladdinTransform = aladdin->getTransform();
  _aladdinController = aladdin->getComponentT<PlayableAladdinController>();
  _selfTransform = getGameObject()->getTransform();
  _selfSpriteRenderer = getGameObject()->getComponentT<SpriteRenderer>();
  _selfAnimator = getGameObject()->getComponentT<Animator>();
  _childSpriteRenderer = getGameObject()->getTransform()->getChild( 0 )
                                        ->getGameObject()->getComponentT<SpriteRenderer>();
  _childAnimator = getGameObject()->getTransform()->getChild( 0 )
                                  ->getGameObject()->getComponentT<Animator>();
  _collider5 = static_cast<Collider*>(getGameObject()->getComponent( "5" ));
  _collider10 = static_cast<Collider*>(getGameObject()->getComponent( "10" ));
  _collider5->setActive( false );
  _collider10->setActive( false );

  _peddlerTextPrefab = GameManager::get()->getPrefabV2( "Peddler Text" );
}

void PeddlerController::onUpdate( const float delta ) {
  if ( abs( _selfTransform->getPositionX() - _aladdinTransform->getPositionX() ) > 200
    && _selfAnimator->getActionName() == "pavilion_2" ) {
    _selfAnimator->setAction( "idle_1" );
    _childSpriteRenderer->setVisible( false );
    _collider5->setActive( false );
    _collider10->setActive( false );
  }
  if ( abs( _selfTransform->getPositionX() - _aladdinTransform->getPositionX() ) <= 200
    && _selfAnimator->getActionName() == "idle_1" ) {
    _selfAnimator->setAction( "pavilion_1" );
  }
  else if ( _selfAnimator->getActionName() == "pavilion_1" ) {
    if ( _selfAnimator->getCurrentFrameIndex() == 24 ) {
      _childSpriteRenderer->setVisible( true );
      _childAnimator->setAction( "idle_2" );
      _collider5->setActive( true );
      _collider10->setActive( true );
    }

    if ( !_selfAnimator->isPlaying() ) {
      _selfAnimator->setAction( "pavilion_2" );
    }
  }
}

void PeddlerController::onTriggerStay( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  const auto selfCollider = collision.getColliderA() == otherCollider
                              ? collision.getColliderB()
                              : collision.getColliderA();

  if ( otherObject->getTag() == ALADDIN_TAG && otherCollider->getTag() == ALADDIN_TAG
    && Input::get()->getKeyDown( ALA_KEY_UP_ARROW ) ) {
    if ( selfCollider->getName() == "5" ) {
      if ( _aladdinController->getGems() >= 5 ) {
        _aladdinController->setGems( _aladdinController->getGems() - 5 );
        _aladdinController->setLives( _aladdinController->getLives() + 1 );
      }
      else {
        _peddlerTextPrefab->instantiate();
      }
    }
    else if ( selfCollider->getName() == "10" ) {
      if ( _aladdinController->getGems() >= 10 ) {
        _aladdinController->setGems( _aladdinController->getGems() - 10 );
      }
      else {
        _peddlerTextPrefab->instantiate();
      }
    }
  }
}
