#include "PreCompile.h"
#include "UI_Icon.h"




AIcon::AIcon() 
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
	
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetupAttachment(RootComponent);

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("UI");

}

AIcon::~AIcon() 
{
	SpriteRenderer = nullptr;
	Collision = nullptr;
}

void AIcon::BeginPlay()
{
	AActor::BeginPlay();
}

void AIcon::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
