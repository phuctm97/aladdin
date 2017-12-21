#ifndef __PLATFORM_CONTROLLER_H__
#define __PLATFORM_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(PlatformController, ala::GameObjectComponent)
private:
  ala::GameObject* _other;
  ala::Logger _logger;
  bool _isChangePosition = false;
  ala::Vec2 _oldPosition;

  ala::Collider* _uponCollider;


public:
  PlatformController( ala::GameObject* gameObject, const string& name = "" );

protected:
  void onTriggerEnter( const ala::CollisionInfo& collision ) override;

  void onTriggerExit( const ala::CollisionInfo& collision ) override;

  void onUpdate( const float delta ) override;

  void onInitialize() override;
};


#endif //!__PLATFORM_CONTROLLER_H__
