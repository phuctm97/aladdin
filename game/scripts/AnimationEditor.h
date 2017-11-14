#ifndef __ANIMATION_EDITOR_H__
#define __ANIMATION_EDITOR_H__

#include <aladdin.h>

class AnimationEditor : public ala::GameObjectComponent
{
private:
  ala::Animation* _animation;
  ala::AnimationAction* _currentAction;

public:
  AnimationEditor(ala::GameObject* gameObject, const std::string &entryAction, ala::Animation* animation = NULL, const std::string& name = "");
  AnimationEditor( ala::GameObject* gameObject, const std::string &entryAction, const std::string& animationResourceName = "", const std::string& name = "" );
};

#endif //!__ANIMATION_EDITOR_H__