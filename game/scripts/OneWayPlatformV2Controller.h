#ifndef __PLATFORM_V2_CONTROLLER_H__
#define __PLATFORM_V2_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(OneWayPlatformV2Controller, ala::GameObjectComponent)
private:
  ala::Transform* _aladdinTransform;
  ala::Collider* _aladdinBodyCollider;
  ala::Transform* _selfTransform;

public:
  OneWayPlatformV2Controller( ala::GameObject* gameObject, const std::string& name = "" );

  bool isAladdinAbove() const;

protected:
  void onInitialize() override;
};

#endif //!__PLATFORM_V2_CONTROLLER_H__
