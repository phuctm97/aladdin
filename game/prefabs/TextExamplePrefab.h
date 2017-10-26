#ifndef __TEXT_EXAMPLE_PREFAB_H__
#define __TEXT_EXAMPLE_PREFAB_H__

#include <aladdin.h>

class TextExamplePrefab : public ala::Prefab {
public:
  TextExamplePrefab() : Prefab("Text Example") {}

  void doInstantiate(ala::GameObject* object) override;
};

#endif //!__TEXT_EXAMPLE_PREFAB_H__
