#ifndef __JAFAR_CONTROLLER_H__
#define __JAFAR_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(JafarController, ala::GameObjectComponent)
private:
  int _mode;

  float _health;

  ala::Transform* _aladdinTransform;

  ala::Transform* _selfTransform;

public:
  JafarController( ala::GameObject* gameObject, const std::string& name = "" );

  char getDirectionToFaceAladdin() const;

  float getHealth() const;

  int getMode() const;

  void onTriggerEnter( const ala::CollisionInfo& collision ) override;

protected:
  void onInitialize() override;

  void onHit();
};

#endif //!__JAFAR_CONTROLLER_H__
