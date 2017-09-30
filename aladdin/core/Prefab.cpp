/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Prefab.h"
#include "GameManager.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0( ala::Prefab, "ala::Prefab" )

Prefab::Prefab( const std::string& name )
  : _name( name ),
    _destructed( false ),
    _released( false ) {
  GameManager::get()->registerPrefab( this );
  TOTAL_PREFABS_CREATED++;
}

Prefab::~Prefab() {
  _destructed = true;
  ALA_ASSERT(_released);
  TOTAL_PREFABS_DELETED++;
}

const std::string& Prefab::getName() const {
  return _name;
}

GameObject* Prefab::instantiate() {
  if ( _destructed || _released ) return NULL;
  GameObject* object = doInstantiate();
  if ( object != NULL ) {
    ala::GameManager::get()->getRunningScene()->addGameObject( object );
  }
  return object;
}

GameObject* Prefab::doInstantiate() {
  return NULL;
}

void Prefab::release() {
  ALA_ASSERT((!_released) && (!_destructed));
  _released = true;
  onRelease();
  GameManager::get()->removePrefab( this );
  delete this;
}

void Prefab::onRelease() { }

// =============================================
// Debug memory allocation
// =============================================
long Prefab::TOTAL_PREFABS_CREATED( 0 );
long Prefab::TOTAL_PREFABS_DELETED( 0 );
}
