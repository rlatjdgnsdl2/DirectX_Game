#include "PreCompile.h"
#include "Monster.h"



AMonster::AMonster()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>().get();
	SpriteRenderer->SetupAttachment(RootComponent);
	
	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("Monster");
		InsertCollision("Character", Collision);
	}

	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("MonsterAttack");
		Collision->SetActive(false);
		InsertCollision("Attack", Collision);
	}

	{
		UMyCollision* Collision = CreateDefaultSubObject<UMyCollision>().get();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("Scope");
		Collision->SetActive(false);
		Collision->SetColor(UContentsConst::SCOPE_COLOR);
		InsertCollision("Scope", Collision);
	}
}

AMonster::~AMonster()
{

}





