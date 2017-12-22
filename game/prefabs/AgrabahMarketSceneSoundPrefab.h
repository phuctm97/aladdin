#ifndef __AGRAB_SCENE_SOUND_PREFAB_H__
#define __AGRAB_SCENE_SOUND_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(AgrabahMarketSceneSoundPrefab, ala::PrefabV2)
public:
	AgrabahMarketSceneSoundPrefab() : PrefabV2("Agrabah Market Scene Sound") {}

protected:
	void doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const override;
};

#endif // !__AGRAB_SCENE_SOUND_PREFAB_H__
