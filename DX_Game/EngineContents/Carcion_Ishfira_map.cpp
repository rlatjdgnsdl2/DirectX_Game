#include "PreCompile.h"
#include "Carcion_Ishfira_map.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>


ACarcion_Ishfira_Map::ACarcion_Ishfira_Map()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
	BackRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BackRenderer->SetupAttachment(RootComponent);
	BackRenderer->AddZ(static_cast<float>(Z_ORDER::BackGround));
	BackRenderer->CreateAnimation("Ishfira", "Ishfira", 0, 9);
	BackRenderer->ChangeAnimation("Ishfira");

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
		Collision->SetCollisionProfileName("EndArea");
		Collision->SetScale3D(FVector(MapSize.X, 100.0f, 1.0f));
		Collision->SetRelativeLocation(FVector(0.0f, MapSize.Y));
		EndArea.insert({ "Up", Collision });
	}
	{
		std::shared_ptr<UCollision> Collision = CreateDefaultSubObject<UCollision>();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("FootHold");
		Collision->SetScale3D(FVector(MapSize.X, 100.0f, 1.0f));
		Collision->SetRelativeLocation(FVector(0.0f, -100.0f));
		EndArea.insert({ "Down", Collision });
	}





}

ACarcion_Ishfira_Map::~ACarcion_Ishfira_Map()
{

}
