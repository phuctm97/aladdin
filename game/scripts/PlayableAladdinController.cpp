#include "PlayableAladdinController.h"
#include "DirectionController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(PlayableAladdinController, ala::GameObjectComponent)

PlayableAladdinController::
PlayableAladdinController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ), _health( 0 ), _lives( 0 ), _apples( 0 ), _recovering( false ) {}

void PlayableAladdinController::setLives( const int lives ) {
  _lives = lives;
}

int PlayableAladdinController::getLives() const {
  return _lives;
}

void PlayableAladdinController::setApples( const int apples ) {
  _apples = apples;
}

int PlayableAladdinController::getApples() const {
  return _apples;
}

void PlayableAladdinController::setHealth( const int health ) {
  _health = health;
}

int PlayableAladdinController::getHealth() const {
  return _health;
}

bool PlayableAladdinController::isRecovering() const {
  return _recovering;
}

void PlayableAladdinController::setRecovering() {
  if ( _recovering ) return;

  _recovering = true;

  const auto actionManager = getGameObject()->getComponentT<ActionManager>();
  actionManager->play( new Sequence( {
    new Blink( 0.05f, 10 ),
    new CallFunc( [this] { this->_recovering = false; } )
  } ) );
}

void PlayableAladdinController::throwApple( const char direction,
                                            const float offsetX, const float offsetY,
                                            const float impulseX, const float impulseY ) {
  if ( _apples <= 0 ) return;
  _apples -= 1;

  const auto transform = getGameObject()->getTransform();
  const auto collider = static_cast<Collider*>(getGameObject()->getComponent( "Body" ));

  const auto apple = GameManager::get()->getPrefab( "Throwable Apple" )->instantiate(
    transform->getPosition() + Vec2( collider->getSize().getWidth() / 2 + offsetX,
                                     collider->getSize().getHeight() / 2 + offsetY ) );
  const auto appleDirection = apple->getComponentT<DirectionController>();

  if ( direction == 'L' ) {
    appleDirection->setLeft();
  }
  else {
    appleDirection->setRight();
  }

  const auto appleBody = apple->getComponentT<Rigidbody>();
  appleBody->addImpulse( Vec2( impulseX, impulseY ) );
}

void PlayableAladdinController::onCollisionEnter( const ala::CollisionInfo& collision ) {}

void PlayableAladdinController::onTriggerEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  if ( otherObject->getTag() == ENEMY_TAG && otherCollider->getTag() == SWORD_TAG ) {
    onHit();
  }
}

void PlayableAladdinController::onTriggerStay( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  if ( otherObject->getTag() == CHARCOAL_BURNER_TAG ) {
    onHit();
  }
}

void PlayableAladdinController::onTriggerExit( const ala::CollisionInfo& collision ) {}

void PlayableAladdinController::onHit() {
  if ( _recovering ) return;

  const auto stateManager = getGameObject()->getComponentT<StateManager>();
  if ( stateManager->getCurrentStateName() == "idle" ) {
    setRecovering();
    stateManager->changeState( "hit" );
  }
}
