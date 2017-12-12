#include "AladdinController.h"
#include "ThrowableAppleController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

AladdinController::AladdinController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ), _logger( "AladdinController" ),
    _collidedWithGround( false ), _colliedWithKnife( false ), _health( 10 ),
    _lives( 3 ), _apples( 5 ), _recovering( false ) {}

bool AladdinController::isCollidedWithGround() const { return _collidedWithGround; }

bool AladdinController::isCollidedWithKnife() const {
  return _colliedWithKnife;
}

void AladdinController::resetCollidedWithGround() { _collidedWithGround = false; }

void AladdinController::onUpdate( const float delta ) {}

void AladdinController::onCollisionEnter( const ala::CollisionInfo& collision ) {
  if ( collision.getColliderA()->getGameObject()->getTag() == GROUND_TAG ||
    collision.getColliderB()->getGameObject()->getTag() == GROUND_TAG ) {
    _collidedWithGround = true;
  }
}

void AladdinController::onTriggerEnter( const ala::CollisionInfo& collision ) {}

void AladdinController::onTriggerStay( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  if ( otherObject->getTag() == CHARCOAL_BURNER_TAG ) {
    onHitCharcoalBurner( otherObject );
  }
}

void AladdinController::onHitCharcoalBurner( ala::GameObject* burnerObject ) {
  if ( _recovering ) return;

  const auto stateManager = getGameObject()->getComponentT<StateManager>();
  if ( stateManager->getCurrentStateName() == "idle_left" ) {
    stateManager->changeState( "hit_left" );
    setRecovering();
  }
  else if ( stateManager->getCurrentStateName() == "idle_right" ) {
    stateManager->changeState( "hit_right" );
    setRecovering();
  }
}

void AladdinController::throwApple( const char direction, const float directX, const float directY,
                                    const float impulseX, const float impulseY ) {
  if ( _apples <= 0 ) return;
  _apples -= 1;

  const auto transform = getGameObject()->getTransform();
  const auto collider = getGameObject()->getComponentT<Collider>();

  const auto apple = GameManager::get()->getPrefab( "Throwable Apple" )->instantiate(
    transform->getPosition() + Vec2( collider->getSize().getWidth() / 2 + directX,
                                     collider->getSize().getHeight() / 2 + directY ) );
  const auto appleStateManager = static_cast<StateManager*>(apple->getComponentT<StateManager>());

  if ( direction == 'L' ) {
    appleStateManager->changeState( "left" );
  }
  else {
    appleStateManager->changeState( "right" );
  }

  const auto appleBody = apple->getComponentT<Rigidbody>();
  appleBody->addImpulse( Vec2( impulseX, impulseY ) );
}

void AladdinController::setLives( const int lives ) {
  _lives = lives;
}

int AladdinController::getLives() const {
  return _lives;
}

void AladdinController::setApples( const int apples ) {
  _apples = apples;
}

int AladdinController::getApples() const {
  return _apples;
}

void AladdinController::setHealth( const int health ) {
  _health = health;
}

int AladdinController::getHealth() const {
  return _health;
}

bool AladdinController::isRecovering() const {
  return _recovering;
}

void AladdinController::setRecovering() {
  if ( _recovering ) return;

  _recovering = true;

  const auto actionManager = getGameObject()->getComponentT<ActionManager>();
  actionManager->play( new Sequence( {
    new Blink( 0.05f, 10 ),
    new CallFunc( [this] { this->_recovering = false; } )
  } ) );
}
