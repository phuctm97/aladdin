#include "Scene.h"
#include "StdHelper.h"
#include "GameResource.h"
#include "GameManager.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0(ala::Scene, "ala::Scene")

// ================================================
// Basic
// ================================================

Scene::Scene( const std::string& name ) :
  _name( name ),
  _inited( false ),
  _destructed( false ),
  _released( false ) {
  TOTAL_SCENE_CREATED++;
}

Scene::~Scene() {
  _destructed = true;

  if ( _inited ) {
    // make sure object released before destruction
    ALA_ASSERT(_released);
  }

  TOTAL_SCENE_DELETED++;
}

const std::string& Scene::getName() const {
  return _name;
}


// =================================================
// Events
// =================================================

bool Scene::isInited() const {
  return _inited;
}

bool Scene::isReleased() const {
  return _released;
}

void Scene::init() {
  // make sure scene is not initialized;
  ALA_ASSERT(!_inited);

  // child pre init
  if ( !onPreInit() ) {
    return;
  }

  _inited = true;

  // load Scene resources
  for ( GameResource* resource : GameManager::get()->getResourcesWith( this ) ) {
    resource->load();
  }

  // init child object
  for ( const auto it : _gameObjects ) {
    it.second->init();
  }

  // child post init
  onPostInit();
}

bool Scene::onPreInit() {
  return true;
}

void Scene::onPostInit() {}

void Scene::update( float delta ) {
  // make sure scene is initialized and not released
  if ( (!_inited) || (_released) )
    return;

  onPreUpdate( delta );

  // TODO: scene update here
  for ( const auto it : _gameObjects ) {
    it.second->update( delta );
  }

  onPostUpdate( delta );
}

void Scene::onPreUpdate( float delta ) {}

void Scene::onPostUpdate( float delta ) {}

void Scene::render() {
  // make sure scene is initialized and not released
  if ( (!_inited) || (_released) )
    return;

  onPreRender();

  for ( const auto it : _gameObjects ) {
    it.second->render();
  }

  onPostRender();
}

void Scene::onPreRender() {}

void Scene::onPostRender() {}

void Scene::release() {
  // make sure scene is initialized and not released
  ALA_ASSERT(_inited && (!_released) && (!_destructed));

  // Child PreRelease
  if ( !onPreRelease() ) {
    return;
  }

  _released = true;

  // Scene Release

  // release game object
  std::vector<GameObject*> gameObjectsToRelease;
  for ( const auto it : _gameObjects ) {
    gameObjectsToRelease.push_back( it.second );
  }
  _gameObjects.clear();
  for ( GameObject* gameObject : gameObjectsToRelease ) {
    gameObject->release();
  }

  // release resource scope with this
  for ( GameResource* resouce : GameManager::get()->getResourcesWith( this ) ) {
    resouce->release();
  }

  // child post release
  onPostRelease();

  // delete self
  delete this;
}

bool Scene::onPreRelease() {
  return true;
}

void Scene::onPostRelease() {}

// ==================================================
// Objects Management
// ==================================================

GameObject* Scene::getGameObject( long id ) {
  const auto it = _gameObjects.find( id );
  if ( it == _gameObjects.end() ) return NULL;
  return it->second;
}

void Scene::addGameObject( GameObject* gameObject ) {
  if ( _destructed || _released ) return;
  if ( gameObject == NULL )return;

  const auto rc = _gameObjects.emplace( gameObject->getId(), gameObject );

  const bool sucess = rc.second;
  if ( sucess ) {
    gameObject->setParent( NULL );
  }
}

void Scene::removeGameObject( GameObject* gameObject ) {
  if ( _destructed || _released ) return;
  if ( gameObject == NULL ) return;

  _gameObjects.erase( gameObject->getId() );
}

// =============================================
// Debug memory allocation
// =============================================
long Scene::TOTAL_SCENE_CREATED( 0 );
long Scene::TOTAL_SCENE_DELETED( 0 );
}
