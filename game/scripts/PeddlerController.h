#ifndef __PEDDLER_CONTROLLER_H__
#define __PEDDLER_CONTROLLER_H__

#include <aladdin.h>
#include "PlayableAladdinController.h"

ALA_CLASS_HEADER_1(PeddlerController, ala::GameObjectComponent)
private:
  ala::Transform* _aladdinTransform;
  PlayableAladdinController* _aladdinController;
  ala::Transform* _selfTransform;
  ala::SpriteRenderer* _selfSpriteRenderer;
  ala::Animator* _selfAnimator;
  ala::SpriteRenderer* _childSpriteRenderer;
  ala::Animator* _childAnimator;
  ala::Collider* _collider5;
  ala::Collider* _collider10;
  ala::PrefabV2* _peddlerTextPrefab;

public:
  PeddlerController( ala::GameObject* gameObject, const std::string& name = "" );

protected:
  void onInitialize() override;

  void onUpdate( const float delta ) override;

public:
  void onTriggerStay( const ala::CollisionInfo& collision ) override;
};

#endif //!__PEDDLER_CONTROLLER_H__
