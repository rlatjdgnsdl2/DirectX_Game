#pragma once
#include <EngineCore/Actor.h>

// ���� :
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



	std::shared_ptr<class USpriteRenderer> GetRenderer()
	{
		return TempRenderer;
	}


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> TempRenderer;
	std::shared_ptr<class USpriteRenderer> Child;
};

