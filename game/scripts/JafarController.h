#ifndef __JAFAR_CONTROLLER_H__
#define __JAFAR_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(JafarController, ala::GameObjectComponent)
private:
  ala::Transform* _aladdinTransform;

  ala::Transform* _selfTransform;

public:
  JafarController( ala::GameObject* gameObject, const std::string& name = "" );

  char getDirectionToFaceAladdin() const;

protected:
  void onInitialize() override;
};

#endif //!__JAFAR_CONTROLLER_H__
