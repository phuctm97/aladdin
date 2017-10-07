#ifndef __ISTATE_H__
#define __ISTATE_H__

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
#endif //__ISTATE_H__
