#ifndef __ALADDIN_CORE_I_STATE_H__
#define __ALADDIN_CORE_I_STATE_H__

#include "ClassMeta.h"
#include "GameObject.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(IState)
private:
  GameObject* _gameObject;
public:
  virtual IState* checkTransition();
  virtual void onStateEnter();
  virtual void onStateExit();
  virtual void onUpdate(const float dt);

  GameObject* getGameObject() const;

  IState(GameObject* gameObject);
  virtual ~IState();
};
}
#endif //__ALADDIN_CORE_I_STATE_H__
