#include "PreCompile.h"
#include "Skill_UltimateDrive.h"


ASkill_UltimateDrive::ASkill_UltimateDrive() 
{

}

ASkill_UltimateDrive::~ASkill_UltimateDrive() 
{

}

void ASkill_UltimateDrive::BeginPlay()
{
	AActor::BeginPlay();
	{
		std::shared_ptr<USpriteRenderer> SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		if (RootComponent == nullptr)
		{
			RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
		}
		SpriteRenderer->SetupAttachment(RootComponent);
		SpriteRenderer->CreateAnimation("UltimateDrive_Start_Effect_Front", "UltimateDrive_Start_Effect_Front", 0, 4);
		SpriteRenderer->CreateAnimation("UltimateDrive_KeyDown_Effect_Front", "UltimateDrive_KeyDown_Effect_Front", 0, 4);
		SpriteRenderer->CreateAnimation("UltimateDrive_End_Effect_Front", "UltimateDrive_End_Effect_Front", 0, 4);
		
		SpriteRenderers.insert(std::make_pair(static_cast<int>(Z_ORDER::Skill_PlayerFront), SpriteRenderer));
		
	}
	{
		std::shared_ptr<USpriteRenderer> SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		if (RootComponent == nullptr)
		{
			RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
		}
		SpriteRenderer->SetupAttachment(RootComponent);
		SpriteRenderer->CreateAnimation("UltimateDrive_Start_Effect_Back", "UltimateDrive_Start_Effect_Back", 0, 4);
		SpriteRenderer->CreateAnimation("UltimateDrive_KeyDown_Effect_Back", "UltimateDrive_KeyDown_Effect_Back", 0, 4);
		SpriteRenderer->CreateAnimation("UltimateDrive_End_Effect_Back", "UltimateDrive_End_Effect_Back", 0, 4);
		SpriteRenderers.insert(std::make_pair(static_cast<int>(Z_ORDER::Skill_PlayerBack), SpriteRenderer));
	}

	SpriteRenderers[static_cast<int>(Z_ORDER::Skill_PlayerFront)]->ChangeAnimation("UltimateDrive_Start_Effect_Front");
	SpriteRenderers[static_cast<int>(Z_ORDER::Skill_PlayerBack)]->ChangeAnimation("UltimateDrive_Start_Effect_Back");


}

void ASkill_UltimateDrive::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
