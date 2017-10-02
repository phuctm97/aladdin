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
ALA_CLASS_SOURCE_2(ala::Graphics, ala::Initializable, ala::Releasable)

Graphics* Graphics::__instance( NULL );

Graphics::Graphics():
  _logger( "ala::Graphics" ),
  _directX( 0 ),
  _directXDevice( 0 ),
  _directXSprite( 0 ) {
  ALA_ASSERT((!isInitialized()) && (!isInitializing()) && (!isReleased()) && (!isReleasing()));
  _logger.debug( "Created" );
}

Graphics::~Graphics() {
  if ( isInitialized() ) {
    ALA_ASSERT(isReleased());
  }
  _logger.debug( "Released" );
}

Graphics* Graphics::get() {
  if ( __instance == NULL ) {
    __instance = new Graphics();
  }
  return __instance;
}

void Graphics::initialize() {
  ALA_ASSERT((!isInitialized()) && (!isInitializing()));

  setToInitializing();

  initDirectX();

  setToInitialized();
}

void Graphics::release() {
  ALA_ASSERT(isInitialized() && (!isReleased()) && (!isReleasing()));

  setToReleasing();

  releaseDirectX();

  setToReleased();

  // destroy
  delete this;
}

// ==========================================
// Platform specific
// ==========================================

void Graphics::initDirectX() {
  HRESULT result;

  // init DirectX
  _directX = Direct3DCreate9( D3D_SDK_VERSION );
  ALA_ASSERT(!FAILED(_directX));
  _logger.debug( "Initialized DirectX" );

  // init DirectX device
  D3DPRESENT_PARAMETERS d3dpp;
  ZeroMemory(&d3dpp, sizeof(d3dpp));
  d3dpp.BackBufferCount = 1;
  d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
  d3dpp.BackBufferWidth = _screenWidth;
  d3dpp.BackBufferHeight = _screenHeight;
  d3dpp.Windowed = true;
  d3dpp.hDeviceWindow = _hWnd;
  d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
  result = _directX->CreateDevice(
    D3DADAPTER_DEFAULT,
    D3DDEVTYPE_HAL,
    _hWnd,
    D3DCREATE_HARDWARE_VERTEXPROCESSING,
    &d3dpp,
    &_directXDevice );

  ALA_ASSERT(result == D3D_OK);
  ALA_ASSERT(!FAILED(_directXDevice));
  _logger.debug( "Created DirectX Device" );


  // init DirectX Sprite
  result = D3DXCreateSprite( _directXDevice, &_directXSprite );
  ALA_ASSERT(result == D3D_OK);
  ALA_ASSERT(!FAILED(_directXSprite));
  _logger.debug( "Created DirectX Sprite" );
}

void Graphics::releaseDirectX() {
  if ( _directXSprite ) {
    _directXSprite->Release();
    _logger.debug( "Released DirectX Sprite" );
  }
  if ( _directXDevice ) {
    _directXDevice->Release();
    _logger.debug( "Released DirectX Device" );
  }
  if ( _directX ) {
    _directX->Release();
    _logger.debug( "Released DirectX" );
  }
}

void Graphics::beginRendering() {
  // clear screen
  ALA_ASSERT(_directXDevice->Clear( 0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0 ) == D3D_OK);

  // start rendering
  ALA_ASSERT(_directXDevice->BeginScene() == D3D_OK);
  ALA_ASSERT(_directXSprite->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_DONOTSAVESTATE ) == D3D_OK);
}

void Graphics::endRendering() {
  // stop rendering
  ALA_ASSERT(_directXSprite->End() == D3D_OK);
  ALA_ASSERT(_directXDevice->EndScene() == D3D_OK);

  // display back buffer to screen
  ALA_ASSERT(_directXDevice->Present( 0, 0, 0, 0 ) == D3D_OK);
}

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

void Graphics::drawSprite( Sprite* sprite, const Vec2& position, const Rect& srcRect ) {
  LPDIRECT3DTEXTURE9 texture = sprite->getDirectXTexture();
  ALA_ASSERT(texture);

  RECT dSrcRect;
  dSrcRect.left = static_cast<LONG>(srcRect.getTopLeft().getX());
  dSrcRect.top = static_cast<LONG>(srcRect.getTopLeft().getY());
  dSrcRect.right = static_cast<LONG>(srcRect.getTopLeft().getX() + srcRect.getSize().getWidth());
  dSrcRect.bottom = static_cast<LONG>(srcRect.getTopLeft().getY() + srcRect.getSize().getHeight());

  D3DXVECTOR3 dPostition;
  dPostition.x = position.getX();
  dPostition.y = position.getY();
  dPostition.z = 0;

  if ( srcRect.getSize().getWidth() == 0 || srcRect.getSize().getHeight() == 0 ) {
    _directXSprite->Draw(
      texture,
      NULL,
      NULL,
      &dPostition,
      D3DCOLOR_XRGB(255, 255, 255) );
  }
  else {
    _directXSprite->Draw(
      texture,
      &dSrcRect,
      NULL,
      &dPostition,
      D3DCOLOR_XRGB(255, 255, 255) );
  }
}
}
