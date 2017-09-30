/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "GameObject.h"
#include "GameManager.h"
#include "StdHelper.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0(ala::GameObject, "ala::GameObject")

GameObject::GameObject( const std::string& name )
  : _id( GameManager::get()->newId() ),
    _name( name ),
    _inited( false ),
    _destructed( false ),
    _released( false ),
    _parent( NULL ) {
  // attach to GameManager
  GameManager::get()->attach( this );

  // for debug memory allocation
  TOTAL_OBJECT_CREATED++;
}

GameObject::~GameObject() {
  _destructed = true;

  if ( _inited ) {
    // make sure object released after destruction
    ALA_ASSERT(_released);
  }

  // for debug memory allocation
  TOTAL_OBJECT_DELETED++;
}

long GameObject::getId() const {
  return _id;
}

const std::string& GameObject::getName() const {
  return _name;
}

// ===========================================================
// Events
// ===========================================================

bool GameObject::isInited() const {
  return _inited;
}

bool GameObject::isReleased() const {
  return _released;
}

void GameObject::init() {
  // make sure object is not initialized;
  ALA_ASSERT(!_inited);

  // child pre init
  if ( !onPreInit() ) {
    return;
  }

  _inited = true;

  for ( GameObjectComponent* component : _components ) {
    component->init();
  }

  for ( const auto it : _children ) {
    it.second->init();
  }

  // child post init
  onPostInit();
}

bool GameObject::onPreInit() {
  return true;
}

void GameObject::onPostInit() {}

void GameObject::update( float delta ) {
  // make sure object is initialized and not released
  if ( (!_inited) || (_released) )
    return;

  onPreUpdate( delta );

  for ( GameObjectComponent* component : _components ) {
    component->update( delta );
  }

  for ( const auto it : _children ) {
    it.second->update( delta );
  }

  onPostUpdate( delta );
}

void GameObject::onPreUpdate( float delta ) {}

void GameObject::onPostUpdate( float delta ) {}

void GameObject::render() {
  // make sure object is initialized and not released
  if ( (!_inited) || (_released) )
    return;

  onPreRender();

  for ( GameObjectComponent* component : _components ) {
    component->render();
  }

  for ( const auto it : _children ) {
    it.second->render();
  }

  onPostRender();
}

void GameObject::onPreRender() {}

void GameObject::onPostRender() {}

void GameObject::release() {
  // make sure object is initialized and not released
  ALA_ASSERT(_inited && (!_released) && (!_destructed));

  // child pre release
  if ( !onPreRelease() ) return;

  _released = true;

  std::vector<GameObject*> gameObjectsToRelease;
  for ( const auto it : _children ) {
    gameObjectsToRelease.push_back( it.second );
  }
  _children.clear();
  for ( GameObject* object : gameObjectsToRelease ) {
    object->release();
  }

  std::vector<GameObjectComponent*> componentsToRelease;
  for ( GameObjectComponent* component : _components ) {
    componentsToRelease.push_back( component );
  }
  _components.clear();
  for ( GameObjectComponent* component : componentsToRelease ) {
    component->release();
  }

  // child post release
  onPostRelease();

  // remove from parent
  removeFromParent();

  // detach from GameManager
  GameManager::get()->detach( this );

  delete this;
}

bool GameObject::onPreRelease() {
  return true;
}

void GameObject::onPostRelease() {}

// ============================================================
// Components
// ============================================================

void GameObject::addComponent( GameObjectComponent* component ) {
  if ( _destructed || _released ) return;

  if ( component == NULL )
    return;

  if ( !StdHelper::vectorContain<GameObjectComponent*>( _components, component ) ) {
    _components.emplace_back( component );
  }
}

void GameObject::removeComponent( GameObjectComponent* component ) {
  if ( _destructed || _released ) return;

  if ( component == NULL )
    return;

  StdHelper::vectorErase<GameObjectComponent*>( _components, component );
}

GameObjectComponent* GameObject::getComponent( const std::string& name ) const {
  for ( GameObjectComponent* component : _components ) {
    if ( component != NULL && component->getName() == name ) {
      return component;
    }
  }
  return NULL;
}

std::vector<GameObjectComponent*> GameObject::getAllComponents( const std::string& name ) const {
  std::vector<GameObjectComponent*> ret;

  for ( GameObjectComponent* component : _components ) {
    if ( component != NULL && component->getName() == name ) {
      ret.emplace_back( component );
    }
  }
  return ret;
}

std::vector<GameObjectComponent*> GameObject::getAllComponents() const {
  return _components;
}

// ==================================================
// Objects Management
// ==================================================

GameObject* GameObject::getParent() const {
  return _parent;
}

void GameObject::setParent( GameObject* parent ) {
  if ( _destructed || _released ) return;
  if ( _parent == parent ) return;

  ALA_ASSERT(parent != this);

  if ( _parent == NULL ) {
    ALA_ASSERT(GameManager::get()->getRunningScene()->getGameObject(getId()) == NULL);
  }
  else {
    ALA_ASSERT(_parent->getChild(getId()) == NULL);
  }

  if ( parent == NULL ) {
    ALA_ASSERT(GameManager::get()->getRunningScene()->getGameObject(getId()) != NULL);
  }
  else {
    ALA_ASSERT(parent->getChild(getId()) != NULL);
  }

  _parent = parent;
}

void GameObject::removeFromParent() {
  if ( _parent == NULL ) {
    GameManager::get()->getRunningScene()->removeGameObject( this );
  }
  else {
    _parent->removeChild( this );
  }
}

GameObject* GameObject::getChild( long id ) {
  const auto it = _children.find( id );
  if ( it == _children.end() ) return NULL;
  return it->second;
}

void GameObject::addChild( GameObject* gameObject ) {
  if ( _destructed || _released ) return;
  if ( gameObject == NULL ) return;

  const auto rc = _children.emplace( gameObject->getId(), gameObject );

  const bool success = rc.second;
  if ( success ) {
    gameObject->setParent( this );
  }
}

void GameObject::removeChild( GameObject* gameObject ) {
  if ( _destructed || _released ) return;
  if ( gameObject == NULL ) return;

  _children.erase( gameObject->getId() );
}


// ============================================
// Debug memory allocation
// ============================================

long GameObject::TOTAL_OBJECT_CREATED( 0 );

long GameObject::TOTAL_OBJECT_DELETED( 0 );
}
