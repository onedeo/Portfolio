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
	//normal과 tangent를 가지고 있으면 bitangent를 외적해서 구할 수 있다
};