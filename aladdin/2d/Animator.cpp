#include "Animator.h"
#include "RectMessageArg.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::Animator, ala::GameObjectComponent)

Animator::~Animator ( )
{
}

void Animator::onUpdate ( const float delta )
{
  if(!_isPlaying)
  {
    return;
  }

  _elapsedTime += delta;

  if (_elapsedTime >= _interval)
  {
    playNext();

    _elapsedTime = 0;
  }

}

Animator::Animator ( GameObject* gameObject, const std::string &entryAction, Animation* animation, float interval, std::string name )
  :GameObjectComponent ( gameObject, name ),
  _interval ( interval>0? interval: 1000)
{



}

Animator::Animator ( GameObject* gameObject, const std::string &entryAction, const std::string& animationResourceName, float interval, std::string name )
  :GameObjectComponent(gameObject, name),
  _interval(interval>0 ? interval : 1000)
{
}

void Animator::setAction ( const std::string& actionName )
{
  _currentAction = _animation->getAction(actionName);
}

const std::string& Animator::getAction ( ) const
{
  return _currentAction->getActionName();
}

void Animator::setInterval ( const float interval )
{
  _interval = interval;
}

Rect Animator::getCurrentFrame ( ) const
{
  return *_frameIterator;
}

void Animator::pause ( )
{
  _isPlaying = false;
}

void Animator::playNext ( )
{
  ++_frameIterator;

  if(_frameIterator == _currentAction->getFrames (  ).end (  ))
  {
    playFromStart();
  }
}

void Animator::play ( )
{
  _isPlaying = true;
}

void Animator::playFromStart ( )
{
  _frameIterator = _currentAction->getFrames().begin();
}
}
