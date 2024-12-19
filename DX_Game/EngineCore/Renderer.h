#pragma once
#include "SceneComponent.h"

struct EngineVertex
{
	float4 POSITIONR;
	float4 COLOR;
};

// ���� :
class URenderer : public USceneComponent
{
	friend class ULevel;

public:
	// constrcuter destructer
	ENGINEAPI URenderer();
	ENGINEAPI ~URenderer();

	// delete Function
	URenderer(const URenderer& _Other) = delete;
	URenderer(URenderer&& _Other) noexcept = delete;
	URenderer& operator=(const URenderer& _Other) = delete;
	URenderer& operator=(URenderer&& _Other) noexcept = delete;

	void SetOrder(int _Order) override;

protected:
	ENGINEAPI void BeginPlay() override;

private:
	virtual void Render(float _DeltaTime);

public:
	Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> InputLayOut = nullptr;
	void InputAssembler1Init();
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


	Microsoft::WRL::ComPtr<ID3D11Buffer> IndexBuffer = nullptr;
	// �ﰢ���� ������ �����ϰ� �׷��ּ���.
	D3D11_PRIMITIVE_TOPOLOGY Topology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	void InputAssembler2Init();
	void InputAssembler2Setting();

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> RasterizerState = nullptr;
	void RasterizerInit();
	void RasterizerSetting();

	Microsoft::WRL::ComPtr<ID3DBlob> PSShaderCodeBlob = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> PSErrorCodeBlob = nullptr; // �߰� ������ �����
	Microsoft::WRL::ComPtr<ID3D11VertexShader> PixelShader = nullptr;
	void VertexShaderInit();
	void VertexShaderSetting();

};

