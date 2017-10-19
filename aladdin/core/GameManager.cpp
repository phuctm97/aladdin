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
  _logger( "ala::GameManager" ),
  _screenWidth( 0 ),
  _screenHeight( 0 ),
  _idCounter( 0 ),
  _runningScene( NULL ),
  _sceneToReplaceInNextFrame( NULL ),
  _globalMessenger( new Messenger() ) {
  ALA_ASSERT((!isReleased()) && (!isReleasing()));
  _logger.info( "Created" );
}

GameManager::~GameManager() {
  ALA_ASSERT(isReleased());
  _logger.info( "Released" );
}

void GameManager::update( const float delta ) {
  if ( isReleasing() || isReleased() ) return;

  updateRunningScene();
}

void GameManager::release() {
  ALA_ASSERT((!isReleased()) && (!isReleasing()));

  setToReleasing();

  // release messenger
  _globalMessenger->release();

  setToReleased();

  // destroy
  delete this;
}

void GameManager::onBackgroundToForeground() {}

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
  if ( gameObject == NULL ) return;
  _attachedObjects.emplace( gameObject->getId(), gameObject );
}

void GameManager::detach( GameObject* gameObject ) {
  if ( isReleasing() || isReleased() ) return;
  if ( gameObject == NULL ) return;
  _attachedObjects.erase( gameObject->getId() );
}

std::vector<GameObject*> GameManager::getAllObjects() {
  std::vector<GameObject*> ret;

  for ( const auto it : _attachedObjects ) {
    ret.push_back( it.second );
  }

  return ret;
}

GameObject* GameManager::getObjectById( const long id ) {
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
  if ( scene == NULL ) return;
  if ( scene == _runningScene ) return;
  doReplaceScene( scene );
}

void GameManager::replaceSceneInNextFrame( Scene* scene ) {
  if ( isReleasing() || isReleased() ) return;
  if ( scene == NULL ) return;
  if ( scene == _runningScene ) return;
  _sceneToReplaceInNextFrame = scene;
}

void GameManager::updateRunningScene() {
  if ( _sceneToReplaceInNextFrame == NULL ) return;
  doReplaceScene( _sceneToReplaceInNextFrame );
  _sceneToReplaceInNextFrame = NULL;
}

void GameManager::doReplaceScene( Scene* scene ) {
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

  // make sure there is no duplicate resources
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

  // make sure there is no duplicate prefab
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

// ===============================================
// Global messenger
// ===============================================

Messenger* GameManager::getGlobalMessenger() const {
  return _globalMessenger;
}

void GameManager::addLayer( const std::string& layer ) {
  if ( isReleasing() || isReleased() ) return;
  const auto it = _layers.find( layer );
  if ( it != _layers.end() ) return;
  _layers.emplace( layer, _layers.size() + 1 );
}

int GameManager::getLayerIndex( const std::string& layer ) {
  if ( isReleasing() || isReleased() ) return -1;
  const auto it = _layers.find( layer );
  if ( it == _layers.end() ) {
    addLayer( layer );
    return _layers[layer];
  }
  return it->second;
}
}
