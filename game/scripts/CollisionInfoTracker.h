#ifndef __COLLISION_INFO_TRACKER_H__
#define __COLLISION_INFO_TRACKER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(CollisionInfoTracker, ala::GameObjectComponent)
private:
  std::unordered_set<int> _collidedObjects;
  std::unordered_set<int> _collidedObjectTags;
  std::unordered_set<int> _collidedColliderTags;

public:
  CollisionInfoTracker( ala::GameObject* gameObject, const std::string& name = "" );

  void onCollisionEnter( const ala::CollisionInfo& collision ) override;

  void onTriggerEnter( const ala::CollisionInfo& collision ) override;

  void reset();

  bool collidedWithObject( const int id ) const;

  bool collidedWithObjectTag( const int tag ) const;

  bool collidedWithColliderTag( const int tag ) const;

  bool collided() const;

protected:
  void onRender() override;
};

#endif //!__COLLISION_INFO_TRACKER_H__
