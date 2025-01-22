#pragma once
#include <EngineCore/Collision.h>

//	Ό³Έν:
class UMyCollision : public UCollision
{
public:
	UMyCollision();
	virtual ~UMyCollision();
	UMyCollision(const UMyCollision& _Other) = delete;
	UMyCollision(UMyCollision&& _Other) noexcept = delete;
	UMyCollision& operator=(const UMyCollision& _Other) = delete;
	UMyCollision& operator=(UMyCollision&& _Other) noexcept = delete;

	void DebugRender(class UEngineCamera* _Camera, float _DeltaTime) override;

protected:

private:
	

};

