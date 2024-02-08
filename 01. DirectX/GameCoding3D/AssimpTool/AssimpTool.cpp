#include "pch.h"
#include "AssimpTool.h"
#include "Converter.h"

void AssimpTool::Init()
{
	/*
	���� fbx(Ȥ�� �ٸ�����)�� �����ͼ� ���� ���ϴ� customdata�� �����ϴ� ����
	*/
	// House, Tank
	/*
	{ // HOUSE
		shared_ptr<Converter> converter = make_shared<Converter>();

		// FBX(Ȥ�� �ٸ� ����) -> Memory
		converter->ReadAssetFile(L"House/House.fbx");

		// Memory -> CustomData (File)
		converter->ExportMaterialData(L"House/House");
		converter->ExportModelData(L"House/House");

		// CustomData -> Memory : Client�ʿ��� ������ ������ �� �ҷ����δ�
	}
	{ // TOWER
		shared_ptr<Converter> converter = make_shared<Converter>();

		// FBX(Ȥ�� �ٸ� ����) -> Memory
		converter->ReadAssetFile(L"Tower/Tower.fbx");

		// Memory -> CustomData (File)
		converter->ExportMaterialData(L"Tower/Tower");
		converter->ExportModelData(L"Tower/Tower");

		// CustomData -> Memory
	}
	{ // TANK
		shared_ptr<Converter> converter = make_shared<Converter>();

		// FBX(Ȥ�� �ٸ� ����) -> Memory
		converter->ReadAssetFile(L"Tank/Tank.fbx");

		// Memory -> CustomData (File)
		converter->ExportMaterialData(L"Tank/Tank");
		converter->ExportModelData(L"Tank/Tank");

		// CustomData -> Memory : Client�ʿ��� ������ ������ �� �ҷ����δ�

	}
	*/

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
