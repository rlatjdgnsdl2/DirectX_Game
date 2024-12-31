#include "PreCompile.h"
#include "UIShortKeySetting.h"
#include <EngineCore/DefaultSceneComponent.h>


UIShortKeySetting::UIShortKeySetting() 
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
	Back = CreateDefaultSubObject<USpriteRenderer>();
	Back->SetupAttachment(RootComponent);
	Back->SetSprite("Player_Walk");
	
	
}

UIShortKeySetting::~UIShortKeySetting() 
{

}
