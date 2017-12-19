#include "SceneConfiguration.h"
#include "../pugixml/pugixml.hpp"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(SceneConfiguration, ala::GameResource)

const std::vector<SceneObjectConfiguration>& SceneConfiguration::getObjectConfigurations() const {
  return _objectConfigurations;
}

bool SceneConfiguration::isPhysicsEnabled() const {
  return _physicsEnabled;
}

const Vec2& SceneConfiguration::getPhysicsGravity() const {
  return _physicsGravity;
}

bool SceneConfiguration::isQuadTreeEnabled() const { return _quadTreeEnabled; }

float SceneConfiguration::getSpaceMinX() const { return _spaceMinX; }

float SceneConfiguration::getSpaceMinY() const { return _spaceMinY; }

float SceneConfiguration::getSpaceWidth() const { return _spaceWidth; }

float SceneConfiguration::getSpaceHeight() const { return _spaceHeight; }

int SceneConfiguration::getQuadTreeLevel() const {
  return _quadTreeLevel;
}

void SceneConfiguration::onLoad() {
  pugi::xml_document document;
  pugi::xml_parse_result result = document.load_file( _sourceFile.c_str() );
  ALA_ASSERT(result);

  std::stringstream stringBuilder;
  std::string str;

  const auto& sceneNode = document.child( "Scene" );

  const auto& physicsNode = sceneNode.child( "physics" );
  if ( !physicsNode.empty() ) {
    str = physicsNode.attribute( "gravity" ).as_string( "" );
    if ( !str.empty() ) {
      stringBuilder.clear();
      stringBuilder.str( str );

      float x, y;
      stringBuilder >> x >> y;

      _physicsEnabled = true;
      _physicsGravity = Vec2( x, y );
    }
    else {
      _physicsEnabled = false;
    }
  }
  else {
    _physicsEnabled = false;
  }

  const auto& quadNode = sceneNode.child( "quad" );
  if ( !quadNode.empty() ) {
    _quadTreeLevel = quadNode.attribute( "level" ).as_int( 3 );
    _spaceMinX = quadNode.attribute( "minX" ).as_float( 0 );
    _spaceMinY = quadNode.attribute( "minY" ).as_float( 0 );
    _spaceWidth = quadNode.attribute( "width" ).as_float( 0 );
    _spaceHeight = quadNode.attribute( "height" ).as_float( 0 );
    _quadTreeEnabled = true;
  }
  else {
    _quadTreeEnabled = false;
  }

  const auto& objectNodes = sceneNode.children( "object" );

  _objectConfigurations.clear();

  for ( const auto& objectNode : objectNodes ) {
    SceneObjectConfiguration objectConfiguration;

    objectConfiguration.name = objectNode.attribute( "name" ).as_string( "" );
    objectConfiguration.layer = objectNode.attribute( "layer" ).as_string( "" );
    objectConfiguration.tag = objectNode.attribute( "tag" ).as_int( -1 );
    objectConfiguration.quadIndex = objectNode.attribute( "quadIndex" ).as_string( "" );

    const auto& prefabNode = objectNode.child( "prefab" );

    if ( !prefabNode.empty() ) {
      objectConfiguration.prefabName = prefabNode.attribute( "name" ).as_string( "" );
      objectConfiguration.prefabVersion = prefabNode.attribute( "version" ).as_int( 1 );
      objectConfiguration.prefabArgs = prefabNode.attribute( "args" ).as_string( "" );
    }
    else {
      objectConfiguration.prefabName = "";
      objectConfiguration.prefabVersion = 0;
    }

    const auto& transformNode = objectNode.child( "transform" );
    if ( !transformNode.empty() ) {
      str = transformNode.attribute( "position" ).as_string( "" );

      if ( !str.empty() ) {
        stringBuilder.clear();
        stringBuilder.str( str );
        float x, y;
        stringBuilder >> x >> y;

        objectConfiguration.applyTransformPosition = true;
        objectConfiguration.transformPosition = Vec2( x, y );
      }
      else {
        objectConfiguration.applyTransformPosition = false;
      }

      str = transformNode.attribute( "scale" ).as_string( "" );

      if ( !str.empty() ) {
        stringBuilder.clear();
        stringBuilder.str( str );
        float x, y;
        stringBuilder >> x >> y;

        objectConfiguration.applyTransformScale = true;
        objectConfiguration.transformScale = Vec2( x, y );
      }
      else {
        objectConfiguration.applyTransformScale = false;
      }

      str = transformNode.attribute( "rotation" ).as_string( "" );

      if ( !str.empty() ) {
        stringBuilder.clear();
        stringBuilder.str( str );
        float r;
        stringBuilder >> r;

        objectConfiguration.applyTransformRotation = true;
        objectConfiguration.transformRotation = r;
      }
      else {
        objectConfiguration.applyTransformRotation = false;
      }
    }
    else {
      objectConfiguration.applyTransformPosition = false;
      objectConfiguration.applyTransformScale = false;
      objectConfiguration.applyTransformRotation = false;
    }

    _objectConfigurations.push_back( objectConfiguration );
  }
}

void SceneConfiguration::onRelease() {}
}
