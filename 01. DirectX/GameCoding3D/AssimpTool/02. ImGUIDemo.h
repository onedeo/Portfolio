#pragma once
#include "IExecute.h"

class IMGUIDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	void Test();

private:
	shared_ptr<Shader> _shader;
	shared_ptr<GameObject> _obj;
	shared_ptr<GameObject> _camera;

private:
	bool show_demo_window=true;
	bool show_another_window = true;
	Vec4 clear_color = Vec4(0.f);

};

