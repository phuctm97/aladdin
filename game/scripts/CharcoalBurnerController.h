#ifndef __CHARCOAL_BURNER_CONTROLLER_H__
#define __CHARCOAL_BURNER_CONTROLLER_H__

#include <aladdin.h>

class CharcoalBurnerController : ala::GameObjectComponent
{
private:
  bool _touchingAladdin;
  float _firingMinX, _firingMaxX, _firingX;

public:
  CharcoalBurnerController( ala::GameObject* gameObject, const std::string& name = "" );

  void onTriggerEnter( const ala::CollisionInfo& collision ) override;

  void onTriggerStay( const ala::CollisionInfo& collision ) override;

  void onTriggerExit( const ala::CollisionInfo& collision ) override;

  float getFiringX() const;
  
  bool isTouchingAladdin() const;

protected:
  void onInitialize() override;

  void onUpdate( const float delta ) override;

private:
  void updateFiringX();
};

#endif //!__CHARCOAL_BURNER_CONTROLLER_H__
