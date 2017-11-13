#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__

/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include <aladdin.h>

class ExperimentalScene : public ala::Scene, public ala::MessageListener {
public:
  ExperimentalScene();

protected:
  void onPreInitialize() override;

  void onPreRelease() override;

private:
  ala::Logger _logger;
};

#endif //!__INTRO_SCENE_H__
