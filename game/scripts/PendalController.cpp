#include "PendalController.h"
#include "../Define.h"
USING_NAMESPACE_ALA;

PendalController::PendalController(ala::GameObject * object, const string & name)
	:GameObjectComponent(object, name), _logger("PendalController") {
	_camera = GameManager::get()->getMainCamera();
	_visibleWidth = GameManager::get()->getVisibleWidth();
	_visibleHeight = GameManager::get()->getVisibleHeight();
}


void PendalController::onCollisionEnter(const ala::CollisionInfo & collision)
{
	getCollisionObject(collision);
	if (_other->getTag() == ALADDIN_TAG) {
		if (collision.getNormal() == Vec2(0, -1)) {
			getGameObject()->getComponentT<StateManager>()->changeState("drop");
			getGameObject()->getComponentT<Collider>()->ignoreTag(ALADDIN_TAG);
		}
	}
	if (_other->getTag() == GROUND_TAG) {
		if (collision.getNormal() == Vec2(0, 1)) {
			checkReset = true;
		}
	}
}


void PendalController::onUpdate(const float delta)
{
	if (checkReset) {
		if (ABS(_camera->getTransform()->getPositionX() - 1486.5f) > (_visibleWidth / 2 + 20.0f) ||
			ABS(_camera->getTransform()->getPositionY() - 128.0f) > (_visibleHeight / 2 + 5.0f))
		{
			getGameObject()->getComponentT<StateManager>()->changeState("disappear");
			checkReset = false;
		}
	}
}

void PendalController::getCollisionObject(const ala::CollisionInfo & collision)
{
	_other = collision.getColliderA()->getGameObject() == getGameObject() ?
		collision.getColliderB()->getGameObject() :
		collision.getColliderA()->getGameObject();
}


