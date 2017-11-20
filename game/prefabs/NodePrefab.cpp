#include "NodePrefab.h"
#include "../scripts/NodeController.h"

USING_NAMESPACE_ALA;

void NodePrefab::doInstantiate(ala::GameObject * object) const
{
	new RectRenderer(object, Vec2(), Size(3, 3), Color(255, 0, 0));
	new NodeController(object);
}
