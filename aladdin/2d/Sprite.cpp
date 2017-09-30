#include "Sprite.h"
#include "Graphics.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0( ala::Sprite, "ala::Sprite" )

Sprite::Sprite( const std::string& sourceFile, const ala::Color& transColor )
  : _sourceFile( sourceFile ),
    _transColor( transColor ),
    _directXTexture( 0 ) {
  Graphics::get()->loadSprite( this );
}

Sprite::~Sprite() {
  if ( _directXTexture ) {
    _directXTexture->Release();
  }
}

const std::string& Sprite::getSourceFile() const {
  return _sourceFile;
}

const ala::Color& Sprite::getTransColor() const {
  return _transColor;
}

void Sprite::setDirectXTexture( LPDIRECT3DTEXTURE9 directXTexture ) {
  _directXTexture = directXTexture;
}

LPDIRECT3DTEXTURE9 Sprite::getDirectXTexture() {
  return _directXTexture;
}
}
