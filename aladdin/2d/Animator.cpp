#include "Animator.h"
#include "RectMessageArgs.h"

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
    ++_frameIterator;
    if(_frameIterator == _frames.end (  ))
    {
      _frameIterator = _frames.begin();
    }
    getGameObject()->getMessenger()->broadcast(SOURCE_RECT_CHANGE_MESSAGE, new RectMessageArgs(*_frameIterator));
    _elapsedTime = 0;
  }
}

Animator::Animator ( GameObject* gameObject, const std::string &entryAction, Animation* animation,const float interval,const std::string& name )
  :GameObjectComponent ( gameObject, name ),
  _interval ( interval>0? interval: 1000)
{
  _animation = animation;
  _frames = _animation->getFrameForAction(entryAction);

  _frameIterator = _frames.begin();

  getGameObject()->getMessenger()->broadcast(SOURCE_RECT_CHANGE_MESSAGE, new RectMessageArgs(*_frameIterator));

}

Animator::Animator ( GameObject* gameObject, const std::string &entryAction, const std::string& animationResourceName,const float interval,const std::string& name )
  :GameObjectComponent(gameObject, name),
  _interval(interval>0 ? interval : 1000)
{
  _animation = static_cast<Animation*>(GameManager::get()->getResource(animationResourceName));
  _frames = _animation->getFrameForAction(entryAction);

  _frameIterator = _frames.begin (  );

  getGameObject()->getMessenger()->broadcast(SOURCE_RECT_CHANGE_MESSAGE, new RectMessageArgs(*_frameIterator));
}

void Animator::setAction (const std::string& actionName )
{
  _frames = _animation->getFrameForAction(actionName);
  _frameIterator = _frames.begin (  );
}

void Animator::setFrameInterval (const float interval )
{
  _interval = interval < 0 ? _interval : interval;
}

Rect Animator::getCurrentFrame ( ) const
{
  return *_frameIterator;
}
}
