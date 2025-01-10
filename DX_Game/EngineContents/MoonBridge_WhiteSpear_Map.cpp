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
		Collision->SetRelativeLocation(FVector(-MapSize.Half().X-Collision->GetWorldScale3D().Half().X, MapSize.Half().Y));
		EndArea.insert({ "Left", Collision });
	}
	{
		std::shared_ptr<UCollision> Collision = CreateDefaultSubObject<UCollision>();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("EndArea");
		Collision->SetScale3D(FVector(100.0f, MapSize.Y, 1.0f));
		Collision->SetRelativeLocation(FVector(MapSize.Half().X + Collision->GetWorldScale3D().Half().X, MapSize.Half().Y));
		EndArea.insert({ "Right", Collision });
	}

	{
		std::shared_ptr<UCollision> Collision = CreateDefaultSubObject<UCollision>();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("FootHold");
		Collision->SetScale3D(FVector(MapSize.X, 100.0f, 1.0f));
		Collision->SetRelativeLocation(FVector(0.0f, 200.0f));
		EndArea.insert({ "Down", Collision });
	}





}

AMoonBridge_WhiteSpear_Map::~AMoonBridge_WhiteSpear_Map()
{

}

void AMoonBridge_WhiteSpear_Map::BeginPlay()
{
	AActor::BeginPlay();
	AddActorLocation(FVector(0.0f, -450.0f));
}
