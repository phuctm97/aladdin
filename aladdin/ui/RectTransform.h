#ifndef __RECT_TRANSFORM_H__
#define __RECT_TRANSFORM_H__

#include "../core/Transform.h"
#include "../2d/Rect.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1 ( RectTransform, ala::Transform )
private:
  Rect _boundingRect;
public:
  RectTransform(GameObject* gameObject, const Rect& rect, Transform* parentTransform = NULL, const std::string& name = "");
  virtual ~RectTransform();

  const Rect& getBoundingRect() const;
  void setBoundingRect(const Rect& rect);

};
}
#endif //!__RECT_TRANSFORM_H__