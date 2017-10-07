#ifndef __GO_UP_STATE_H__
#define __GO_UP_STATE_H__

#include "core/IState.h"

class GoUpState : public ala::IState
{
public:
  GoUpState(ala::GameObject* gameObject);

  IState* checkTransition() override;
  void onUpdate(const float dt) override;
};

#endif //__GO_UP_STATE_H__