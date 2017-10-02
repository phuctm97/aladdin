/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Graphics.h"
#include "Sprite.h"

NAMESPACE_ALA
{
// ==========================================
// Basic
// ==========================================
ALA_CLASS_SOURCE_0(ala::Graphics)

Graphics* Graphics::__instance( NULL );

Graphics::Graphics():
  _logger( new Logger( "ala::Graphics" ) ),
  _directXDevice( 0 ),
  _directXSprite( 0 ) {
  _logger->debug( "Created" );
}

Graphics::~Graphics() {
  _logger->debug( "Released" );
  delete _logger;
}

Graphics* Graphics::get() {
  if ( __instance == NULL ) {
    __instance = new Graphics();
  }
  return __instance;
}

// ==========================================
// Platform specific
// ==========================================

void Graphics::loadSprite( Sprite* sprite ) {
  if ( sprite->getDirectXTexture() ) {
    sprite->getDirectXTexture()->Release();
  }
  HRESULT result;

  // load image info
  D3DXIMAGE_INFO info;
  result = D3DXGetImageInfoFromFile( sprite->getSourceFile().c_str(), &info );
  ALA_ASSERT(result == D3D_OK);

  // create texture
  LPDIRECT3DTEXTURE9 texture = NULL;
  D3DXCreateTextureFromFileEx(
    _directXDevice, //Direct3D device object
    sprite->getSourceFile().c_str(), //bitmap filename
    info.Width, //bitmap image width
    info.Height, //bitmap image height
    1, //mip-map levels (1 for no chain)
    D3DPOOL_DEFAULT, //the type of surface (standard)
    D3DFMT_UNKNOWN, //surface format (default)
    D3DPOOL_DEFAULT, //memory class for the texture
    D3DX_DEFAULT, //image filter
    D3DX_DEFAULT, //mip filter
    D3DCOLOR_XRGB(sprite->getTransColor().getR(), sprite->getTransColor().getG(), sprite->getTransColor().getB()), //color key for transparency
    &info, //bitmap file info (from loaded file)
    NULL, //color palette
    &texture ); //destination texture

  ALA_ASSERT(result == D3D_OK);
  sprite->setDirectXTexture( texture );
  sprite->setContentSize( Size( static_cast<float>(info.Width), static_cast<float>(info.Height) ) );
}

void Graphics::drawSprite( Sprite* sprite, const Vec2& origin, const D3DXMATRIX& transformMatrix, const Color& backColor, const Rect& srcRect, float zIndex ) {
  LPDIRECT3DTEXTURE9 texture = sprite->getDirectXTexture();
  ALA_ASSERT(texture);

  RECT dSrcRect;
  dSrcRect.left = static_cast<LONG>(srcRect.getTopLeft().getX());
  dSrcRect.top = static_cast<LONG>(srcRect.getTopLeft().getY());
  dSrcRect.right = static_cast<LONG>(srcRect.getTopLeft().getX() + srcRect.getSize().getWidth());
  dSrcRect.bottom = static_cast<LONG>(srcRect.getTopLeft().getY() + srcRect.getSize().getHeight());

  D3DXVECTOR3 dPostition;
  dPostition.x = 0;
  dPostition.y = 0;
  dPostition.z = zIndex;

  D3DXMATRIX oldMatrix;
  _directXSprite->GetTransform(&oldMatrix);
  D3DXMATRIX finalMatrix = transformMatrix*oldMatrix;


  _directXSprite->SetTransform(&transformMatrix);

  D3DXVECTOR3 center = D3DXVECTOR3(abs(dSrcRect.right - dSrcRect.left) * origin.getX (  ), abs(dSrcRect.top - dSrcRect.bottom) * (1-origin.getY (  )), 0);

  if ( srcRect.getSize().getWidth() == 0 || srcRect.getSize().getHeight() == 0 ) {
    _directXSprite->Draw(
      texture,
      NULL,
      &center,
      &dPostition,
      D3DXCOLOR(backColor.getR (  )/256.f,backColor.getG (  )/256.f , backColor.getB()/256.f, backColor.getA (  )/256.f) );
  }
  else {
    _directXSprite->Draw(
      texture,
      &dSrcRect,
      &center,
      &dPostition,
      D3DXCOLOR(backColor.getR() / 256.f, backColor.getG() / 256.f, backColor.getB() / 256.f, backColor.getA() / 256.f));
  }

  _directXSprite->SetTransform(&oldMatrix);
}
}
