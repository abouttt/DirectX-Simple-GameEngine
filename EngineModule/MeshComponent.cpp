#include "pch.h"

#include <Matrix4x4.h>

#include "Material.h"
#include "Mesh.h"
#include "Texture.h"

#include "MeshComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"

std::list<MeshComponent*> MeshComponent::mContainerPtr;
std::list<MeshComponent*> MeshComponent::mEnabledTruePtr;
std::list<MeshComponent*> MeshComponent::mEnabledFalsePtr;

MeshComponent::MeshComponent()
    : mMeshPtr(nullptr)
    , mMaterialPtr(GetResources().GetMaterial(_T("Default-Material")))
{
    mContainerPtr.emplace_back(this);

    //
    OnEnable();
}

MeshComponent::MeshComponent(Mesh* const mesh)
    : mMeshPtr(mesh)
    , mMaterialPtr(GetResources().GetMaterial(_T("Default-Material")))
{
    mContainerPtr.emplace_back(this);

    //
    OnEnable();
}

MeshComponent::MeshComponent(Mesh* const mesh, Material* const material)
    : mMeshPtr(mesh)
    , mMaterialPtr(material)
{
    mContainerPtr.emplace_back(this);

    //
    OnEnable();
}

MeshComponent::~MeshComponent()
{
    mContainerPtr.erase(std::find(mContainerPtr.begin(), mContainerPtr.end(), this));
    mMeshPtr = nullptr;
    mMaterialPtr = nullptr;
}

Mesh* MeshComponent::GetMesh()
{
    return mMeshPtr;
}

Material* MeshComponent::GetMaterial()
{
    return mMaterialPtr;
}

void MeshComponent::SetMesh(Mesh* const mesh)
{
    mMeshPtr = mesh;
}

void MeshComponent::SetMaterial(Material* const material)
{
    mMaterialPtr = material;
}

void MeshComponent::OnEnable()
{
    for (auto it = mEnabledFalsePtr.begin(); it != mEnabledFalsePtr.end();)
    {
        if (*it == this)
        {
            mEnabledFalsePtr.erase(it);
            break;
        }
    }

    mEnabledTruePtr.emplace_back(this);
}

void MeshComponent::OnDisable()
{
    for (auto it = mEnabledTruePtr.begin(); it != mEnabledTruePtr.end();)
    {
        if (*it == this)
        {
            mEnabledTruePtr.erase(it);
            break;
        }
    }

    mEnabledFalsePtr.emplace_back(this);
}

void MeshComponent::render(IDirect3DDevice9* const device)
{
    assert(device);

    if (!mMeshPtr)
    {
        return;
    }

    auto matWorld = GetTransform()->GetMatrix();
    device->SetTransform(D3DTS_WORLD, &matWorld.NativeMatrix);

    D3DMATERIAL9 nativeMtrl;
    ::ZeroMemory(&nativeMtrl, sizeof(D3DMATERIAL9));
    device->SetMaterial(&nativeMtrl);
    device->SetTexture(0, nullptr);

    if (mMaterialPtr)
    {
        switch (mMaterialPtr->GetRenderingMode())
        {
        case eRenderingMode::Cutout:
            device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
            break;
        default:
            device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
            break;
        }

        device->SetMaterial(&mMaterialPtr->GetNativeMaterial());

        auto texture = mMaterialPtr->GetTexture();
        if (texture)
        {
            device->SetTexture(0, texture->GetNativeTexture());
        }
    }

    mMeshPtr->GetNativeMesh()->DrawSubset(0);
}
