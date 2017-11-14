#include "AnimationAction.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0(ala::AnimationAction)

AnimationAction::AnimationAction ( ): _loop( false ), _interval( 0 ) {}

AnimationAction::AnimationAction(const std::vector<ala::Rect>& frames, const std::vector<Vec2>& frameAnchors, const std::string& actionName, const std::string& textureName, const float interval, const bool loop)
{
  _frames = frames;
  _frameAnchors = frameAnchors;
  _interval = interval;
  _loop = loop;
  _actionName = actionName;
  _textureName = textureName;
}

AnimationAction::~AnimationAction() {}

const std::vector<ala::Rect>& AnimationAction::getFrames() const
{
  return _frames;
}

const std::vector<Vec2>& AnimationAction::getFrameAnchors() const {
  return _frameAnchors;
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

const std::string& AnimationAction::getTextureName ( ) const
{
  return _textureName;
}
}
