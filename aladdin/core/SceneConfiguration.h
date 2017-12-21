#ifndef __ALADDIN_CORE_SCENE_CONFIGURATION_H__
#define __ALADDIN_CORE_SCENE_CONFIGURATION_H__

#include "GameResource.h"

NAMESPACE_ALA
{
struct SceneObjectConfiguration
{
  std::string name = "";
  std::string layer = "";
  int tag = -1;
  std::string quadIndex = "";

  std::string prefabName = "";
  int prefabVersion = 0;
  std::string prefabArgs = "";

  bool applyTransformPosition = false;
  Vec2 transformPosition = Vec2( 0, 0 );
  bool applyTransformScale = false;
  Vec2 transformScale = Vec2( 1, 1 );
  bool applyTransformRotation = false;
  float transformRotation = 0;
};

ALA_CLASS_HEADER_1(SceneConfiguration, ala::GameResource)
private:
  std::string _sourceFile;

  bool _physicsEnabled;
  Vec2 _physicsGravity;

  bool _quadTreeEnabled;
  int _quadTreeLevel;
  float _spaceMinX;
  float _spaceMinY;
  float _spaceWidth;
  float _spaceHeight;

  std::vector<SceneObjectConfiguration> _objectConfigurations;

public:
  SceneConfiguration( const std::string& name, const std::string& sourceFile, Scene* sceneScope = NULL )
    : GameResource( name, sceneScope ), _sourceFile( sourceFile ), _physicsEnabled( false ),
      _quadTreeEnabled( false ), _quadTreeLevel( 3 ), _spaceMinX( 0 ), _spaceMinY( 0 ), _spaceWidth( 0 ),
      _spaceHeight( 0 ) {}

  const std::vector<SceneObjectConfiguration>& getObjectConfigurations() const;

  bool isPhysicsEnabled() const;

  const Vec2& getPhysicsGravity() const;

  bool isQuadTreeEnabled() const;

  float getSpaceMinX() const;

  float getSpaceMinY() const;

  float getSpaceWidth() const;

  float getSpaceHeight() const;

  int getQuadTreeLevel() const;

protected:
  void onLoad() override;

  void onRelease() override;
};
}

#endif //!__ALADDIN_CORE_SCENE_CONFIGURATION_H__
