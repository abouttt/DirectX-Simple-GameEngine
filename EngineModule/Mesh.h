#pragma once

class Mesh
{
public:
	Mesh(const std::wstring& name, ID3DXMesh* const nativeMesh);
	~Mesh();

public:
	const std::wstring& GetName() const;
	ID3DXMesh* GetNativeMesh();


private:
	const std::wstring mName;
	ID3DXMesh* mNativeMesh;
};

