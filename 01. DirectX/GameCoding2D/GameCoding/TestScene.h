#pragma once
#include "Scene.h"
class TestScene : public Scene
{
public:
	TestScene(shared_ptr<Graphics> graphics);
	~TestScene() override;

	void Awake() override;
	void AddSceneObjects();
};

