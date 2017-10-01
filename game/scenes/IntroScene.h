#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__

/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include <core/Scene.h>

class IntroScene : public ala::Scene {
public:
  IntroScene();

protected:
  void onPreInitialize() override;
};

#endif //!__INTRO_SCENE_H__
