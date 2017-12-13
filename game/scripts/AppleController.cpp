#include "AppleController.h"
#include "./HubController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

AppleController::AppleController(ala::GameObject * gameObject, const string & name)
	: GameObjectComponent(gameObject, name)
{
}

void AppleController::onTriggerEnter(const ala::CollisionInfo & collision)
{
	if (collision.getColliderA()->getGameObject()->getTag() == ALADDIN_TAG ||
		collision.getColliderB()->getGameObject()->getTag() == ALADDIN_TAG)
		getGameObject()->getComponentT<StateManager>()->changeState("ate");
}
