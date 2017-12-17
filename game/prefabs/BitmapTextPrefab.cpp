#include "BitmapTextPrefab.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(BitmapTextPrefab, ala::PrefabV2)

void BitmapTextPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto bitmapName = nextString( argsStream );
  const auto fontName = nextString( argsStream );
  const auto text = nextLine( argsStream );
  const auto characterAlignment = nextChar( argsStream );
  const auto textAlignment = nextChar( argsStream );
  const auto characterSpacing = nextFloat( argsStream );

  // components
  const auto bitmapText = new BitmapText( object, bitmapName, fontName );
  bitmapText->setText( text );

  switch ( characterAlignment ) {
  case 'T': bitmapText->setCharacterAlignment( BitmapText::TOP );
    break;
  case 'B': bitmapText->setCharacterAlignment( BitmapText::BOTTOM );
    break;
  default: bitmapText->setCharacterAlignment( BitmapText::CENTER );
    break;
  }

  switch ( textAlignment ) {
  case 'L': bitmapText->setTextAlignment( BitmapText::LEFT );
    break;
  case 'R': bitmapText->setTextAlignment( BitmapText::RIGHT );
    break;
  default: bitmapText->setTextAlignment( BitmapText::CENTER );
    break;
  }

  bitmapText->setCharacterSpacing( characterSpacing );
}
