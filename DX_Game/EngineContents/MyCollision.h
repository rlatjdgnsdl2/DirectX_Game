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
	void SetColor(FVector _Color)
	{
		Color = _Color;
	}

protected:

private:
	FVector Color = { 0.0f, 1.0f, 0.0f ,1.0f };
	

};

