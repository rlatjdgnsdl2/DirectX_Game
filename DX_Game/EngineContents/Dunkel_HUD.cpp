#include "PreCompile.h"
#include "Dunkel_HUD.h"
#include "PlayerHpMpBox.h"
#include "PlayerHpBar.h"




ADunkel_HUD::ADunkel_HUD() 
{
	
}

ADunkel_HUD::~ADunkel_HUD() 
{

}

void ADunkel_HUD::BeginPlay()
{
	AHUD::BeginPlay();
	{
		std::shared_ptr<UPlayerHpMpBox> PlayerHpMpBox = CreateWidget<UPlayerHpMpBox>(-1);
		std::shared_ptr<UPlayerHpBar> PlayerHpBar = CreateWidget<UPlayerHpBar>(-2);
	}
}
