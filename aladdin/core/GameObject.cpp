/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "GameObject.h"
#include "GameManager.h"
#include "StdHelper.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_2(ala::GameObject, ala::Initializable, ala::Releasable)

GameObject::GameObject( Scene* parentScene, const std::string& name )
  : _id( GameManager::get()->newId() ),
    _name( name ),
    _parentScene( parentScene ),
    _messenger( new Messenger() ) {
  // check initial state
  ALA_ASSERT((!isInitialized()) && (!isInitializing()) && (!isReleased()) && (!isReleasing()));

  // default components
  _transform = new Transform( this );

  // attach to GameManager
  GameManager::get()->attach( this );

  // make sure parent scene is not null
  ALA_ASSERT(_parentScene != NULL);

  // attach to Scene
  _parentScene->addGameObject( this );

  // for debug memory allocation
  TOTAL_OBJECTS_CREATED++;
}

GameObject::GameObject( GameObject* parentObject, const std::string& name )
  : _id( GameManager::get()->newId() ),
    _name( name ),
    _parentScene( NULL ),
    _messenger( new Messenger() ) {

  // check initial state
  ALA_ASSERT((!isInitialized()) && (!isInitializing()) && (!isReleased()) && (!isReleasing()));

  // make sure parent object is not null
  ALA_ASSERT(parentObject != NULL);

  // default components
  _transform = new Transform( this, parentObject->getTransform() );

  // attach to GameManager
  GameManager::get()->attach( this );

  // for debug memory allocation
  TOTAL_OBJECTS_CREATED++;
}

GameObject::~GameObject() {
  if ( isInitialized() ) {
    // make sure object released after destruction
    ALA_ASSERT(isReleased());
  }

  // for debug memory allocation
  TOTAL_OBJECTS_DELETED++;
}

long GameObject::getId() const {
  return _id;
}

const std::string& GameObject::getName() const {
  return _name;
}

Scene* GameObject::getParentScene() const {
  return _parentScene;
}

// ===========================================================
// Events
// ===========================================================

void GameObject::initialize() {
  // make sure object is not initialized;
  ALA_ASSERT((!isInitialized()) && (!isInitializing()));

  setToInitializing();

  // TODO: lock mutual exclusive when run in multithreading mode

  // init components
  for ( auto component : _components ) {
    component->initialize();
  }

  setToInitialized();
}

void GameObject::update( const float delta ) {
  // make sure object is initialized and not released
  if ( (!isInitialized()) || isReleasing() || isReleased() ) return;

  // update components
  for ( auto component : _components ) {
    component->update( delta );
  }
}

void GameObject::render() {
  // make sure object is initialized and not released
  if ( (!isInitialized()) || isReleasing() || isReleased() ) return;

  // render components
  for ( auto component : _components ) {
    component->render();
  }
}

void GameObject::release() {
  // make sure object is initialized and not released
  ALA_ASSERT((isInitialized()) && (!isReleasing()) && (!isReleased()));

  setToReleasing();

  // TODO: lock mutual exclusive when run in multithreading mode

  // release components
  for ( auto component : _components ) {
    component->release();
  }

  // remove from parent scene
  if ( _parentScene != NULL ) {
    _parentScene->removeGameObject( this );
  }

  // release messenger
  _messenger->release();

  // detach from GameManager
  GameManager::get()->detach( this );

  setToReleased();

  // destroy
  delete this;
}

// ============================================================
// Components
// ============================================================

void GameObject::addComponent( GameObjectComponent* component ) {
  if ( isReleasing() || isReleased() ) return;
  if ( component == NULL ) return;
  if ( StdHelper::vectorContain<GameObjectComponent*>( _components, component ) ) return;
  _components.emplace_back( component );
}

void GameObject::removeComponent( GameObjectComponent* component ) {
  if ( isReleasing() || isReleased() ) return;
  if ( component == NULL ) return;

  // prevent remove default components
  ALA_ASSERT(isDefaultComponents( component ));
  StdHelper::vectorErase<GameObjectComponent*>( _components, component );
}

GameObjectComponent* GameObject::getComponent( const std::string& name ) const {
  for ( auto component : _components ) {
    if ( component != NULL && component->getName() == name ) {
      return component;
    }
  }
  return NULL;
}

std::vector<GameObjectComponent*> GameObject::getAllComponents( const std::string& name ) const {
  std::vector<GameObjectComponent*> ret;

  for ( auto component : _components ) {
    if ( component != NULL && component->getName() == name ) {
      ret.emplace_back( component );
    }
  }

  return ret;
}

std::vector<GameObjectComponent*> GameObject::getAllComponents() const {
  return _components;
}

// ========================================================
// Default components
// ========================================================

bool GameObject::isDefaultComponents( GameObjectComponent* component ) {
  if ( component == _transform ) return true;
  return false;
}

Transform* GameObject::getTransform() const {
  return _transform;
}

// ===========================================================
// Messenger
// ===========================================================

Messenger* GameObject::getMessenger() const {
  return _messenger;
}

// ============================================
// Debug memory allocation
// ============================================

long GameObject::TOTAL_OBJECTS_CREATED( 0 );

long GameObject::TOTAL_OBJECTS_DELETED( 0 );
}
