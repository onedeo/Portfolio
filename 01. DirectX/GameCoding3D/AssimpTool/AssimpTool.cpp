#include "pch.h"
#include "AssimpTool.h"
#include "Converter.h"

void AssimpTool::Init()
{
	/*
	기존 fbx(혹은 다른파일)을 가져와서 내가 원하는 customdata로 변경하는 과정
	*/
	
	// Portfolio
	// StoneMonster
	{
		shared_ptr<Converter> converter = make_shared<Converter>();
		converter->ReadAssetFile(L"StoneMonster/Stonefbx.fbx");
		converter->ExportMaterialData(L"StoneMonster/StoneMonster");
		converter->ExportModelData(L"StoneMonster/StoneMonster");
	}
	// Ellie
	{
		shared_ptr<Converter> converter = make_shared<Converter>();
		converter->ReadAssetFile(L"Ellie/Ellie.fbx");
		converter->ExportMaterialData(L"Ellie/Ellie");
		converter->ExportModelData(L"Ellie/Ellie");
	}

	{ // Kachujin
		shared_ptr<Converter> converter = make_shared<Converter>();
		converter->ReadAssetFile(L"Kachujin/Mesh.fbx");
		converter->ExportMaterialData(L"Kachujin/Kachujin");
		converter->ExportModelData(L"Kachujin/Kachujin");
	}
	{// Dool
		shared_ptr<Converter> converter = make_shared<Converter>();
		converter->ReadAssetFile(L"Dool/Dool.fbx");
		converter->ExportModelData(L"Dool/Dool");

	}
	// Animation
	{
		shared_ptr<Converter> converter = make_shared<Converter>();
		converter->ReadAssetFile(L"Kachujin/Idle.fbx");
		converter->ExportAnimationData(L"Kachujin/Idle");
	}
	{
		shared_ptr<Converter> converter = make_shared<Converter>();
		converter->ReadAssetFile(L"Kachujin/Run.fbx");
		converter->ExportAnimationData(L"Kachujin/Run");
	}
	{
		shared_ptr<Converter> converter = make_shared<Converter>();
		converter->ReadAssetFile(L"Kachujin/Slash.fbx");
		converter->ExportAnimationData(L"Kachujin/Slash");
	}
}

void AssimpTool::Update()
{
}

void AssimpTool::Render()
{
}
