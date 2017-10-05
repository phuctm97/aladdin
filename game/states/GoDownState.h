#ifndef __GO_DOWN_STATE_H__
#define __GO_DOWN_STATE_H__

#include "core/IState.h"

class GoDownState : public ala::IState
{
public:
  GoDownState(ala::GameObject* gameObject);

  IState* checkTransition() override;
  void onUpdate(const float dt) override;
};

#endif //__GO_DOWN_STATE_H__