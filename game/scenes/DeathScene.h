#ifndef __DEATH_SCENE_H__
#define __DEATH_SCENE_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1( DeathScene, ala::Scene )
public:
  DeathScene() {}

protected:
  void onPreInitialize() override;
};

#endif //!__DEATH_SCENE_H__
