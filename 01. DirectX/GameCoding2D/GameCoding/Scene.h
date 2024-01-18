#pragma once

class Scene
{
public:
	Scene(shared_ptr<Graphics> graphics);
	virtual ~Scene();
	virtual void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FixedUpdate();

public:
	void AddGameObject(shared_ptr<GameObject> gameObject);
	void RemoveGameObject(shared_ptr<GameObject> gameObject);
	
	const vector<shared_ptr<GameObject>>& GetGameObjects() { return _gameObjects; }

protected:
	vector<shared_ptr<GameObject>> _gameObjects;
	shared_ptr<Graphics> _graphics;
};

