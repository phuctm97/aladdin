#ifndef __PARALLAX_CONTROLLER_H__
#define __PARALLAX_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(ParallaxController, ala::GameObjectComponent)
private:
  ala::Vec2 _offset;
  float _speed;

  ala::Transform* _selfTransform;

  std::vector<ala::Transform*> _layerTransforms;
  std::vector<float> _layerSizes;

public:
  ParallaxController( ala::GameObject* gameObject, const std::string& name = "" );

  void setOffset( const ala::Vec2& offset );

  void setSpeed( const float speed );

protected:
  void onInitialize() override;

  void onRender() override;
};

#endif //!__PARALLAX_CONTROLLER_H__
