#ifndef __DEBUG_SCENE_H__
#define __DEBUG_SCENE_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(DebugScene, ala::Scene)
  void onPreInitialize() override;
};

#endif //!__DEBUG_SCENE_H__