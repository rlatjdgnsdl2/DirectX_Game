#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AFreyd : public AActor
{
public:
	// constrcuter destructer
	AFreyd();
	virtual ~AFreyd();

	// delete Function
	AFreyd(const AFreyd& _Other) = delete;
	AFreyd(AFreyd&& _Other) noexcept = delete;
	AFreyd& operator=(const AFreyd& _Other) = delete;
	AFreyd& operator=(AFreyd&& _Other) noexcept = delete;

protected:

private:

};

