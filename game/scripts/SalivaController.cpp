#include "SalivaController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

SalivaController::SalivaController(ala::GameObject* gameObject, const std::string& name)
	: GameObjectComponent(gameObject, name) {}

void SalivaController::onUpdate(const float delta) {

	const auto aladdin = GameManager::get()->getObjectByName("Aladdin");
	if (aladdin == NULL) return;

	const auto visibleWidth = GameManager::get()->getVisibleWidth();

	if (ABS(getGameObject()->getTransform()->getPosition().getX() - aladdin->getTransform()->getPosition().getX()) < 40
		) {
	}
	else {
	}
}
