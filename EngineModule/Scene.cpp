#include "pch.h"
#include "GameEngine.h"
#include "ResourceManager.h" 
#include "Scene.h"

#include "CameraComponent.h"
#include "GameBehaviourComponent.h"
#include "LightComponent.h"
#include "MeshComponent.h"

GameEngine* Scene::mEnginePtr = nullptr;

Scene::Scene(const std::wstring& name)
	: mName(name)
	, mGameObjects()
{
}

Scene::~Scene()
{
}

const std::wstring& Scene::GetName() const
{
	return mName;
}

std::size_t Scene::GetRootCount() const
{
	return mGameObjects.size();
}

std::vector<GameObject*> Scene::GetRootGameObject() const
{
	std::vector<GameObject*> result;
	
	if (mGameObjects.empty())
	{
		return result;
	}

	result.reserve(mGameObjects.size());
	for (auto& gameObject : mGameObjects)
	{
		result.emplace_back(gameObject.get());
	}
	return result;
}

GameObject* Scene::CreateGameObject(const std::wstring& name, const std::wstring& tag)
{
	auto newGameObject = std::make_unique<GameObject>(name, tag);
	mGameObjects.emplace_back(std::move(newGameObject));
	return mGameObjects.back().get();
}

GameObject* Scene::CreateCube(const std::wstring& name)
{
	return createGameObjectWithMesh(name, _T("Cube"));
}

GameObject* Scene::CreateSphere(const std::wstring& name)
{
	return createGameObjectWithMesh(name, _T("Sphere"));
}

GameObject* Scene::CreateQuad(const std::wstring& name)
{
	return createGameObjectWithMesh(name, _T("Quad"));
}

GameObject* Scene::CreateCamera(const std::wstring& name)
{
	auto newGameObject = CreateGameObject(name);
	newGameObject->AddComponent<CameraComponent>();
	if (!CameraComponent::GetMainCamera())
	{
		newGameObject->SetTag(_T("MainCamera"));
	}
	return newGameObject;
}

GameObject* Scene::CreateLight(const std::wstring& name, const eLightType lightType)
{
	auto newGameObject = CreateGameObject(name);
	newGameObject->AddComponent<LightComponent>(lightType);
	return newGameObject;
}

GameObject* Scene::FindGameObject(const std::wstring& name)
{
	for (auto it = GameObject::mTrueContainerPtr.begin(); it != GameObject::mFalseContainerPtr.end(); ++it)
	{
		if ((*it)->GetName() == name)
		{
			return *it;
		}
	}

	return nullptr;
}

GameObject* Scene::FindGameObjectWithTag(const std::wstring& tag)
{
	for (auto it = GameObject::mTrueContainerPtr.begin(); it != GameObject::mFalseContainerPtr.end(); ++it)
	{
		if ((*it)->GetTag() == tag)
		{
			return *it;
		}
	}

	return nullptr;
}

InputManager& Scene::GetInput()
{
	return mEnginePtr->GetInput();
}

RenderManager& Scene::GetRenderer()
{
	return mEnginePtr->GetRenderer();
}

ResourceManager& Scene::GetResources()
{
	return mEnginePtr->GetResources();
}

TimeManager& Scene::GetTime()
{
	return mEnginePtr->GetTime();
}

void Scene::update()
{
	for (auto it = GameBehaviourComponent::mTrueContainerPtr.begin(); it != GameBehaviourComponent::mFalseContainerPtr.end(); ++it)
	{
		if ((*it)->IsActive())
		{
			if (!(*it)->mbStarted)
			{
				(*it)->Start();
				(*it)->mbStarted = true;
			}

			(*it)->Update();
		}
	}
}

void Scene::lateUpdate()
{
	for (auto it = GameBehaviourComponent::mTrueContainerPtr.begin(); it != GameBehaviourComponent::mFalseContainerPtr.end(); ++it)
	{
		if ((*it)->IsActive())
		{
			(*it)->LateUpdate();
		}
	}
}

GameObject* Scene::createGameObjectWithMesh(const std::wstring& name, const std::wstring& meshName)
{
	auto newGameObject = CreateGameObject(name);
	newGameObject->AddComponent<MeshComponent>(mEnginePtr->GetResources().GetMesh(meshName));
	return newGameObject;
}
