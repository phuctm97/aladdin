#include "Animation.h"

#include "../pugixml/pugixml.hpp"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::Animation, ala::GameResource)


void Animation::onLoad ( )
{
  pugi::xml_document _animationFile;
  pugi::xml_parse_result result = _animationFile.load_file(_sourceFile.c_str (  ));

  ALA_ASSERT(result);

  auto atlasNode = _animationFile.child("TextureAtlas");

  auto actionNodes = atlasNode.children();

  for(auto action: actionNodes)
  {
    std::string actionName = action.attribute("actionName").as_string();

    auto frameNodes = action.children("Rect");

    std::vector<Rect> frames;

    for(auto frame: frameNodes)
    {
      Rect rect;
      rect.setTopLeft(Vec2(static_cast<float>(frame.attribute( "x" ).as_int()), static_cast<float>(frame.attribute( "y" ).as_int())));
      rect.setSize(Size(static_cast<float>(frame.attribute( "width" ).as_int()), static_cast<float>(frame.attribute( "height" ).as_int())));
      rect.setTopLeft(Vec2(rect.getTopLeft().getX(), rect.getTopLeft().getY()));
      frames.push_back(rect);
    }

    _frames[actionName] = frames;
  }
}

void Animation::onRelease ( )
{
}

Animation::Animation ( const std::string& name, const std::string& sourceFile, Scene* scope )
  : GameResource ( name, scope )
{
  _sourceFile = sourceFile;
}

const std::vector<Rect>& Animation::getFrameForAction (const std::string& actionName )
{
  return _frames[actionName];
}

Animation::~Animation ( )
{
}
}
