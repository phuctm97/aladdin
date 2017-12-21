#ifndef __DIRECTION_CONTROLLER_H__
#define __DIRECTION_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1( DirectionController, ala::GameObjectComponent)
private:
  bool _applyPhysics;
  bool _positiveAsRight;
  int _direction;
  std::vector<std::function<bool()>> _reverseCases;
  ala::Rigidbody* _selfBody;

public:
  DirectionController( ala::GameObject* gameObject, const bool positiveAsRight = true, const int direction = -1,
                       const std::string& name = "" );

  void setApplyPhysics( const bool v );

  bool isApplyPhysics() const;

  bool isLeft() const;

  bool isRight() const;

  void setDirection( const int direction );

  void setLeft();

  void setRight();

  void turn();

  void addReverseCase( const std::function<bool()>& c );

protected:
  void onInitialize() override;

  void onUpdate( const float delta ) override;
};

#endif //!__DIRECTION_CONTROLLER_H__
