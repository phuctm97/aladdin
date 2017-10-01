#ifndef __ALADDIN_CORE_GAME_OBJECT_COMPONENT_H__
#define __ALADDIN_CORE_GAME_OBJECT_COMPONENT_H__

/*
 * Created by phuctm97 on Sep 27th 2017
 */

#include "ClassMeta.h"
#include "Initializable.h"
#include "Releasable.h"

NAMESPACE_ALA
{
class GameObject;

ALA_CLASS_HEADER_2(GameObjectComponent, ala::Initializable, ala::Releasable)
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
protected:
  /**
   * \brief Happen when component is initialized
   * \return true to continue initlization or false to stop it and crash the application
   */
  virtual void onInitialize();


  /**
   * \brief Happen when component is updated
   * \param delta 
   */
  virtual void onUpdate( const float delta );


  /**
   * \brief Happen when component is rendered
   */
  virtual void onRender();


  /**
   * \brief Happen when component is released
   */
  virtual void onRelease();

public:
  void initialize() override;

  void update( const float delta );

  void render();

  void release() override;
};
}

#endif //__ALADDIN_CORE_GAME_OBJECT_COMPONENT_H__
