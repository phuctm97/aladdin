#ifndef __JAFAR_STAR_CONTROLLER_H__
#define __JAFAR_STAR_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(JafarStarController, ala::GameObjectComponent)
private:
  float _movingSpeed;

  ala::Vec2 _targetPosition;

  ala::Transform* _aladdinTransform;

  ala::Transform* _selfTransform;

  ala::PrefabV2* _explosionPrefab;

public:
  JafarStarController( ala::GameObject* gameObject, const float movingSpeed = 7.0f, const std::string& name = "" );

  const ala::Vec2& getTargetPosition() const;

  void onTriggerEnter( const ala::CollisionInfo& collision ) override;

protected:
  void onInitialize() override;

  void onUpdate( const float delta ) override;

private:
  void explode() const;
};

#endif //!__JAFAR_STAR_CONTROLLER_H__
