#ifndef __GO_LEFT_STATE_H__
#define __GO_LEFT_STATE_H__

#include "core/IState.h"

class GoLeftState: public ala::IState
{
public:
  GoLeftState(ala::GameObject* gameObject);

  IState* checkTransition() override;
  void onUpdate(const float dt) override;
};

#endif //__GO_LEFT_STATE_H__