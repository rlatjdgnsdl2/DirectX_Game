#pragma once
#include "Actor.h"

// ���� :
class AGameMode : public AActor
{
public:
	// constrcuter destructer
	ENGINEAPI AGameMode();
	ENGINEAPI virtual ~AGameMode();

	// delete Function
	AGameMode(const AGameMode& _Other) = delete;
	AGameMode(AGameMode&& _Other) noexcept = delete;
	AGameMode& operator=(const AGameMode& _Other) = delete;
	AGameMode& operator=(AGameMode&& _Other) noexcept = delete;

	ENGINEAPI virtual void Tick(float _DeltaTime) override;

protected:

private:

};

