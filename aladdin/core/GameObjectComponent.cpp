/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "GameObjectComponent.h"
#include "GameObject.h"

NAMESPACE_ALA
{
// ================================================
// Basic
// ================================================

ALA_CLASS_SOURCE_0(ala::GameObjectComponent, "ala::GameObjectComponent")

GameObjectComponent::GameObjectComponent( GameObject* gameObject, const std::string& name )
  : _name( name ),
    _gameObject( gameObject ),
    _inited( false ),
    _destructed( false ),
    _released( false ) {
  ALA_ASSERT(gameObject != NULL);
  gameObject->attach( this );
}

GameObjectComponent::~GameObjectComponent() {
  _destructed = true;

  if ( _inited ) {
    // make sure object released after destruction
    ALA_ASSERT(_released);
  }
}

const std::string& GameObjectComponent::getName() const {
  return _name;
}

GameObject* GameObjectComponent::getGameObject() const {
  return _gameObject;
}


// =================================================
// Events
// =================================================

void GameObjectComponent::init() {
  // make sure object is not initialized;
  ALA_ASSERT(!_inited);

  if ( !onInit() ) {
    return;
  }

  _inited = true;
}

bool GameObjectComponent::onInit() {
  return true;
}

void GameObjectComponent::update( float delta ) {
  // make sure object is initialized and not released
  if ( (!_inited) || (_released) )
    return;

  onUpdate( delta );
}

void GameObjectComponent::onUpdate( float delta ) {}

void GameObjectComponent::onRender() {}

void GameObjectComponent::render() {
  // make sure object is initialized and not released
  if ( (!_inited) || (_released) )
    return;

  onRender();
}

void GameObjectComponent::release() {
  // make sure object is initialized and not released
  ALA_ASSERT(_inited && (!_released) && (!_destructed));

  _released = true;

  onRelease();

  _gameObject->detach( this );

  delete this;
}

void GameObjectComponent::onRelease() {}

bool GameObjectComponent::isInited() const {
  return _inited;
}

bool GameObjectComponent::isReleased() const {
  return _released;
}
}
