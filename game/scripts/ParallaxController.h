#ifndef __PARALLAX_CONTROLLER_H__
#define __PARALLAX_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(ParallaxController, ala::GameObjectComponent)
private:
  ala::Vec2 _offset;

public:
  ParallaxController( ala::GameObject* gameObject, const std::string& name = "" );

  void setOffset( const ala::Vec2& offset );

protected:
  void onRender() override;
};

#endif //!__PARALLAX_CONTROLLER_H__
