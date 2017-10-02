/*
 * Created by phuctm97 on Sep 30th 2017
 */

#ifndef __ALADDIN_CORE_TRANSFORM2_H__
#define __ALADDIN_CORE_TRANSFORM2_H__

#include "GameObjectComponent.h"
#include "Vec2.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(Transform, ala::GameObjectComponent)

  // ===================================================
  // Basic
  // ===================================================
private:
  Vec2 _position;
  Vec2 _scale;
  float _rotation;
  Vec2 _origin;
public:
  Transform( GameObject* gameObject, Transform* parentTransform = NULL, const std::string& name = "" );

  virtual ~Transform();

  const Vec2& getPosition() const;

  float getPositionX() const;

  float getPositionY() const;

  void setPosition( const Vec2& position );

  void setPosition(const float x, const float y);

  void setPositionX( const float x );

  void setPositionY( const float y );

  const Vec2& getScale() const;

  void setScale( const Vec2& scale );

  void setScaleX(float x);

  void setScaleY(float y);

  void setScale(float scale);

  float getRotation() const;

  void setRotation( const float rotation );

  // =======================================================
  // Children management
  // =======================================================

private:
  std::vector<Transform*> _children;

  Transform* _parent;

public:
  std::vector<Transform*> getChildren() const;

  Transform* getChild( const int index ) const;

  Transform* getParent() const;

  /**
   * \brief Attach a transform as child of this transform, this will not remove child from old parent and change its parent, you should not call this method directly
   * \param child Child transform to attach
   */
  void addChild( Transform* child );

  /**
   * \brief Detach a transform from this children, this will not reset child parent or object, you should not call this method directly
   * \param child Child transform to detach
   */
  void removeChild( Transform* child );

  void setParent(Transform* parent);
protected:
  void onRelease() override;

  void onUpdate( const float delta ) override;

  void onRender() override;

public:
  D3DXMATRIX calculateLocalToParentMatrix();
  D3DXMATRIX getLocalToWorldMatrix();
  D3DXMATRIX getWorldToLocalMatrix();
private:
  // specifies if the localToWorldTransform
  // needs to be recalulated
  bool _isDirty;
  // the transform that converts local coordinates
  // to world coordinates
  D3DXMATRIX _localToWorldMatrix;
  // specifies if the worldToLocalMatrix
  // needs to be recalculated
  bool _isInverseDirty;
  // the transform that converts world cooridnates
  // to local coordinates
  D3DXMATRIX _worldToLocalMatrix;

  void setDirty();
};
}

#endif //!__ALADDIN_CORE_TRANSFORM2_H__
