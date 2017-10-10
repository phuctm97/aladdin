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

  AnimationAction* _currentAction;
  std::vector<Rect>::const_iterator _frameIterator;

  float _elapsedTime;
  float _interval;

  bool _isPlaying;

protected:
  virtual ~Animator();

  virtual void onUpdate(const float delta);
public:
  Animator(GameObject* gameObject, const std::string &entryAction, Animation* animationName = NULL, float interval = 1000, std::string name = "");
  Animator(GameObject* gameObject, const std::string &entryAction, const std::string &animationResourceName = "", float interval = 1000, std::string name = "");

  void setAction(const std::string& actionName);
  const std::string& getAction() const;

  void setInterval(const float interval);
  Rect getCurrentFrame() const;

  void pause();
  void playNext();
  void play();
  void playFromStart();
};
}
#endif //!__ALADDIN_2D_ANIMATOR_H__