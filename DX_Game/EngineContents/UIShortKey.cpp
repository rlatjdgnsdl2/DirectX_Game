#include "PreCompile.h"
#include "UIShortKey.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>



UIShortKey::UIShortKey()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();

	SpriteRenderer_Front = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer_Front->SetupAttachment(RootComponent);
	SpriteRenderer_Front->SetTexture("ShortKey_Front.png",true);
	SpriteRenderer_Front->AddRelativeLocation(FVector(0.0f, 65.0f, 0.0f));

	SpriteRenderer_Back = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer_Back->SetupAttachment(RootComponent);
	SpriteRenderer_Back->SetTexture("ShortKey_Back.png", true);




	{
		std::shared_ptr<UCollision> Collision = CreateDefaultSubObject<UCollision>();
		Collision->SetupAttachment(RootComponent);
		Collision->SetScale3D(IconSize);
		Collision->SetRelativeLocation(QPos);
		Collision->SetCollisionProfileName("UI");
		ShortKeyCollisionMap.insert({ 'Q', Collision });
	}
	{
		std::shared_ptr<UCollision> Collision = CreateDefaultSubObject<UCollision>();
		Collision->SetupAttachment(RootComponent);
		Collision->SetScale3D(IconSize);
		Collision->SetRelativeLocation(FVector(QPos.X+IconSize.X,QPos.Y,QPos.Z));
		Collision->SetCollisionProfileName("UI");
		ShortKeyCollisionMap.insert({ 'W', Collision });
	}
	{
		std::shared_ptr<UCollision> Collision = CreateDefaultSubObject<UCollision>();
		Collision->SetupAttachment(RootComponent);
		Collision->SetScale3D(IconSize);
		Collision->SetRelativeLocation(FVector(QPos.X + IconSize.X*2, QPos.Y, QPos.Z));
		Collision->SetCollisionProfileName("UI");
		ShortKeyCollisionMap.insert({ 'E', Collision });
	}
	{
		std::shared_ptr<UCollision> Collision = CreateDefaultSubObject<UCollision>();
		Collision->SetupAttachment(RootComponent);
		Collision->SetScale3D(IconSize);
		Collision->SetRelativeLocation(FVector(QPos.X + IconSize.X*3, QPos.Y, QPos.Z));
		Collision->SetCollisionProfileName("UI");
		ShortKeyCollisionMap.insert({ 'R', Collision });
	}







}

UIShortKey::~UIShortKey()
{

}
