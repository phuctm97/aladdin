#ifndef __RETRY_SCENE_CONTROLLER_PREFAB_H__
#define __RETRY_SCENE_CONTROLLER_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(RetrySceneControllerPrefab, ala::PrefabV2)
public:
  RetrySceneControllerPrefab()
    : PrefabV2( "Retry Scene Controller" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__RETRY_SCENE_CONTROLLER_PREFAB_H__
