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
    _released( false ) {
  ALA_ASSERT(gameObject != NULL);

  gameObject->attach( this );
}

GameObjectComponent::~GameObjectComponent() {
  if ( _inited && (!_released) ) {
    release();

    // make sure object released after destruction
    ALA_ASSERT(_released);
  }

  _gameObject->detach( this );
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
    _inited = false;
    return;
  }

  _inited = true;

  // make sure object initialized after initialization
  ALA_ASSERT(_inited);
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
  ALA_ASSERT(_inited);
  ALA_ASSERT(!_released);

  onRelease();

  _released = true;

  // make sure object released after release
  ALA_ASSERT(_released);
}

void GameObjectComponent::onRelease() {}

bool GameObjectComponent::isInited() const {
  return _inited;
}

bool GameObjectComponent::isReleased() const {
  return _released;
}
}
