#include "StateManager.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::StateManager, ala::GameObjectComponent)


void StateManager::onUpdate ( const float delta )
{
  auto nextState = _currentState->checkTransition();

  changeState(nextState);

  _currentState->onUpdate(delta);
}

void StateManager::onRelease ( )
{
  delete(_currentState);
}

  StateManager::StateManager ( GameObject* gameObject, IState* startState, const std::string& name ):
  GameObjectComponent ( gameObject, name )
{
  _currentState = startState;
  _currentState->onStateEnter();
}

StateManager::~StateManager ( )
{
}

void StateManager::changeState ( IState* state )
{
  if(state)
  {
    _currentState->onStateExit();
    delete(_currentState);
    _currentState = state;
    _currentState->onStateEnter();
  }
}
}
