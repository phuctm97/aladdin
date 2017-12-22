#include "AgrabahMarketSceneSound.h"
#include"../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(AgrabahMarketSceneSound, ala::PrefabV2)

void AgrabahMarketSceneSound::doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const
{
	const auto SceneSound = new AudioSource(object, "Background Agrabahmarket.wav");
	const auto stateManager = new StateManager(object, "static");

	new State(stateManager, "static", [=] {
		SceneSound->play();
		}, NULL, NULL);
}
