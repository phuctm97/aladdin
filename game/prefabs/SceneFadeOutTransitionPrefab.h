#ifndef __SCENE_FADE_OUT_TRANSITION_PREFAB_H__
#define __SCENE_FADE_OUT_TRANSITION_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(SceneFadeOutTransitionPrefab, ala::PrefabV2)
public:
  SceneFadeOutTransitionPrefab()
    : PrefabV2( "Scene Fade Out Transition" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__SCENE_FADE_OUT_TRANSITION_PREFAB_H__
