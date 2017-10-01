/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Prefab.h"
#include "GameManager.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::Prefab, ala::Releasable)

Prefab::Prefab( const std::string& name )
  : _name( name ) {
  ALA_ASSERT((!isReleasing()) && (!isReleased()));

  GameManager::get()->registerPrefab( this );
  TOTAL_PREFABS_CREATED++;
}

Prefab::~Prefab() {
  ALA_ASSERT(isReleased());
  TOTAL_PREFABS_DELETED++;
}

const std::string& Prefab::getName() const {
  return _name;
}

GameObject* Prefab::instantiate( const std::string& name ) {
  if ( isReleasing() || isReleased() ) return NULL;
  return instantiate( GameManager::get()->getRunningScene(), name );
}

GameObject* Prefab::instantiate( Scene* scene, const std::string& name ) {
  if ( isReleasing() || isReleased() ) return NULL;

  const auto object = new GameObject( scene, name );
  doInstantiate( object );

  return object;
}

GameObject* Prefab::instantiate( GameObject* parentObject, const std::string& name ) {
  if ( isReleasing() || isReleased() ) return NULL;

  const auto object = new GameObject( parentObject, name );
  doInstantiate( object );

  return object;
}

void Prefab::release() {
  ALA_ASSERT((!isReleasing()) && (!isReleased()));

  setToReleasing();

  onRelease();

  GameManager::get()->removePrefab( this );

  setToReleased();

  delete this;
}

void Prefab::onRelease() { }

// =============================================
// Debug memory allocation
// =============================================
long Prefab::TOTAL_PREFABS_CREATED( 0 );
long Prefab::TOTAL_PREFABS_DELETED( 0 );
}
