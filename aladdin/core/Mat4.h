#ifndef __ALADDIN_CORE_MAT4_H__
#define __ALADDIN_CORE_MAT4_H__

#include "ClassMeta.h"
#include "Vec2.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(Mat4)
private:
	float _11, _12, _13, _14;
	float _21, _22, _23, _24;
	float _31, _32, _33, _34;
	float _41, _42, _43, _44;
public:
	void operator += (const Mat4 &mat);
	void operator -= (const Mat4 &mat);
	void operator *= (float v);
	void operator /= (float v);
	Mat4 operator - () const;
	Mat4 operator + (const Mat4 &mat) const;
	Mat4 operator - (const Mat4 &mat) const;
	Mat4 operator * (const Mat4 &mat) const;
	Mat4 operator * (float v) const;
	Mat4 operator / (float v) const;

	static Mat4 getEmptyMat();
	static Mat4 getIdentityMat();

  float getDet() const;
  float getTrace() const;
	Mat4 getTranspose() const;
  Mat4 getInverse() const;

	static Mat4 getRotationXMatrix(float angle);
	static Mat4 getRotationYMatrix(float angle);
	static Mat4 getRotationZMatrix(float angle);

	static Mat4 getTranslationMatrix(Vec2 translation);
	static Mat4 getTranslationMatrix(float x, float y, float z);

	static Mat4 getScalingMatrix(Vec2 scale);
	static Mat4 getScalingMatrix(float x, float y, float z);

  D3DXMATRIX convertToDirectXMatrix() const;
};
}

#endif //!__ALADDIN_CORE_MAT4_H__
