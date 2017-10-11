#ifndef __DOWN_RIGHT_STATE_H__
#define __DOWN_RIGHT_STATE_H__

#include <aladdin.h>

class DownRightState : public ala::IState
{
public:
  DownRightState(ala::GameObject* gameObject);

  IState* checkTransition() override;
  void onUpdate(const float dt) override;
  void onStateEnter() override;
};

#endif //__GO_LEFT_STATE_H__