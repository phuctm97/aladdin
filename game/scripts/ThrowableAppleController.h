#ifndef __THROWABLE_APPLE_CONTROLLER_H__
#define __THROWABLE_APPLE_CONTROLLER_H__

#include <aladdin.h>

class ThrowableAppleController : public ala::GameObjectComponent
{
private:
  bool _collidedWithGround;
  char direct;
public:
  ThrowableAppleController( ala::GameObject* gameObject, const std::string& name = "" );

  bool isCollidedWithGround() const;

  void resetCollidedWithGround();

  void onTriggerEnter( const ala::CollisionInfo& collision ) override;

  void chekDirectionLeft(const char& direction);

  char getDirection();


protected:
	void onInitialize() override;


	void onPhysicsUpdate(const float delta) override;
	void onUpdate(const float delta) override;
};

#endif //!__THROWABLE_APPLE_CONTROLLER_H__
