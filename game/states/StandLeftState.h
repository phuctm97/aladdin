#ifndef __STAND_LEFT_STATE_H__
#define __STAND_LEFT_STATE_H__

#include <aladdin.h>

class StandLeftState : public ala::IState
{
public:
  StandLeftState(ala::GameObject* gameObject);

  IState* checkTransition() override;
  void onUpdate(const float dt) override;
  void onStateEnter() override;
};

#endif //!__STAND_LEFT_STATE_H__