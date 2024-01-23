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