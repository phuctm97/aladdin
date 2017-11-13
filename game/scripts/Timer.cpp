#include "Timer.h"

USING_NAMESPACE_ALA;

Timer::Timer( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _timer( 0 ) {}

void Timer::start( const float time ) {
  _timer = time;
}

bool Timer::isDone() const {
  return _timer <= 0;
}

void Timer::onPreUpdate( const float delta ) {
  if ( _timer > 0 ) _timer -= delta;
}

void Timer::onUpdate( const float delta ) {}
