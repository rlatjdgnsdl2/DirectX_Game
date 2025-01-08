#include "PreCompile.h"
#include "Skill_UltimateDrive.h"


ASkill_UltimateDrive::ASkill_UltimateDrive()
{

	{
		std::shared_ptr<USpriteRenderer> SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetupAttachment(RootComponent);
		SpriteRenderer->CreateAnimation("UltimateDrive_Start_Effect_Front", "UltimateDrive_Start_Effect_Front", 0, 4, 0.05f, false);
		SpriteRenderer->CreateAnimation("UltimateDrive_KeyDown_Effect_Front", "UltimateDrive_KeyDown_Effect_Front", 0, 5,0.05f);
		SpriteRenderer->CreateAnimation("UltimateDrive_End_Effect_Front", "UltimateDrive_End_Effect_Front", 0, 4,0.05f,false);




		SpriteRenderer->AddZ(static_cast<float>(Z_ORDER::Skill_Front));
		SpriteRenderer->ChangeAnimation("UltimateDrive_KeyDown_Effect_Front");

		SpriteRenderers.insert(std::make_pair("Front", SpriteRenderer));
	}

	{
		std::shared_ptr<USpriteRenderer> SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();

		SpriteRenderer->SetupAttachment(RootComponent);
		SpriteRenderer->CreateAnimation("UltimateDrive_Start_Effect_Back", "UltimateDrive_Start_Effect_Back", 0, 4,0.05f);
		SpriteRenderer->CreateAnimation("UltimateDrive_KeyDown_Effect_Back", "UltimateDrive_KeyDown_Effect_Back", 0, 5, 0.05f);
		SpriteRenderer->CreateAnimation("UltimateDrive_End_Effect_Back", "UltimateDrive_End_Effect_Back", 0, 4, 0.05f);
		
		SpriteRenderer->SetLoopValue("UltimateDrive_Start_Effect_Back", false);
		SpriteRenderer->SetLoopValue("UltimateDrive_End_Effect_Back", false);


		SpriteRenderer->AddZ(static_cast<float>(Z_ORDER::Skill_Back));
		SpriteRenderer->AddRelativeLocation(FVector(250.0f, 100.0f, 0.0f));
		SpriteRenderers.insert(std::make_pair("Back", SpriteRenderer));
	}
	

	std::shared_ptr<UTimeEventComponent> TimeEvent = CreateDefaultSubObject<UTimeEventComponent>();
	TimeEvent->AddEndEvent(0.3f, [this]() 
		{
			ChangeState(Skill_Frame::KeyDown);
		});

}

ASkill_UltimateDrive::~ASkill_UltimateDrive()
{

}

void ASkill_UltimateDrive::BeginPlay()
{
	ASkill::BeginPlay();
	FrameState.CreateState(Skill_Frame::Start, [this](float _DeltaTime)
		{
		},
		[this]()
		{
			SpriteRenderers["Front"]->ChangeAnimation("UltimateDrive_Start_Effect_Front");
			SpriteRenderers["Front"]->SetRelativeLocation(FVector(70.0f,-30.0f,static_cast<float>(Z_ORDER::Skill_Front)));
			SpriteRenderers["Back"]->ChangeAnimation("UltimateDrive_Start_Effect_Back");
			SpriteRenderers["Back"]->SetRelativeLocation(FVector(80.0f, -20.0f, static_cast<float>(Z_ORDER::Skill_Back)));
		});
	FrameState.CreateState(Skill_Frame::KeyDown, [this](float _DeltaTime)
		{
		},
		[this]()
		{
			SpriteRenderers["Front"]->ChangeAnimation("UltimateDrive_KeyDown_Effect_Front");
			SpriteRenderers["Front"]->SetRelativeLocation(FVector(-130.0f, -150.0f, static_cast<float>(Z_ORDER::Skill_Front)));
			SpriteRenderers["Back"]->ChangeAnimation("UltimateDrive_KeyDown_Effect_Back");
			SpriteRenderers["Back"]->SetRelativeLocation(FVector(100.0f, -55.0f, static_cast<float>(Z_ORDER::Skill_Back)));
		});

	FrameState.CreateState(Skill_Frame::End, [this](float _DeltaTime) {},
		[this]()
		{
			SpriteRenderers["Front"]->ChangeAnimation("UltimateDrive_End_Effect_Front");
			SpriteRenderers["Front"]->SetRelativeLocation(FVector(-130.0f, -150.0f, static_cast<float>(Z_ORDER::Skill_Front)));
			SpriteRenderers["Back"]->ChangeAnimation("UltimateDrive_End_Effect_Back");
			SpriteRenderers["Back"]->SetRelativeLocation(FVector(100.0f, -55.0f, static_cast<float>(Z_ORDER::Skill_Back)));
		});

	FrameState.ChangeState(Skill_Frame::Start);
}

void ASkill_UltimateDrive::Tick(float _DeltaTime)
{
	ASkill::Tick(_DeltaTime);	
	if (Skill_Frame::End == static_cast<Skill_Frame>(FrameState.GetCurStateValue())) {
		if (SpriteRenderers["Front"]->IsCurAnimationEnd()) {
			SetActive(false);
			Destroy();
		}
	}
}
