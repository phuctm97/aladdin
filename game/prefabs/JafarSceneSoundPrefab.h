#ifndef __JAFAR_SCENE_SOUND_PREFAB_H__
#define __JAFAR_SCENE_SOUND_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(JafarSceneSoundPrefab, ala::PrefabV2)
public:
	JafarSceneSoundPrefab() : PrefabV2("Jafar scene sound") {}

protected:
	void doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const override;
};

#endif // !__JAFAR_SCENE_SOUND_PREFAB_H__
