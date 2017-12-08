#include "HandEnemyController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

HandEnemyController::HandEnemyController(ala::GameObject* gameObject, const std::string& name)
	: GameObjectComponent(gameObject, name), _nearAladdin(false) {}

bool HandEnemyController::isAladdinNear() const { return _nearAladdin; }

void HandEnemyController::onUpdate(const float delta) {
	/*_nearAladdin = true;
	return;*/

	const auto aladdin = GameManager::get()->getObjectByName("Aladdin");
	if (aladdin == NULL) return;

	const auto visibleWidth = GameManager::get()->getVisibleWidth();

	if (ABS(getGameObject()->getTransform()->getPosition().getX() - aladdin->getTransform()->getPosition().getX()) < 40
		) {
		_nearAladdin = true;
	}
	else {
		_nearAladdin = false;
	}
}
