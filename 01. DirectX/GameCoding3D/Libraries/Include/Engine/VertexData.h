#pragma once

struct VertexData
{
	Vec3 position = { 0, 0, 0 };
};

struct VertexTextureData
{
	VertexTextureData() {}
	VertexTextureData(Vec3 position, Vec2 uv)
	{
		this->position = position;
		this->uv = uv;
	}
	Vec3 position = { 0, 0, 0 };
	Vec2 uv = { 0, 0 };
};

struct VertexColorData
{
	Vec3 position = { 0, 0, 0 };
	Color color = { 0, 0, 0, 0 };
};

struct VertexTextureNormalData
{
	VertexTextureNormalData() {}
	VertexTextureNormalData(Vec3 pos, Vec2 uv, Vec3 nor)
	{
		position = pos;
		this->uv = uv;
		normal = nor;
	}
	Vec3 position = { 0, 0, 0 };
	Vec2 uv = { 0, 0 };
	Vec3 normal = { 0, 0, 0 };
};

struct VertexTextureNormalTangentData
{
	VertexTextureNormalTangentData() {}
	VertexTextureNormalTangentData(Vec3 pos, Vec2 uv, Vec3 normal, Vec3 tan)
	{
		position = pos;
		this->uv = uv;
		this->normal = normal;
		tangent = tan;
	}
	Vec3 position = { 0,0,0 };
	Vec2 uv = { 0,0 };
	Vec3 normal = { 0,0,0 };
	Vec3 tangent = { 0,0,0 };
	//normal�� tangent�� ������ ������ bitangent�� �����ؼ� ���� �� �ִ�
};

struct VertexTextureNormalTangentBlendData
{
	VertexTextureNormalTangentBlendData() {}
	VertexTextureNormalTangentBlendData(Vec3 pos, Vec2 uv, Vec3 normal, Vec3 tan, Vec4 blendIn, Vec4 blendWe)
	{
		position = pos;
		this->uv = uv;
		this->normal = normal;
		tangent = tan;
		blendIndices = blendIn;
		blendWeights = blendWe;
	}
	Vec3 position = { 0,0,0 };
	Vec2 uv = { 0,0 };
	Vec3 normal = { 0,0,0 };
	Vec3 tangent = { 0,0,0 };
	Vec4 blendIndices = { 0,0,0,0 }; // bone
	Vec4 blendWeights = { 0,0,0,0 }; // bone ���� ���� (4��, ����)
};

using ModelVertexType = VertexTextureNormalTangentBlendData;