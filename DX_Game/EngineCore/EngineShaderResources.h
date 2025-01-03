#pragma once
#include "EngineConstantBuffer.h"
#include <EngineBase/Object.h>

class UEngineShaderRes : public UObject
{
public:
	EShaderType Type = EShaderType::MAX;
	UINT BindIndex = 0;
};

class UEngineConstantBufferRes : public UEngineShaderRes
{
public:
	void* Data = nullptr; // �ڽſ��� ���õ� �����ʹ� ������ ������ ���� ���̴�.
	UINT BufferSize;
	std::shared_ptr<UEngineConstantBuffer> Res;

	void Setting()
	{
		if (nullptr != Data)
		{
			Res->ChangeData(Data, Res->GetBufferInfo().ByteWidth);
		}

		Res->Setting(Type, BindIndex);
	}
};

// Render�� 2�� �������.
// Renderer1
// ������ �׸��� �ʹ�.
// 
// Renderer2
// ����� �׸��� �;�.

// ���� : �ְ� ���̴��� �˻��ؼ� 
// �� ���������� �����ؾ��� ���� �ٸ���?
// �̳༮�� ������ ũ�� 2���� �Դϴ�.

// ���̴��� ������ �ִ� �� �������� ���̴� ���ҽ��� �����ϴ� ����
// �������� ������ �ִ� �� �׷��� �ؼ� ����� ���ҽ����� �����͸� �����ϴ� ���ҷ� ������ ���� �̴ϴ�.
class UEngineShaderResources
{
	// 

public:
	// constrcuter destructer
	UEngineShaderResources();
	~UEngineShaderResources();

	// delete Function
	// �̳༮�� ���縦 ���������� �غ����̴�.
	//UEngineShaderResources(const UEngineShaderResources& _Other) = delete;
	//UEngineShaderResources(UEngineShaderResources&& _Other) noexcept = delete;
	//UEngineShaderResources& operator=(const UEngineShaderResources& _Other) = delete;
	//UEngineShaderResources& operator=(UEngineShaderResources&& _Other) noexcept = delete;

	void CreateConstantBufferRes(std::string_view Name, UEngineConstantBufferRes Res);

	void Setting();

protected:

private:
	std::map<std::string, UEngineConstantBufferRes> ConstantBufferRes;
	// std::map<std::string, UEngineConstantBufferRes> TextureSetters;
	// std::map<std::string, UEngineConstantBufferRes> ConstantBufferSetters;
	// std::map<std::string, UEngineConstantBufferRes> ConstantBufferSetters;

};

