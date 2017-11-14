#ifndef __BALL_CONTROLLER_H__
#define __BALL_CONTROLLER_H__

/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include <aladdin.h>

class BasicController : public ala::GameObjectComponent, public ala::MessageListener {
private:
  char _state;
  float _speed;
  ala::Logger _logger;

public:
  BasicController( ala::GameObject* gameObject, const std::string& name = "" );

protected:
  void onInitialize() override;

  void onUpdate( const float delta ) override;

  void onRelease() override;

	void onCollisionEnter(const ala::CollisionInfo& collision) override;
	void onCollisionStay(const ala::CollisionInfo& collision) override;
	void onCollisionExit(const ala::CollisionInfo& collision) override;
	void onTriggerEnter(const ala::CollisionInfo& collision) override;
	void onTriggerStay(const ala::CollisionInfo& collision) override;
	void onTriggerExit(const ala::CollisionInfo& collision) override;
};


#endif //!__BALL_CONTROLLER_H__
