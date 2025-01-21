#include "PreCompile.h"
#include "DamageSkinActor.h"


ADamageSkinActor::ADamageSkinActor()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
	std::vector<float> PosX = { 0.0f, 50.0f, 100.0f, 150.0f, 200.0f, 250.0f, 300.0f, 350.0f, 400.0f, 450.0f, 500.0f, 550.0f, 600.0f, 650.0f };
	for (int i = 0; i < 14; i++)
	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>().get();
		SpriteRenderer->SetupAttachment(RootComponent);
		SpriteRenderer->CreateAnimation("DamageSkin_48", "DamageSkin_0", 0, 4);
		SpriteRenderer->CreateAnimation("DamageSkin_49", "DamageSkin_1", 0, 4);
		SpriteRenderer->CreateAnimation("DamageSkin_50", "DamageSkin_2", 0, 4);
		SpriteRenderer->CreateAnimation("DamageSkin_51", "DamageSkin_3", 0, 4);
		SpriteRenderer->CreateAnimation("DamageSkin_52", "DamageSkin_4", 0, 4);
		SpriteRenderer->CreateAnimation("DamageSkin_53", "DamageSkin_5", 0, 4);
		SpriteRenderer->CreateAnimation("DamageSkin_54", "DamageSkin_6", 0, 4);
		SpriteRenderer->CreateAnimation("DamageSkin_55", "DamageSkin_7", 0, 4);
		SpriteRenderer->CreateAnimation("DamageSkin_56", "DamageSkin_8", 0, 4);
		SpriteRenderer->CreateAnimation("DamageSkin_57", "DamageSkin_9", 0, 4);
		SpriteRenderer->CreateAnimation("DamageSkin_4948", "DamageSkin_10", 0, 4);
		SpriteRenderer->CreateAnimation("DamageSkin_4949", "DamageSkin_11", 0, 4);
		SpriteRenderer->SetRelativeLocation(FVector(PosX[i], 0.0f));
		SpriteRenderer->SetZ(static_cast<float>(Z_ORDER::DamageSkin));

		SpriteRenderers.push_back(SpriteRenderer);
	}
}

ADamageSkinActor::~ADamageSkinActor()
{

}

void ADamageSkinActor::BeginPlay()
{
	AActor::BeginPlay();
	DamageString = std::to_string(Damage);

	int DamageIndex = DamageString.size() - 1;
	int RenderIndex = SpriteRenderers.size() - 1;
	for (int i = 0; i <= DamageIndex; i++)
	{
		if (i == 4) 
		{
			SpriteRenderers[RenderIndex]->ChangeAnimation("DamageSkin_4948");
			RenderIndex--;
			SpriteRenderers[RenderIndex]->ChangeAnimation("DamageSkin_" + std::to_string(DamageString[DamageIndex-i]));
		}
		else if (i == 8) 
		{
			SpriteRenderers[RenderIndex]->ChangeAnimation("DamageSkin_4949");
			RenderIndex--;
			SpriteRenderers[RenderIndex]->ChangeAnimation("DamageSkin_" + std::to_string(DamageString[DamageIndex-i]));
		}
		else {
			SpriteRenderers[RenderIndex]->ChangeAnimation("DamageSkin_" + std::to_string(DamageString[DamageIndex-i]));
		}
		RenderIndex--;
	}
}

void ADamageSkinActor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	CurTime += _DeltaTime;


}
