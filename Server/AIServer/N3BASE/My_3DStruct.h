﻿#ifndef __MY_3DSTRUCT_H_
#define __MY_3DSTRUCT_H_

#include <d3dx9.h>
#include <d3dx9math.h>
#include <string>

const float __PI = 3.141592654f;
const float __PI2 = 6.283185308f;
const float FRAME_SELFPLAY = FLT_MIN;

struct __Vector2 : public D3DXVECTOR2 // 2D Vertex
{
public:
	void Zero();
	void Set(float fx, float fy);
	__Vector2() = default;
	__Vector2(float fx, float fy);
};

struct __Matrix44;
struct __Quaternion;

struct __Vector3 : public D3DXVECTOR3 // 3D Vertex
{
public:
	void	Normalize();
	float	Magnitude() const;
	float	Dot(const D3DXVECTOR3& vec) const;
	void	Cross(const D3DXVECTOR3& v1, const D3DXVECTOR3& v2);
	void	Absolute();

	void Zero();
	void Set(float fx, float fy, float fz);

	__Vector3() = default;
	__Vector3(float fx, float fy, float fz);
	__Vector3(const _D3DVECTOR& vec);
	__Vector3(const D3DXVECTOR3& vec);

	const __Vector3& operator = (const __Vector3& vec);

	const __Vector3 operator * (const D3DXMATRIX& mtx) const;
	void operator *= (float fDelta);
	void operator *= (const D3DXMATRIX& mtx);
	__Vector3 operator + (const D3DXVECTOR3& vec) const;
	__Vector3 operator - (const D3DXVECTOR3& vec) const;
	__Vector3 operator * (const D3DXVECTOR3& vec) const;
	__Vector3 operator / (const D3DXVECTOR3& vec) const;

	void operator += (const D3DXVECTOR3& vec);
	void operator -= (const D3DXVECTOR3& vec);
	void operator *= (const D3DXVECTOR3& vec);
	void operator /= (const D3DXVECTOR3& vec);

	__Vector3 operator + (float fDelta) const;
	__Vector3 operator - (float fDelta) const;
	__Vector3 operator * (float fDelta) const;
	__Vector3 operator / (float fDelta) const;
};

struct __Matrix44 : public D3DXMATRIX // 4x4 Matrix
{
public:
	void Zero();
	void Identity();
	const __Vector3 Pos() const;
	void PosSet(float x, float y, float z);
	void PosSet(const D3DXVECTOR3& v);
	void RotationX(float fDelta);
	void RotationY(float fDelta);
	void RotationZ(float fDelta);
	void Rotation(float fX, float fY, float fZ);
	void Rotation(const D3DXVECTOR3& v);
	void Scale(float sx, float sy, float sz);
	void Scale(const D3DXVECTOR3& v);

	void Direction(const D3DXVECTOR3& vDir);

	__Matrix44 operator * (const D3DXMATRIX& mtx);
	void operator *= (const D3DXMATRIX& mtx);
	void operator += (const D3DXVECTOR3& v);
	void operator -= (const D3DXVECTOR3& v);

	__Matrix44 operator * (const __Quaternion& qRot);
	void operator *= (const __Quaternion& qRot);

	void operator = (const D3DXQUATERNION& qt);

	__Matrix44() = default;
	__Matrix44(const _D3DMATRIX& mtx);
	__Matrix44(const D3DXMATRIX& mtx);
	__Matrix44(const D3DXQUATERNION& qt);
};

struct __Quaternion : public D3DXQUATERNION
{
public:
	void Identity();
	void Set(float fX, float fY, float fZ, float fW);

	void RotationAxis(const __Vector3& v, float fRadian);
	void RotationAxis(float fX, float fY, float fZ, float fRadian);
	void operator = (const D3DXMATRIX& mtx);

	void AxisAngle(__Vector3& vAxisResult, float& fRadianResult) const;
	void Slerp(const D3DXQUATERNION& qt1, const D3DXQUATERNION& qt2, float fDelta);

	__Quaternion() = default;
	__Quaternion(const D3DXMATRIX& mtx);
	__Quaternion(const D3DXQUATERNION& qt);
};

inline void __Vector2::Zero()
{
	x = y = 0;
}

inline void __Vector2::Set(float fx, float fy)
{
	x = fx;
	y = fy;
}

inline __Vector2::__Vector2(float fx, float fy)
{
	x = fx;
	y = fy;
}

