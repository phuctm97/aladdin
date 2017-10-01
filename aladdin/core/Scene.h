/*
 * Created by phuctm97 on Sep 30th 2017
 */

#ifndef __ALADDIN_CORE_SCENE_H__
#define __ALADDIN_CORE_SCENE_H__

/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "GameObject.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_2(Scene, ala::Initializable, ala::Releasable)

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
public:
  void initialize() override;

protected:

  /**
   * \brief Add Default Objects and Scene Resources here, they will be init right after this function return
   */
  virtual void onPreInitialize();

  /**
  * \brief Add special Logic happen after initlization, every object and component in scene has been initialized
  * Object and Component added to scene there will be not automatically init, so you have to init them manually
  */
  virtual void onPostInitialize();

public:
  void update( const float delta );

protected:

  /**
   * \brief Happen before scene, its objects and components were updated
   * \param delta 
   */
  virtual void onPreUpdate( const float delta );


  /**
   * \brief Happen after scene, its objects and components were updated
   */
  virtual void onPostUpdate( const float delta );

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
  void release() override;

protected:

  /**
   * \brief Happen before scene, its objects and components were released
   */
  virtual void onPreRelease();


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
  GameObject* getGameObject( const long id );

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
