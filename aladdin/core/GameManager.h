#ifndef __ALADDIN_CORE_GAME_MANAGER_H__
#define __ALADDIN_CORE_GAME_MANAGER_H__

/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "Base.h"
#include "GameObject.h"
#include "Scene.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(GameManager)
  // ==============================================
  // Basic
  // ==============================================
private:
  static GameManager* __instance;

public:
  GameManager();

  ~GameManager();

  static GameManager* get();

  // ===============================================
  // Object Management
  // ===============================================
private:
  bool _destructing;
  long _idCounter;
  std::unordered_map<long, GameObject*> _attachedObjects;

public:
  long newObjectId();

  void attach( GameObject* gameObject );

  void detach( GameObject* gameObject );

  GameObject* getObjectById( long id );

  template <class T>
  T* getObjectTById( long id );

  std::vector<GameObject*> getAllObjectsByName( const std::string& name );

  GameObject* getObjectByName( const std::string& name );

  template <class T>
  T* getObjectTByName( const std::string& name );

  // ===============================================
  // Scene Management
  // ===============================================
private:
  Scene* _runningScene;

public:
  Scene* getRunningScene() const;

  void replaceScene( Scene* scene );
};

// TEMPLATE DEFINITIONS

// ===============================================
// Object Management
// ===============================================

template <class T>
T* GameManager::getObjectTById( long id ) {
  const auto objectIt = _attachedObjects.find( id );
  if ( objectIt == _attachedObjects.end() ) return NULL;

  const auto object = objectIt->second;
  if ( object->isInstanceOf<T>() ) {
    return static_cast<T *>(object);
  }
  return NULL;
}

template <class T>
T* GameManager::getObjectTByName( const std::string& name ) {
  for ( auto& pair : _attachedObjects ) {
    auto object = pair.second;
    if ( object == NULL ) continue;
    if ( object->getName() == name ) {
      if ( object->isInstanceOf<T>() ) {
        return static_cast<T *>(object);
      }
    }
  }
  return NULL;
}
}

#endif //__ALADDIN_CORE_GAME_MANAGER_H__
