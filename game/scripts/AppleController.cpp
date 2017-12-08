#include "AppleController.h"
#include "./HubController.h"
USING_NAMESPACE_ALA;

AppleController::AppleController(ala::GameObject * gameObject, const string & name)
	: GameObjectComponent(gameObject, name)
{
}

void AppleController::onTriggerEnter(const ala::CollisionInfo & collision)
{
	getGameObject()->getComponentT<StateManager>()->changeState("ate");
}
