#include "AladdinController.h"
#include "ThrowableAppleController.h"

USING_NAMESPACE_ALA;

AladdinController::AladdinController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _logger( "AladdinController" ), _collidedWithGround( false ) {}

bool AladdinController::isCollidedWithGround() const { return _collidedWithGround; }

void AladdinController::resetCollidedWithGround() { _collidedWithGround = false; }

void AladdinController::onUpdate( const float delta ) {}

void AladdinController::onCollisionEnter( const ala::CollisionInfo& collision ) {
  if ( collision.getColliderA()->getGameObject()->getName() == "Ground" || collision.getColliderB()->getGameObject()->
                                                                                     getName() == "Ground" ) {
    _collidedWithGround = true;
  }
}

void AladdinController::throwApple(char direction, float directX, float directY, float impulseX, float impulseY)
{
	const auto transform = getGameObject()->getTransform();
	const auto collider = getGameObject()->getComponentT<Collider>();

	const auto apple = GameManager::get()->getPrefab("Throwable Apple")->instantiate(
		transform->getPosition() + Vec2(collider->getSize().getWidth() / 2 + directX,
			collider->getSize().getHeight() / 2+ directY));
	const auto appleController = (ThrowableAppleController*)apple->getComponent("controller");
	//appleController->chekDirectionLeft(direction);
	if(direction == 'L')
	{
		transform->setScaleX(-ABS(transform->getScale().getX()));
	}
	else
	{
		transform->setScaleX(ABS(transform->getScale().getX()));
	}
	const auto appleBody = apple->getComponentT<Rigidbody>();
	appleBody->addImpulse(Vec2(impulseX, impulseY));


}
