#ifndef __BALL_CONTROLLER_H__
#define __BALL_CONTROLLER_H__

/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include <aladdin.h>

class BallController : public ala::GameObjectComponent, public ala::MessageListener {
private:
  char _state;
  float _speed;
  ala::Logger _logger;

public:
  BallController( ala::GameObject* gameObject, const std::string& name = "" );

protected:
  void onInitialize() override;

  void onUpdate( const float delta ) override;

  void onRelease() override;
};


#endif //!__BALL_CONTROLLER_H__
