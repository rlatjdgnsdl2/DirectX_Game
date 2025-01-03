#pragma once
#include "EngineShaderResources.h"
#include "Mesh.h"
#include "EngineMaterial.h"
#include "EngineEnums.h"

// ���� : �������� �ּҴ���
//        Draw�� �ϴ� �ִ� �̳༮�� ������� �Ұ��̴�.
// �̳༮�� ���� �������� ����� �� ������ ���߿� 3D �Ž����� �������� �Ѵٸ�
// 3D�Ž��� �Ž� n���� �̷���� �ִٴ� ���� �˼��� �ִ�.
// ���ΰ��̶�� 
// ���ΰ��� �Ӹ�  RenderUnit
// ���ΰ��� ��  RenderUnit
// ���ΰ��� ��  RenderUnit
// ���ΰ��� ���� RenderUnit
class URenderUnit
{
public:
	// constrcuter destructer
	URenderUnit();
	~URenderUnit();

	// �Ž�(��ü) 
	std::shared_ptr<UMesh> Mesh;
	// ��Ƽ����(�Ǻ�)
	std::shared_ptr<UEngineMaterial> Material;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> InputLayOut;

	ENGINEAPI void SetMesh(std::string_view _Name);
	ENGINEAPI void SetMaterial(std::string_view _Name);

	//void SetInputAssembler1();
	//void SetInputAssembler1();

	ENGINEAPI virtual void Render(class UEngineCamera* _Camera, float _DeltaTime);

	void MaterialResourcesCheck();

private:
	// �ڽŸ��� ���ҽ��� ������ �ֽ��ϴ�.
	std::map<EShaderType, UEngineShaderResources> Resources;

	void InputLayOutCreate();
};

