#include "JafarFootFirePrefab.h"
#include "../Define.h"
#include "../scripts/NodeController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(JafarFootFirePrefab, ala::PrefabV2)

void JafarFootFirePrefab::doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const
{
	const auto density = 5.0f;
	// components
	const auto spriteRenderer = new SpriteRenderer(object, "jafar.png");

	const auto animator = new Animator(object, "jafar_snake_foot_fire", "jafar.anm");
	//new NodeController(object);
	//new AnimationEditor(object, "jafar_snake_foot_fire");
	//return;
	const auto body = new Rigidbody(object, PhysicsMaterial(density), ALA_BODY_TYPE_STATIC, 1.0f);

	const auto collider = new Collider(object, false, Vec2(0, 0), Size(40, 50));
	collider->setTag(BOSS_TAG);
	collider->ignoreTag(ENEMY_TAG);
	collider->ignoreTag(ALADDIN_TAG);

	const auto stateManager = new StateManager(object, "idle");

	//state
	// configurations
	object->setLayer("Supporting Character");
	object->setTag(ENEMY_TAG);

	new State(stateManager, "null", NULL, NULL, NULL);

	new State(stateManager, "idle", [=] {
		animator->setAction("jafar_snake_foot_fire");
		body->setVelocity(Vec2(0, 0));
	}, NULL, NULL);

}