inline void	__Vector3::Normalize()
{
	float fn = sqrtf((x * x) + (y * y) + (z * z));
	if (fn == 0)
		return;

	x /= fn;
	y /= fn;
	z /= fn;
}

inline float __Vector3::Magnitude() const
{
	return sqrtf((x * x) + (y * y) + (z * z));
}

inline float __Vector3::Dot(const D3DXVECTOR3& vec) const
{
	return (x * vec.x) + (y * vec.y) + (z * vec.z);
}

inline void __Vector3::Cross(const D3DXVECTOR3& v1, const D3DXVECTOR3& v2)
{
	x = (v1.y * v2.z) - (v1.z * v2.y);
	y = (v1.z * v2.x) - (v1.x * v2.z);
	z = (v1.x * v2.y) - (v1.y * v2.x);
}

inline void __Vector3::Absolute()
{
	if (x < 0)
		x *= -1.0f;

	if (y < 0)
		y *= -1.0f;

	if (z < 0)
		z *= -1.0f;
}

inline void __Vector3::Zero()
{
	x = y = z = 0;
}

inline void __Vector3::Set(float fx, float fy, float fz)
{
	x = fx;
	y = fy;
	z = fz;
}

//inline __Vector3::__Vector3()
//{
//}

inline __Vector3::__Vector3(float fx, float fy, float fz)
{
	x = fx;
	y = fy;
	z = fz;
}

