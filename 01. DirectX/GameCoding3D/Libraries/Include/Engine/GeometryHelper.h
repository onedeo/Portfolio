#pragma once
#include "Geometry.h"
#include "VertexData.h"

class GeometryHelper
{
public:
	static void CreateQuad(shared_ptr<Geometry<VertexColorData>> geometry, Color color);
	static void CreateQuad(shared_ptr<Geometry<VertexTextureData>> geometry);
	static void CreateCube(shared_ptr<Geometry<VertexTextureData>> geometry);
	static void CreateSphere(shared_ptr<Geometry<VertexTextureData>> geometry);
	static void CreateGrid(shared_ptr<Geometry<VertexTextureData>> geometry, int32 sizeX, int32 sizeZ);

	static void CreateQuad(shared_ptr<Geometry<VertexTextureNormalData>> geometry);
	static void CreateCube(shared_ptr<Geometry<VertexTextureNormalData>> geometry);
	static void CreateSphere(shared_ptr<Geometry<VertexTextureNormalData>> geometry);
	static void CreateGrid(shared_ptr<Geometry<VertexTextureNormalData>> geometry, int32 sizeX, int32 sizeZ);

	static void CreateQuad(shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry);
	static void CreateCube(shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry);
	static void CreateSphere(shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry);
	static void CreateGrid(shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry, int32 sizeX, int32 sizeZ);

public:
	static void CreateVertexIndex(vector<VertexTextureNormalTangentData>& _vtx, vector<uint32>& _idx);
	static void CreateBody(shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry);
	static void CreateHead(shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry);
	static void CreateLArm(shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry);
	static void CreateRArm(shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry);
	static void CreateLLeg(shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry);
	static void CreateRLeg(shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry);
};

