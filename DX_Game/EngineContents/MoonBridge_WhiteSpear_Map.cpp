#include "PreCompile.h"
#include "MoonBridge_WhiteSpear_Map.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>


AMoonBridge_WhiteSpear_Map::AMoonBridge_WhiteSpear_Map()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
	BackRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BackRenderer->SetupAttachment(RootComponent);
	BackRenderer->AddZ(static_cast<float>(Z_ORDER::BackGround));
	BackRenderer->CreateAnimation("WhiteSpear", "WhiteSpear", 0, 8);
	BackRenderer->ChangeAnimation("WhiteSpear");

	FVector MapSize = BackRenderer->GetWorldScale3D();

	{
		std::shared_ptr<UCollision> Collision = CreateDefaultSubObject<UCollision>();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("EndArea");
		Collision->SetScale3D(FVector(100.0f, MapSize.Y, 1.0f));
		Collision->AddRelativeLocation(FVector(-MapSize.hX() - Collision->GetWorldScale3D().hX(), 0.0f));
		EndArea.insert({ "Left", Collision });
	}
	{
		std::shared_ptr<UCollision> Collision = CreateDefaultSubObject<UCollision>();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("EndArea");
		Collision->SetScale3D(FVector(100.0f, MapSize.Y, 1.0f));
		Collision->AddRelativeLocation(FVector(MapSize.hX() + Collision->GetWorldScale3D().hX(), 0.0f));
		EndArea.insert({ "Right", Collision });
	}

	{
		std::shared_ptr<UCollision> Collision = CreateDefaultSubObject<UCollision>();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("EndArea");
		Collision->SetScale3D(FVector(MapSize.X, 100.0f, 1.0f));
		Collision->AddRelativeLocation(FVector(0.0f,-MapSize.hY() + 200.0f));
		EndArea.insert({ "Down", Collision });
	}


	{
		std::shared_ptr<UCollision> Collision = CreateDefaultSubObject<UCollision>();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("FootHold");
		Collision->SetScale3D(FVector(100.0f, 1.0f, 1.0f));
		Collision->AddRelativeLocation(FVector(1000.0f, 0.0f));
		FootHoldCollisions.push_back(Collision);
	}







}

AMoonBridge_WhiteSpear_Map::~AMoonBridge_WhiteSpear_Map()
{

}

void AMoonBridge_WhiteSpear_Map::BeginPlay()
{
	AActor::BeginPlay();
	AddActorLocation(FVector(0.0f, 200.0f));
	
}
