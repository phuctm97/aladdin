/*
 * Created by phuctm97 on Sep 30th 2017
 */

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

  /**
   * \brief Add Default Objects and Scene Resources here, they will be init right after this function return
   * \return return true if everything were right otherwise return false and the application will crash
   */
  virtual bool onPreInit();

  /**
  * \brief Add special Logic happen after initlization, every object and component in scene has been initialized
  * Object and Component added to scene there will be not automatically init, so you have to init them manually
  */
  virtual void onPostInit();

public:
  void update( float delta );

protected:

  /**
   * \brief Happen before scene, its objects and components were updated
   * \param delta 
   */
  virtual void onPreUpdate( float delta );


  /**
   * \brief Happen after scene, its objects and components were updated
   */
  virtual void onPostUpdate( float delta );

public:
  void render();

protected:
  /**
   * \brief Happen before scene, its objects and components were rendered
   */
  virtual void onPreRender();


  /**
   * \brief Happen after scene, its objects and components were rendered
   */
  virtual void onPostRender();

public:
  void release();

protected:

  /**
   * \brief Happen before scene, its objects and components were released
   * \return true if you want to continue releasing and false if not
   */
  virtual bool onPreRelease();

  
  /**
   * \brief Happen after scene, its objects and components were released and destroyed
   */
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
