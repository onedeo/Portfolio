#pragma once

class Scene;

enum SceneName
{
	Test,

	End,
};

class SceneManager
{
public:
	SceneManager(shared_ptr<Graphics> graphics);
	~SceneManager();

	void Init();
	void Update();
	void AddScene(shared_ptr<Scene> scene, SceneName name);

	void LoadScene(SceneName sceneName);
public:
	shared_ptr<Scene> GetActiveScene() { return _activeScene; }

private:
	shared_ptr<Scene> LoadTestScene();

private:
	
private:
	shared_ptr<Scene> _activeScene;
	array<shared_ptr<Scene>,SceneName::End> _scenes;
};

