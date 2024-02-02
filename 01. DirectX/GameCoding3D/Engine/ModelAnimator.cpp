#include "pch.h"
#include "ModelAnimator.h"
#include "Material.h"
#include "ModelMesh.h"
#include "Model.h"
#include "ModelAnimation.h"

ModelAnimator::ModelAnimator(shared_ptr<Shader> shader)
	: Super(ComponentType::Animator), _shader(shader)
{
}

ModelAnimator::~ModelAnimator()
{
}

// Keyframe
/*
void ModelAnimator::Update()
{
	if (_model == nullptr) return;

	// TO DO : Model Animation Render
	if (_texture == nullptr)
		CreateTexture();

	_keyframeDesc.sumTime += DT;

	shared_ptr<ModelAnimation> current = _model->GetAnimationByIndex(_keyframeDesc.animIndex);
	if (current)
	{
		float timePerFrame = 1 / (current->frameRate * _keyframeDesc.speed);
		if (_keyframeDesc.sumTime >= timePerFrame)
		{
			_keyframeDesc.sumTime = 0.f;
			_keyframeDesc.currFrame = (_keyframeDesc.currFrame + 1) % current->frameCount;
			_keyframeDesc.nextFrame = (_keyframeDesc.nextFrame + 1) % current->frameCount;
		}

		_keyframeDesc.ratio = (_keyframeDesc.sumTime / timePerFrame);
	}

	// Animation Update
	ImGui::InputInt("AnimIndex", &_keyframeDesc.animIndex);
	_keyframeDesc.animIndex %= _model->GetAnimationCount();
	ImGui::InputFloat("Speed", &_keyframeDesc.speed, 0.5f, 4.f);

	// �ִϸ��̼� ���� ������ ���� push
	RENDER->PushKeyframeData(_keyframeDesc);

	// SRV�� ���� ���� ����
	_shader->GetSRV("TransformMap")->SetResource(_srv.Get());

	// Bones
	BoneDesc boneDesc;

	const uint32 boneCount = _model->GetBoneCount();
	for (uint32 i = 0; i < boneCount; i++)
	{
		shared_ptr<ModelBone> bone = _model->GetBoneByIndex(i);
		boneDesc.transforms[i] = bone->transform;
	}
	RENDER->PushBoneData(boneDesc);

	// Transform
	auto world = GetTransform()->GetWorldMatrix();
	RENDER->PushTransformData(TransformDesc{ world });

	const auto& meshes = _model->GetMeshes();
	for (auto& mesh : meshes)
	{
		if (mesh->material) mesh->material->Update();

		// Bone Index
		_shader->GetScalar("BoneIndex")->SetInt(mesh->boneIndex);

		uint32 stride = mesh->vertexBuffer->GetStride();
		uint32 offset = mesh->vertexBuffer->GetOffset();

		DC->IASetVertexBuffers(0, 1, mesh->vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
		DC->IASetIndexBuffer(mesh->indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

		_shader->DrawIndexed(0, _pass, mesh->indexBuffer->GetCount(), 0, 0);
	}
}
*/

