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

ALA_CLASS_SOURCE_2(GameObjectComponent, ala::Initializable, ala::Releasable)

GameObjectComponent::GameObjectComponent( GameObject* gameObject, const std::string& name )
  : _name( name ),
    _gameObject( gameObject ) {
  // check game object
  ALA_ASSERT(gameObject != NULL);

  // check initial state
  ALA_ASSERT((!isInitialized()) && (!isInitializing()) && (!isReleased()) && (!isReleasing()));

  gameObject->addComponent( this );
}

GameObjectComponent::~GameObjectComponent() {
  if ( isInitialized() ) {
    // make sure object released after destruction
    ALA_ASSERT(isReleased());
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

void GameObjectComponent::initialize() {
  // make sure object is not initialized;
  ALA_ASSERT((!isInitialized()) && (!isInitializing()));

  setToInitializing();

  // TODO: lock mutual exclusive when run in multithreading mode

  onInitialize();

  setToInitialized();
}

void GameObjectComponent::onInitialize() {}

void GameObjectComponent::update( const float delta ) {
  // make sure object is initialized and not released
  if ( (!isInitialized()) || (!isInitializing()) || isReleasing() || isReleased() ) return;

  onUpdate( delta );
}

void GameObjectComponent::onUpdate( const float delta ) {}

void GameObjectComponent::onRender() {}

void GameObjectComponent::render() {
  // make sure object is initialized and not released
  if ( (!isInitialized()) || (!isInitializing()) || isReleasing() || isReleased() ) return;

  onRender();
}

void GameObjectComponent::release() {
  // make sure object is initialized and not released
  ALA_ASSERT((isInitialized()) && (!isReleasing()) && (!isReleased()));

  setToReleasing();

  // TODO: lock mutual exclusive when run in multithreading mode

  onRelease();

  setToReleased();

  // destroy
  delete this;
}

void GameObjectComponent::onRelease() {}
}
