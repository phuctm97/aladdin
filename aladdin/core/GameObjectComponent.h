#ifndef __ALADDIN_CORE_GAME_OBJECT_COMPONENT_H__
#define __ALADDIN_CORE_GAME_OBJECT_COMPONENT_H__

/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "Base.h"

NAMESPACE_ALA
{
class GameObject;

ALA_CLASS_HEADER_0(GameObjectComponent)
  // =====================================================
  // Basic
  // =====================================================
private:
  std::string _name;
  GameObject* _gameObject;

public:
  GameObjectComponent( GameObject* gameObject, const std::string& name = "" );

  ~GameObjectComponent();

  const std::string& getName() const;

  GameObject* getGameObject() const;

  // ==================================================
  // Events
  // ==================================================
private:
  bool _inited;
  bool _released;

protected:
  virtual bool onInit();

  virtual void onUpdate( float delta );

  virtual void onRender();

  virtual void onRelease();

public:
  bool isInited() const;

  bool isReleased() const;

  void init();

  void update( float delta );

  void render();

  void release();
};
}

#endif //__ALADDIN_CORE_GAME_OBJECT_COMPONENT_H__
