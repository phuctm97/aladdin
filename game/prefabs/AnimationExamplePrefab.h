#ifndef __ANIMATION_EXAMPLE_PREFAB_H__
#define __ANIMATION_EXAMPLE_PREFAB_H__

#include <aladdin.h>

class AnimationExamplePrefab : public ala::Prefab {
public:
  AnimationExamplePrefab() : Prefab("AnimationExample") {}

  void doInstantiate(ala::GameObject* object) override;
};

#endif //!__ANIMATION_EXAMPLE_PREFAB_H__
