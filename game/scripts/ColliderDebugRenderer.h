#ifndef __COLLIDER_DEBUG_RENDERER_H__
#define __COLLIDER_DEBUG_RENDERER_H__

#include <aladdin.h>

class ColliderDebugRenderer : public ala::GameObjectComponent
{
private:
  ala::Sprite* _sprite;
  ala::Color _backColor;
  int _zOrder;

public:
  ColliderDebugRenderer( ala::GameObject* gameObject, const std::string& debugSpriteResourceName, const float opacity = 1.0f,
                         const std::string& name = "" );

  int getZOrder() const;

  void setZOrder( const int order );

  void setOpacity( const float opacity );

  float getOpacity() const;

protected:
  void onRender() override;

private:
  int calculateWorldZOrder() const;
};

#endif //!__COLLIDER_DEBUG_RENDERER_H__
