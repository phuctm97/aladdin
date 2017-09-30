#ifndef __ALADDIN_CORE_GAME_RESOURCE_H__
#define __ALADDIN_CORE_GAME_RESOURCE_H__

#include "Base.h"
#include "Scene.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(GameResource)
private:
  std::string _name;
  Scene* _sceneScope;
  bool _loaded;
  bool _destructed;
  bool _released;

public:
  GameResource( const std::string& name, Scene* sceneScope = NULL );

  ~GameResource();

  const std::string& getName() const;

  void load();

  void release();

  bool isLoaded() const;

  bool isReleased() const;

  void setGameScope();

  void setSceneScope( Scene* sceneScope );

  Scene* getSceneScope() const;

protected:
  virtual bool onLoad() = 0;

  virtual void onRelease() = 0;

  // =============================================
  // Debug memory allocation
  // =============================================
public:
  static long TOTAL_RESOURCES_CREATED;
  static long TOTAL_RESOURCES_DELETED;
};
}

#endif //!__ALADDIN_CORE_GAME_RESOURCE_H__
