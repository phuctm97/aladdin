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
  if(!_isPlaying)
  {
    return;
  }

  _elapsedTime += delta;

  if (_elapsedTime >= _currentAction->getInterval (  ))
  {
    ++_frameIterator;
    if (_frameIterator == _currentAction->getFrames().end() )
    {
      if(!_currentAction->isLoop (  ))
      {
        _isPlaying = false;
        return;
      }
      else
      {
        playFromStart();
        _elapsedTime = 0;
      }
    }
    else
    {
      getGameObject()->getMessenger()->broadcast(SOURCE_RECT_CHANGE_MESSAGE, new RectMessageArgs(*_frameIterator));
      _elapsedTime = 0;
    }


  }

}

Animator::Animator ( GameObject* gameObject, const std::string &entryAction, Animation* animation,const std::string& name )
  :GameObjectComponent ( gameObject, name )
{
  _isPlaying = true;

  _animation = animation;
  _currentAction = _animation->getAction(entryAction);

  _frameIterator = _currentAction->getFrames (  ).begin();

  getGameObject()->getMessenger()->broadcast(SOURCE_RECT_CHANGE_MESSAGE, new RectMessageArgs(*_frameIterator));
}

Animator::Animator ( GameObject* gameObject, const std::string &entryAction, const std::string& animationResourceName, const std::string& name )
  :GameObjectComponent(gameObject, name)
{
  _isPlaying = true;

  _animation = static_cast<Animation*>(GameManager::get()->getResource(animationResourceName));
  _currentAction = _animation->getAction(entryAction);

  _frameIterator = _currentAction->getFrames().begin();

  getGameObject()->getMessenger()->broadcast(SOURCE_RECT_CHANGE_MESSAGE, new RectMessageArgs(*_frameIterator));

}

void Animator::setAction ( const std::string& actionName )
{
  _currentAction = _animation->getAction(actionName);
  _frameIterator = _currentAction->getFrames().begin();
  _isPlaying = true;
  getGameObject()->getMessenger()->broadcast(SOURCE_RECT_CHANGE_MESSAGE, new RectMessageArgs(*_frameIterator));
}

const std::string& Animator::getAction ( ) const
{
  return _currentAction->getActionName();
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
  else
  {
    getGameObject()->getMessenger()->broadcast(SOURCE_RECT_CHANGE_MESSAGE, new RectMessageArgs(*_frameIterator));
  }
}

void Animator::play ( )
{
  _isPlaying = true;
}

void Animator::playFromStart ( )
{
  _isPlaying = true;

  _frameIterator = _currentAction->getFrames().begin();

  getGameObject()->getMessenger()->broadcast(SOURCE_RECT_CHANGE_MESSAGE, new RectMessageArgs(*_frameIterator));
}

bool Animator::isPlaying ( ) const
{
  return _isPlaying;
}
}
