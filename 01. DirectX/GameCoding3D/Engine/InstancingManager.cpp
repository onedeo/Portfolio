#include "pch.h"
#include "InstancingManager.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "ModelRenderer.h"
#include "ModelAnimator.h"

void InstancingManager::Render(vector<shared_ptr<GameObject>>& gameObjects)
{
	ClearData();
	// 현재 프레임에 그려야 하는 모든 물체들을 render에 전달 후 instancing 되어야 할 obj들을 buffer에 전달

	RenderMeshRenderer(gameObjects);
	RenderModelRenderer(gameObjects);
	RenderAnimRenderer(gameObjects);
}

void InstancingManager::ClearData()
{
	for (auto& pair : _buffers)
	{
		// pair : using InstanceID = ::pair<uint64, uint64>;
		pair.second->ClearData();
	}
}

void InstancingManager::RenderMeshRenderer(vector<shared_ptr<GameObject>>& gameObjects)
{
	map<InstanceID, vector<shared_ptr<GameObject>>> cache;

	// 씬에 있는 모든 오브젝트 분류 단계
	for (shared_ptr<GameObject>& gameObject : gameObjects)
	{
		if (gameObject->GetMeshRenderer() == nullptr)
			continue;

		const InstanceID instanceID = gameObject->GetMeshRenderer()->GetInstanceID();
		cache[instanceID].push_back(gameObject);
	}

	// 분류된 오브젝트 순회하며 렌더
	for (auto& pair : cache)
	{
		const vector<shared_ptr<GameObject>>& vec = pair.second;
		{
			const InstanceID instanceId = pair.first;

			for (int32 i = 0; i < vec.size(); i++)
			{
				const shared_ptr<GameObject>& gameObject = vec[i];
				InstancingData data;
				data.world = gameObject->GetTransform()->GetWorldMatrix();

				AddData(instanceId, data);
			}

			// 그려주기
			shared_ptr<InstancingBuffer>& buffer = _buffers[instanceId];
			vec[0]->GetMeshRenderer()->RenderInstancing(buffer);
		}
	}
}

void InstancingManager::RenderModelRenderer(vector<shared_ptr<GameObject>>& gameObjects)
{
	map<InstanceID, vector<shared_ptr<GameObject>>> cache;

	// 씬에 있는 모든 오브젝트 분류 단계
	for (shared_ptr<GameObject>& gameObject : gameObjects)
	{
		if (gameObject->GetModelRenderer() == nullptr)
			continue;

		const InstanceID instanceID = gameObject->GetModelRenderer()->GetInstanceID();
		cache[instanceID].push_back(gameObject);
	}

	// 분류된 오브젝트 순회하며 렌더
	for (auto& pair : cache)
	{
		const vector<shared_ptr<GameObject>>& vec = pair.second;
		{
			const InstanceID instanceId = pair.first;

			for (int32 i = 0; i < vec.size(); i++)
			{
				const shared_ptr<GameObject>& gameObject = vec[i];
				InstancingData data;
				data.world = gameObject->GetTransform()->GetWorldMatrix();

				AddData(instanceId, data);
			}

			// 그려주기
			shared_ptr<InstancingBuffer>& buffer = _buffers[instanceId];
			vec[0]->GetModelRenderer()->RenderInstancing(buffer);
		}
	}
}

void InstancingManager::RenderAnimRenderer(vector<shared_ptr<GameObject>>& gameObjects)
{
	map<InstanceID, vector<shared_ptr<GameObject>>> cache;

	// 씬에 있는 모든 오브젝트 분류 단계
	for (shared_ptr<GameObject>& gameObject : gameObjects)
	{
		if (gameObject->GetModelAnimator() == nullptr)
			continue;

		const InstanceID instanceID = gameObject->GetModelAnimator()->GetInstanceID();
		cache[instanceID].push_back(gameObject);
	}

	// 분류된 오브젝트 순회하며 렌더
	for (auto& pair : cache)
	{
		shared_ptr<InstancedTweenDesc> tweenDesc = make_shared<InstancedTweenDesc>();

		const vector<shared_ptr<GameObject>>& vec = pair.second;
		{
			const InstanceID instanceId = pair.first;

			for (int32 i = 0; i < vec.size(); i++)
			{
				const shared_ptr<GameObject>& gameObject = vec[i];
				InstancingData data;
				data.world = gameObject->GetTransform()->GetWorldMatrix();

				AddData(instanceId, data);

				// INSTANCING
				gameObject->GetModelAnimator()->UpdateTweenData();
				tweenDesc->tweens[i] = gameObject->GetModelAnimator()->GetTweenDesc();
			}

			vec[0]->GetModelAnimator()->GetShader()->PushTweenData(*tweenDesc.get());

			// 그려주기
			shared_ptr<InstancingBuffer>& buffer = _buffers[instanceId];
			vec[0]->GetModelAnimator()->RenderInstancing(buffer);
		}
	}
}

void InstancingManager::AddData(InstanceID instanceId, InstancingData& data)
{
	if (_buffers.find(instanceId) == _buffers.end())
		_buffers[instanceId] = make_shared<InstancingBuffer>();

	_buffers[instanceId]->AddData(data);
}
