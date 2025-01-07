#pragma once
#include <EngineCore/Actor.h>

//	Ό³Έν:
class AIcon : public AActor
{
public:
	AIcon();
	virtual ~AIcon();
	AIcon(const AIcon& _Other) = delete;
	AIcon(AIcon&& _Other) noexcept = delete;
	AIcon& operator=(const AIcon& _Other) = delete;
	AIcon& operator=(AIcon&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

protected:
	std::shared_ptr<class USpriteRenderer> SpriteRenderer;
	std::shared_ptr<class UCollision> Collision;

private:
	

};

