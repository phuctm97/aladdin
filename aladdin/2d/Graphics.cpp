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

bool Graphics::beginRendering() {
  // clear screen
  if ( _directXDevice->Clear( 0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0 ) != D3D_OK ) {
    _directXDevice->Present( 0, 0, 0, 0 );
    return false;
  }

  // start rendering
  if ( _directXDevice->BeginScene() != D3D_OK ) {
    _directXDevice->Present( 0, 0, 0, 0 );
    return false;
  }

  if ( _directXSprite->Begin( D3DXSPRITE_ALPHABLEND ) != D3D_OK ) {
    _directXDevice->EndScene();
    _directXDevice->Present( 0, 0, 0, 0 );
    return false;
  }

  return true;
}

void Graphics::endRendering() {
  // stop rendering
  _directXSprite->End();
  _directXDevice->EndScene();

  // display back buffer to screen
  _directXDevice->Present( 0, 0, 0, 0 );
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

void Graphics::drawSprite( Sprite* sprite, const Vec2& origin, const Mat4& transformMatrix, const Color& backColor, const Rect& srcRect, const int zIndex ) {
  LPDIRECT3DTEXTURE9 texture = sprite->getDirectXTexture();
  ALA_ASSERT(texture);

  RECT dSrcRect = convertToWindowsRect( srcRect );

  D3DXVECTOR3 dPostition;
  dPostition.x = 0;
  dPostition.y = 0;
  dPostition.z = static_cast<float>(zIndex);

  D3DXMATRIX oldMatrix;

  auto transformationMatrix = convertToDirectXMatrix( transformMatrix );

  _directXSprite->GetTransform( &oldMatrix );
  D3DXMATRIX finalMatrix = transformationMatrix * oldMatrix;


  _directXSprite->SetTransform( &finalMatrix );

  D3DXVECTOR3 center = D3DXVECTOR3( abs( dSrcRect.right - dSrcRect.left ) * origin.getX(), abs( dSrcRect.top - dSrcRect.bottom ) * (1 - origin.getY()), 0 );

  if ( srcRect.getSize().getWidth() == 0 || srcRect.getSize().getHeight() == 0 ) {
    _directXSprite->Draw(
      texture,
      NULL,
      &center,
      &dPostition,
      D3DXCOLOR( backColor.getR() / 256.f, backColor.getG() / 256.f, backColor.getB() / 256.f, backColor.getA() / 256.f ) );
  }
  else {
    _directXSprite->Draw(
      texture,
      &dSrcRect,
      &center,
      &dPostition,
      D3DXCOLOR( backColor.getR() / 256.f, backColor.getG() / 256.f, backColor.getB() / 256.f, backColor.getA() / 256.f ) );
  }

  _directXSprite->SetTransform( &oldMatrix );
}

D3DXMATRIX Graphics::convertToDirectXMatrix( const Mat4& mat ) const {

  D3DXMATRIX result;
  result._11 = mat.get11();
  result._12 = mat.get12();
  result._13 = mat.get13();
  result._14 = mat.get14();

  result._21 = mat.get21();
  result._22 = mat.get22();
  result._23 = mat.get23();
  result._24 = mat.get24();

  result._31 = mat.get31();
  result._32 = mat.get32();
  result._33 = mat.get33();
  result._34 = mat.get34();

  result._41 = mat.get41();
  result._42 = mat.get42();
  result._43 = mat.get43();
  result._44 = mat.get44();

  return result;
}

RECT Graphics::convertToWindowsRect( const Rect& srcRect ) const {
  RECT desRect;
  desRect.left = static_cast<LONG>(srcRect.getTopLeft().getX());
  desRect.top = static_cast<LONG>(srcRect.getTopLeft().getY());
  desRect.right = static_cast<LONG>(srcRect.getTopLeft().getX() + srcRect.getSize().getWidth());
  desRect.bottom = static_cast<LONG>(srcRect.getTopLeft().getY() + srcRect.getSize().getHeight());
  return desRect;
}
}
