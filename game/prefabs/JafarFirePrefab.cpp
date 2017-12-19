#include "JafarFirePrefab.h"
#include "../Define.h"
#include "../scripts/DirectionController.h"
#include "../scripts/NodeController.h"
#include "../scripts/CollisionTracker.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(JafarFirePrefab, ala::PrefabV2)

void JafarFirePrefab::doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const
{
	const auto dir = nextChar(argsStream);
	const auto impulseX = 280;
	const auto impulseY = 0;

	// constants
	const auto gameManager = GameManager::get();

	const auto density = 5.0f;

	// components
	const auto spriteRenderer = new SpriteRenderer(object, "jafar.png");

	const auto animator = new Animator(object, "fire_attack", "jafar.anm");

	//new AnimationEditor(object, "fire_attack");
	//return;
	const auto body = new Rigidbody(object, PhysicsMaterial(density), ALA_BODY_TYPE_DYNAMIC, 1.0f);

	const auto collider = new Collider(object, false, Vec2(0, 0), Size(40, 50));
	collider->setTag(BOSS_TAG);
	collider->ignoreTag(BOSS_TAG);
	collider->ignoreTag(ENEMY_TAG);
	collider->ignoreTag(ALADDIN_TAG);

	//new ColliderRenderer(collider);

	const auto stateManager = new StateManager(object, "initial");

	const auto direction = new DirectionController(object);
	if (dir == 'L') direction->setLeft();
	else if (dir == 'R') direction->setRight();

	const auto transform = object->getTransform();


	// configurations
	object->setLayer("Supporting Character");
	object->setTag(ENEMY_TAG);
	const auto collisionTracker = new CollisionTracker(object);

	new State(stateManager, "null", NULL, NULL, NULL);

	//stages
	new State(stateManager, "initial",
		[=] {
		// animation effect
			{
				animator->setAction("fire_attack");
				body->setVelocity(Vec2(impulseX, impulseY));
				collisionTracker->reset();
			}
			
	}, [=](float dt) {
		if (collisionTracker->collidedWithObjectTag(WALL_TAG)) {
			object->release();
		}
		}, NULL);
}
