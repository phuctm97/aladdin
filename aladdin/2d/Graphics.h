#ifndef __ALADDIN_2D_GRAPHICS_2D_H__
#define __ALADDIN_2D_GRAPHICS_2D_H__

/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "2dInclude.h"
#include "Rect.h"

NAMESPACE_ALA
{
class Sprite;

ALA_CLASS_HEADER_0(Graphics)
  // ==========================================
  // Basic
  // ==========================================
  friend class Application;

private:
  static Graphics* __instance;
  Logger* _logger;

public:
  Graphics();

  virtual ~Graphics();

  static Graphics* get();

  // ==========================================
  // Platform specific
  // ==========================================
private:
  IDirect3DDevice9* _directXDevice;

  LPD3DXSPRITE _directXSprite;

public:
  void loadSprite( Sprite* sprite );

  void drawSprite( Sprite* sprite, const Vec2& position, const Rect& srcRect = Rect() );
};
}

#endif //!__ALADDIN_2D_GRAPHICS_2D_H__
