#include "PreCompile.h"
#include "Dunkel_HUD.h"
#include "PlayerHpMpBoxFront.h"
#include "PlayerHpMpBoxBack.h"
#include "PlayerHpBar.h"
#include "PlayerMpBar.h"
#include "PlayerHpBarEffect.h"
#include "PlayerMpBarEffect.h"




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
		std::shared_ptr<UPlayerHpMpBoxFront> PlayerHpMpBoxFront = CreateWidget<UPlayerHpMpBoxFront>(-1);
		std::shared_ptr<UPlayerHpMpBoxBack> PlayerHpMpBoxBack = CreateWidget<UPlayerHpMpBoxBack>(-3);
		std::shared_ptr<UPlayerHpBar> PlayerHpBar = CreateWidget<UPlayerHpBar>(-2);
		std::shared_ptr<UPlayerMpBar> PlayerMpBar = CreateWidget<UPlayerMpBar>(-2);
		std::shared_ptr<UPlayerHpBarEffect> PlayerHpBarEffect = CreateWidget<UPlayerHpBarEffect>(-1);
		std::shared_ptr<UPlayerMpBarEffect> PlayerMpBarEffect = CreateWidget<UPlayerMpBarEffect>(-1);
		PlayerHpBar->SetPlayerHpBarEffect(PlayerHpBarEffect.get());
		PlayerMpBar->SetPlayerMpBarEffect(PlayerMpBarEffect.get());
	}
}
