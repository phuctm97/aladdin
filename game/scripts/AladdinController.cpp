#include "AladdinController.h"
#include "ThrowableAppleController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

AladdinController::AladdinController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ), _collidedWithGround( false ) {}

bool AladdinController::isCollidedWithGround() const { return _collidedWithGround; }

void AladdinController::resetCollidedWithGround() { _collidedWithGround = false; }

void AladdinController::onUpdate( const float delta ) {}

void AladdinController::onCollisionEnter( const ala::CollisionInfo& collision ) {
  if ( collision.getColliderA()->getGameObject()->getTag() == GROUND_TAG ||
    collision.getColliderB()->getGameObject()->getTag() == GROUND_TAG ) {
    _collidedWithGround = true;
  }
}

void AladdinController::throwApple( const char direction, const float directX, const float directY,
                                    const float impulseX, const float impulseY ) const {
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
