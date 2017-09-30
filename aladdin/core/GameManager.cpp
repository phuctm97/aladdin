/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "GameManager.h"
#include "Logger.h"

NAMESPACE_ALA
{
// ===========================================
// Basic
// ===========================================

ALA_CLASS_SOURCE_0(ala::GameManager, "ala::GameManager")

GameManager* GameManager::__instance( NULL );

GameManager* GameManager::get() {
  if ( __instance == NULL ) {
    __instance = new GameManager();
  }
  return __instance;
}

GameManager::GameManager() :
  _destructed( false ),
  _released( false ),
  _screenWidth( 0 ),
  _screenHeight( 0 ),
  _idCounter( 0 ),
  _runningScene( NULL ) {
  getLogger()->debug( "Created" );
}

GameManager::~GameManager() {
  _destructed = true;
  ALA_ASSERT(_released);
  getLogger()->debug( "Released" );
}

void GameManager::release() {
  ALA_ASSERT((!_released) && (!_destructed));
  _released = true;
  delete this;
}

// ==============================================
// Game Information
// ==============================================
float GameManager::getScreenWidth() const {
  return _screenWidth;
}

float GameManager::getScreenHeight() const {
  return _screenHeight;
}

// =============================================
// Id Generator
// =============================================
long GameManager::newId() {
  return ++_idCounter;
}

// ==============================================
// Object Management
// ==============================================

void GameManager::attach( GameObject* gameObject ) {
  if ( _destructed || _released ) return;

  // insert to attach table by id
  if ( gameObject != NULL ) {
    _attachedObjects.emplace( gameObject->getId(), gameObject );
  }
}

void GameManager::detach( GameObject* gameObject ) {
  if ( _destructed || _released ) return;

  if ( gameObject != NULL ) {
    _attachedObjects.erase( gameObject->getId() );
  }
}

std::vector<GameObject*> GameManager::getAllObjects() {
  std::vector<GameObject*> ret;

  for ( const auto it : _attachedObjects ) {
    ret.push_back( it.second );
  }

  return ret;
}

GameObject* GameManager::getObjectById( long id ) {
  const auto objectIt = _attachedObjects.find( id );
  if ( objectIt == _attachedObjects.end() ) return NULL;

  const auto object = objectIt->second;
  return object;
}

std::vector<GameObject*> GameManager::getAllObjectsByName( const std::string& name ) {
  std::vector<GameObject*> ret;

  for ( auto& pair : _attachedObjects ) {
    auto object = pair.second;
    if ( object == NULL ) continue;
    if ( object->getName() == name ) {
      ret.emplace_back( object );
    }
  }

  return ret;
}

GameObject* GameManager::getObjectByName( const std::string& name ) {
  for ( auto& pair : _attachedObjects ) {
    const auto object = pair.second;
    if ( object == NULL ) continue;
    if ( object->getName() == name ) {
      return object;
    }
  }
  return NULL;
}

// ==================================================
// Scene Management
// ==================================================

Scene* GameManager::getRunningScene() const {
  return _runningScene;
}

void GameManager::replaceScene( Scene* scene ) {
  if ( _destructed || _released ) return;

  ALA_ASSERT(scene != NULL);
  ALA_ASSERT(scene != _runningScene);

  if ( _runningScene != NULL ) {
    _runningScene->release();
  }

  _runningScene = scene;
  _runningScene->init();
}

// ===============================================
// Resource Management
// ===============================================

void GameManager::attach( GameResource* resource ) {
  if ( _destructed || _released ) return;
  if ( resource == NULL ) return;
  auto rc = _attachedResources.emplace( resource->getName(), resource );
  ALA_ASSERT(rc.second == true);
}

void GameManager::detach( GameResource* resource ) {
  if ( _destructed || _released ) return;
  if ( resource == NULL ) return;
  _attachedResources.erase( resource->getName() );
}

GameResource* GameManager::getResource( const std::string& name ) {
  const auto it = _attachedResources.find( name );
  if ( it == _attachedResources.end() ) return NULL;
  return it->second;
}

std::vector<GameResource*> GameManager::getResourcesWith( Scene* scope ) {
  std::vector<GameResource*> ret;

  for ( const auto it : _attachedResources ) {
    GameResource* resource = it.second;
    if ( resource->getSceneScope() == scope ) {
      ret.push_back( resource );
    }
  }

  return ret;
}

std::vector<GameResource*> GameManager::getAllResources() {
  std::vector<GameResource*> ret;

  for ( const auto it : _attachedResources ) {
    GameResource* resource = it.second;
    ret.push_back( resource );
  }

  return ret;
}

// ===============================================
// Prefab Management
// ===============================================

void GameManager::registerPrefab( Prefab* prefab ) {
  if ( _destructed || _released ) return;
  if ( prefab == NULL ) return;

  auto rc = _registeredPrefabs.emplace( prefab->getName(), prefab );
  ALA_ASSERT(rc.second == true);
}

void GameManager::removePrefab( Prefab* prefab ) {
  if ( _destructed || _released ) return;
  if ( prefab == NULL ) return;
  _registeredPrefabs.erase( prefab->getName() );
}

Prefab* GameManager::getPrefab( const std::string& name ) {
  const auto it = _registeredPrefabs.find( name );
  if ( it == _registeredPrefabs.end() ) return NULL;
  return it->second;
}

std::vector<Prefab*> GameManager::getAllPrefabs() {
  std::vector<Prefab*> ret;

  for ( const auto it : _registeredPrefabs ) {
    ret.push_back( it.second );
  }

  return ret;
}
}
