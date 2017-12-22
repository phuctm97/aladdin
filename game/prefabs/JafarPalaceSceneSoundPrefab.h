#ifndef __JAFAR_SCENE_SOUND_PREFAB_H__
#define __JAFAR_SCENE_SOUND_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(JafarPalaceSceneSoundPrefab, ala::PrefabV2)
public:
  JafarPalaceSceneSoundPrefab() : PrefabV2( "Jafar Palace Scene Sound" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif // !__JAFAR_SCENE_SOUND_PREFAB_H__
