#ifndef __ALADDIN_CORE_GAME_OBJECT_COMPONENT_H__
#define __ALADDIN_CORE_GAME_OBJECT_COMPONENT_H__

/*
 * Created by phuctm97 on Sep 27th 2017
 */

#include "ClassMeta.h"

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

  virtual ~GameObjectComponent();

  const std::string& getName() const;

  GameObject* getGameObject() const;

  // ==================================================
  // Events
  // ==================================================
private:
  bool _inited;
  bool _destructed;
  bool _released;

protected:
  /**
   * \brief Happen when component is initialized
   * \return true to continue initlization or false to stop it and crash the application
   */
  virtual bool onInit();


  /**
   * \brief Happen when component is updated
   * \param delta 
   */
  virtual void onUpdate( float delta );


  /**
   * \brief Happen when component is rendered
   */
  virtual void onRender();


  /**
   * \brief Happen when component is released
   */
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
