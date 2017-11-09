#include "PhysicsManager.h"
#include "../core/StdHelper.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(PhysicsManager, Releasable)

PhysicsManager* PhysicsManager::__instance = NULL;


bool PhysicsManager::getCollisionInfo(GameObject* a, GameObject* b, CollisionInfo& collisionInfo) const
{
	collisionInfo.setObjectA(a);
	collisionInfo.setObjectB(b);

	const auto colliderA = a->getComponentT<Collider>();
	const auto colliderB = b->getComponentT<Collider>();

	const auto rigidbodyA = a->getComponentT<Rigidbody>();
	const auto rigidbodyB = b->getComponentT<Rigidbody>();

	auto n = rigidbodyB->getPosition() - rigidbodyA->getPosition();

	auto rectA = colliderA->getBoundingRect();
	auto rectB = colliderB->getBoundingRect();

	const float aExtentX = rectA.getSize().getWidth()/2;
	const float bExtentX = rectB.getSize().getWidth() / 2;

	const float xOverlap = aExtentX + bExtentX - abs(n.getX());

	if(xOverlap > 0)
	{
		const float aExtentY = rectA.getSize().getHeight()/2;
		const float bExtentY = rectB.getSize().getHeight() / 2;

		const float yOverlap = aExtentY + bExtentY - abs(n.getY());

		if(yOverlap > 0)
		{
			if(xOverlap < yOverlap)
			{
				if(n.getX() < 0)
				{
					collisionInfo.setNormal(Vec2(-1, 0));
				}
				else
				{
					collisionInfo.setNormal(Vec2(1, 0));
				}

				collisionInfo.setPenetration(xOverlap);

				return true;
			}
			else
			{
				if(n.getY() < 0)
				{
					collisionInfo.setNormal(Vec2(0, -1));
				}
				else
				{
					collisionInfo.setNormal(Vec2(0, 1));
				}

				collisionInfo.setPenetration(yOverlap);

				return true;
			}
		}
	}

	return false;
}

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

	//check collision
	for(auto it1 = _colliders.begin(); it1 != _colliders.end(); ++it1)
	{
		for(auto it2 = it1 + 1; it2 != _colliders.end(); ++it2)
		{
			const auto gameObject1 = (*it1)->getGameObject();
			const auto gameObject2 = (*it2)->getGameObject();

			auto rb1 = gameObject1->getComponentT<Rigidbody>();
			auto rb2 = gameObject2->getComponentT<Rigidbody>();

			auto rectA = (*it1)->getBoundingRect();
			auto rectB = (*it2)->getBoundingRect();

			if (abs(rectA.getMidX() - rectB.getMidX()) > rectA.getSize().getWidth()/2 + rectB.getSize().getWidth()/2) continue;
			if (abs(rectA.getMidY() - rectB.getMidY()) > rectA.getSize().getHeight()/2 + rectB.getSize().getHeight()/2) continue;

			CollisionInfo collisionInfo;
			if (!getCollisionInfo(gameObject1, gameObject2, collisionInfo))
			{
				continue;
			}

			const Vec2 relativeVelocity = rb2->getVelocity() - rb1->getVelocity();
			const float velocityAlongNormal = relativeVelocity.dot(collisionInfo.getNormal());

			//do not resolve if objects are seperating
			if(velocityAlongNormal > 0)
			{
				return;
			}

			const float restitution = MIN(rb1->getPhysicsMaterial().getRestitution(), rb2->getPhysicsMaterial().getRestitution());

			float impulseScalar = -(1 + restitution) * velocityAlongNormal;
			impulseScalar /= rb1->getInverseMass() + rb2->getInverseMass();

			//apply impulse
			const Vec2 impulse = collisionInfo.getNormal()* impulseScalar;

			rb1->setVelocity(rb1->getVelocity() - impulse * rb1->getInverseMass());
			rb2->setVelocity(rb2->getVelocity() + impulse * rb2->getInverseMass());

			//positional correction
			const float percent = 0.2; // usually 20% to 80%
			const float slop = 0.01; // usually 0.01 to 0.1
			const Vec2 correction = collisionInfo.getNormal()* (MAX(collisionInfo.getPenetration() - slop, 0.0f) / (rb1->getInverseMass() + rb2->getInverseMass())) * percent;
			rb1->setPosition(rb1->getPosition() - correction*rb1->getInverseMass());
			rb2->setPosition(rb2->getPosition() - correction*rb2->getInverseMass());

			//collision happens
			_logger.info("collision");
		}
	}
	

  //update transform position
  for(auto rigidbody: _rigidbodies)
  {
    rigidbody->getGameObject()->getTransform()->setPosition(rigidbody->getPosition());
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
