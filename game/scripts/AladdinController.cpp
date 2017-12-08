#include "AladdinController.h"
#include "ThrowableAppleController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

AladdinController::AladdinController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ), _collidedWithGround( false ), _logger( "AladdinController" ) {}

bool AladdinController::isCollidedWithGround() const { return _collidedWithGround; }

bool AladdinController::isCollidedWithKnife() const
{
	return _colliedWithKnife;
}

bool AladdinController::isAladdinRightPosition() const
{
	return _aladdinPosition;
}

void AladdinController::resetCollidedWithGround() { _collidedWithGround = false; }

void AladdinController::onUpdate( const float delta )
{
	const auto adorableguard = GameManager::get()->getObjectByName("Adorable Guard");
	if (adorableguard == NULL) return;

	const auto visibleWidth = GameManager::get()->getVisibleWidth();

	if (adorableguard->getTransform()->getPosition().getX() < getGameObject()->getTransform()->getPosition().getX())
	{
		_aladdinPosition = true; //Aladdin is in the right of enemy
	}
	else _aladdinPosition = false; //Aladdin is in the left of enemy
}

void AladdinController::onCollisionEnter( const ala::CollisionInfo& collision ) {
  if ( collision.getColliderA()->getGameObject()->getTag() == GROUND_TAG ||
    collision.getColliderB()->getGameObject()->getTag() == GROUND_TAG ) {
    _collidedWithGround = true;
  }
}

void AladdinController::onTriggerEnter( const ala::CollisionInfo& collision ) {
	if (collision.getColliderA()->getTag() == KNIFE_TAG ||
		collision.getColliderB()->getTag() == KNIFE_TAG) {
		_colliedWithKnife = true;
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
