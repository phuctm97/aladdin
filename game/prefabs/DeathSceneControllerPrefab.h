#ifndef __DEATH_SCENE_CONTROLLER_PREFAB_H__
#define __DEATH_SCENE_CONTROLLER_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(DeathSceneControllerPrefab, ala::PrefabV2)
public:
  DeathSceneControllerPrefab()
    : PrefabV2( "Death Scene Controller" ) {}

private:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__DEATH_SCENE_CONTROLLER_PREFAB_H__
