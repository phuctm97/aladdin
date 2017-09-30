#ifndef __ALADDIN_CORE_GAME_OBJECT_H__
#define __ALADDIN_CORE_GAME_OBJECT_H__

/*
* Created on Sep 27th 2017
*/

#include "Base.h"
#include "GameObjectComponent.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(GameObject)
  // =========================================================================
  // Basic
  // =========================================================================
private:
  long _id;
  std::string _name;

public:
  GameObject( const std::string& name = "" );

  ~GameObject();

  long getId() const;

  const std::string& getName() const;

  // =========================================================
  // Events
  // =========================================================
private:
  bool _inited;
  bool _destructed;
  bool _released;

public:
  bool isInited() const;

  bool isReleased() const;

  void init();

protected:
  /**
  * \brief Add Child Objects and Components here, they will be init right after this function return.
  * \return return true if everything were right otherwise return false and the application will crash
  */
  virtual bool onPreInit();

  /**
  * \brief Add special Logic happen after initlization, every children and component in object has been initialized
  * Component added to scene there will be not automatically init, so you have to init them manually
  */
  virtual void onPostInit();

public:
  void update( float delta );

protected:
  /**
  * \brief Happen before object, its children and components were updated
  * \param delta
  */
  virtual void onPreUpdate( float delta );

  /**
  * \brief Happen after object, its children and components were updated
  */
  virtual void onPostUpdate( float delta );

public:
  void render();

protected:
  /**
  * \brief Happen before object, its children and components were rendered
  */
  virtual void onPreRender();

  /**
  * \brief Happen after object, its children and components were rendered
  */
  virtual void onPostRender();

public:
  void release();

protected:
  /**
  * \brief Happen before object, its children and components were released
  * \return true if you want to continue releasing and false if not
  */
  virtual bool onPreRelease();

  /**
  * \brief Happen after object, its children and components were released and destroyed
  */
  virtual void onPostRelease();

  // ========================================================
  // Components
  // ========================================================
private:
  std::vector<GameObjectComponent*> _components;

public:
  void addComponent( GameObjectComponent* component );

  void removeComponent( GameObjectComponent* component );

  GameObjectComponent* getComponent( const std::string& name ) const;

  std::vector<GameObjectComponent*> getAllComponents() const;

  std::vector<GameObjectComponent*> getAllComponents( const std::string& name ) const;

  template <class T>
  T* getComponentT() const;

  template <class T>
  std::vector<T*> getAllComponentTs() const;

  // ==================================================
  // Objects Management
  // ==================================================
private:
  GameObject* _parent;

  std::unordered_map<long, GameObject*> _children;

public:
  GameObject* getParent() const;

  void setParent( GameObject* parent );

  void removeFromParent();

  GameObject* getChild( long id );

  void addChild( GameObject* gameObject );

  void removeChild( GameObject* gameObject );

  // ===========================================================
  // Debug memory allocation
  // ===========================================================
public:
  static long TOTAL_OBJECT_CREATED;
  static long TOTAL_OBJECT_DELETED;
};

// TEMPLATE DEFINITIONS

// ========================================================
// Components
// ========================================================

template <class T>
T* GameObject::getComponentT() const {
  for ( GameObjectComponent* component : _components ) {
    if ( component != NULL && component->isInstanceOf<T>() ) {
      return static_cast<T*>(component);
    }
  }
  return NULL;
}

template <class T>
std::vector<T*> GameObject::getAllComponentTs() const {
  std::vector<T*> ret;

  for ( GameObjectComponent* component : _components ) {
    if ( component != NULL && component->isInstanceOf<T>() ) {
      ret.emplace_back( component );
    }
  }
  return ret;
}
}


#endif //!__ALADDIN_CORE_GAME_OBJECT_H__