// Tween
void ModelAnimator::Update()
{
	if (_model == nullptr) return;

	if (_texture == nullptr)
		CreateTexture();

	TweenDesc& desc = _tweenDesc;

	desc.curr.sumTime += DT;
	// current animation
	{
		shared_ptr<ModelAnimation> currentAnim = _model->GetAnimationByIndex(desc.curr.animIndex);
		if (currentAnim)
		{
			float timePerFrame = 1 / (currentAnim->frameRate * desc.curr.speed);
			if (desc.curr.sumTime >= timePerFrame)
			{
				desc.curr.sumTime = 0;
				desc.curr.currFrame = (desc.curr.currFrame + 1) % currentAnim->frameCount;
				desc.curr.nextFrame = (desc.curr.currFrame + 1) % currentAnim->frameCount;
			}

			desc.curr.ratio = (desc.curr.sumTime / timePerFrame);
		}
	}

	// next animation�� ���� �Ǿ� �ִٸ�
	if (desc.next.animIndex >= 0)
	{
		desc.tweenSumTime += DT;
		desc.tweenRatio = desc.tweenSumTime / desc.tweenDuration;

		if (desc.tweenRatio >= 1.f)
		{
			// �ִϸ��̼� ��ü ����
			desc.curr = desc.next;
			desc.ClearNextAnim();
		}
		else
		{
			// ��ü��
			shared_ptr<ModelAnimation> nextAnim = _model->GetAnimationByIndex(desc.next.animIndex);
			desc.next.sumTime += DT;

			float timePerFrame = 1.f / (nextAnim->frameRate * desc.next.speed);

			if (desc.next.ratio >= 1.f)
			{
				desc.next.sumTime = 0;

				desc.next.currFrame = (desc.next.currFrame + 1) % nextAnim->frameCount;
				desc.next.nextFrame = (desc.next.currFrame + 1) % nextAnim->frameCount;
			}

			desc.next.ratio = desc.next.sumTime / timePerFrame;
		}
	}
	
	// Animation Update
	ImGui::InputInt("AnimIndex", &desc.curr.animIndex);
	_keyframeDesc.animIndex %= _model->GetAnimationCount();

	static int32 nextAnimIndex = 0;
	if (ImGui::InputInt("NextAnimIndex", &nextAnimIndex))
	{
		nextAnimIndex %= _model->GetAnimationCount();
		desc.ClearNextAnim(); // ������ �о��ֱ�
		desc.next.animIndex = nextAnimIndex;
	}
	if (_model->GetAnimationCount() > 0)
		desc.curr.animIndex %= _model->GetAnimationCount();

	ImGui::InputFloat("Speed", &desc.curr.speed, 0.5f, 4.f);

	// �ִϸ��̼� ���� ������ ���� push
	RENDER->PushTweenData(desc);

	// SRV�� ���� ���� ����
	_shader->GetSRV("TransformMap")->SetResource(_srv.Get());

	// Bones
	BoneDesc boneDesc;

	const uint32 boneCount = _model->GetBoneCount();
	for (uint32 i = 0; i < boneCount; i++)
	{
		shared_ptr<ModelBone> bone = _model->GetBoneByIndex(i);
		boneDesc.transforms[i] = bone->transform;
	}
	RENDER->PushBoneData(boneDesc);

	// Transform
	auto world = GetTransform()->GetWorldMatrix();
	RENDER->PushTransformData(TransformDesc{ world });

	const auto& meshes = _model->GetMeshes();
	for (auto& mesh : meshes)
	{
		if (mesh->material) mesh->material->Update();

		// Bone Index
		_shader->GetScalar("BoneIndex")->SetInt(mesh->boneIndex);

		uint32 stride = mesh->vertexBuffer->GetStride();
		uint32 offset = mesh->vertexBuffer->GetOffset();

		DC->IASetVertexBuffers(0, 1, mesh->vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
		DC->IASetIndexBuffer(mesh->indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

		_shader->DrawIndexed(0, _pass, mesh->indexBuffer->GetCount(), 0, 0);
	}
}

void ModelAnimator::SetModel(shared_ptr<Model> model)
{
	_model = model;

	const auto& materials = _model->GetMaterials();
	for (auto& material : materials)
	{
		material->SetShader(_shader);
	}
}


void ModelAnimator::CreateTexture()
{
	if (_model->GetAnimationCount() == 0)	return;

	_animTransforms.resize(_model->GetAnimationCount());
	for (uint32 i = 0; i < _model->GetAnimationCount(); i++)
		CreateAnimationTransform(i);

	// Creature Texture
	{
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
		desc.Width = MAX_MODEL_TRANSFORMS * 4; // format�� 16����Ʈ�� �ִ�, ����� 4*16���� 64����Ʈ
		desc.Height = MAX_MODEL_KEYFRAMES;
		desc.ArraySize = _model->GetAnimationCount();
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; // 16����Ʈ
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.MipLevels = 1;
		desc.SampleDesc.Count = 1;

		const uint32 dataSize = MAX_MODEL_TRANSFORMS * sizeof(Matrix);
		const uint32 pageSize = dataSize * MAX_MODEL_KEYFRAMES;
		void* mallocPtr = ::malloc(pageSize * _model->GetAnimationCount());
		/*
		C : malloc / malloc free
		C++ : new / delete
		���������� �Ҵ��� �Ǵ� ��������, ������ ȣ�� ���� �ٸ�
		*/
		// ����ȭ�� �����͸� ����
		for (uint32 c = 0; c < _model->GetAnimationCount(); c++)
		{
			uint32 startOffset = c * pageSize;
			BYTE* pageStartPtr = reinterpret_cast<BYTE*>(mallocPtr) + startOffset;
			/*
			������ Ÿ�Կ� ���� �̵��ϴ� ����Ʈ ���� �ٸ���.
			���� ��� int�� ������ a���� a+4 �ϸ� 4byte(int�� ũ��)�� 4�� ���°�����
			���ϴ� ��ŭ ������ 1����Ʈ �������� cast����� �Ѵ�
			*/

			for (uint32 f = 0; f < MAX_MODEL_KEYFRAMES; f++)
			{
				void* ptr = pageStartPtr + dataSize * f;
				::memcpy(ptr, _animTransforms[c].transforms[f].data(), dataSize);
			}
		}

		// ���ҽ� �����
		vector<D3D11_SUBRESOURCE_DATA> subResources(_model->GetAnimationCount());

		for (uint32 c = 0; c < _model->GetAnimationCount(); c++)
		{
			void* ptr = (BYTE*)mallocPtr + c * pageSize;
			subResources[c].pSysMem = ptr;
			subResources[c].SysMemPitch = dataSize;
			subResources[c].SysMemSlicePitch = pageSize;
		}

		HRESULT hr = DEVICE->CreateTexture2D(&desc, subResources.data(), _texture.GetAddressOf());
		CHECK(hr);

		::free(mallocPtr);
	}

	// Create SRV
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
		desc.Texture2DArray.MipLevels = 1;
		desc.Texture2DArray.ArraySize = _model->GetAnimationCount();

		HRESULT hr = DEVICE->CreateShaderResourceView(_texture.Get(), &desc, _srv.GetAddressOf());
		CHECK(hr);
	}
}

void ModelAnimator::CreateAnimationTransform(uint32 index)
{
	vector<Matrix> tempAnimBoneTransforms(MAX_MODEL_TRANSFORMS, Matrix::Identity);

	shared_ptr<ModelAnimation> animation = _model->GetAnimationByIndex(index);
	for (uint32 f = 0; f < animation->frameCount; f++)
	{
		for (uint32 b = 0; b < _model->GetBoneCount(); b++)
		{
			shared_ptr<ModelBone> bone = _model->GetBoneByIndex(b);

			Matrix matAnimation;

			shared_ptr<ModelKeyframe> frame = animation->GetKeyframe(bone->name);
			if (frame != nullptr)
			{
				ModelKeyframeData& data = frame->transforms[f];
				Matrix S, R, T;
				S = Matrix::CreateScale(data.scale.x, data.scale.y, data.scale.z);
				R = Matrix::CreateFromQuaternion(data.rotation);
				T = Matrix::CreateTranslation(data.translation.x, data.translation.y, data.translation.z);

				matAnimation = S * R * T;
			}
			else
			{
				matAnimation = Matrix::Identity;
			}

			/*
			bone->transform�� �ش� transform�� root��ǥ���� ���� �ѹ��� matrix
			�� matrix�� ������� ���ϸ� �ٽ� local matrix�� ��ȯ
			*/
			Matrix toRootMatrix = bone->transform;
			Matrix invGlobal = toRootMatrix.Invert();

			Matrix matParent = Matrix::Identity;

			int32 parentIndex = bone->parentIndex;
			if (parentIndex >= 0)
				matParent = tempAnimBoneTransforms[parentIndex];

			tempAnimBoneTransforms[b] = matAnimation * matParent;

			_animTransforms[index].transforms[f][b] = invGlobal * tempAnimBoneTransforms[b];
		}
	}
}

