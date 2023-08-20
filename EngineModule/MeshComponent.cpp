#include "pch.h"

#include <Matrix4x4.h>

#include "Material.h"
#include "Mesh.h"
#include "Texture.h"

#include "MeshComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"

std::list<MeshComponent*> MeshComponent::mAllContainerPtr;
std::list<MeshComponent*> MeshComponent::mTrueContainerPtr;
std::list<MeshComponent*> MeshComponent::mFalseContainerPtr;

MeshComponent::MeshComponent()
    : BehaviourComponent(reinterpret_cast<std::list<BehaviourComponent*>&>(mAllContainerPtr))
    , mMeshPtr(nullptr)
    , mMaterialPtr(GetResources().GetMaterial(_T("Default-Material")))
{
    OnEnable();
}

MeshComponent::MeshComponent(Mesh* const mesh)
    : BehaviourComponent(reinterpret_cast<std::list<BehaviourComponent*>&>(mAllContainerPtr))
    , mMeshPtr(mesh)
    , mMaterialPtr(GetResources().GetMaterial(_T("Default-Material")))
{
    OnEnable();
}

MeshComponent::MeshComponent(Mesh* const mesh, Material* const material)
    : BehaviourComponent(reinterpret_cast<std::list<BehaviourComponent*>&>(mAllContainerPtr))
    , mMeshPtr(mesh)
    , mMaterialPtr(material)
{
    OnEnable();
}

MeshComponent::~MeshComponent()
{
    mMeshPtr = nullptr;
    mMaterialPtr = nullptr;

    RemoveThisAllContainer(
        reinterpret_cast<std::list<BehaviourComponent*>&>(mAllContainerPtr),
        reinterpret_cast<std::list<BehaviourComponent*>&>(mTrueContainerPtr),
        reinterpret_cast<std::list<BehaviourComponent*>&>(mFalseContainerPtr));
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
    InAndOutContainer(reinterpret_cast<std::list<BehaviourComponent*>&>(mTrueContainerPtr),
        reinterpret_cast<std::list<BehaviourComponent*>&>(mFalseContainerPtr));
}

void MeshComponent::OnDisable()
{
    InAndOutContainer(reinterpret_cast<std::list<BehaviourComponent*>&>(mFalseContainerPtr),
        reinterpret_cast<std::list<BehaviourComponent*>&>(mTrueContainerPtr));
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
