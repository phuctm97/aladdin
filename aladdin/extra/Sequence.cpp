#include "Sequence.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1( ala::Sequence, ala::Action )

Sequence::Sequence( const std::vector<Action*>& actions ) : _currentAction( NULL ) {
  for ( const auto action : actions ) _actions.push( action );
}

void Sequence::onStart() {}

void Sequence::onUpdate( const float delta ) {
  if ( _actions.empty() && _currentAction == NULL ) {
    done();
    return;
  }

  if ( _currentAction == NULL ) {
    _currentAction = _actions.front();
    _actions.pop();
  }

  if ( !_currentAction->isStarted() ) {
    _currentAction->start( getActionManager() );
  }
  else if ( _currentAction->isDone() ) {
    _currentAction->release();
    _currentAction = NULL;
  }
  else {
    _currentAction->update( delta );
  }
}
}
