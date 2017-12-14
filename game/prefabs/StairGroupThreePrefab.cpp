#include "StairGroupThreePrefab.h"
#include "../Define.h"
#include "../scripts/StairGroupThreeController.h"

USING_NAMESPACE_ALA;

void StairGroupThreePrefab::doInstantiate(ala::GameObject * object) const
{
	//Constants
	const auto body = new Rigidbody(object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC);

	//Components
	vector<Vec2> position{
		Vec2(2152.5f, -4.0f),
		Vec2(2190.5f, 3.5f),
		Vec2(2221.5f, 11.5f),
		Vec2(2254.5f, 19.0f),
		Vec2(2286.5f, 27.0f),
		Vec2(2326.5f, 35.0f),
		Vec2(2382.5f, 43.0f),
		Vec2(2494.5f, 51.0f)		
	};

	vector<Size> size{
		Size(39.0f, 5.0f),
		Size(39.0f, 5.0f),
		Size(39.0f, 5.0f),
		Size(39.0f, 5.0f),
		Size(39.0f, 5.0f),
		Size(55.0f, 5.0f),
		Size(55.0f, 5.0f),
		Size(182.0f, 5.0f)
	};


	for (size_t i = 0; i<position.size(); i++)
	{
		const auto collider = new Collider(object, false, position[i], size[i], 1, 0, "Static");
		new ColliderRenderer(collider);
	}

	const auto checkActive = new Collider(object, true, Vec2(2090.0f, 33.0f), Size(11.0f, 73.0f), 1, 0, "Triggerer");
	new ColliderRenderer(checkActive);

	//Renderer
	new StairGroupThreeController(object, "Controller");

	object->setTag(GROUND_TAG);
	object->setLayer("Foreground");

}

