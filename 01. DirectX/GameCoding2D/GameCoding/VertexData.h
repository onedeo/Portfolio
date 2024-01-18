#pragma once
struct VertexTextureData
{
	Vec3 position = SimpleMath::Vector3::Zero;;
	Vec2 uv = SimpleMath::Vector2::Zero;;

	static vector<D3D11_INPUT_ELEMENT_DESC> descs;
};

struct VertexColorData
{
	Vec3 position = SimpleMath::Vector3::Zero;
	Color color = SimpleMath::Vector4::Zero;

	static vector<D3D11_INPUT_ELEMENT_DESC> descs;
};

