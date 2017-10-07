#ifndef __ALADDIN_2D_ANIMATOR_H__
#define __ALADDIN_2D_ANIMATOR_H__

#include "2dInclude.h"
#include "Rect.h"
#include "Animation.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(Animator, ala::GameObjectComponent)
private:
  Animation* _animation;

  std::vector<Rect> _frames;
  std::vector<Rect>::iterator _frameIterator;

  float _elapsedTime;
  float _interval;

protected:
  virtual ~Animator();

  void onUpdate(const float delta) override;
public:
  Animator(GameObject* gameObject, const std::string &entryAction, Animation* animationName = NULL, const float interval = 1000, const std::string& name = "");
  Animator(GameObject* gameObject, const std::string &entryAction, const std::string &animationResourceName = "", const float interval = 1000, const std::string& name = "");

  void setAction(const std::string& actionName);

  void setFrameInterval(const float interval);
  Rect getCurrentFrame() const;
};
}
#endif //!__ALADDIN_2D_ANIMATOR_H__