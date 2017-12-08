#include "AladdinController.h"
#include "ThrowableAppleController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

AladdinController::AladdinController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ), _collidedWithGround( false ), _health( 10 ), _lives( 3 ), _apples( 5 ),
    _logger( "AladdinController" ) {}

bool AladdinController::isCollidedWithGround() const { return _collidedWithGround; }

void AladdinController::resetCollidedWithGround() { _collidedWithGround = false; }

void AladdinController::onUpdate( const float delta ) {}

void AladdinController::onCollisionEnter( const ala::CollisionInfo& collision ) {
  if ( collision.getColliderA()->getGameObject()->getTag() == GROUND_TAG ||
    collision.getColliderB()->getGameObject()->getTag() == GROUND_TAG ) {
    _collidedWithGround = true;
  }
}

void AladdinController::onTriggerEnter( const ala::CollisionInfo& collision ) {}

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
    appleStateManager->changeState( "apple_left" );
  }
  else {
    appleStateManager->changeState( "apple_right" );
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
