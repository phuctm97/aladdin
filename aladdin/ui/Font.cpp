#include "Font.h"
#include "../2d/Graphics.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1 (Font, ala::GameResource)

Font::Font (const std::string& name, const std::string& fontName, const std::string&fontPath, Scene* scope)
  :GameResource ( name, scope )
{
  if(fontPath == "")
  {
    _isSystemFont = true;
    _fontName = fontName;
  }
  else
  {
    _isSystemFont = false;
    _fileName = fontPath + "/" + fontName;
    _fontName = fontName;
  }
}

ID3DXFont* Font::getFont ( const FontInfo& fontInfo )
{
  const auto font = _fonts.find(fontInfo);

  if(font == _fonts.end (  ))
  {
    const auto fontResource = Graphics::get (  )->loadFont(_fontName, fontInfo);
    _fonts[fontInfo] = fontResource;
    return fontResource;
  }
  else
  {
    return font->second;
  }
}

Font::~Font ( )
{
}

void Font::onLoad ( )
{
  _fileName = "C:\\Users\\15520\\Source\\Repos\\aladdin\\game\\fonts\\Sail-Regular.otf";
  int rs = 0;
  auto name = TEXT(_fileName.c_str());
  if(!_isSystemFont)
  {
    rs = AddFontResourceEx(TEXT(_fileName.c_str()), FR_PRIVATE, NULL);
  }
}

void Font::onRelease ( )
{
  if(!_isSystemFont)
  {
    RemoveFontResourceEx(TEXT (_fileName.c_str()), FR_PRIVATE, NULL);
  }
}
}
