#include "Action.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1( ala::Action, ala::Releasable )

Action::Action() : _done( false ) {}

Action::~Action() {}

bool Action::isDone() const {
  return _done;
}

void Action::update( const float delta ) {
  if ( _done ) {
    release();
  }
  else {
    onUpdate( delta );
  }
}

void Action::release() {
  onRelease();

  delete this;
}

void Action::done() {
  _done = true;
}

void Action::onUpdate( float delta ) {}

void Action::onRelease() {}
}
