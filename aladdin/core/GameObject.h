#ifndef __ALADDIN_CORE_GAME_OBJECT_H__
#define __ALADDIN_CORE_GAME_OBJECT_H__

/*
* Created on Sep 27th 2017
*/

#include "GameObjectComponent.h"
#include "Transform.h"

NAMESPACE_ALA
{
class Scene;

ALA_CLASS_HEADER_2(GameObject, ala::Initializable, ala::Releasable)
  // =========================================================================
  // Basic
  // =========================================================================
private:
  long _id;
  std::string _name;
  Scene* _parentScene;

public:
  /**
   * \brief Create a game object, attach to game manager and attach to parent scene
   */
  GameObject( Scene* parentScene, const std::string& name = "" );

  /**
   * \brief Create a game object, attach to game manager and attach its transform to "parentObject"'s transform 
   */
  GameObject( GameObject* parentObject, const std::string& name = "" );

  virtual ~GameObject();

  long getId() const;

  const std::string& getName() const;

  Scene* getParentScene() const;

  // =========================================================
  // Events
  // =========================================================
public:
  void initialize() override;

  void update( const float delta );

  void render();

  /**
   * \brief Release and destroy game object, automatically removed from parent scene or "parent object" and detached from game manager
   */
  void release() override;

  // ========================================================
  // Components
  // ========================================================
private:
  std::vector<GameObjectComponent*> _components;

public:
  /**
   * \brief Attach a component to game object, this will not change component's game object, you should not call this method directly
   * \param component Component to attach
   */
  void addComponent( GameObjectComponent* component );


  /**
   * \brief Detach a component from game object, this will not release component, you will have to delete in your own when it's necessary
   * \param component Component to detach
   */
  void removeComponent( GameObjectComponent* component );

  GameObjectComponent* getComponent( const std::string& name ) const;

  std::vector<GameObjectComponent*> getAllComponents() const;

  std::vector<GameObjectComponent*> getAllComponents( const std::string& name ) const;

  template <class T>
  T* getComponentT() const;

  template <class T>
  std::vector<T*> getAllComponentTs() const;

  // ========================================================
  // Default components
  // ========================================================
private:
  Transform* _transform;

  bool isDefaultComponents( GameObjectComponent* component );

public:
  Transform* getTransform() const;

  // ===========================================================
  // Debug memory allocation
  // ===========================================================
public:
  static long TOTAL_OBJECTS_CREATED;
  static long TOTAL_OBJECTS_DELETED;
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
