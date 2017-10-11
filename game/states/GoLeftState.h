#ifndef __GO_LEFT_STATE_H__
#define __GO_LEFT_STATE_H__

#include <aladdin.h>

class GoLeftState: public ala::IState
{
public:
  GoLeftState(ala::GameObject* gameObject);

  IState* checkTransition() override;
  void onUpdate(const float dt) override;
  void onStateEnter() override;
};

#endif //__GO_LEFT_STATE_H__