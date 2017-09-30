#include "Graphics.h"
#include "Sprite.h"

NAMESPACE_ALA
{
// ==========================================
// Basic
// ==========================================
ALA_CLASS_SOURCE_0(ala::Graphics, "ala::Graphics")

Graphics* Graphics::__instance( NULL );

Graphics::Graphics(): _directXDevice( 0 ), _directXSprite( 0 ) { }

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
}
}
