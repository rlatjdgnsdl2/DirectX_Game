#pragma once
#include <EngineCore/Pawn.h>

//	Ό³Έν:
class TempPawn : public APawn
{
public:
	TempPawn();
	virtual ~TempPawn();
	TempPawn(const TempPawn& _Other) = delete;
	TempPawn(TempPawn&& _Other) noexcept = delete;
	TempPawn& operator=(const TempPawn& _Other) = delete;
	TempPawn& operator=(TempPawn&& _Other) noexcept = delete;

protected:

private:

};

