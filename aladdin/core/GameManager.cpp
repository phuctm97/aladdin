/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "GameManager.h"
#include "Logger.h"

NAMESPACE_ALA
{
// ===========================================
// Basic
// ===========================================

ALA_CLASS_SOURCE_0(ala::GameManager, "ala::GameManager")

GameManager* GameManager::__instance( NULL );

GameManager* GameManager::get() {
  if ( __instance == NULL ) {
    __instance = new GameManager();
  }
  return __instance;
}

GameManager::GameManager() :
  _destructing( false ),
  _idCounter( 0 ),
  _runningScene( NULL ) {
  getLogger()->debug( "Created GameManager" );
}

GameManager::~GameManager() {
  _destructing = true;
  getLogger()->debug( "Released GameManager" );
  getLogger()->debug( "Total Object Created: %ld", GameObject::TOTAL_OBJECT_CREATED );
  getLogger()->debug( "Total Object Deleted: %ld", GameObject::TOTAL_OBJECT_DELETED );
  getLogger()->debug( "Total Scene Retained: %ld", Scene::TOTAL_SCENE_CREATED );
  getLogger()->debug( "Total Scene Released: %ld", Scene::TOTAL_SCENE_DELETED );
  getLogger()->debug( "Total Reference Retained: %ld", Base::TOTAL_REFERENCE_RETAINED );
  getLogger()->debug( "Total Reference Released: %ld", Base::TOTAL_REFERENCE_RELEASED );
}


// ==============================================
// Object Management
// ==============================================

long GameManager::newObjectId() {
  return ++_idCounter;
}

void GameManager::attach( GameObject* gameObject ) {
  if ( _destructing ) return;

  // insert to attach table by id
  if ( gameObject != NULL ) {
    _attachedObjects.emplace( gameObject->getId(), gameObject );
  }
}

void GameManager::detach( GameObject* gameObject ) {
  if ( _destructing ) return;

  if ( gameObject != NULL ) {
    _attachedObjects.erase( gameObject->getId() );
  }
}

GameObject* GameManager::getObjectById( long id ) {
  const auto objectIt = _attachedObjects.find( id );
  if ( objectIt == _attachedObjects.end() ) return NULL;

  const auto object = objectIt->second;
  return object;
}

std::vector<GameObject*> GameManager::getAllObjectsByName( const std::string& name ) {
  std::vector<GameObject*> ret;

  for ( auto& pair : _attachedObjects ) {
    auto object = pair.second;
    if ( object == NULL ) continue;
    if ( object->getName() == name ) {
      ret.emplace_back( object );
    }
  }

  return ret;
}

GameObject* GameManager::getObjectByName( const std::string& name ) {
  for ( auto& pair : _attachedObjects ) {
    const auto object = pair.second;
    if ( object == NULL ) continue;
    if ( object->getName() == name ) {
      return object;
    }
  }
  return NULL;
}

Scene* GameManager::getRunningScene() const {
  return _runningScene;
}

void GameManager::replaceScene( Scene* scene ) {
  ALA_ASSERT(scene != NULL);
  ALA_ASSERT(scene != _runningScene);

  SAFE_DELETE(_runningScene);
  _runningScene = scene;
}
}
