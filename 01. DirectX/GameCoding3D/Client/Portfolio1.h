#pragma once

enum Scenes
{
	BASIC,
	LIGHT,
	HEIGHT,
	MESH,
	ANIMATION,
	INSTANCINGS,
	GAME1,

	END,
};

class Portfolio1 : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

private:
	//GUI
	void SetGUI();

	// Scens
	void SetSceneBasic();
	void SetSceneLights();
	void SetSceneHeight();

private:
	void LoadAll();
	void LoadTextures();

private:
	shared_ptr<Shader> _shader;
	shared_ptr<Scene> _scenes[END];

};

