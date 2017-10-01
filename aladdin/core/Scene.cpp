/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Scene.h"
#include "StdHelper.h"
#include "GameResource.h"
#include "GameManager.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_2(ala::Scene, ala::Initializable, ala::Releasable)

// ================================================
// Basic
// ================================================

Scene::Scene( const std::string& name ) :
  _name( name ) {
  // check initial state
  ALA_ASSERT((!isInitialized()) && (!isInitializing()) && (!isReleased()) && (!isReleasing()));

  TOTAL_SCENE_CREATED++;
}

Scene::~Scene() {
  if ( isInitialized() ) {
    // make sure object released after destruction
    ALA_ASSERT(isReleased());
  }

  TOTAL_SCENE_DELETED++;
}

const std::string& Scene::getName() const {
  return _name;
}

// =================================================
// Events
// =================================================

void Scene::initialize() {
  // make sure scene is not initialized;
  ALA_ASSERT((!isInitializing()) && (!isInitialized()));

  onPreInitialize();

  setToInitializing();

  // TODO: lock mutual exclusive when run in multithreading mode

  // load resources scope with this
  for ( auto resource : GameManager::get()->getResourcesWith( this ) ) {
    resource->load();
  }

  // init game objects
  for ( const auto it : _gameObjects ) {
    auto object = it.second;
    object->initialize();
  }

  setToInitialized();

  onPostInitialize();
}

void Scene::onPreInitialize() {}

void Scene::onPostInitialize() {}

void Scene::update( const float delta ) {
  // make sure scene is initialized and not released
  if ( (!isInitialized()) || (!isInitializing()) || isReleasing() || isReleased() ) return;

  onPreUpdate( delta );

  // update game objects
  for ( const auto it : _gameObjects ) {
    auto object = it.second;
    object->update( delta );
  }

  onPostUpdate( delta );
}

void Scene::onPreUpdate( const float delta ) {}

void Scene::onPostUpdate( const float delta ) {}

void Scene::render() {
  // make sure scene is initialized and not released
  if ( (!isInitialized()) || (!isInitializing()) || isReleasing() || isReleased() ) return;

  onPreRender();

  // render game objects
  for ( const auto it : _gameObjects ) {
    auto object = it.second;
    object->render();
  }

  onPostRender();
}

void Scene::onPreRender() {}

void Scene::onPostRender() {}

void Scene::release() {
  // make sure scene is initialized and not released
  ALA_ASSERT((isInitialized()) && (!isReleasing()) && (!isReleased()));

  onPreRelease();

  setToReleasing();

  // TODO: lock mutual exclusive when run in multithreading mode

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

void Scene::onPreRelease() {}

void Scene::onPostRelease() {}

// ==================================================
// Objects Management
// ==================================================

GameObject* Scene::getGameObject( const long id ) {
  const auto it = _gameObjects.find( id );
  if ( it == _gameObjects.end() ) return NULL;
  return it->second;
}

void Scene::addGameObject( GameObject* gameObject ) {
  if ( isReleasing() || isReleased() ) return;
  if ( gameObject == NULL )return;

  const auto rc = _gameObjects.emplace( gameObject->getId(), gameObject );
  const auto sucess = rc.second;
  if ( sucess ) {
    // TODO: set object's parent
  }
}

void Scene::removeGameObject( GameObject* gameObject ) {
  if ( isReleasing() || isReleased() ) return;
  if ( gameObject == NULL ) return;

  _gameObjects.erase( gameObject->getId() );
}

// =============================================
// Debug memory allocation
// =============================================
long Scene::TOTAL_SCENE_CREATED( 0 );
long Scene::TOTAL_SCENE_DELETED( 0 );
}
