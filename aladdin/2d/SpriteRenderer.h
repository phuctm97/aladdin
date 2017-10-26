/*
 * Created by phuctm97 on Sep 30th 2017
 */

#ifndef __ALADDIN_2D_SPRITE_RENDERER_H__
#define __ALADDIN_2D_SPRITE_RENDERER_H__

#define ALA_MAX_Z_ORDER 999

#include "2dInclude.h"
#include "Sprite.h"
#include "Rect.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(SpriteRenderer, ala::GameObjectComponent)
private:
  Sprite* _sprite;
  Color _backColor;
  int _zOrder;

  Rect _srcRect;

public:
  SpriteRenderer( GameObject* gameObject, Sprite* sprite = NULL, const std::string& name = "" );

  SpriteRenderer( GameObject* gameObject, const std::string& spriteResourceName = "", const std::string& name = "" );

  virtual ~SpriteRenderer();

  Sprite* getSprite() const;

  void setSprite( Sprite* sprite );

  const Color& getBackColor() const;

  void setBackColor( const Color& color );

  Size getFrameSize() const;

  void setZOrder( const int zOrder );

  int getZOrder() const;

  const Rect& getSourceRect() const;

  void setSourceRect(const Rect& rect);

protected:
  void onInitialize() override;
  void onRender() override;
  void onRelease() override;

private:
  int calculateWorldZOrder() const;
};
}

#endif //!__ALADDIN_2D_SPRITE_RENDERER_H__
