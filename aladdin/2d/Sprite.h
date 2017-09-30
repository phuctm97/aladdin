#ifndef __ALADDIN_2D_SPRITE_H__
#define __ALADDIN_2D_SPRITE_H__

#include "2dInclude.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(Sprite)
  // ======================================
  // Basic
  // ======================================
private:
  std::string _sourceFile;
  ala::Color _transColor;

public:
  Sprite( const std::string& sourceFile, const ala::Color& transColor = ala::Color( 255, 0, 255 ) );

  ~Sprite();

  const std::string& getSourceFile() const;

  const ala::Color& getTransColor() const;

  // ======================================
  // Platform specific
  // ======================================

private:
  LPDIRECT3DTEXTURE9 _directXTexture;

public:
  void setDirectXTexture( LPDIRECT3DTEXTURE9 directXTexture );

  LPDIRECT3DTEXTURE9 getDirectXTexture();
};
}

#endif //!__ALADDIN_2D_SPRITE_H__
