#ifndef __CAMEL_CONTROLLER_H__
#define __CAMEL_CONTROLLER_H__

#include <aladdin.h>
#include "DirectionController.h"

ALA_CLASS_HEADER_1(CamelController, ala::GameObjectComponent)
private:
  bool _aladdinJumpingOn;

  ala::Collider* _selfCollider;
  ala::Transform* _selfTransform;
  DirectionController* _selfDirection;

  ala::StateManager* _aladdinStateManager;
  ala::PrefabV2* _floatingSavilaPrefab;

protected:
  void onInitialize() override;

public:
  CamelController( ala::GameObject* gameObject, const std::string& name = "" );

  void resetAladdinJumpingOn();

  bool isAladdinJumpingOn() const;

  void puffSaliva( float directX, float directY ) const;

  void onTriggerEnter( const ala::CollisionInfo& collision ) override;
};

#endif //!__CAMEL_CONTROLLER_H__
