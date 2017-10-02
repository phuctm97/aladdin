#ifndef __ALADDIN_CORE_GAME_MANAGER_H__
#define __ALADDIN_CORE_GAME_MANAGER_H__

/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "GameObject.h"
#include "Scene.h"
#include "GameResource.h"
#include "Prefab.h"
#include "Logger.h"
#include "Messenger.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(GameManager, ala::Releasable)
  // ==============================================
  // Basic
  // ==============================================
  friend class Application;

private:
  static GameManager* __instance;
  Logger _logger;

public:
  GameManager();

  virtual ~GameManager();

  static GameManager* get();

  void release() override;

  // ===============================================
  // Game Information
  // ===============================================
private:
  float _screenWidth;
  float _screenHeight;

public:
  float getScreenWidth() const;
  float getScreenHeight() const;

  // ===============================================
  // Id Generator
  // ===============================================
private:
  long _idCounter;

public:
  long newId();

  // ===============================================
  // Object Management
  // ===============================================
private:
  std::unordered_map<long, GameObject*> _attachedObjects;

public:
  void attach( GameObject* gameObject );

  void detach( GameObject* gameObject );

  std::vector<GameObject*> getAllObjects();

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

  // ===============================================
  // Resource Management
  // ===============================================
private:
  std::unordered_map<std::string, GameResource*> _attachedResources;

public:
  void attach( GameResource* resource );

  void detach( GameResource* resource );

  GameResource* getResource( const std::string& name );

  std::vector<GameResource*> getResourcesWith( Scene* scope );

  std::vector<GameResource*> getAllResources();

  // ===============================================
  // Prefab Management
  // ===============================================
private:
  std::unordered_map<std::string, Prefab*> _registeredPrefabs;

public:
  void registerPrefab( Prefab* prefab );

  void removePrefab( Prefab* prefab );

  Prefab* getPrefab( const std::string& name );

  std::vector<Prefab*> getAllPrefabs();

// ===============================================
// Global messenger
// ===============================================
private:
  Messenger* _globalMessenger;
public:
  Messenger* getGlobalMessenger() const;
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
  if ( ALA_IS_INSTANCE_OF( object, T) ) {
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
      if ( ALA_IS_INSTANCE_OF(object, T) ) {
        return static_cast<T *>(object);
      }
    }
  }
  return NULL;
}
}

#endif //__ALADDIN_CORE_GAME_MANAGER_H__
