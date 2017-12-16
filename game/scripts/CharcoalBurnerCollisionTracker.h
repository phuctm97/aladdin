#ifndef __CHARCOAL_BURNER_COLLISION_TRACKER_H__
#define __CHARCOAL_BURNER_COLLISION_TRACKER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1( CharcoalBurnerCollisionTracker, ala::GameObjectComponent )
private:
  bool _beingCollided;

public:
  CharcoalBurnerCollisionTracker( ala::GameObject* gameObject, const std::string& name = "" );

  void onTriggerEnter( const ala::CollisionInfo& collision ) override;

  void onTriggerExit( const ala::CollisionInfo& collision ) override;

  bool isBeingCollided() const;
};

#endif //!__CHARCOAL_BURNER_COLLISION_TRACKER_H__
