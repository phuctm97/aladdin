#ifndef __ALADDIN_CONTROLLER_H__
#define __ALADDIN_CONTROLLER_H__

#include <aladdin.h>

class AladdinController : public ala::GameObjectComponent
{
private:
  ala::Logger _logger;
  float _walkSpeed;

public:
  AladdinController( ala::GameObject* gameObject, const std::string& name = "" );

protected:
  void onUpdate( const float delta ) override;
};

#endif //!__ALADDIN_CONTROLLER_H__
