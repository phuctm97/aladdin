#ifndef __STAND_RIGHT_STATE_H__
#define __STAND_RIGHT_STATE_H__
#include "core/IState.h"

class StandRightState : public ala::IState
{
public:
  StandRightState(ala::GameObject* gameObject);

  IState* checkTransition() override;
  void onUpdate(const float dt) override;
  void onStateEnter() override;
};
#endif //__STAND_RIGHT_STATE_H__