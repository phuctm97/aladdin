#ifndef __ANIMATION_EDITOR_H__
#define __ANIMATION_EDITOR_H__

#include <aladdin.h>

class AnimationEditor : public ala::GameObjectComponent
{
private:
  ala::Logger _logger;
  std::string _actionName;

public:
  AnimationEditor(ala::GameObject* gameObject, const std::string& actionName, const std::string& name = "");

protected:
  bool onPreInitialize() override;
  
  void onUpdate( const float delta ) override;
};

#endif //!__ANIMATION_EDITOR_H__