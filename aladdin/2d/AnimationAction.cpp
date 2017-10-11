#include "AnimationAction.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0(ala::AnimationAction)

AnimationAction::AnimationAction ( ): _loop( false ), _interval( 0 ) {}

AnimationAction::AnimationAction(const std::vector<ala::Rect>& frames, const std::string& actionName, const float interval, const bool loop)
{
  _frames = frames;
  _interval = interval;
  _loop = loop;
  _actionName = actionName;
}

AnimationAction::~AnimationAction() {}

const std::vector<ala::Rect>& AnimationAction::getFrames() const
{
  return _frames;
}

float AnimationAction::getInterval() const
{
  return _interval;
}

bool AnimationAction::isLoop() const
{
  return _loop;
}

const std::string& AnimationAction::getActionName ( ) const
{
  return _actionName;
}
}