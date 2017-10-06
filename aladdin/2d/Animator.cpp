#include "Animator.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::Animator, ala::GameObjectComponent)

Animator::~Animator ( )
{
}

void Animator::onUpdate ( const float delta )
{
  _elapsedTime += delta;
  if(_elapsedTime >= _interval)
  {
    auto size = _currentFrame.size();
    if(_currentIndex >= size- 1)
    {
      _currentIndex = 0;
    }
    else
    {
      _currentIndex++;
    }
    _elapsedTime = 0;
  }
}

Animator::Animator ( GameObject* gameObject, const std::string &entryAction, Animation* animation, float interval, std::string name )
  :GameObjectComponent ( gameObject, name ),
  _interval ( interval>0? interval: 1000)
{
  _animation = animation;
  _currentFrame = _animation->getFrameForAction(entryAction);
}

Animator::Animator ( GameObject* gameObject, const std::string &entryAction, const std::string& animationResourceName, float interval, std::string name )
  :GameObjectComponent(gameObject, name),
  _interval(interval>0 ? interval : 1000)
{
  _animation = static_cast<Animation*>(GameManager::get()->getResource(animationResourceName));
  _currentFrame = _animation->getFrameForAction(entryAction);
}

void Animator::setAction ( std::string actionName )
{
  _currentFrame = _animation->getFrameForAction(actionName);
  _currentIndex = 0;
}

void Animator::setFrameInterval ( float interval )
{
  _interval = interval < 0 ? _interval : interval;
}

Rect Animator::getCurrentFrame ( ) const
{
  return _currentFrame[_currentIndex];
}
}
