﻿#ifndef __GO_RIGHT_STATE_H__
#define __GO_RIGHT_STATE_H__

#include "core/IState.h"

class GoRightState : public ala::IState
{
public:
  GoRightState(ala::GameObject* gameObject);

  IState* checkTransition() override;
  void onUpdate(const float dt) override;
};

#endif //__GO_RIGHT_STATE_H__