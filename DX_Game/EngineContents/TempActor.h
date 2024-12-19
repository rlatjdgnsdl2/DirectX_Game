#pragma once
#include <EngineCore/Actor.h>

//	����:
class ATempActor : public AActor
{
public:
	ATempActor();
	virtual ~ATempActor();
	ATempActor(const ATempActor& _Other) = delete;
	ATempActor(ATempActor&& _Other) noexcept = delete;
	ATempActor& operator=(const ATempActor& _Other) = delete;
	ATempActor& operator=(ATempActor&& _Other) noexcept = delete;

protected:

private:

};

