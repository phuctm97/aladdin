#ifndef __ALADDIN_2D_2D_MACROS_H__
#define __ALADDIN_2D_2D_MACROS_H__

/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "../core/CoreMacros.h"

#define ALA_MAIN_CAMERA "Aladdin Main Camera"

#define ALA_EMPTY_SPRITE(R, G, B, A) ("Aladdin Empty Sprite " + std::string({ (char)(R), (char)(G), (char)(B), (char)(A) }))
#define ALA_EMPTY_RED_SPRITE "Aladdin Empty Red Sprite"
#define ALA_EMPTY_GREEN_SPRITE "Aladdin Empty Green Sprite"
#define ALA_EMPTY_BLUE_SPRITE "Aladdin Empty Blue Sprite"

#define ALA_CAMERA_MIN_Z 0.0f
#define ALA_CAMERA_MAX_Z 100000.0f

#define ALA_MAX_Z_ORDER 999

#endif //!__ALADDIN_2D_2D_MACROS_H__
