#include "PlatformController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

PlatformController::PlatformController(ala::GameObject * gameObject, const string & name)
	:GameObjectComponent(gameObject, name), _logger("PlatformLogger") {  }

void PlatformController::onTriggerEnter(const ala::CollisionInfo & collision)
{
	getCollisionObject(collision);
	_logger.info("Enter");
	if (collision.getNormal() == Vec2(0, -1)) {
		_oldPosition = _other->getTransform()->getPosition();
		float height = getGameObject()->getTransform()->getPositionY() + 
			static_cast<Collider*>(getGameObject()->getComponent("Upon"))->getSize().getHeight() +
			static_cast<Collider*>(getGameObject()->getComponent("Upon"))->getOffset().getY() + 
			_other->getComponentT<Collider>()->getSize().getHeight() / 2 +
		_other->getComponentT<Collider>()->getOffset().getY() / 2 + 1;
		_oldPosition.setY(height);
		return;
	}
	if (_other->getTag() == ALADDIN_TAG) {
		const auto alaStateManager = _other->getComponentT<StateManager>();
		getGameObject()->getComponent("Upon")->setActive(false);
	}
	

}

void PlatformController::onTriggerStay(const ala::CollisionInfo & collision)
{
	//_logger.info("Stay");
}

void PlatformController::onTriggerExit(const ala::CollisionInfo & collision)
{
	getGameObject()->getComponent("Upon")->setActive(true);
	_logger.info("Exit");
}


void PlatformController::onUpdate(const float delta) {
	if (_isChangePosition) {
		_other->getTransform()->setPosition(_oldPosition);
	}
}


void PlatformController::getCollisionObject(const ala::CollisionInfo & collision)
{
	_other = collision.getColliderA()->getGameObject() == getGameObject() ?
		collision.getColliderB()->getGameObject() :
		collision.getColliderA()->getGameObject();
}




