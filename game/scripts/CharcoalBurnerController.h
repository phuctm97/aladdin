#ifndef __CHARCOAL_BURNER_CONTROLLER_H__
#define __CHARCOAL_BURNER_CONTROLLER_H__

#include <aladdin.h>

class CharcoalBurnerController : ala::GameObjectComponent
{
private:
  bool _firing;

public:
  CharcoalBurnerController( ala::GameObject* gameObject, const std::string& name );

  void onTriggerEnter( const ala::CollisionInfo& collision ) override;

  void onTriggerStay( const ala::CollisionInfo& collision ) override;

  void onTriggerExit( const ala::CollisionInfo& collision ) override;
};

#endif //!__CHARCOAL_BURNER_CONTROLLER_H__
