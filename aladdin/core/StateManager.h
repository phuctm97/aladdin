#ifndef __STATE_MANAGER_H__
#define __STATE_MANAGER_H__

#include "IState.h"
#include "GameObjectComponent.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1 ( StateManager, GameObjectComponent )
private:
  IState* _currentState;

protected:
  void onUpdate(const float delta) override;
  void onRelease() override;
public:
  StateManager(GameObject* gameObject, IState* startState, const std::string& name = "");
  virtual ~StateManager();

  void changeState(IState* state);
};
}

#endif //__STATE_MANAGER_H__