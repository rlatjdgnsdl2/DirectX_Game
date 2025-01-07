#pragma once
#include <EngineCore/Actor.h>

//	Ό³Έν:
class UIShortKey : public AActor
{
public:
	UIShortKey();
	virtual ~UIShortKey();
	UIShortKey(const UIShortKey& _Other) = delete;
	UIShortKey(UIShortKey&& _Other) noexcept = delete;
	UIShortKey& operator=(const UIShortKey& _Other) = delete;
	UIShortKey& operator=(UIShortKey&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<class USpriteRenderer> SpriteRenderer_Front;
	std::shared_ptr<class USpriteRenderer> SpriteRenderer_Back;
	std::map<int, std::shared_ptr<class UCollision>> ShortKeyCollisionMap;

	FVector IconSize = FVector(32.0f, 32.0f, 1.0f);
	FVector QPos = FVector(-236.0f, 75.0f, 1.0f);

};

