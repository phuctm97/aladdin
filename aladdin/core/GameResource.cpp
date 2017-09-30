#include "GameResource.h"
#include "GameManager.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0( ala::GameResource, "ala::GameResource" )

GameResource::GameResource( const std::string& name, Scene* sceneScope )
  : _name( name ), _sceneScope( sceneScope ), _loaded( false ), _released( false ) {
  GameManager::get()->attach( this );
  TOTAL_RESOURCES_CREATED++;
}

GameResource::~GameResource() {
  if ( _loaded && (!_released) ) {
    release();

    ALA_ASSERT(_released);
  }
  GameManager::get()->detach( this );
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
  ALA_ASSERT(_loaded && (!_released));
  onRelease();
  _released = true;
  ALA_ASSERT(_released);
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

bool GameResource::onLoad() {
  return true;
}

void GameResource::onRelease() {}

// =============================================
// Debug memory allocation
// =============================================
long GameResource::TOTAL_RESOURCES_CREATED( 0 );
long GameResource::TOTAL_RESOURCES_DELETED( 0 );
}
