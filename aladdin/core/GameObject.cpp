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
    _releasing( 0 ),
    _parent( NULL ) {
  // attach to GameManager
  GameManager::get()->attach( this );

  // for debug memory allocation
  TOTAL_OBJECT_CREATED++;
}

GameObject::~GameObject() {
  _releasing = 1;

  if ( (_inited) && (!isReleased()) ) {
    release();

    // make sure object released after destruction
    ALA_ASSERT(isReleased());
  }

  // remove from parent
  removeFromParent();

  // detach from GameManager
  GameManager::get()->detach( this );

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
  return _releasing == 2;
}

bool GameObject::isReleasing() const {
  return _releasing == 1;
}

void GameObject::init() {
  // make sure object is not initialized;
  ALA_ASSERT(!_inited);

  // TODO: subscriber pre init

  // child pre init
  if ( !onPreInit() ) {
    _inited = false;
    return;
  }


  // TODO: game object init here
  for ( GameObjectComponent* component : _components ) {
    component->init();
  }

  for ( const auto it : _children ) {
    it.second->init();
  }
  _inited = true;


  // make sure object initialized after initialization
  ALA_ASSERT(_inited);


  // child post init
  onPostInit();

  // TODO: client subscriber post init
}

bool GameObject::onPreInit() {
  return true;
}

void GameObject::onPostInit() {}

void GameObject::update( float delta ) {
  // make sure object is initialized and not released
  if ( (!_inited) || (_releasing > 0) )
    return;

  onPreUpdate( delta );

  // TODO: game object update here
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
  if ( (!_inited) || (_releasing > 0) )
    return;

  onPreRender();

  // TODO: game object update here
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
  ALA_ASSERT(_inited);
  ALA_ASSERT(!isReleased());

  _releasing = 1;

  ALA_ASSERT(isReleasing());
  // TODO: client subscriber pre release

  // child pre release
  if ( !onPreRelease() ) return;


  // TODO: game object release here
  for ( const auto it : _children ) {
    GameObject* gameObject = it.second;
    delete gameObject;
  }
  _children.clear();
  ALA_ASSERT(_children.empty());

  for ( GameObjectComponent* component : _components ) {
    delete component;
  }
  _components.clear();
  ALA_ASSERT(_components.empty());

  _releasing = 2;

  // make sure object released after release
  ALA_ASSERT(isReleased());

  // child post release
  onPostRelease();

  // TODO: client subscriber post release
}

bool GameObject::onPreRelease() {
  return true;
}

void GameObject::onPostRelease() {}

// ============================================================
// Components
// ============================================================

void GameObject::attach( GameObjectComponent* component ) {
  if ( _releasing > 0 ) return;

  if ( component == NULL )
    return;

  if ( !StdHelper::vectorContain<GameObjectComponent*>( _components, component ) ) {
    _components.emplace_back( component );
  }
}

void GameObject::detach( GameObjectComponent* component ) {
  if ( _releasing > 0 ) return;

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
  if ( _releasing > 0 ) return;
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
  if ( _releasing > 0 ) return;

  if ( gameObject == NULL ) return;

  _children.emplace( gameObject->getId(), gameObject );
  gameObject->setParent( this );
}

void GameObject::removeChild( GameObject* gameObject ) {
  if ( _releasing > 0 ) return;

  if ( gameObject == NULL ) return;

  _children.erase( gameObject->getId() );
}


// ============================================
// Debug memory allocation
// ============================================

long GameObject::TOTAL_OBJECT_CREATED( 0 );

long GameObject::TOTAL_OBJECT_DELETED( 0 );
}
