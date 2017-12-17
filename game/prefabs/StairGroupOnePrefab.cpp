#include "StairGroupOnePrefab.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

void StairGroupOnePrefab::doInstantiate(ala::GameObject * object) const
{
	//Constants
	const auto body = new Rigidbody(object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC);
	
	//Components
	vector<Vec2> position{
		Vec2(1015.5f, -46.0f),
		Vec2(1055.5f, -36.0f),
		Vec2(1096.0f, -28.5f),
		Vec2(1136.0f, -21.5f),
		Vec2(1176.0f, -12.5f),
		Vec2(1215.0f, -5.5f),
		Vec2(1286.0f, 2.5f)
	};

	vector<Size> size{
		Size(45.0f, 8.0f),
		Size(42.0f, 7.0f),
		Size(42.0f, 6.0f),
		Size(45.0f, 7.0f),
		Size(43.0f, 6.0f),
		Size(43.0f, 7.0f),
		Size(106.0f, 7.0f)
	};


	for (size_t i=0; i<position.size(); i++)
	{
		const auto collider = new Collider(object, false, position[i], size[i], 1, 0);
		new ColliderRenderer(collider);
	}

	
	//Renderer

	object->setTag(GROUND_TAG);
	object->setLayer("Foreground");
}

