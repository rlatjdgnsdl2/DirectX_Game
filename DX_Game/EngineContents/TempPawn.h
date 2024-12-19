#pragma once
#include <EngineCore/Pawn.h>

//	Ό³Έν:
class ATempPawn : public APawn
{
public:
	ATempPawn();
	virtual ~ATempPawn();
	ATempPawn(const ATempPawn& _Other) = delete;
	ATempPawn(ATempPawn&& _Other) noexcept = delete;
	ATempPawn& operator=(const ATempPawn& _Other) = delete;
	ATempPawn& operator=(ATempPawn&& _Other) noexcept = delete;


	virtual void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:

};

