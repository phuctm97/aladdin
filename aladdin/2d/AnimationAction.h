#pragma once

#include "2dInclude.h"
#include "Rect.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0 (AnimationAction)
private:
  bool _loop;
  float _interval;

  std::string _actionName;

  std::vector< Rect> _frames;
public:
  AnimationAction();
  AnimationAction(const std::vector<Rect>& frames, const std::string& actionName, const float interval = 0, const bool loop = true);

  const std::vector<Rect>& getFrames() const;

  float getInterval() const;

  bool isLoop() const;

  const std::string& getActionName() const;
};
}