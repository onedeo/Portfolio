#pragma once

// Assimp file load
struct ModelKeyframeData
{
	float time;
	Vec3 scale;
	Quaternion rotation;
	Vec3 translation;
};
struct ModelKeyframe
{
	wstring boneName;
	vector<ModelKeyframeData> transforms;
};

struct ModelAnimation
{
	shared_ptr<ModelKeyframe> GetKeyframe(const wstring& name);

	wstring name;
	float duration = 0.f;
	float frameRate = 0.f;
	uint32 frameCount = 0;
	unordered_map<wstring, shared_ptr<ModelKeyframe>> keyframes;
};

