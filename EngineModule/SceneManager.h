#pragma once

class Scene;

class SceneManager
{
public:
	friend class GameEngine;

public:
	SceneManager();
	~SceneManager();

public:
	template<typename T>
	void CreateScene(const std::wstring& name);
	std::size_t GetSceneCount();
	Scene* GetActiveScene();
	Scene* GetSceneAt(const std::size_t index);
	void LoadScene(const std::size_t index);
	void LoadScene(const std::wstring& name);

private:
	void loadScene();

private:
	bool mbReserved;
	std::vector<std::unique_ptr<Scene>> mScenes;
	std::size_t mCurrentSceneIndex;
	std::size_t mNextSceneIndex;
};

template<typename T>
inline void SceneManager::CreateScene(const std::wstring& name)
{
	auto newScene = std::make_unique<T>(name);
	mScenes.push_back(std::move(newScene));
}
