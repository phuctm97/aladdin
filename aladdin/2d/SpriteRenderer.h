/*
 * Created by phuctm97 on Sep 30th 2017
 */

#ifndef __ALADDIN_2D_SPRITE_RENDERER_H__
#define __ALADDIN_2D_SPRITE_RENDERER_H__

#include "2dInclude.h"
#include "Sprite.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(SpriteRenderer, ala::GameObjectComponent)
private:
  Sprite* _sprite;
  Color _backColor;

public:
  SpriteRenderer( GameObject* gameObject, Sprite* sprite = NULL, const std::string& name = "" );

  SpriteRenderer( GameObject* gameObject, const std::string& spriteResourceName = "", const std::string& name = "" );

  virtual ~SpriteRenderer();

  Sprite* getSprite() const;

  void setSprite( Sprite* sprite );

  const Color& getBackColor() const;

  void setBackColor(const Color& color);

  Size getFrameSize() const;

protected:
  void onRender() override;
};
}

#endif //!__ALADDIN_2D_SPRITE_RENDERER_H__