inline __Vector3::__Vector3(const D3DXVECTOR3& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

inline __Vector3::__Vector3(const _D3DVECTOR& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

inline const __Vector3& __Vector3::operator = (const __Vector3& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	return *this;
}

inline const __Vector3 __Vector3::operator * (const D3DXMATRIX& mtx) const
{
	static __Vector3 vTmp;

	vTmp.x = (x * mtx._11) + (y * mtx._21) + (z * mtx._31 + mtx._41);
	vTmp.y = (x * mtx._12) + (y * mtx._22) + (z * mtx._32 + mtx._42);
	vTmp.z = (x * mtx._13) + (y * mtx._23) + (z * mtx._33 + mtx._43);

	return vTmp;
}

inline void __Vector3::operator *= (float fDelta)
{
	x *= fDelta;
	y *= fDelta;
	z *= fDelta;
}

inline void __Vector3::operator *= (const D3DXMATRIX& mtx)
{
	static __Vector3 vTmp;

	vTmp.Set(x, y, z);
	x = (vTmp.x * mtx._11) + (vTmp.y * mtx._21) + (vTmp.z * mtx._31) + mtx._41;
	y = (vTmp.x * mtx._12) + (vTmp.y * mtx._22) + (vTmp.z * mtx._32) + mtx._42;
	z = (vTmp.x * mtx._13) + (vTmp.y * mtx._23) + (vTmp.z * mtx._33) + mtx._43;
}

inline __Vector3 __Vector3::operator + (const D3DXVECTOR3& vec) const
{
	static __Vector3 vTmp;

	vTmp.x = x + vec.x;
	vTmp.y = y + vec.y;
	vTmp.z = z + vec.z;
	return vTmp;
}

inline __Vector3 __Vector3::operator - (const D3DXVECTOR3& vec) const
{
	static __Vector3 vTmp;

	vTmp.x = x - vec.x;
	vTmp.y = y - vec.y;
	vTmp.z = z - vec.z;
	return vTmp;
}

inline __Vector3 __Vector3::operator * (const D3DXVECTOR3& vec) const
{
	static __Vector3 vTmp;

	vTmp.x = x * vec.x;
	vTmp.y = y * vec.y;
	vTmp.z = z * vec.z;
	return vTmp;
}

inline __Vector3 __Vector3::operator / (const D3DXVECTOR3& vec) const
{
	static __Vector3 vTmp;

	vTmp.x = x / vec.x;
	vTmp.y = y / vec.y;
	vTmp.z = z / vec.z;
	return vTmp;
}

inline void __Vector3::operator += (const D3DXVECTOR3& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
}

inline void __Vector3::operator -= (const D3DXVECTOR3& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
}

inline void __Vector3::operator *= (const D3DXVECTOR3& vec)
{
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;
}

inline void __Vector3::operator /= (const D3DXVECTOR3& vec)
{
	x /= vec.x;
	y /= vec.y;
	z /= vec.z;
}

inline __Vector3 __Vector3::operator + (float fDelta) const
{
	static __Vector3 vTmp;

	vTmp.x = x + fDelta;
	vTmp.y = y + fDelta;
	vTmp.z = z + fDelta;
	return vTmp;
}

inline __Vector3 __Vector3::operator - (float fDelta) const
{
	static __Vector3 vTmp;

	vTmp.x = x - fDelta;
	vTmp.y = y - fDelta;
	vTmp.z = z - fDelta;
	return vTmp;
}

inline __Vector3 __Vector3::operator * (float fDelta) const
{
	static __Vector3 vTmp;

	vTmp.x = x * fDelta;
	vTmp.y = y * fDelta;
	vTmp.z = z * fDelta;
	return vTmp;
}

inline __Vector3 __Vector3::operator / (float fDelta) const
{
	static __Vector3 vTmp;

	vTmp.x = x / fDelta;
	vTmp.y = y / fDelta;
	vTmp.z = z / fDelta;
	return vTmp;
}


inline void __Matrix44::Zero()
{
	memset(this, 0, sizeof(_D3DMATRIX));
}

inline void __Matrix44::Identity()
{
	_12 = _13 = _14 = _21 = _23 = _24 = _31 = _32 = _34 = _41 = _42 = _43 = 0;
	_11 = _22 = _33 = _44 = 1.0f;
}

inline const __Vector3 __Matrix44::Pos() const
{
	static __Vector3 vTmp;

	vTmp.Set(_41, _42, _43);
	return vTmp;
}

inline void __Matrix44::PosSet(float x, float y, float z)
{
	_41 = x; _42 = y; _43 = z;
}

inline void __Matrix44::PosSet(const D3DXVECTOR3& v)
{
	_41 = v.x;
	_42 = v.y;
	_43 = v.z;
}

inline void __Matrix44::RotationX(float fDelta)
{
	Identity();
	_22 = cosf(fDelta); _23 = sinf(fDelta); _32 = -_23; _33 = _22;
}

inline void __Matrix44::RotationY(float fDelta)
{
	Identity();
	_11 = cosf(fDelta); _13 = -sinf(fDelta); _31 = -_13; _33 = _11;
}

inline void __Matrix44::RotationZ(float fDelta)
{
	Identity();
	_11 = cosf(fDelta); _12 = sinf(fDelta); _21 = -_12; _22 = _11;
}

inline void __Matrix44::Rotation(float fX, float fY, float fZ)
{
	float SX = sinf(fX), CX = cosf(fX);
	float SY = sinf(fY), CY = cosf(fY);
	float SZ = sinf(fZ), CZ = cosf(fZ);
	_11 = CY * CZ;
	_12 = CY * SZ;
	_13 = -SY;
	_14 = 0;

	_21 = SX * SY * CZ - CX * SZ;
	_22 = SX * SY * SZ + CX * CZ;
	_23 = SX * CY;
	_24 = 0;

	_31 = CX * SY * CZ + SX * SZ;
	_32 = CX * SY * SZ - SX * CZ;
	_33 = CX * CY;
	_34 = 0;

	_41 = _42 = _43 = 0; _44 = 1;
}

inline void __Matrix44::Rotation(const D3DXVECTOR3& v)
{
	float SX = sinf(v.x), CX = cosf(v.x);
	float SY = sinf(v.y), CY = cosf(v.y);
	float SZ = sinf(v.z), CZ = cosf(v.z);
	_11 = CY * CZ;
	_12 = CY * SZ;
	_13 = -SY;
	_14 = 0;

	_21 = SX * SY * CZ - CX * SZ;
	_22 = SX * SY * SZ + CX * CZ;
	_23 = SX * CY;
	_24 = 0;

	_31 = CX * SY * CZ + SX * SZ;
	_32 = CX * SY * SZ - SX * CZ;
	_33 = CX * CY;
	_34 = 0;

	_41 = _42 = _43 = 0; _44 = 1;
}

inline void __Matrix44::Scale(float sx, float sy, float sz)
{
	Identity();
	_11 = sx; _22 = sy; _33 = sz;
}

inline void __Matrix44::Scale(const D3DXVECTOR3& v)
{
	this->Identity();
	_11 = v.x; _22 = v.y; _33 = v.z;
}

inline __Matrix44::__Matrix44(const _D3DMATRIX& mtx)
{
	memcpy(this, &mtx, sizeof(_D3DMATRIX));
}

inline __Matrix44::__Matrix44(const D3DXMATRIX& mtx)
{
	memcpy(this, &mtx, sizeof(D3DXMATRIX));
}

inline __Matrix44::__Matrix44(const D3DXQUATERNION& qt)
{
	D3DXMatrixRotationQuaternion(this, &qt);
}

inline __Matrix44 __Matrix44::operator * (const D3DXMATRIX& mtx)
{
	static __Matrix44 mtxTmp;

	mtxTmp._11 = _11 * mtx._11 + _12 * mtx._21 + _13 * mtx._31 + _14 * mtx._41;
	mtxTmp._12 = _11 * mtx._12 + _12 * mtx._22 + _13 * mtx._32 + _14 * mtx._42;
	mtxTmp._13 = _11 * mtx._13 + _12 * mtx._23 + _13 * mtx._33 + _14 * mtx._43;
	mtxTmp._14 = _11 * mtx._14 + _12 * mtx._24 + _13 * mtx._34 + _14 * mtx._44;

	mtxTmp._21 = _21 * mtx._11 + _22 * mtx._21 + _23 * mtx._31 + _24 * mtx._41;
	mtxTmp._22 = _21 * mtx._12 + _22 * mtx._22 + _23 * mtx._32 + _24 * mtx._42;
	mtxTmp._23 = _21 * mtx._13 + _22 * mtx._23 + _23 * mtx._33 + _24 * mtx._43;
	mtxTmp._24 = _21 * mtx._14 + _22 * mtx._24 + _23 * mtx._34 + _24 * mtx._44;

	mtxTmp._31 = _31 * mtx._11 + _32 * mtx._21 + _33 * mtx._31 + _34 * mtx._41;
	mtxTmp._32 = _31 * mtx._12 + _32 * mtx._22 + _33 * mtx._32 + _34 * mtx._42;
	mtxTmp._33 = _31 * mtx._13 + _32 * mtx._23 + _33 * mtx._33 + _34 * mtx._43;
	mtxTmp._34 = _31 * mtx._14 + _32 * mtx._24 + _33 * mtx._34 + _34 * mtx._44;

	mtxTmp._41 = _41 * mtx._11 + _42 * mtx._21 + _43 * mtx._31 + _44 * mtx._41;
	mtxTmp._42 = _41 * mtx._12 + _42 * mtx._22 + _43 * mtx._32 + _44 * mtx._42;
	mtxTmp._43 = _41 * mtx._13 + _42 * mtx._23 + _43 * mtx._33 + _44 * mtx._43;
	mtxTmp._44 = _41 * mtx._14 + _42 * mtx._24 + _43 * mtx._34 + _44 * mtx._44;

	// 최적화 된 코드..	
	// dino 막음.. 아래 코드는 4번째 행들의 계산을 생략하여서 부정확한 계산을 한다.
	// 보통 4번째 행이 (0, 0, 0, 1)인 matrix를 쓰지만 projection matrix의 경우
	// (0, 0, 1, 0)인 matrix를 쓰므로 이상한 결과를 초래한다.
//	mtxTmp._11 = _11 * mtx._11 + _12 * mtx._21 + _13 * mtx._31;
//	mtxTmp._12 = _11 * mtx._12 + _12 * mtx._22 + _13 * mtx._32;
//	mtxTmp._13 = _11 * mtx._13 + _12 * mtx._23 + _13 * mtx._33;
//	mtxTmp._14 = 0;

//	mtxTmp._21 = _21 * mtx._11 + _22 * mtx._21 + _23 * mtx._31;
//	mtxTmp._22 = _21 * mtx._12 + _22 * mtx._22 + _23 * mtx._32;
//	mtxTmp._23 = _21 * mtx._13 + _22 * mtx._23 + _23 * mtx._33;
//	mtxTmp._24 = 0;

//	mtxTmp._31 = _31 * mtx._11 + _32 * mtx._21 + _33 * mtx._31;
//	mtxTmp._32 = _31 * mtx._12 + _32 * mtx._22 + _33 * mtx._32;
//	mtxTmp._33 = _31 * mtx._13 + _32 * mtx._23 + _33 * mtx._33;
//	mtxTmp._34 = 0;

//	mtxTmp._41 = _41 * mtx._11 + _42 * mtx._21 + _43 * mtx._31 + mtx._41;
//	mtxTmp._42 = _41 * mtx._12 + _42 * mtx._22 + _43 * mtx._32 + mtx._42;
//	mtxTmp._43 = _41 * mtx._13 + _42 * mtx._23 + _43 * mtx._33 + mtx._43;
//	mtxTmp._44 = 1.0f;

	return mtxTmp;
}

inline void __Matrix44::operator *= (const D3DXMATRIX& mtx)
{
	static __Matrix44 mtxTmp;

	memcpy(&mtxTmp, this, sizeof(__Matrix44));

	_11 = mtxTmp._11 * mtx._11 + mtxTmp._12 * mtx._21 + mtxTmp._13 * mtx._31 + mtxTmp._14 * mtx._41;
	_12 = mtxTmp._11 * mtx._12 + mtxTmp._12 * mtx._22 + mtxTmp._13 * mtx._32 + mtxTmp._14 * mtx._42;
	_13 = mtxTmp._11 * mtx._13 + mtxTmp._12 * mtx._23 + mtxTmp._13 * mtx._33 + mtxTmp._14 * mtx._43;
	_14 = mtxTmp._11 * mtx._14 + mtxTmp._12 * mtx._24 + mtxTmp._13 * mtx._34 + mtxTmp._14 * mtx._44;

	_21 = mtxTmp._21 * mtx._11 + mtxTmp._22 * mtx._21 + mtxTmp._23 * mtx._31 + mtxTmp._24 * mtx._41;
	_22 = mtxTmp._21 * mtx._12 + mtxTmp._22 * mtx._22 + mtxTmp._23 * mtx._32 + mtxTmp._24 * mtx._42;
	_23 = mtxTmp._21 * mtx._13 + mtxTmp._22 * mtx._23 + mtxTmp._23 * mtx._33 + mtxTmp._24 * mtx._43;
	_24 = mtxTmp._21 * mtx._14 + mtxTmp._22 * mtx._24 + mtxTmp._23 * mtx._34 + mtxTmp._24 * mtx._44;

	_31 = mtxTmp._31 * mtx._11 + mtxTmp._32 * mtx._21 + mtxTmp._33 * mtx._31 + mtxTmp._34 * mtx._41;
	_32 = mtxTmp._31 * mtx._12 + mtxTmp._32 * mtx._22 + mtxTmp._33 * mtx._32 + mtxTmp._34 * mtx._42;
	_33 = mtxTmp._31 * mtx._13 + mtxTmp._32 * mtx._23 + mtxTmp._33 * mtx._33 + mtxTmp._34 * mtx._43;
	_34 = mtxTmp._31 * mtx._14 + mtxTmp._32 * mtx._24 + mtxTmp._33 * mtx._34 + mtxTmp._34 * mtx._44;

	_41 = mtxTmp._41 * mtx._11 + mtxTmp._42 * mtx._21 + mtxTmp._43 * mtx._31 + mtxTmp._44 * mtx._41;
	_42 = mtxTmp._41 * mtx._12 + mtxTmp._42 * mtx._22 + mtxTmp._43 * mtx._32 + mtxTmp._44 * mtx._42;
	_43 = mtxTmp._41 * mtx._13 + mtxTmp._42 * mtx._23 + mtxTmp._43 * mtx._33 + mtxTmp._44 * mtx._43;
	_44 = mtxTmp._41 * mtx._14 + mtxTmp._42 * mtx._24 + mtxTmp._43 * mtx._34 + mtxTmp._44 * mtx._44;

	// dino 막음.. 아래 코드는 4번째 행들의 계산을 생략하여서 부정확한 계산을 한다.
	// 보통 4번째 행이 (0, 0, 0, 1)인 matrix를 쓰지만 projection matrix의 경우
	// (0, 0, 1, 0)인 matrix를 쓰므로 이상한 결과를 초래한다.
//	_11 = mtxTmp._11 * mtx._11 + mtxTmp._12 * mtx._21 + mtxTmp._13 * mtx._31;
//	_12 = mtxTmp._11 * mtx._12 + mtxTmp._12 * mtx._22 + mtxTmp._13 * mtx._32;
//	_13 = mtxTmp._11 * mtx._13 + mtxTmp._12 * mtx._23 + mtxTmp._13 * mtx._33;
//	_14 = 0;

//	_21 = mtxTmp._21 * mtx._11 + mtxTmp._22 * mtx._21 + mtxTmp._23 * mtx._31 + mtxTmp._24 * mtx._41;
//	_22 = mtxTmp._21 * mtx._12 + mtxTmp._22 * mtx._22 + mtxTmp._23 * mtx._32 + mtxTmp._24 * mtx._42;
//	_23 = mtxTmp._21 * mtx._13 + mtxTmp._22 * mtx._23 + mtxTmp._23 * mtx._33 + mtxTmp._24 * mtx._43;
//	_24 = 0;

//	_31 = mtxTmp._31 * mtx._11 + mtxTmp._32 * mtx._21 + mtxTmp._33 * mtx._31 + mtxTmp._34 * mtx._41;
//	_32 = mtxTmp._31 * mtx._12 + mtxTmp._32 * mtx._22 + mtxTmp._33 * mtx._32 + mtxTmp._34 * mtx._42;
//	_33 = mtxTmp._31 * mtx._13 + mtxTmp._32 * mtx._23 + mtxTmp._33 * mtx._33 + mtxTmp._34 * mtx._43;
//	_34 = 0;

//	_41 = mtxTmp._41 * mtx._11 + mtxTmp._42 * mtx._21 + mtxTmp._43 * mtx._31 + mtx._41;
//	_42 = mtxTmp._41 * mtx._12 + mtxTmp._42 * mtx._22 + mtxTmp._43 * mtx._32 + mtx._42;
//	_43 = mtxTmp._41 * mtx._13 + mtxTmp._42 * mtx._23 + mtxTmp._43 * mtx._33 + mtx._43;
//	_44 = 1;
}

inline void __Matrix44::operator += (const D3DXVECTOR3& v)
{
	_41 += v.x;
	_42 += v.y;
	_43 += v.z;
}

inline void __Matrix44::operator -= (const D3DXVECTOR3& v)
{
	_41 -= v.x;
	_42 -= v.y;
	_43 -= v.z;
}

inline __Matrix44 __Matrix44::operator * (const __Quaternion& qRot)
{
	static __Matrix44 mtx;
	mtx.operator = (qRot);

	return this->operator * (mtx);
}

inline void __Matrix44::operator *= (const __Quaternion& qRot)
{
	static __Matrix44 mtx;
	mtx.operator = (qRot);

	this->operator *= (mtx);
}

inline void __Matrix44::operator = (const D3DXQUATERNION& qt)
{
	D3DXMatrixRotationQuaternion(this, &qt);
}

inline void __Matrix44::Direction(const D3DXVECTOR3& vDir)
{
	Identity();

	static __Vector3 vDir2, vRight, vUp;
	vUp.Set(0, 1, 0);
	vDir2 = vDir;
	vDir2.Normalize();
	vRight.Cross(vUp, vDir2); // right = CrossProduct(world_up, view_dir);
	vUp.Cross(vDir2, vRight); // up = CrossProduct(view_dir, right);
	vRight.Normalize(); // right = Normalize(right);
	vUp.Normalize(); // up = Normalize(up);

	_11 = vRight.x; // view(0, 0) = right.x;
	_21 = vRight.y; // view(1, 0) = right.y;
	_31 = vRight.z; // view(2, 0) = right.z;
	_12 = vUp.x; // view(0, 1) = up.x;
	_22 = vUp.y; // view(1, 1) = up.y;
	_32 = vUp.z; // view(2, 1) = up.z;
	_13 = vDir2.x; // view(0, 2) = view_dir.x;
	_23 = vDir2.y; // view(1, 2) = view_dir.y;
	_33 = vDir2.z; // view(2, 2) = view_dir.z;

	D3DXMatrixInverse(this, nullptr, this);

//  view(3, 0) = -DotProduct(right, from);
//  view(3, 1) = -DotProduct(up, from);
//  view(3, 2) = -DotProduct(view_dir, from);

	// Set roll
//	if (roll != 0.0f) {
//		view = MatrixMult(RotateZMatrix(-roll), view);
//	}

//  return view;
//} // end ViewMatrix
}

inline void __Quaternion::Identity()
{
	x = y = z = 0;
	w = 1.0f;
}

inline void __Quaternion::Set(float fX, float fY, float fZ, float fW)
{
	x = fX;
	y = fY;
	z = fZ;
	w = fW;
}

inline void __Quaternion::RotationAxis(const __Vector3& v, float fRadian)
{
	D3DXQuaternionRotationAxis(this, &v, fRadian);
}

inline void __Quaternion::RotationAxis(float fX, float fY, float fZ, float fRadian)
{
	__Vector3 v(fX, fY, fZ);
	D3DXQuaternionRotationAxis(this, &v, fRadian);
}

inline void __Quaternion::operator = (const D3DXMATRIX& mtx)
{
	D3DXQuaternionRotationMatrix(this, &mtx);
}

inline void __Quaternion::AxisAngle(__Vector3& vAxisResult, float& fRadianResult) const
{
	D3DXQuaternionToAxisAngle(this, &vAxisResult, &fRadianResult);
}

inline void __Quaternion::Slerp(const D3DXQUATERNION& qt1, const D3DXQUATERNION& qt2, float fDelta)
{
	D3DXQuaternionSlerp(this, &qt1, &qt2, fDelta);
}

inline __Quaternion::__Quaternion(const D3DXMATRIX& mtx)
{
	D3DXQuaternionRotationMatrix(this, &mtx);
}

inline __Quaternion::__Quaternion(const D3DXQUATERNION& qt)
{
	x = qt.x;
	y = qt.y;
	z = qt.z;
	w = qt.w;
}

#include "CrtDbg.h"

#ifndef _DEBUG
#define __ASSERT(expr, expMessage) void(0)
#else
#define __ASSERT(expr, expMessage) \
if(!(expr)) \
{ \
	_CrtDbgReport(_CRT_ASSERT, __FILE__, __LINE__, "N3 Custom Assert Functon", expMessage); \
	char __szErr[512]; \
	sprintf(__szErr, "  ---- N3 Assert Warning (File:%s, Line:%d) ---- \n", __FILE__, __LINE__); \
	OutputDebugString(__szErr); \
	sprintf(__szErr, "    : %s\n", expMessage); \
	OutputDebugString(__szErr); \
	_CrtDbgBreak(); \
}
#endif

bool			_IntersectTriangle(const __Vector3& vOrig, const __Vector3& vDir, const __Vector3& v0, const __Vector3& v1, const __Vector3& v2, float& fT, float& fU, float& fV, __Vector3* pVCol = nullptr);
bool			_IntersectTriangle(const __Vector3& vOrig, const __Vector3& vDir, const __Vector3& v0, const __Vector3& v1, const __Vector3& v2);
void			_Convert2D_To_3DCoordinate(int ixScreen, int iyScreen, const __Matrix44& mtxView, const __Matrix44& mtxPrj, const D3DVIEWPORT9& vp, __Vector3& vPosResult, __Vector3& vDirResult);
float			_Yaw2D(float fDirX, float fDirZ);

inline bool _IntersectTriangle(const __Vector3& vOrig, const __Vector3& vDir,
							  const __Vector3& v0, const __Vector3& v1, const __Vector3& v2,
							  float& fT, float& fU, float& fV, __Vector3* pVCol)
{
	// Find vectors for two edges sharing vert0
	static __Vector3 vEdge1, vEdge2;

	vEdge1 = v1 - v0;
	vEdge2 = v2 - v0;

	// Begin calculating determinant - also used to calculate U parameter
	__Vector3 pVec;	float fDet;

//	By : Ecli666 ( On 2001-09-12 오전 10:39:01 )

	pVec.Cross(vEdge1, vEdge2);
	fDet = pVec.Dot(vDir);
	if (fDet > -0.0001f)
		return FALSE;

//	~(By Ecli666 On 2001-09-12 오전 10:39:01 )

	pVec.Cross(vDir, vEdge2);

	// If determinant is near zero, ray lies in plane of triangle
	fDet = vEdge1.Dot(pVec);
	if (fDet < 0.0001f)		// 거의 0에 가까우면 삼각형 평면과 지나가는 선이 평행하다.
		return FALSE;

	// Calculate distance from vert0 to ray origin
	__Vector3 tVec = vOrig - v0;

	// Calculate U parameter and test bounds
	fU = tVec.Dot(pVec);
	if (fU < 0.0f || fU > fDet)
		return FALSE;

	// Prepare to test V parameter
	__Vector3 qVec;
	qVec.Cross(tVec, vEdge1);

	// Calculate V parameter and test bounds
	fV = D3DXVec3Dot(&vDir, &qVec);
	if (fV < 0.0f || fU + fV > fDet)
		return FALSE;

	// Calculate t, scale parameters, ray intersects triangle
	fT = D3DXVec3Dot(&vEdge2, &qVec);
	float fInvDet = 1.0f / fDet;
	fT *= fInvDet;
	fU *= fInvDet;
	fV *= fInvDet;

	// t가 클수록 멀리 직선과 평면과 만나는 점이 멀다.
	// t*dir + orig 를 구하면 만나는 점을 구할 수 있다.
	// u와 v의 의미는 무엇일까?
	// 추측 : v0 (0,0), v1(1,0), v2(0,1) <괄호안은 (U, V)좌표> 이런식으로 어느 점에 가깝나 나타낸 것 같음
	//

	if (pVCol) (*pVCol) = vOrig + (vDir * fT);	// 접점을 계산..

	// *t < 0 이면 뒤쪽...
	if (fT < 0.0f)
		return FALSE;

	return TRUE;
}

inline bool _IntersectTriangle(const __Vector3& vOrig, const __Vector3& vDir, const __Vector3& v0, const __Vector3& v1, const __Vector3& v2)
{
	// Find vectors for two edges sharing vert0
	// Begin calculating determinant - also used to calculate U parameter
	static float fDet, fT, fU, fV;
	static __Vector3 vEdge1, vEdge2, tVec, pVec, qVec;

	vEdge1 = v1 - v0;
	vEdge2 = v2 - v0;


//	By : Ecli666 ( On 2001-09-12 오전 10:39:01 )

	pVec.Cross(vEdge1, vEdge2);
	fDet = pVec.Dot(vDir);
	if (fDet > -0.0001f)
		return FALSE;

//	~(By Ecli666 On 2001-09-12 오전 10:39:01 )

	pVec.Cross(vDir, vEdge2);

	// If determinant is near zero, ray lies in plane of triangle
	fDet = vEdge1.Dot(pVec);
	if (fDet < 0.0001f)		// 거의 0에 가까우면 삼각형 평면과 지나가는 선이 평행하다.
		return FALSE;

	// Calculate distance from vert0 to ray origin
	tVec = vOrig - v0;

	// Calculate U parameter and test bounds
	fU = tVec.Dot(pVec);
	if (fU < 0.0f || fU > fDet)
		return FALSE;

	// Prepare to test V parameter
	qVec.Cross(tVec, vEdge1);

	// Calculate V parameter and test bounds
	fV = D3DXVec3Dot(&vDir, &qVec);
	if (fV < 0.0f || fU + fV > fDet)
		return FALSE;

	// Calculate t, scale parameters, ray intersects triangle
	fT = D3DXVec3Dot(&vEdge2, &qVec) / fDet;

	// *t < 0 이면 뒤쪽...
	if (fT < 0.0f)
		return FALSE;

	return TRUE;
}

inline void _Convert2D_To_3DCoordinate(int ixScreen, int iyScreen,
										const __Matrix44& mtxView, const __Matrix44& mtxPrj, const D3DVIEWPORT9& vp,
										__Vector3& vPosResult, __Vector3& vDirResult)
{
	// Compute the vector of the pick ray in screen space
	static __Vector3 vTmp;

	vTmp.x = (((2.0f * ixScreen) / (vp.Width)) - 1) / mtxPrj._11;
	vTmp.y = -(((2.0f * iyScreen) / (vp.Height)) - 1) / mtxPrj._22;
	vTmp.z = 1.0f;

	// Transform the screen space pick ray into 3D space
	__Matrix44 mtxVI;
	::D3DXMatrixInverse(&mtxVI, nullptr, &mtxView);
	vDirResult.x = vTmp.x * mtxVI._11 + vTmp.y * mtxVI._21 + vTmp.z * mtxVI._31;
	vDirResult.y = vTmp.x * mtxVI._12 + vTmp.y * mtxVI._22 + vTmp.z * mtxVI._32;
	vDirResult.z = vTmp.x * mtxVI._13 + vTmp.y * mtxVI._23 + vTmp.z * mtxVI._33;
	vPosResult = mtxVI.Pos();
}

inline void _LoadStringFromResource(DWORD dwID, std::string& szText)
{
	static char szBuffer[512];
	szBuffer[0] = '\0';
//	::LoadString(nullptr, MAKEINTRESOURCE(dwID), szBuffer, 256);
	::LoadString(nullptr, dwID, szBuffer, 256);
	szText = szBuffer;
}

#endif // __MY_3DSTRUCT_H_

