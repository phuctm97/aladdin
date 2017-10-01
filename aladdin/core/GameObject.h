#ifndef __ALADDIN_CORE_GAME_OBJECT_H__
#define __ALADDIN_CORE_GAME_OBJECT_H__

/*
* Created on Sep 27th 2017
*/

#include "GameObjectComponent.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_2(GameObject, ala::Initializable, ala::Releasable)
  // =========================================================================
  // Basic
  // =========================================================================
private:
  long _id;
  std::string _name;

public:
  GameObject( const std::string& name = "" );

  virtual ~GameObject();

  long getId() const;

  const std::string& getName() const;

  // =========================================================
  // Events
  // =========================================================
public:
  void initialize() override;

  void update( const float delta );

  void render();

  void release() override;

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
    if ( component != NULL && ALA_IS_INSTANCE_OF(component, T) ) {
      return static_cast<T*>(component);
    }
  }
  return NULL;
}

template <class T>
std::vector<T*> GameObject::getAllComponentTs() const {
  std::vector<T*> ret;

  for ( GameObjectComponent* component : _components ) {
    if ( component != NULL && ALA_IS_INSTANCE_OF( component, T) ) {
      ret.emplace_back( component );
    }
  }
  return ret;
}
}


#endif //!__ALADDIN_CORE_GAME_OBJECT_H__
