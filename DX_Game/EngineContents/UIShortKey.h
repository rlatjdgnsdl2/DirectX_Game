#pragma once
#include <EngineCore/Actor.h>

//	����:
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

};

