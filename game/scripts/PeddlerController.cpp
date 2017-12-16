#include "PeddlerController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

PeddlerController::PeddlerController(ala::GameObject* gameObject, const std::string& name)
	: GameObjectComponent(gameObject, name), showedPavilion(false) {}

bool PeddlerController::isShowedPavilion() const { return showedPavilion; }

void PeddlerController::ShowedPavilion() {
	showedPavilion = true;
}
