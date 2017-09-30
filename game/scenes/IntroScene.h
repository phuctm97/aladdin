#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__

#include <core/Scene.h>

class IntroScene : public ala::Scene {
public:
  IntroScene();

protected:
  virtual bool onPreInit() override;
};

#endif //!__INTRO_SCENE_H__
