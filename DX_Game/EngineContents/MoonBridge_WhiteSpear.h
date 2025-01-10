#pragma once
#include <EngineCore/GameMode.h>

//	����:
class AMoonBridge_WhiteSpear :public AGameMode
{
public:
	AMoonBridge_WhiteSpear();
	virtual ~AMoonBridge_WhiteSpear();
	AMoonBridge_WhiteSpear(const AMoonBridge_WhiteSpear& _Other) = delete;
	AMoonBridge_WhiteSpear(AMoonBridge_WhiteSpear&& _Other) noexcept = delete;
	AMoonBridge_WhiteSpear& operator=(const AMoonBridge_WhiteSpear& _Other) = delete;
	AMoonBridge_WhiteSpear& operator=(AMoonBridge_WhiteSpear&& _Other) noexcept = delete;

	virtual void BeginPlay() override;

protected:

private:
	std::shared_ptr<class AMoonBridge_WhiteSpear_Map> MoonBridge_WhiteSpear_Map = nullptr;
};

