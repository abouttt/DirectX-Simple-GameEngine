#include "pch.h"
#include "Mesh.h"

Mesh::Mesh(const std::wstring* name, ID3DXMesh* const nativeMesh)
	: mName(name)
	, mNativeMesh(nativeMesh)
{
}

Mesh::~Mesh()
{
	if (mNativeMesh)
	{
		mNativeMesh->Release();
		mNativeMesh = nullptr;
	}
}

const std::wstring& Mesh::GetName() const
{
	return *mName;
}

ID3DXMesh* Mesh::GetNativeMesh()
{
	return mNativeMesh;
}
