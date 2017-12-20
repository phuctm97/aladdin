#ifndef __LEVEL_COMPLETE_SCENE_CONTROLLER_PREFAB_H__
#define __LEVEL_COMPLETE_SCENE_CONTROLLER_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(LevelCompleteSceneControllerPrefab, ala::PrefabV2)
public:
  LevelCompleteSceneControllerPrefab()
    : PrefabV2( "Level Complete Scene Controller" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__LEVEL_COMPLETE_SCENE_CONTROLLER_PREFAB_H__
