#pragma once
#include <EngineCore/Actor.h>


// ���� :
class AJurai : public AActor
{
public:
	// constrcuter destructer
	AJurai();
	virtual ~AJurai();

	// delete Function
	AJurai(const AJurai& _Other) = delete;
	AJurai(AJurai&& _Other) noexcept = delete;
	AJurai& operator=(const AJurai& _Other) = delete;
	AJurai& operator=(AJurai&& _Other) noexcept = delete;

protected:

private:

};

