#ifndef __BITMAP_TEXT_PREFAB_H__
#define __BITMAP_TEXT_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(BitmapTextPrefab, ala::PrefabV2)
public:
  BitmapTextPrefab()
    : PrefabV2( "Bitmap Text" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__BITMAP_TEXT_PREFAB_H__
