#ifndef __ALADDIN_CORE_SCENE_H__
#define __ALADDIN_CORE_SCENE_H__

/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "Base.h"
#include "GameObject.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(Scene)

  // ================================================
  // Basic
  // ================================================
private:
  std::string _name;

public:
  Scene( const std::string& name );

  virtual ~Scene();

  const std::string& getName() const;

  // ==================================================
  // Events
  // ==================================================
private:
  bool _inited;
  bool _destructed;
  bool _released;

public:
  bool isInited() const;

  bool isReleased() const;

  void init();

protected:
  virtual bool onPreInit();

  virtual void onPostInit();

public:
  void update( float delta );

protected:
  virtual void onPreUpdate( float delta );

  virtual void onPostUpdate( float delta );

public:
  void render();

protected:
  virtual void onPreRender();

  virtual void onPostRender();

public:
  void release();

protected:
  virtual bool onPreRelease();

  virtual void onPostRelease();

  // ==================================================
  // Objects Management
  // ==================================================
private:
  std::unordered_map<long, GameObject*> _gameObjects;

public:
  GameObject* getGameObject( long id );

  void addGameObject( GameObject* gameObject );

  void removeGameObject( GameObject* gameObject );

  // =============================================
  // Debug memory allocation
  // =============================================
public:
  static long TOTAL_SCENE_CREATED;
  static long TOTAL_SCENE_DELETED;
};
}

#endif //!__ALADDIN_CORE_SCENE_H__
