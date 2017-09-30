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
  int _releasing;

public:
  bool isInited() const;

  bool isReleased() const;

  bool isReleasing() const;

  void init();

protected:
  virtual bool onPreInit();

  virtual void onPostInit();

public:
  void update( float delta );

protected:
  virtual void onPreUpdate( float delta );

  virtual void onPostUpdate( float delta );

public:
  void render();

protected:
  virtual void onPreRender();

  virtual void onPostRender();

public:
  void release();

protected:
  virtual bool onPreRelease();

  virtual void onPostRelease();

  // ========================================================
  // Components
  // ========================================================
private:
  std::vector<GameObjectComponent*> _components;

public:
  void attach( GameObjectComponent* component );

  void detach( GameObjectComponent* component );

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
