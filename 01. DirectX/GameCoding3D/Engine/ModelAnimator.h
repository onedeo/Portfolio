#pragma once

class Model;
struct AnimTransform
{
	// [ ] [ ] [ ] [ ] [ ] .... 250 �� �迭
	using TransformArrayType = array<Matrix, MAX_MODEL_TRANSFORMS>;

	//2�� �迭
	array<TransformArrayType, MAX_MODEL_KEYFRAMES> transforms;
};

class ModelAnimator : public Component
{
	using Super = Component;

public:
	ModelAnimator(shared_ptr<Shader> shader);
	virtual ~ModelAnimator();

	virtual void Update() override;
	void UpdateTweenData();

	void SetModel(shared_ptr<Model> model);
	void SetPass(uint8 pass) { _pass = pass; }
	shared_ptr<Shader> GetShader() { return _shader; }

	// Instancing
	void RenderInstancing(shared_ptr<class InstancingBuffer>& buffer);
	InstanceID GetInstanceID();
	TweenDesc& GetTweenDesc() { return _tweenDesc; }

private:
	void CreateTexture();
	void CreateAnimationTransform(uint32 index);

private:
	vector<AnimTransform> _animTransforms;
	ComPtr<ID3D11Texture2D> _texture;
	ComPtr<ID3D11ShaderResourceView> _srv;

private:
	TweenDesc _tweenDesc;

private : 
	shared_ptr<Shader> _shader;
	uint8 _pass = 0;
	shared_ptr<Model> _model;

};
