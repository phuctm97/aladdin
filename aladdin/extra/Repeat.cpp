#include "Repeat.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::Repeat, ala::Action)

Repeat::Repeat( Action* action, const int count ): _action( action ),
                                                   _count( count ), _eslapsedCount( 0 ) {}

void Repeat::onStart() {
  _eslapsedCount = 0;
}

void Repeat::onUpdate( const float delta ) {
  if ( !_action->isStarted() ) {
    _action->start( getActionManager() );
  }
  else if ( _action->isDone() ) {
    _eslapsedCount++;
    if ( _eslapsedCount == _count ) {
      _action->release();
      done();
    }
    else {
      _action->start( getActionManager() );
    }
  }
  else {
    _action->update( delta );
  }
}
}
