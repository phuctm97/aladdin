#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__

/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include <core/Scene.h>
#include "core/IMessageArg.h"

class IntroScene : public ala::Scene {
public:
  IntroScene();

protected:
  void onPreInitialize() override;
  void onPreRelease() override;
private:
  void onBallDirectionChanged(ala::IMessageArg* arg);
  long _ballDirectionChangedListener;
};

#endif //!__INTRO_SCENE_H__
