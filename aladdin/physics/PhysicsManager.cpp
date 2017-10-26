#include "PhysicsManager.h"
#include "../core/StdHelper.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(PhysicsManager, Releasable)

PhysicsManager* PhysicsManager::__instance = NULL;

PhysicsManager::PhysicsManager ( ):
  _logger ( "ala::PhysicsManager" )
{
  ALA_ASSERT((!isReleased()) && (!isReleasing()));
  _logger.info("Created");
}

PhysicsManager::~PhysicsManager ( )
{
  ALA_ASSERT(isReleased());
  _logger.info("Released");
}

PhysicsManager* PhysicsManager::get ( )
{
  if(__instance == NULL)
  {
    __instance = new PhysicsManager;
  }

  return __instance;
}

void PhysicsManager::update ( const float delta )
{
  if (isReleasing() || isReleased()) return;

  //update transform position
  for(auto rigidbody: _rigidbodies)
  {
    rigidbody->getGameObject()->getTransform()->setPosition(rigidbody->getPosition());
    _logger.info("Update position: %.2f %.2f", rigidbody->getPosition().getX(), rigidbody->getPosition().getY());
  }
}

void PhysicsManager::release ( )
{
  ALA_ASSERT((!isReleased()) && (!isReleasing()));

  setToReleasing();

  setToReleased();

  // destroy
  delete this;
}

void PhysicsManager::attach ( Rigidbody* rigidbody )
{
  if (isReleasing() || isReleased()) return;
  if (rigidbody == NULL) return;
  _rigidbodies.push_back(rigidbody);
}

void PhysicsManager::detach ( Rigidbody* rigidbody )
{
  if (isReleasing() || isReleased()) return;
  if (rigidbody == NULL) return;
  StdHelper::vectorErase(_rigidbodies, rigidbody);
}

void PhysicsManager::attach ( Collider* collider )
{
  if (isReleasing() || isReleased()) return;
  if (collider == NULL) return;
  _colliders.push_back(collider);
}

void PhysicsManager::detach ( Collider* collider )
{
  if (isReleasing() || isReleased()) return;
  if (collider == NULL) return;
  StdHelper::vectorErase(_colliders, collider);
}
}
