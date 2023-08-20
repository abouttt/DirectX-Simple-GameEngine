#include "pch.h"

#include <CameraComponent.h>
#include <GameObject.h>
#include <ImageComponent.h>
#include <MeshComponent.h>
//#include <SoundComponent.h>
#include <TransformComponent.h>
#include <TextComponent.h>

#include "DevScene.h"
#include "CameraController.h"
#include "Rotator.h"

DevScene::DevScene(const std::wstring& name)
	: Scene(name)
{
}

DevScene::~DevScene()
{
}

void DevScene::Init()
{
	auto camera = CreateCamera(_T("Main Camera"));
	camera->GetTransform()->SetPosition(Vector3(0.f, 0.f, -10.f));
	camera->AddComponent<CameraController>();

	auto light = CreateLight(_T("Directional Light"), eLightType::Directional);
	light->GetTransform()->SetRotation(Vector3(10, -10, 10));

	auto cacodoom = CreateQuad(_T("Caco Doom"));
	cacodoom->GetTransform()->SetPosition(Vector3(2, 0, 0));
	cacodoom->GetComponent<MeshComponent>()->SetMaterial(GetResources().GetMaterial(_T("Cacodoom")));

	auto sound = CreateGameObject(_T("Sound"));
	//sound->AddComponent<SoundComponent>();
	//sound->GetComponent<SoundComponent>()->LoadSoundFile(_T("pop.wav"));

	auto cube = CreateCube(_T("Cube"));
	cube->GetTransform()->SetPosition(Vector3(0, 0, 0));
	cube->GetComponent<MeshComponent>()->SetMaterial(GetResources().GetMaterial(_T("Crate")));
	cube->AddComponent<Rotator>();

	auto cube2 = CreateCube(_T("Cube2"));
	cube2->GetTransform()->SetPosition(Vector3(3, 0, 0));
	cube2->GetTransform()->SetParent(cube->GetTransform());
	cube2->AddComponent<Rotator>();

	auto cube3 = CreateCube(_T("Cube3"));
	cube3->GetTransform()->SetPosition(Vector3(6, 0, 0));
	cube3->GetTransform()->SetParent(cube2->GetTransform());
	cube3->AddComponent<Rotator>();

	auto fire = CreateSphere(_T("Fire"));
	fire->GetTransform()->SetPosition(Vector3(-2, 0, 0));
	fire->GetComponent<MeshComponent>()->SetMaterial(GetResources().GetMaterial(_T("Fire")));

	auto ice = CreateSphere(_T("Ice"));
	ice->GetTransform()->SetPosition(Vector3(-4, 0, 0));
	ice->GetComponent<MeshComponent>()->SetMaterial(GetResources().GetMaterial(_T("Ice")));

	auto doomguy = CreateQuad(_T("Doom Guy"));
	doomguy->GetTransform()->SetPosition(Vector3(2, 0, 5));
	doomguy->GetComponent<MeshComponent>()->SetMaterial(GetResources().GetMaterial(_T("DoomGuy")));

	auto image = CreateImage(_T("DoomGuy Image"), GetResources().GetTexture(_T("DoomGuy")));
	image->GetTransform()->SetPosition(Vector3(10, 50, 0));
	image->GetTransform()->SetScale(Vector3(0.1f, 0.1f, 0.f));

	auto text = CreateText(_T("Text"));
	text->GetComponent<TextComponent>()->SetText(_T("Text!!!"));
	text->GetTransform()->SetPosition(Vector3(10, 10, 0));
}
