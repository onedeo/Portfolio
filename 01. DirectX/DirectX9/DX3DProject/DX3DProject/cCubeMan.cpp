#include "framework.h"
#include "cCubeMan.h"
#include "cCubeNode.h"
#include "cBody.h"
#include "cHead.h"
#include "cLeftArm.h"
#include "cRightArm.h"
#include "cLeftLeg.h"
#include "cRightLeg.h"

cCubeMan::cCubeMan()
	: m_pRoot(NULL)
{
}

cCubeMan::~cCubeMan()
{
	if (m_pRoot)
		m_pRoot->Destroy();
}

void cCubeMan::Setup()
{
	cCharacter::Setup();

	// Material
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));

	// Light
	m_stMtl.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtl.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	// Parts
	cBody* pBody = new cBody();
	pBody->Setup();
	pBody->SetParentWorldTM(&m_matWorld);
	m_pRoot = pBody;

	cHead* pHead = new cHead();
	pHead->Setup();
	m_pRoot->AddChild(pHead);

	cLeftArm* pLeftArm = new cLeftArm();
	pLeftArm->Setup();
	pLeftArm->SetRotDeltaX(-0.1f);
	m_pRoot->AddChild(pLeftArm);

	cRightArm* pRightArm = new cRightArm();
	pRightArm->Setup();
	pRightArm->SetRotDeltaX(0.1f);
	m_pRoot->AddChild(pRightArm);

	cLeftLeg* pLeftleg = new cLeftLeg();
	pLeftleg->Setup();
	pLeftleg->SetRotDeltaX(-0.1f);
	m_pRoot->AddChild(pLeftleg);

	cRightLeg* pRightLeg= new cRightLeg();
	pRightLeg->Setup();
	pRightLeg->SetRotDeltaX(0.1f);
	m_pRoot->AddChild(pRightLeg);
}

void cCubeMan::Update()
{
	cCharacter::Update();
	if (m_pRoot)		m_pRoot->Update();
}

void cCubeMan::Render()
{
	if (DEVICE)
	{
		DEVICE->SetRenderState(D3DRS_LIGHTING, true);
		DEVICE->SetMaterial(&m_stMtl);

		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);

		DEVICE->SetTransform(D3DTS_WORLD, &matWorld);

		if (m_pRoot) m_pRoot->Render();

		DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	}
}
