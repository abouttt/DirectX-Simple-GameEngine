#include "pch.h"
#include "MathUtil.h"
#include "Matrix4x4.h"
#include "Vector3.h"
#include "Quaternion.h"

const Matrix4x4 Matrix4x4::Identity = Matrix4x4(
	1.f, 0.f, 0.f, 0.f,
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f,
	0.f, 0.f, 0.f, 1.f);

const Matrix4x4 Matrix4x4::Zero = Matrix4x4(
	0.f, 0.f, 0.f, 0.f,
	0.f, 0.f, 0.f, 0.f,
	0.f, 0.f, 0.f, 0.f,
	0.f, 0.f, 0.f, 0.f);

Matrix4x4::Matrix4x4()
	: NativeMatrix()
{
}

Matrix4x4::Matrix4x4(const Matrix4x4& other)
	: NativeMatrix(other.NativeMatrix)
{
}

Matrix4x4::Matrix4x4(
	float _11, float _12, float _13, float _14,
	float _21, float _22, float _23, float _24,
	float _31, float _32, float _33, float _34,
	float _41, float _42, float _43, float _44)
	: NativeMatrix(
		_11, _12, _13, _14,
		_21, _22, _23, _24,
		_31, _32, _33, _34,
		_41, _42, _43, _44)
{
}

Matrix4x4 Matrix4x4::LookAt(const Vector3& from, const Vector3& to, const Vector3& up)
{
	Matrix4x4 result;
	D3DXMatrixLookAtLH(&result.NativeMatrix, &from.NativeVector3, &to.NativeVector3, &up.NativeVector3);
	return result;
}

Matrix4x4 Matrix4x4::Perspective(float fov, float aspect, float zn, float zf)
{
	Matrix4x4 result;
	D3DXMatrixPerspectiveFovLH(&result.NativeMatrix, fov, aspect, zn, zf);
	return result;
}

Matrix4x4 Matrix4x4::Ortho(float w, float h, float zn, float zf)
{
	Matrix4x4 result;
	D3DXMatrixOrthoLH(&result.NativeMatrix, w, h, zn, zf);
	return result;
}

Matrix4x4 Matrix4x4::Translate(const Vector3& v)
{
	Matrix4x4 result;
	D3DXMatrixTranslation(&result.NativeMatrix, v.X, v.Y, v.Z);
	return result;
}

Matrix4x4 Matrix4x4::Rotate(const Vector3& v)
{
	Matrix4x4 result;
	Quaternion rotation;
	D3DXQuaternionRotationYawPitchRoll(&rotation.NativeQuaternion, v.Y, v.X, v.Z);
	D3DXMatrixRotationQuaternion(&result.NativeMatrix, &rotation.NativeQuaternion);
	return result;
}

Matrix4x4 Matrix4x4::Rotate(const Quaternion& q)
{
	Matrix4x4 result;
	D3DXMatrixRotationQuaternion(&result.NativeMatrix, &q.NativeQuaternion);
	return result;
}

Matrix4x4 Matrix4x4::Scale(const Vector3& v)
{
	Matrix4x4 result;
	D3DXMatrixScaling(&result.NativeMatrix, v.X, v.Y, v.Z);
	return result;
}

bool Matrix4x4::IsIdentity()
{
	return *this == Identity;
}

float Matrix4x4::GetDeterminant() const
{
	return D3DXMatrixDeterminant(&NativeMatrix);
}

Matrix4x4 Matrix4x4::GetInverse() const
{
	Matrix4x4 result;
	float determinant = GetDeterminant();
	D3DXMatrixInverse(&result.NativeMatrix, &determinant, &NativeMatrix);
	return result;
}

Matrix4x4 Matrix4x4::GetTranspose() const
{
	return Matrix4x4(
		m[0][0], m[1][0], m[2][0], m[3][0],
		m[0][1], m[1][1], m[2][1], m[3][1],
		m[0][2], m[1][2], m[2][2], m[3][2],
		m[0][3], m[1][3], m[2][3], m[3][3]);
}

void Matrix4x4::SetIdentity()
{
	*this = Identity;
}

void Matrix4x4::SetInverse()
{
	float determinant = GetDeterminant();
	D3DXMatrixInverse(&NativeMatrix, &determinant, &NativeMatrix);
}

void Matrix4x4::SetTranspose()
{
	Matrix4x4 tmp(
		m[0][0], m[1][0], m[2][0], m[3][0],
		m[0][1], m[1][1], m[2][1], m[3][1],
		m[0][2], m[1][2], m[2][2], m[3][2],
		m[0][3], m[1][3], m[2][3], m[3][3]);
	*this = tmp;
}

void Matrix4x4::SetPerspective(float fov, float aspect, float zn, float zf)
{
	D3DXMatrixPerspectiveFovLH(&NativeMatrix, fov, aspect, zn, zf);
}

void Matrix4x4::SetOrtho(float w, float h, float zn, float zf)
{
	D3DXMatrixOrthoLH(&NativeMatrix, w, h, zn, zf);
}

float& Matrix4x4::operator()(int row, int col)
{
	return m[row][col];
}

float Matrix4x4::operator()(int row, int col) const
{
	return m[row][col];
}

Matrix4x4::operator float* ()
{
	return (float*)&_11;
}

Matrix4x4::operator const float* () const
{
	return (float*)&_11;
}

Matrix4x4& Matrix4x4::operator*=(const float d)
{
	NativeMatrix *= d;
	return *this;
}

Matrix4x4& Matrix4x4::operator/=(const float d)
{
	NativeMatrix /= d;
	return *this;
}

Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& other)
{
	NativeMatrix += other.NativeMatrix;
	return *this;
}

Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& other)
{
	NativeMatrix -= other.NativeMatrix;
	return *this;
}

Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& other)
{
	D3DXMatrixMultiply(&NativeMatrix, &NativeMatrix, &other.NativeMatrix);
	return *this;
}

Matrix4x4 Matrix4x4::operator*(float d)
{
	Matrix4x4 result;
	result.NativeMatrix = NativeMatrix * d;
	return result;
}

Matrix4x4 Matrix4x4::operator/(float d)
{
	Matrix4x4 result;
	result.NativeMatrix = NativeMatrix / d;
	return result;
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other)
{
	Matrix4x4 result;
	result.NativeMatrix = NativeMatrix + other.NativeMatrix;
	return result;
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& other)
{
	Matrix4x4 result;
	result.NativeMatrix = NativeMatrix - other.NativeMatrix;
	return result;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other)
{
	Matrix4x4 result;
	D3DXMatrixMultiply(&result.NativeMatrix, &NativeMatrix, &other.NativeMatrix);
	return result;
}

bool Matrix4x4::operator==(const Matrix4x4& other)
{
	return 0 == memcmp(this, &other, sizeof(D3DXMATRIX));
}

bool Matrix4x4::operator!=(const Matrix4x4& other)
{
	return 0 != memcmp(this, &other, sizeof(D3DXMATRIX));
}
