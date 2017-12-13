#ifndef __HUB_CONTROLLER_H__
#define __HUB_CONTROLLER_H__

#include <aladdin.h>

class HubController : public ala::GameObjectComponent
{
public:
  HubController( ala::GameObject* gameObject, const std::string& name = "" );

  void setLives( const int lives ) const;

  void setApples( const int apples ) const;

  void setScores( const int scores ) const;

protected:
  void onUpdate( const float delta ) override;
};


#endif //!__HUB_CONTROLLER_H__
