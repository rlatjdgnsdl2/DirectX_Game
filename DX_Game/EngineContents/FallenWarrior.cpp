#include "PreCompile.h"
#include "FallenWarrior.h"



AFallenWarrior::AFallenWarrior()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetupAttachment(RootComponent);

	SpriteRenderer->CreateAnimation("Spawn", "FallenWarrior_Spawn", 0, 13, 0.1f, false);
	SpriteRenderer->CreateAnimation("Stand", "FallenWarrior_Stand", 0, 7);
	SpriteRenderer->CreateAnimation("Move", "FallenWarrior_Move", 0, 7);
	SpriteRenderer->CreateAnimation("Attack", "FallenWarrior_Attack", 0, 11);
	SpriteRenderer->CreateAnimation("Die", "FallenWarrior_Die", 0, 13);

	AnimaionFSM.CreateState(DunkelAnim_State::Spawn, [this](float _DeltaTime)
		{
			if (SpriteRenderer->IsCurAnimationEnd())
			{
				AnimaionFSM.ChangeState(DunkelAnim_State::Stand);
			}
		},
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Spawn", true);
			//SpriteRenderer->SetRelativeLocation(FVector(20.0f, 30.0f, static_cast<float>(Z_ORDER::Boss)));
			//Collision->SetActive(false);

		});
	AnimaionFSM.CreateState(DunkelAnim_State::Stand, nullptr,
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Stand");
			SpriteRenderer->SetRelativeLocation(FVector(0.0f, 0.0f, static_cast<float>(Z_ORDER::Boss)));
			//Collision->SetActive(true);
			//Collision->SetRelativeLocation(FVector(50.0f, 10.0f));
		});
	


}

AFallenWarrior::~AFallenWarrior()
{

}

void AFallenWarrior::BeginPlay()
{
	AMonster::BeginPlay();
	AnimaionFSM.ChangeState(DunkelAnim_State::Spawn);
	
}

void AFallenWarrior::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);
}
