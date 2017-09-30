/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "GameResource.h"
#include "GameManager.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0( ala::GameResource, "ala::GameResource" )

GameResource::GameResource( const std::string& name, Scene* sceneScope )
  : _name( name ),
    _sceneScope( sceneScope ),
    _loaded( false ),
    _destructed( false ),
    _released( false ) {
  GameManager::get()->attach( this );
  TOTAL_RESOURCES_CREATED++;
}

GameResource::~GameResource() {
  _destructed = true;
  if ( _loaded ) {
    ALA_ASSERT(_released);
  }
  TOTAL_RESOURCES_DELETED++;
}

const std::string& GameResource::getName() const {
  return _name;
}

void GameResource::load() {
  ALA_ASSERT(!_loaded);
  _loaded = onLoad();
  ALA_ASSERT(_loaded);
}

void GameResource::release() {
  ALA_ASSERT(_loaded && (!_released) && (!_destructed));

  _released = true;

  onRelease();

  GameManager::get()->detach( this );

  delete this;
}

bool GameResource::isLoaded() const {
  return _loaded;
}

bool GameResource::isReleased() const {
  return _released;
}

void GameResource::setGameScope() {
  _sceneScope = NULL;
}

void GameResource::setSceneScope( Scene* sceneScope ) {
  _sceneScope = sceneScope;
}

Scene* GameResource::getSceneScope() const {
  return _sceneScope;
}

// =============================================
// Debug memory allocation
// =============================================
long GameResource::TOTAL_RESOURCES_CREATED( 0 );
long GameResource::TOTAL_RESOURCES_DELETED( 0 );
}
