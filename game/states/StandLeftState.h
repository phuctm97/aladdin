#include "core/IState.h"

class StandLeftState : public ala::IState
{
public:
  StandLeftState(ala::GameObject* gameObject);

  IState* checkTransition() override;
  void onUpdate(const float dt) override;
  void onStateEnter() override;
};
