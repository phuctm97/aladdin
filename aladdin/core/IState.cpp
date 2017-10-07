#include "IState.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0 ( ala::IState )

IState* IState::checkTransition ( )
{
  return NULL;
}

void IState::onStateEnter ( )
{
}

void IState::onStateExit ( )
{
}

void IState::onUpdate ( const float dt )
{
}

GameObject* IState::getGameObject ( ) const
{
  return _gameObject;
}

IState::IState ( GameObject* gameObject )
{
  _gameObject = gameObject;
}

  IState::~IState ( )
{
}
}
