#pragma once
#include "SceneComponent.h"
#include "EngineSprite.h"
#include "RenderUnit.h"



struct FUVValue
{
	float4 PlusUVValue;
};

// ���� : � �������̵� �Ҽ� �մ� ������ ����ڴ�.
// �������̶� �������� �ϴ°� �ƴմϴ�. 3D
class URenderer : public USceneComponent
{
	friend class UEngineCamera;

public:
	// constrcuter destructer
	ENGINEAPI URenderer();
	ENGINEAPI ~URenderer();

	// delete Function
	URenderer(const URenderer& _Other) = delete;
	URenderer(URenderer&& _Other) noexcept = delete;
	URenderer& operator=(const URenderer& _Other) = delete;
	URenderer& operator=(URenderer&& _Other) noexcept = delete;

	ENGINEAPI void SetOrder(int _Order) override;
	ENGINEAPI void SetTexture(std::string_view _Value);

	ENGINEAPI void SetTexture(UEngineTexture* _Value);
	ENGINEAPI void AddUVPlusValue(float4 _Value);

	ENGINEAPI void SetSpriteData(UEngineSprite* _Sprite, size_t _Index);

	ENGINEAPI void SetMesh(std::string_view _Name);

	ENGINEAPI void SetBlend(std::string_view _Name);

protected:
	ENGINEAPI void BeginPlay() override;
	ENGINEAPI virtual void Render(UEngineCamera* _Camera, float _DeltaTime);

private:
	class UMesh* Mesh = nullptr;
	class UEngineBlend* Blend = nullptr;

	FSpriteData SpriteData;
	FUVValue UVValueData;
	UEngineTexture* Texture = nullptr;

	Microsoft::WRL::ComPtr<ID3D11SamplerState> SamplerState = nullptr; // ���÷� ������Ʈ
	Microsoft::WRL::ComPtr<ID3D11Buffer> TransformConstBuffer = nullptr; // �������
	Microsoft::WRL::ComPtr<ID3D11Buffer> SpriteConstBuffer = nullptr; // ��������Ʈ�� �������
	Microsoft::WRL::ComPtr<ID3D11Buffer> UVValue = nullptr; // �������
	void ShaderResInit();
	void ShaderResSetting();

	// Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> InputLayOut = nullptr;
	// void InputAssembler1Init();
	void InputAssembler1Setting();
	void InputAssembler1LayOut();

	// ���� ��İ����ִ�(������Ű�� �ܰ�) �ܰ��Դϴ�.
	// �װ� ���� �ڵ��ؼ� �� ¥����Ѵ�.
	// HLSL�̶�� ���������� �� �̿��ؼ� ���� ���ο� �� ����� �� ¥���մϴ�.

	Microsoft::WRL::ComPtr<ID3DBlob> VSShaderCodeBlob = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> VSErrorCodeBlob = nullptr; // �߰� ������ �����
	Microsoft::WRL::ComPtr<ID3D11VertexShader> VertexShader = nullptr;
	void VertexShaderInit();
	void VertexShaderSetting();


	// Microsoft::WRL::ComPtr<ID3D11Buffer> IndexBuffer = nullptr;
	// �ﰢ���� ������ �����ϰ� �׷��ּ���.
	D3D11_PRIMITIVE_TOPOLOGY Topology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	// void InputAssembler2Init();
	void InputAssembler2Setting();

	D3D11_VIEWPORT ViewPortInfo;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> RasterizerState = nullptr;
	void RasterizerInit();
	void RasterizerSetting();

	// ���̴��̱� ������ ���ؽ����̴��� ����մϴ�. 
	Microsoft::WRL::ComPtr<ID3DBlob> PSShaderCodeBlob = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> PSErrorCodeBlob = nullptr; // �߰� ������ �����
	Microsoft::WRL::ComPtr<ID3D11PixelShader> PixelShader = nullptr;
	void PixelShaderInit();
	void PixelShaderSetting();

	void OutPutMergeSetting();

	std::vector<URenderUnit> Units;
};

