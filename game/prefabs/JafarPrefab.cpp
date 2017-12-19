#include "JafarPrefab.h"
#include "../Define.h"
#include "../scripts/DirectionController.h"
#include "../scripts/JafarController.h"
#include "../scripts/NodeController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(JafarPrefab, ala::PrefabV2)

void JafarPrefab::doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const
{
	// constants
	const auto gameManager = GameManager::get();
	const auto JafarFireAttackPrefab = gameManager->getPrefabV2("Jafar fire attack");

	const auto density = 5.0f;

	const auto swordOffset = Vec2(-50, 5);
	const auto swordSize = Size(50, 32);

	// components
	const auto spriteRenderer = new SpriteRenderer(object, "jafar.png");
	const auto audio = new AudioSource(object, "Jafar Snake.wav");

	const auto animator = new Animator(object, "jafar_snake_attack", "jafar.anm");

	//new AnimationEditor(object, "fire_attack");
	//return;

	const auto body = new Rigidbody(object, PhysicsMaterial(density), ALA_BODY_TYPE_STATIC);

	const auto collider = new Collider(object, true, Vec2(0, 0), Size(40, 50));
	collider->setTag(BOSS_TAG);
	collider->ignoreTag(ENEMY_TAG);
	collider->ignoreTag(ALADDIN_TAG);

	const auto stateManager = new StateManager(object, "jafar_snake_attack");

	const auto direction = new DirectionController(object, true, -1);

	const auto controller = new JafarController(object);

	// helpers
	const auto timer1 = new Timer(object);
	const auto timer2 = new Timer(object);

	const auto transform = object->getTransform();

	// collider renderers
	new ColliderRenderer(collider);

	// configurations
	object->setLayer("Supporting Character");
	object->setTag(ENEMY_TAG);

	new State(stateManager, "null", NULL, NULL, NULL);

	//states
	new State(stateManager, "jafar_snake_attack",
		[=] {
		// animation effect
			{
				animator->setAction("jafar_snake_attack");
			}

			// move
			{
				body->setVelocity(Vec2(0,0));
			}

			// attack
			{
				timer1->start(0.06f);
			}
	},
		[=](float dt) {

			// direction
			{
				int directionToFace = controller->getDirectionToFaceToAladdin();
				if (directionToFace == 'L' && direction->isRight()) direction->setLeft();
				else if (directionToFace == 'R' && direction->isLeft()) direction->setRight();
			}

			// attack
			{
				if (timer1->isDone()) {
					std::stringstream throwArgsStream;

					if (direction->isRight()) {
						throwArgsStream << 'R';
					}
					else {
						throwArgsStream << 'L';
					}
					audio->play();
					JafarFireAttackPrefab->instantiateWithArgs(throwArgsStream.str())
						->getTransform()
						->setPosition(transform->getPosition() +
							Vec2(collider->getSize().getWidth() / 2,
								collider->getSize().getHeight() / 2 - collider->getSize().getHeight() *
								0.25f));

					timer1->start(5);
				}
			}
	}, NULL);

	new StateTransition(stateManager, "jafar_snake_attack", "jafar_snake_attack", [=] {
		return !animator->isPlaying();
	});

}
