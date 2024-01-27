#ifndef _LIGHT_FX_
#define _LIGHT_FX_

#include "00. Global.fx"

// >> : Struct
struct LightDesc
{
	float4 ambient;
	float4 diffuse;
	float4 specular;
	float4 emissive;
	float3 direction;
	float padding;
};
struct MaterialDesc
{
	float4 ambient;
	float4 diffuse;
	float4 specular;
	float4 emissive;
};
// << : Struct

// >> : ConstBuffer
cbuffer LightBuffer // global에서 한번만 설정하면된다
{
	LightDesc GlobalLight;
};
cbuffer MaterialBuffer // 객체마다 다를 수 있다
{
	MaterialDesc Material;
};

// << : COnstBuffer

// >> : SRV
Texture2D DiffuseMap;
Texture2D SpecularMap;
Texture2D NormalMap;
// << : SRV

// >> : Functions
float4 ComputeLight(float3 normal, float2 uv, float3 worldPosition)
{
	float4 ambientColor = 0;
	float4 diffuseColor = 0;
	float4 specularColor = 0;
	float4 emissiveColor = 0;

	//ambient
	{
		float4 color = GlobalLight.ambient* Material.ambient;
		ambientColor = DiffuseMap.Sample(LinearSampler, uv) * color;
	}
	// diffuse
	{
		float4 color = DiffuseMap.Sample(LinearSampler, uv);
		float value = dot(-GlobalLight.direction, normalize(normal));

		diffuseColor = color * value * GlobalLight.diffuse * Material.diffuse;
	}
	// Specular
	{
		//float3 R = reflect(GlobalLight.direction, normal);
		float3 R = GlobalLight.direction - (2 * normal * dot(GlobalLight.direction, normal));
		R = normalize(R);

		float3 cameraPosition = CameraPosition();
		float3 E = normalize(cameraPosition - worldPosition);

		float value = saturate(dot(R, E)); // clamp(0~1)
		float specular = pow(value, 10);

		specularColor = GlobalLight.specular * Material.specular * specular;
	}
	//Emissive
	{
		float3 E = normalize(CameraPosition() - worldPosition);

		float value = saturate(dot(E, normal));
		float emissive = 1.0f - value;

		// min, max, x 넣으면 부드럽게 보간해주는 함수 : smoothstep
		emissive = smoothstep(0.0f, 1.0f, emissive);
		emissive = pow(emissive, 10);

		emissiveColor = GlobalLight.emissive * Material.emissive * emissive;
	}

	return ambientColor + diffuseColor + emissiveColor + specularColor;

}

void ComputeNormalMapping(inout float3 normal, float3 tangent, float2 uv) //넣은 매개변수 자체를 변경하는것 (레퍼런스, 포인터와 유사)
{
	float4 map = NormalMap.Sample(LinearSampler, uv); // [0, 255] 범위에서 [0,1]사이로 변환
	
	if (any(map.rgb) == false) return;

	float3 N = normalize(normal); // z
	float3 T = normalize(tangent); // x
	float3 B = normalize(cross(N, T)); // y
	float3x3 TBN = float3x3(T, B, N); // TangentSpace -> WorldSpace

	// [0, 1] 범위에서 [-1, 1] 범위로 변환
	float3 tangentSpaceNormal = (map.rgb * 2.0f - 1.0f);
	float3 worldNormal = mul(tangentSpaceNormal, TBN);

	normal = worldNormal;
}

// << : Functons

#endif
