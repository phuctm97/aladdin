#ifndef __DEATH_SOUND_PREFAB_H__
#define __DEATH_SOUND_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(DeathSceneSoundPrefab, ala::PrefabV2)
public:
  DeathSceneSoundPrefab() : PrefabV2( "Death scene sound" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif // !__DEATH_SOUND_PREFAB_H__

