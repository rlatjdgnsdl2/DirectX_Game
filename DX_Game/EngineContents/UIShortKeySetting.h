#pragma once
#include <EngineCore/Actor.h>

//	설명: 단축키설정 UI
class UIShortKeySetting : public AActor
{
public:
	UIShortKeySetting();
	virtual ~UIShortKeySetting();
	UIShortKeySetting(const UIShortKeySetting& _Other) = delete;
	UIShortKeySetting(UIShortKeySetting&& _Other) noexcept = delete;
	UIShortKeySetting& operator=(const UIShortKeySetting& _Other) = delete;
	UIShortKeySetting& operator=(UIShortKeySetting&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<class USpriteRenderer> Back;
	std::shared_ptr<class USpriteRenderer> Front;



};

