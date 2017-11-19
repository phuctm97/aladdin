#include "ThrowableAppleController.h"

USING_NAMESPACE_ALA;

ThrowableAppleController::ThrowableAppleController( ala::GameObject* gameObject, const std::string& name )
	: GameObjectComponent(gameObject, name), _collidedWithGround(false), direct(false)
{
	Logger("ThrowableAppleController").info("constructor");
}


bool ThrowableAppleController::isCollidedWithGround() const {
  return _collidedWithGround;
}

void ThrowableAppleController::onTriggerEnter( const ala::CollisionInfo& collision ) {
  if ( collision.getColliderA()->getGameObject()->getName() == "Ground" || collision.getColliderB()->getGameObject()->
                                                                                     getName() == "Ground" ) {
    _collidedWithGround = true;
  }
}

void ThrowableAppleController::resetCollidedWithGround() { _collidedWithGround = false; }

void ThrowableAppleController::chekDirectionLeft(const char& direction)
{
	if(direction == 'L')
	{
		 direct='L';
	}
	else {
		direct = 'R';
	}
}
char ThrowableAppleController::getDirection()
{
	return direct;
}

void ThrowableAppleController::onInitialize()
{
	if (getGameObject()->getName() == "apple")
	{
		Logger("ThrowableAppleController").info("init");
	}
}

void ThrowableAppleController::onPhysicsUpdate(const float delta)
{
}

void ThrowableAppleController::onUpdate(const float delta)
{
	if (getGameObject()->getName() == "apple")
	{
		Logger("ThrowableAppleController").info("update physics");
	}
}




