#include "NodePrefab.h"
#include "../scripts/NodeController.h"

USING_NAMESPACE_ALA;

void NodePrefab::doInstantiate(ala::GameObject * object) const
{
	const auto gameManager = GameManager::get();
	const auto halfVisibleSize = Size(gameManager->getVisibleWidth() / 2, gameManager->getVisibleHeight() / 2);
	const auto transform = object->getTransform();

	transform->setPosition(Vec2(-halfVisibleSize.getWidth(),
		-halfVisibleSize.getHeight()));

	new RectRenderer(object, Vec2(), Size(3, 3), Color(255, 0, 0));
	new NodeController(object, "NodeController");
	object->setLayer("Foreground");
}
