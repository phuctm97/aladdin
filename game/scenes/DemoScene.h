#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__

/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include <aladdin.h>

class DemoScene : public ala::Scene, public ala::MessageListener {
public:
  DemoScene();

protected:
  void onPreInitialize() override;

  void onPreRelease() override;

private:
  long _ballDirectionChangedListener;

  ala::Logger _logger;
};

#endif //!__INTRO_SCENE_H__
