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

ALA_CLASS_HEADER_2(Graphics, ala::Initializable, ala::Releasable)
  // ==========================================
  // Basic
  // ==========================================
  friend class Application;

private:
  static Graphics* __instance;
  Logger _logger;

public:
  Graphics();

  virtual ~Graphics();

  static Graphics* get();

  void initialize() override;

  void release() override;

  // ==========================================
  // Platform specific
  // ==========================================
private:
  HINSTANCE _hInstance;
  HWND _hWnd;
  UINT _screenWidth;
  UINT _screenHeight;
  IDirect3D9* _directX;
  IDirect3DDevice9* _directXDevice;
  LPD3DXSPRITE _directXSprite;

public:
  void initDirectX();

  void releaseDirectX();

  bool beginRendering();

  void endRendering();

  void loadSprite( Sprite* sprite );

  void drawSprite(Sprite* sprite, const Vec2& origin, const D3DXMATRIX& transformMatrix, const Color& backColor, const Rect& srcRect, float zIndex = 0);
};
}

#endif //!__ALADDIN_2D_GRAPHICS_2D_H__
