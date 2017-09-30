#include "Scene.h"
#include "StdHelper.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0(ala::Scene, "ala::Scene")

// ================================================
// Basic
// ================================================

Scene::Scene( const std::string& name ) :
  _name( name ),
  _inited( false ),
  _releasing( 0 ) {
  TOTAL_SCENE_CREATED++;
}

Scene::~Scene() {
  _releasing = 1;

  if ( _inited && (!isReleased()) ) {
    release();

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

bool Scene::isInited() const {
  return _inited;
}

bool Scene::isReleasing() const {
  return _releasing == 1;
}

bool Scene::isReleased() const {
  return _releasing == 2;
}

void Scene::init() {
  // make sure scene is not initialized;
  ALA_ASSERT(!_inited);

  // TODO: subscriber pre init

  // child pre init
  if ( !onPreInit() ) {
    _inited = false;
    return;
  }


  // TODO: scene init here
  for ( const auto it : _gameObjects ) {
    it.second->init();
  }
  _inited = true;


  // make sure scene initialized after initialization
  ALA_ASSERT(_inited);


  // child post init
  onPostInit();

  // TODO: client subscriber post init
}

bool Scene::onPreInit() {
  return true;
}

void Scene::onPostInit() {}

void Scene::update( float delta ) {
  // make sure scene is initialized and not released
  if ( (!_inited) || (_releasing > 0) )
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
  if ( (!_inited) || (_releasing > 0) )
    return;

  onPreRender();

  // TODO: scene update here
  for ( const auto it : _gameObjects ) {
    it.second->render();
  }

  onPostRender();
}

void Scene::onPreRender() {}

void Scene::onPostRender() {}

void Scene::release() {
  // make sure scene is initialized and not released
  ALA_ASSERT(_inited);
  ALA_ASSERT(!isReleased());

  _releasing = 1;

  ALA_ASSERT(isReleasing());
  // TODO: client subscriber pre release

  // child pre release
  if ( !onPreRelease() ) return;

  // TODO: game object release here
  for ( const auto it : _gameObjects ) {
    GameObject* gameObject = it.second;
    delete gameObject;
  }
  _gameObjects.clear();

  ALA_ASSERT(_gameObjects.empty());
  _releasing = 2;

  // make sure object released after release
  ALA_ASSERT(isReleased());


  // child post release
  onPostRelease();

  // TODO: client subscriber post release
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
  if ( _releasing > 0 ) return;
  if ( gameObject == NULL )return;

  _gameObjects.emplace( gameObject->getId(), gameObject );
  gameObject->setParent( NULL );
}

void Scene::removeGameObject( GameObject* gameObject ) {
  if ( _releasing > 0 ) return;
  if ( gameObject == NULL ) return;

  _gameObjects.erase( gameObject->getId() );
}

// =============================================
// Debug memory allocation
// =============================================
long Scene::TOTAL_SCENE_CREATED( 0 );
long Scene::TOTAL_SCENE_DELETED( 0 );
}
