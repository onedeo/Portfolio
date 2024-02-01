#pragma once

class Model;

class ModelAnimator : public Component
{
	using Super = Component;

public:
	ModelAnimator(shared_ptr<Shader> shader);
	virtual ~ModelAnimator();

	virtual void Update() override;

	void SetModel(shared_ptr<Model> model);
	void SetPass(uint8 pass) { _pass = pass; }

private : 
	shared_ptr<Shader> _shader;
	uint8 _pass = 0;
	shared_ptr<Model> _model;

};

