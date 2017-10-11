#include "AnimationExamplePrefab.h"
#include "../scripts/BallController.h"
#include "core/StateManager.h"
#include "2d/Animator.h"
#include "../states/StandRightState.h"

void AnimationExamplePrefab::doInstantiate(ala::GameObject* object) {
  new ala::SpriteRenderer(object, "aladdin.png");
  new ala::Animator(object, "idle1", "aladdin.animation");
  new ala::AudioSource(object,"wow.vav");
  new ala::StateManager(object, new StandRightState(object));
}
