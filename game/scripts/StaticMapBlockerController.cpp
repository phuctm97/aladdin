#include "StaticMapBlockerController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

StaticMapBlockerController::StaticMapBlockerController(ala::GameObject * gameObject, const string & name)
	:GameObjectComponent(gameObject, name), _logger("MapBlockerLogger")  {  }

void StaticMapBlockerController::onCollisionEnter(const ala::CollisionInfo & collision)
{
	getCollisionObject(collision);

	if (_other->getTag() == ALADDIN_TAG) {
		const auto alaStateManager = _other->getComponentT<StateManager>();
	}
	_logger.info("Enter");
}

void StaticMapBlockerController::onCollisionStay(const ala::CollisionInfo & collision)
{
	_logger.info("Stay");
}

void StaticMapBlockerController::onCollisionExit(const ala::CollisionInfo & collision)
{
	_logger.info("Exit");
}



void StaticMapBlockerController::getCollisionObject(const ala::CollisionInfo & collision)
{
	_other = collision.getColliderA()->getGameObject() == getGameObject() ?
		collision.getColliderB()->getGameObject() :
		collision.getColliderA()->getGameObject();
}




