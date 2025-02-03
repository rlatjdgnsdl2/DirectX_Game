#pragma once
#include <EngineCore/EngineGUIWindow.h>

//	Ό³Έν:
class UDunkel_GUI : public UEngineGUIWindow
{
	friend class ADunkel_GameMode;
public:
	UDunkel_GUI();
	virtual ~UDunkel_GUI();
	UDunkel_GUI(const UDunkel_GUI& _Other) = delete;
	UDunkel_GUI(UDunkel_GUI&& _Other) noexcept = delete;
	UDunkel_GUI& operator=(const UDunkel_GUI& _Other) = delete;
	UDunkel_GUI& operator=(UDunkel_GUI&& _Other) noexcept = delete;

	void BeginPlay() override;

protected:
	void OnGUI() override;
private:
	class APlayer* Player = nullptr;
	class ADunkel_Boss* Dunkel = nullptr;

	
};

