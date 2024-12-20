#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class ATempActor : public AActor
{
public:
	// constrcuter destructer
	ATempActor();
	~ATempActor();

	// delete Function
	ATempActor(const ATempActor& _Other) = delete;
	ATempActor(ATempActor&& _Other) noexcept = delete;
	ATempActor& operator=(const ATempActor& _Other) = delete;
	ATempActor& operator=(ATempActor&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class URenderer> TempRenderer;
};

