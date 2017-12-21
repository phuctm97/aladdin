#include "PendalController.h"
#include "../Define.h"
USING_NAMESPACE_ALA;

PendalController::PendalController(ala::GameObject * object, const string & name)
  : GameObjectComponent( object, name ), _other( NULL ), _logger( "PendalController" ), _resetPoint( Vec2() ) {
  _camera = GameManager::get()->getRunningScene()->getMainCamera();
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
			setResetPoint(getGameObject()->getTransform()->getPosition());
		}
	}
	if (_other->getTag() == GROUND_TAG) {
		if (collision.getNormal() == Vec2(0, 1)) {
			_doReset = true;
		}
	}
}


void PendalController::onUpdate(const float delta)
{
	if (_doReset) {
		if (ABS(_camera->getTransform()->getPositionX() - _resetPoint.getX()) > (_visibleWidth / 2 + 20.0f) ||
			ABS(_camera->getTransform()->getPositionY() - _resetPoint.getY()) > (_visibleHeight / 2 + 5.0f))
		{
			const auto pendal = GameManager::get()->getPrefab("Pendal")->instantiate("NewPendal");
			pendal->getTransform()->setPosition(_resetPoint);
			_doReset = false;
			_doRelease = true;
		}
	}

	if (_doRelease) {
			getGameObject()->getComponentT<StateManager>()->changeState("disappear");
			_doRelease = false;
	}
}

void PendalController::getCollisionObject(const ala::CollisionInfo & collision)
{
	_other = collision.getColliderA()->getGameObject() == getGameObject() ?
		collision.getColliderB()->getGameObject() :
		collision.getColliderA()->getGameObject();
}

void PendalController::setResetPoint(ala::Vec2 vec2)
{
	_resetPoint = vec2;
}


