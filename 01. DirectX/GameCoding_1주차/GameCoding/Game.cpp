#include "pch.h"
#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	
	_graphics = make_shared<Graphics>(hwnd);
	_pipeline = make_shared<Pipeline>(_graphics->GetDeviceContext());

	//GameObject
	_monster = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	{
		_monster->GetOrAddTransform();
		//_monster->GetTransform()->SetScale(Vec3(100.f, 100.f, 100.f));
	}
	
	_camera= make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	{
		_camera->GetOrAddTransform();
		_camera->AddComponent(make_shared<Camera>());
		
	}
}

void Game::Update()
{
	_monster->Update();
	_camera->Update();
}

void Game::Render()
{
	// ���� �ܰ� : IA - VS - RS - PS - OM
	_graphics->RenderBegin(); // �׸� �غ� (��ȭ�� �ʱ�ȭ ��)

	_monster->Render(_pipeline);

	_graphics->RenderEnd();
}


