#include "JafarController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;
ALA_CLASS_SOURCE_1(JafarController, ala::GameObjectComponent)

JafarController::JafarController(ala::GameObject* gameObject, const std::string& name) :
	GameObjectComponent(gameObject, name),
	_aladdinTransform(NULL), _selfTransform(NULL), _selfStateManager(NULL), _selfDirection(NULL) {}

void JafarController::onInitialize()
{
	const auto gameManager = GameManager::get();

	_selfTransform = getGameObject()->getTransform();

	_selfDirection = getGameObject()->getComponentT<DirectionController>();

	_selfStateManager = getGameObject()->getComponentT<StateManager>();

	const auto aladdin = gameManager->getObjectByTag(ALADDIN_TAG);
	if (aladdin != NULL) {
		_aladdinTransform = aladdin->getTransform();
	}
}

char JafarController::getDirectionToFaceToAladdin() const
{
	if (_aladdinTransform->getPositionX() < _selfTransform->getPositionX()) return 'L';
		return 'R';
}

void JafarController::onTriggerEnter(const ala::CollisionInfo& collision)
{
	const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
		? collision.getColliderB()
		: collision.getColliderA();
	const auto otherObject = otherCollider->getGameObject();

	const auto selfCollider = collision.getColliderA() == otherCollider
		? collision.getColliderB()
		: collision.getColliderA();
	if (selfCollider->getTag() == ENEMY_TAG) {
		if (otherObject->getTag() == ALADDIN_TAG &&
			(otherCollider->getTag() == SWORD_TAG || otherCollider->getTag() == APPLE_TAG)) {
			onHit();
		}
		else if (otherObject->getTag() == SAVILA_TAG) {
			onHit();
		}
	}
}
void JafarController::onHit() {
	if (_selfStateManager->getCurrentStateName() == "hit") return;

	const auto hitState = _selfStateManager->getState("hit");
	if (hitState != NULL) {
		_selfStateManager->changeState(hitState);
	}

	_health -= rand() % 2 + 1;
	if (_health <= 0) {
		//onDie();
	}
}

int JafarController::getHealth() const { return _health; }

void JafarController::setHealth(const int health) { _health = health; }




