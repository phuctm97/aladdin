#ifndef __ALADDIN_2D_SPRITE_RENDERER_H__
#define __ALADDIN_2D_SPRITE_RENDERER_H__

#include "2dInclude.h"
#include "Sprite.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(SpriteRenderer, ala::GameObjectComponent)
private:
  Sprite* _sprite;

public:
  SpriteRenderer( GameObject* gameObject, Sprite* sprite = NULL, const std::string& name = "" );

  SpriteRenderer( GameObject* gameObject, const std::string& spriteResourceName = "", const std::string& name = "" );


  Sprite* getSprite() const;

  void setSprite( Sprite* sprite );

protected:
  void onRender() override;
};
}

#endif //!__ALADDIN_2D_SPRITE_RENDERER_H__
