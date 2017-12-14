#include "StairGroupTwoPrefab.h"
#include "../Define.h"
#include "../scripts/StairGroupTwoController.h"

USING_NAMESPACE_ALA;

void StairGroupTwoPrefab::doInstantiate(ala::GameObject * object) const
{
	//Constants
	const auto body = new Rigidbody(object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC);
	
	//Components
	vector<Vec2> position{
		Vec2(2445.0f, -87.5f),
		Vec2(2411.5f, -79.5f),
		Vec2(2387.5f, -71.0f),
		Vec2(2356.0f, -63.0f),
		Vec2(2323.5f, -55.0f),
		Vec2(2291.5f, -47.0f),
		Vec2(2252.5f, -39.0f),
		Vec2(2212.0f, -31.5f),
		Vec2(2179.5f, -23.5f),
		Vec2(2148.0f, -15.0f),
		Vec2(2108.0f, -7.0f),
	};

	vector<Size> size{
		Size(34.0f, 7.0f),
		Size(34.0f, 7.0f),
		Size(34.0f, 7.0f),
		Size(34.0f, 7.0f),
		Size(34.0f, 7.0f),
		Size(34.0f, 7.0f),
		Size(47.0f, 7.0f),
		Size(33.0f, 7.0f),
		Size(33.0f, 7.0f),
		Size(33.0f, 7.0f),
		Size(47.0f, 7.0f)
	};


	for (size_t i = 0; i<position.size(); i++)
	{
		const auto collider = new Collider(object, false, position[i], size[i], 1, 0, "Static");
		new ColliderRenderer(collider);
	}

	const auto checkActive = new Collider(object, true, Vec2(2513.0f, -33.0f), Size(15.0f, 118.0f), 1, 0);
	new ColliderRenderer(checkActive);

	//Renderer
	new StairGroupTwoController(object);

	object->setTag(GROUND_TAG);
	object->setLayer("Foreground");
}

