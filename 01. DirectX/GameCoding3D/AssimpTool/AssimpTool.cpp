#include "pch.h"
#include "AssimpTool.h"
#include "Converter.h"

void AssimpTool::Init()
{
	/*
	기존 fbx(혹은 다른파일)을 가져와서 내가 원하는 customdata로 변경하는 과정
	*/
	//{ // HOUSE
	//	shared_ptr<Converter> converter = make_shared<Converter>();

	//	// FBX(혹은 다른 파일) -> Memory
	//	converter->ReadAssetFile(L"House/House.fbx");

	//	// Memory -> CustomData (File)
	//	converter->ExportMaterialData(L"House/House");
	//	converter->ExportModelData(L"House/House");

	//	// CustomData -> Memory : Client쪽에서 게임을 진행할 때 불러들인다
	//}
	//{ // TOWER
	//	shared_ptr<Converter> converter = make_shared<Converter>();

	//	// FBX(혹은 다른 파일) -> Memory
	//	converter->ReadAssetFile(L"Tower/Tower.fbx");

	//	// Memory -> CustomData (File)
	//	converter->ExportMaterialData(L"Tower/Tower");
	//	converter->ExportModelData(L"Tower/Tower");

	//	// CustomData -> Memory
	//}
	{ // TANK
		shared_ptr<Converter> converter = make_shared<Converter>();

		// FBX(혹은 다른 파일) -> Memory
		converter->ReadAssetFile(L"Tank/Tank.fbx");

		// Memory -> CustomData (File)
		converter->ExportMaterialData(L"Tank/Tank");
		converter->ExportModelData(L"Tank/Tank");

		// CustomData -> Memory : Client쪽에서 게임을 진행할 때 불러들인다

	}
}

void AssimpTool::Update()
{
}

void AssimpTool::Render()
{
}
