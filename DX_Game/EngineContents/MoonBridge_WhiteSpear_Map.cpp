#include "PreCompile.h"
#include "MoonBridge_WhiteSpear_Map.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

#include "Player.h"


AMoonBridge_WhiteSpear_Map::AMoonBridge_WhiteSpear_Map()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
	BackRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BackRenderer->SetupAttachment(RootComponent);
	BackRenderer->SetZ(UContentsConst::BACKGROUND_ZPOS);
	BackRenderer->CreateAnimation("WhiteSpear", "WhiteSpear", 0, 8);
	BackRenderer->ChangeAnimation("WhiteSpear");

	FVector MapSize = BackRenderer->GetWorldScale3D();

	{
		std::shared_ptr<UCollision> Collision = CreateDefaultSubObject<UCollision>();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("EndArea");
		Collision->SetScale3D(FVector(100.0f, MapSize.Y, 1.0f));
		Collision->AddRelativeLocation(FVector(-MapSize.hX() - Collision->GetWorldScale3D().hX(), 0.0f));
		Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
			{
				APlayer* Player = dynamic_cast<APlayer*>(_Right->GetActor());
				float LeftEndArea = _Left->GetTransformRef().ZAxisWorldCenterRight();
				float PlayerLeft = _Right->GetTransformRef().ZAxisWorldCenterLeft();
				Player->AddActorLocation(FVector(LeftEndArea - PlayerLeft, 0.0f, 0.0f));
			});

		EndArea.insert({ "Left", Collision });
	}
	{
		std::shared_ptr<UCollision> Collision = CreateDefaultSubObject<UCollision>();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("EndArea");
		Collision->SetScale3D(FVector(100.0f, MapSize.Y, 1.0f));
		Collision->AddRelativeLocation(FVector(MapSize.hX() + Collision->GetWorldScale3D().hX(), 0.0f));
		Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
			{
				APlayer* Player = dynamic_cast<APlayer*>(_Right->GetActor());
				float RightEndArea = _Left->GetTransformRef().ZAxisWorldCenterLeft();
				float PlayerLeft = _Right->GetTransformRef().ZAxisWorldCenterRight();
				Player->AddActorLocation(FVector(RightEndArea - PlayerLeft, 0.0f, 0.0f));
			});
		EndArea.insert({ "Right", Collision });
	}

	{
		std::shared_ptr<UCollision> Collision = CreateDefaultSubObject<UCollision>();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("EndArea");
		Collision->SetScale3D(FVector(MapSize.X, 100.0f, 1.0f));
		Collision->AddRelativeLocation(FVector(0.0f, -MapSize.hY() + 215.0f));

		Collision->SetCollisionEnter([this](UCollision* _Left, UCollision* _Right)
			{
				
			});
		Collision->SetCollisionEnd([this](UCollision* _Left, UCollision* _Right)
			{
				
			});
		EndArea.insert({ "Down", Collision });
	}

	{
		std::shared_ptr<UCollision> Collision = CreateDefaultSubObject<UCollision>();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("FootHold");
		Collision->SetScale3D(FVector(1000.0f, 1.0f, 1.0f));
		Collision->AddRelativeLocation(FVector(1380.0f, -40.0f));

		Collision->SetCollisionEnter([this](UCollision* _Left, UCollision* _Right)
			{
				
			});
		Collision->SetCollisionEnd([this](UCollision* _Left, UCollision* _Right)
			{
				
			});
		FootHoldCollisions.push_back(Collision);
	}

	GetWorld()->LinkCollisionProfile("EndArea", "Player");
	GetWorld()->LinkCollisionProfile("FootHold", "Player");
}

AMoonBridge_WhiteSpear_Map::~AMoonBridge_WhiteSpear_Map()
{
	EndArea.clear();
	FootHoldCollisions.clear();
	FootHoldRenderers.clear();
	BackRenderer = nullptr;
}

void AMoonBridge_WhiteSpear_Map::BeginPlay()
{
	AActor::BeginPlay();
	AddActorLocation(FVector(0.0f, 200.0f));

}
