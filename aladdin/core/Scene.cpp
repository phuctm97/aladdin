/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Scene.h"
#include "StdHelper.h"
#include "GameResource.h"
#include "GameManager.h"
#include "../2d/2dMacros.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_2(ala::Scene, ala::Initializable, ala::Releasable)

// ================================================
// Basic
// ================================================

Scene::Scene(): _toReleaseInNextFrame( false ), _gameObjectInLock( false ) {
  // check initial state
  ALA_ASSERT((!isInitialized()) && (!isInitializing()) && (!isReleased()) && (!isReleasing()));

  TOTAL_SCENES_CREATED++;
}

Scene::~Scene() {
  if ( isInitialized() ) {
    // make sure object released after destruction
    ALA_ASSERT(isReleased());
  }

  TOTAL_SCENES_DELETED++;
}

// =================================================
// Events
// =================================================

void Scene::initialize() {
  // make sure scene is not initialized;
  ALA_ASSERT((!isInitializing()) && (!isInitialized()));

  // required framework objects
  ala::GameManager::get()->getPrefab(ALA_MAIN_CAMERA)->instantiate(ALA_MAIN_CAMERA);

  onPreInitialize();

  setToInitializing();

  // TODO: lock mutual exclusive when run in multithreading mode

  // load resources scope with this
  for ( auto resource : GameManager::get()->getResourcesWith( this ) ) {
    if ( !resource->isLoaded() ) {
      resource->load();
    }
  }

  // init game objects
  for ( const auto it : _gameObjects ) {
    auto object = it.second;

    if ( !object->isInitialized() ) {
      object->initialize();
    }
  }

  setToInitialized();

  onPostInitialize();
}

void Scene::onPreInitialize()
{
  
}

void Scene::onPostInitialize() {}

void Scene::update( const float delta ) {
  if ( isReleasing() || isReleased() ) return;

  // update to release in next frame
  if ( _toReleaseInNextFrame ) {
    release();
    _toReleaseInNextFrame = false;
    return;
  }

  // update actions
  updateAddAndRemoveGameObjects();

  if ( !isInitialized() ) return;

  lockGameObjects();

  onPreUpdate( delta );

  // update game objects
  for ( const auto it : _gameObjects ) {
    auto object = it.second;
    object->update( delta );
  }

  onPostUpdate( delta );

  unlockGameObjects();
}

void Scene::onPreUpdate( const float delta ) {}

void Scene::onPostUpdate( const float delta ) {}

void Scene::render() {
  // make sure scene is initialized and not being released
  if ( (!isInitialized()) || isReleasing() || isReleased() ) return;

  lockGameObjects();

  onPreRender();

  // render game objects
  for ( const auto it : _gameObjects ) {
    auto object = it.second;
    object->render();
  }

  onPostRender();

  unlockGameObjects();
}

void Scene::onPreRender() {}

void Scene::onPostRender() {}

void Scene::release() {
  // check lock
  if ( _gameObjectInLock ) {
    releaseInNextFrame();
    return;
  }

  // make sure scene is initialized and not released
  ALA_ASSERT(isInitialized() && (!isReleasing()) && (!isReleased()));

  onPreRelease();

  setToReleasing();

  // release game objects
  std::vector<GameObject*> gameObjectsToRelease;
  for ( const auto it : _gameObjects ) {
    auto object = it.second;
    object->release();
  }

  // release resources scope with this
  for ( auto resouce : GameManager::get()->getResourcesWith( this ) ) {
    resouce->release();
  }

  setToReleased();

  onPostRelease();

  // destroy
  delete this;
}

void Scene::releaseInNextFrame() {
  // make sure scene is initialized and not released
  ALA_ASSERT(isInitialized() && (!isReleasing()) && (!isReleased()));
  _toReleaseInNextFrame = true;
}

void Scene::onPreRelease() {}

void Scene::onPostRelease() {}

// ==================================================
// Objects Management
// ==================================================

GameObject* Scene::getGameObject( const long id ) const {
  const auto it = _gameObjects.find( id );
  if ( it == _gameObjects.end() ) return NULL;
  return it->second;
}

GameObject* Scene::getMainCamera() const {
  for(const auto it: _gameObjects) {
    const auto object = it.second;
    if (object->getName() == ALA_MAIN_CAMERA) return object;
  }
  return NULL;
}

void Scene::addGameObject( GameObject* gameObject ) {
  // check lock
  if ( _gameObjectInLock ) {
    addGameObjectInNextFrame( gameObject );
    return;
  }

  if ( isReleasing() || isReleased() ) return;
  if ( gameObject == NULL ) return;
  doAddGameObject( gameObject );
}

void Scene::addGameObjectInNextFrame( GameObject* gameObject ) {
  if ( isReleasing() || isReleased() ) return;
  if ( gameObject == NULL ) return;
  _gameObjectsToAddInNextFrame.push_back( gameObject );
}

void Scene::removeGameObject( GameObject* gameObject ) {
  // check lock
  if ( _gameObjectInLock ) {
    removeGameObjectInNextFrame( gameObject );
    return;
  }

  if ( isReleasing() || isReleased() ) return;
  if ( gameObject == NULL ) return;
  doRemoveGameObject( gameObject );
}

void Scene::removeGameObjectInNextFrame( GameObject* gameObject ) {
  if ( isReleasing() || isReleased() ) return;
  if ( gameObject == NULL ) return;
  _gameObjectsToRemoveInNextFrame.push_back( gameObject );
}

void Scene::lockGameObjects() {
  _gameObjectInLock = true;
}

void Scene::unlockGameObjects() {
  _gameObjectInLock = false;
}

void Scene::updateAddAndRemoveGameObjects() {
  for ( auto object : _gameObjectsToAddInNextFrame ) {
    doAddGameObject( object );
  }
  _gameObjectsToAddInNextFrame.clear();

  for ( auto object : _gameObjectsToRemoveInNextFrame ) {
    doRemoveGameObject( object );
  }
  _gameObjectsToRemoveInNextFrame.clear();
}

void Scene::doAddGameObject( GameObject* gameObject ) {
  _gameObjects.emplace( gameObject->getId(), gameObject );
}

void Scene::doRemoveGameObject( GameObject* gameObject ) {
  _gameObjects.erase( gameObject->getId() );
}

// =============================================
// Debug memory allocation
// =============================================
long Scene::TOTAL_SCENES_CREATED( 0 );
long Scene::TOTAL_SCENES_DELETED( 0 );
}
