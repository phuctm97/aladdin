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

  std::vector<SceneObjectConfiguration> _objectConfigurations;

public:
  SceneConfiguration( const std::string& name, const std::string& sourceFile, Scene* sceneScope = NULL )
    : GameResource( name, sceneScope ), _sourceFile( sourceFile ), _physicsEnabled( false ) {}

  const std::vector<SceneObjectConfiguration>& getObjectConfigurations() const;

  bool isPhysicsEnabled() const;

  const Vec2& getPhysicsGravity() const;

protected:
  void onLoad() override;

  void onRelease() override;
};
}

#endif //!__ALADDIN_CORE_SCENE_CONFIGURATION_H__
