#ifndef __BALL_CONTROLLER_H__
#define __BALL_CONTROLLER_H__

#include <aladdin.h>

class BallController : public ala::GameObjectComponent {
private:
  char _state;
  float _speed;

public:
  BallController( ala::GameObject* gameObject, const std::string& name = "" );

protected:
  void onUpdate( float delta ) override;
};


#endif //!__BALL_CONTROLLER_H__
