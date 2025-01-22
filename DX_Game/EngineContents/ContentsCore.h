#pragma once
#include <EngineCore/IContentsCore.h>

// 규칙을 만드는 수밖에 없다.

// 설명 :
class UContentsCore : public IContentsCore
{
public:
	// constrcuter destructer
	UContentsCore();
	~UContentsCore();

	// delete Function
	UContentsCore(const UContentsCore& _Other) = delete;
	UContentsCore(UContentsCore&& _Other) noexcept = delete;
	UContentsCore& operator=(const UContentsCore& _Other) = delete;
	UContentsCore& operator=(UContentsCore&& _Other) noexcept = delete;

protected:
	void EngineStart(UEngineInitData& _Data) override;
	void EngineTick(float _DeltaTime) override;
	void EngineEnd() override;

	

private:
	void LoadResources();

	void ContentsDepthStencilInit();
	void ContentsTextureInit();
	void ContentsMeshInit();
	void ContentsBlendInit();
	void ContentsRasterizerStateInit();
	void ContentsShaderInit();
	void ContentsMaterialInit();
};

