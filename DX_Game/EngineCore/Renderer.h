#pragma once
#include "SceneComponent.h"

struct EngineVertex
{
	FVector Pos;
	FVector Color;
};


// Ό³Έν :
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
	virtual void Render(float _DeltaTime);

private:
	ID3D11Buffer* VertexBuffer = nullptr;
	ID3D11Buffer* IndexBuffer = nullptr;
	void InitInputAssembler1();
	void SetInputAssembler1();

};

