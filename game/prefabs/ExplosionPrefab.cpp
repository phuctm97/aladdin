#include"ExplosionPrefab.h"
#include"../Define.h"


USING_NAMESPACE_ALA;

void ExplosionPrefab::doInstantiate(ala::GameObject* object) const {
	// components
	const auto spriteRenderer = new SpriteRenderer(object, "enemy_explosions.png");
	const auto animator = new Animator(object, "explosion", "enemy_explosions.anm");

	// //For animationEditor
	//const auto animationEditor = new AnimationEditor( object, "abu_bonus" );
	//return;
	// //For animationEditor

	const auto collider = new Collider(object, false, Vec2(0, 0), Size(24, 15));
	collider->setTag(ENEMY_TAG);
	collider->ignoreTag(ALADDIN_TAG);

	//const auto colliderRenderer = new ColliderRenderer(collider);
	const auto stateManager = new StateManager(object, "explosion_effect");
	const auto transform = object->getTransform();

	// configurations
	object->setTag(ENEMY_TAG);
	object->setLayer("Background");

	// states
	new State(stateManager, "explosion_effect",
		[=] {
		animator->setAction("explosion");
	}, [=](float dt) {
		if (!animator->isPlaying())
			object->release();
	}, NULL);
}