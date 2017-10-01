/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "GameManager.h"

NAMESPACE_ALA
{
// ===========================================
// Basic
// ===========================================

ALA_CLASS_SOURCE_1(ala::GameManager, ala::Releasable)

GameManager* GameManager::__instance( NULL );

GameManager* GameManager::get() {
  if ( __instance == NULL ) {
    __instance = new GameManager();
  }
  return __instance;
}

GameManager::GameManager() :
  _logger( new Logger( "ala::GameManager" ) ),
  _screenWidth( 0 ),
  _screenHeight( 0 ),
  _idCounter( 0 ),
  _runningScene( NULL ) {
  ALA_ASSERT((!isReleased()) && (!isReleasing()));

  _logger->debug( "Created" );
}

GameManager::~GameManager() {
  ALA_ASSERT(isReleased());
  _logger->debug( "Released" );
  delete _logger;
}

void GameManager::release() {
  ALA_ASSERT((!isReleased()) && (!isReleasing()));
  setToReleasing();
  setToReleased();
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
  if ( isReleasing() || isReleased() ) return;

  // insert to attach table by id
  if ( gameObject != NULL ) {
    _attachedObjects.emplace( gameObject->getId(), gameObject );
  }
}

void GameManager::detach( GameObject* gameObject ) {
  if ( isReleasing() || isReleased() ) return;

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
  if ( isReleasing() || isReleased() ) return;

  ALA_ASSERT(scene != NULL);
  ALA_ASSERT(scene != _runningScene);

  if ( _runningScene != NULL ) {
    _runningScene->release();
  }

  _runningScene = scene;
  if ( !_runningScene->isInitialized() ) {
    _runningScene->initialize();
  }
}

// ===============================================
// Resource Management
// ===============================================

void GameManager::attach( GameResource* resource ) {
  if ( isReleasing() || isReleased() ) return;
  if ( resource == NULL ) return;
  auto rc = _attachedResources.emplace( resource->getName(), resource );
  ALA_ASSERT(rc.second == true);
}

void GameManager::detach( GameResource* resource ) {
  if ( isReleasing() || isReleased() ) return;
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
    auto resource = it.second;
    if ( resource->getSceneScope() == scope ) {
      ret.push_back( resource );
    }
  }

  return ret;
}

std::vector<GameResource*> GameManager::getAllResources() {
  std::vector<GameResource*> ret;

  for ( const auto it : _attachedResources ) {
    auto resource = it.second;
    ret.push_back( resource );
  }

  return ret;
}

// ===============================================
// Prefab Management
// ===============================================

void GameManager::registerPrefab( Prefab* prefab ) {
  if ( isReleasing() || isReleased() ) return;
  if ( prefab == NULL ) return;

  auto rc = _registeredPrefabs.emplace( prefab->getName(), prefab );
  ALA_ASSERT(rc.second == true);
}

void GameManager::removePrefab( Prefab* prefab ) {
  if ( isReleasing() || isReleased() ) return;
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
