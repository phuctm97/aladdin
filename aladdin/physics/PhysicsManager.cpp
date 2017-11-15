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

  if (colliderA == NULL || colliderB == NULL || rigidbodyA == NULL || rigidbodyB == NULL) return false;

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

	//update transform position
	for (auto rigidbody : _rigidbodies)
	{
		rigidbody->getGameObject()->getTransform()->setPosition(rigidbody->getPosition());
	}

	std::map<int, std::vector<Collider*>> colliders;

	for(auto collider: _colliders)
	{
		const auto colliderList = colliders.find(collider->getPhysicsLayer());
		if(colliderList != colliders.end())
		{
			colliders[collider->getPhysicsLayer()].push_back(collider);
		}
		else
		{
			std::vector<Collider*> addingCollider;
			addingCollider.push_back(collider);
			colliders[collider->getPhysicsLayer()] = addingCollider;
		}
	}

	for(auto layer: colliders)
	{
		for (auto it1 = layer.second.begin(); it1 != layer.second.end(); ++it1)
		{
			for (auto it2 = it1 + 1; it2 != layer.second.end(); ++it2)
			{
				const auto gameObject1 = (*it1)->getGameObject();
				const auto gameObject2 = (*it2)->getGameObject();

				auto rb1 = gameObject1->getComponentT<Rigidbody>();
				auto rb2 = gameObject2->getComponentT<Rigidbody>();

				auto rectA = (*it1)->getBoundingRect();
				auto rectB = (*it2)->getBoundingRect();

				CollisionInfo collisionInfo;

				if (abs(rectA.getMidX() - rectB.getMidX()) > rectA.getSize().getWidth() / 2 + rectB.getSize().getWidth() / 2)
				{
					if ((*it1)->getTrigger() || (*it2)->getTrigger())
					{
						collisionInfo.setObjectA(gameObject1);
						collisionInfo.setObjectB(gameObject2);
						if (isCollidedLastFrame(collisionInfo))
						{
							(*it1)->getGameObject()->onTriggerExit(collisionInfo);
							(*it2)->getGameObject()->onTriggerExit(collisionInfo);
						}
					}
					else
					{
						collisionInfo.setObjectA(gameObject1);
						collisionInfo.setObjectB(gameObject2);
						if (isCollidedLastFrame(collisionInfo))
						{
							(*it1)->getGameObject()->onCollisionExit(collisionInfo);
							(*it2)->getGameObject()->onCollisionExit(collisionInfo);
						}
					}
					continue;
				}
				if (abs(rectA.getMidY() - rectB.getMidY()) > rectA.getSize().getHeight() / 2 + rectB.getSize().getHeight() / 2)
				{
					if ((*it1)->getTrigger() || (*it2)->getTrigger())
					{
						collisionInfo.setObjectA(gameObject1);
						collisionInfo.setObjectB(gameObject2);
						if (isCollidedLastFrame(collisionInfo))
						{
							(*it1)->getGameObject()->onTriggerExit(collisionInfo);
							(*it2)->getGameObject()->onTriggerExit(collisionInfo);
						}
					}
					else
					{
						collisionInfo.setObjectA(gameObject1);
						collisionInfo.setObjectB(gameObject2);
						if (isCollidedLastFrame(collisionInfo))
						{
							(*it1)->getGameObject()->onCollisionExit(collisionInfo);
							(*it2)->getGameObject()->onCollisionExit(collisionInfo);

						}
					}
					continue;
				}


				if (!getCollisionInfo(gameObject1, gameObject2, collisionInfo))
				{
					if ((*it1)->getTrigger() || (*it2)->getTrigger())
					{
						collisionInfo.setObjectA(gameObject1);
						collisionInfo.setObjectB(gameObject2);
						if (isCollidedLastFrame(collisionInfo))
						{
							(*it1)->getGameObject()->onTriggerExit(collisionInfo);
							(*it2)->getGameObject()->onTriggerExit(collisionInfo);

						}
					}
					else
					{
						collisionInfo.setObjectA(gameObject1);
						collisionInfo.setObjectB(gameObject2);
						if (isCollidedLastFrame(collisionInfo))
						{
							(*it1)->getGameObject()->onCollisionExit(collisionInfo);
							(*it2)->getGameObject()->onCollisionExit(collisionInfo);

						}
					}
					continue;
				}

				_currentCollidingPairs.push_back(collisionInfo);

				if((*it1)->getTrigger() || (*it2)->getTrigger())
				{
					if(!isCollidedLastFrame(collisionInfo))
					{
						(*it1)->getGameObject()->onTriggerEnter(collisionInfo);
						(*it2)->getGameObject()->onTriggerEnter(collisionInfo);

					}

					(*it1)->getGameObject()->onTriggerStay(collisionInfo);
					(*it2)->getGameObject()->onTriggerStay(collisionInfo);

					continue;
				}

				if (!isCollidedLastFrame(collisionInfo))
				{
					(*it1)->getGameObject()->onCollisionEnter(collisionInfo);
					(*it2)->getGameObject()->onCollisionEnter(collisionInfo);

				}

				(*it1)->getGameObject()->onCollisionStay(collisionInfo);
				(*it2)->getGameObject()->onCollisionStay(collisionInfo);


				const Vec2 relativeVelocity = rb2->getVelocity() - rb1->getVelocity();
				const float velocityAlongNormal = relativeVelocity.dot(collisionInfo.getNormal());

				//do not resolve if objects are seperating
				if (velocityAlongNormal > 0)
				{
					return;
				}

				const float restitution = MIN(rb1->getPhysicsMaterial().getRestitution(), rb2->getPhysicsMaterial().getRestitution());

				float impulseScalar = -(1 + restitution) * velocityAlongNormal;
				impulseScalar /= rb1->getInverseMass() + rb2->getInverseMass();

				//apply impulse
				const Vec2 impulse = collisionInfo.getNormal()* impulseScalar;
				
				rb1->resetForce();
				rb2->resetForce();

        //positional correction
        const float percent = 0.2f; // usually 20% to 80%
        const float slop = 0.01f; // usually 0.01 to 0.1
        const Vec2 correction = collisionInfo.getNormal()* (MAX(collisionInfo.getPenetration() - slop, 0.0f) / (rb1->getInverseMass() + rb2->getInverseMass())) * percent;

				if(rb1->getBodyType() == ALA_BODY_TYPE_DYNAMIC)
				{
					rb1->setVelocity(rb1->getVelocity() - impulse * rb1->getInverseMass());

          rb1->setPosition(rb1->getPosition() - correction*rb1->getInverseMass());
				}

				if(rb2->getBodyType() == ALA_BODY_TYPE_DYNAMIC)
				{
					rb2->setVelocity(rb2->getVelocity() + impulse * rb2->getInverseMass());

          rb2->setPosition(rb2->getPosition() + correction*rb2->getInverseMass());
				}
				
				// TODO: Friction
			}
		}

    //update transform position
    for (auto rigidbody : _rigidbodies)
    {
      rigidbody->getGameObject()->getTransform()->setPosition(rigidbody->getPosition());
    }

		_lastCollidingPairs.clear();
		_lastCollidingPairs.insert(_lastCollidingPairs.begin(), _currentCollidingPairs.begin(), _currentCollidingPairs.end());
		_currentCollidingPairs.clear();
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

bool PhysicsManager::isCollidedLastFrame(const CollisionInfo& collisionInfo)
{
	for(const auto collision: _lastCollidingPairs)
	{
		if (collisionInfo.isSameObjects(collision))
		{
			return true;
		}
	}

	return false;
}
}
