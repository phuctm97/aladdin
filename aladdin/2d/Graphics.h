#ifndef __ALADDIN_2D_GRAPHICS_2D_H__
#define __ALADDIN_2D_GRAPHICS_2D_H__

#include "2dInclude.h"

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

public:
  Graphics();

  static Graphics* get();

  // ==========================================
  // Platform specific
  // ==========================================
private:
  IDirect3DDevice9* _directXDevice;

  LPD3DXSPRITE _directXSprite;

public:
  void loadSprite( Sprite* sprite );
};
}

#endif //!__ALADDIN_2D_GRAPHICS_2D_H__
