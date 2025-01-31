#include "PreCompile.h"
#include "Dunkel_Map.h"

#include "Player.h"
#include "PhysicsComponent.h"
#include "MyCollision.h"


ADunkel_Map::ADunkel_Map()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();

	BackRenderer = CreateDefaultSubObject<USpriteRenderer>().get();
	BackRenderer->SetupAttachment(RootComponent);
	BackRenderer->SetZ(UContentsConst::BACKGROUND_ZPOS);
	BackRenderer->CreateAnimation("DunkelMapBackGround", "DunkelMapBackGround", 0, 9);
	BackRenderer->ChangeAnimation("DunkelMapBackGround");

	FVector MapSize = BackRenderer->GetWorldScale3D();
	SetActorLocation(FVector(0.0f, MapSize.hY() - 126.0f));

	{
		std::shared_ptr<UMyCollision> Collision = CreateDefaultSubObject<UMyCollision>();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("EndArea");
		Collision->SetRelativeScale3D(FVector(600.0f, MapSize.Y, 1.0f));
		Collision->AddRelativeLocation(FVector(-MapSize.hX() - 300.0f, 0.0f));
		Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
			{
				float LeftEndArea = _Left->GetTransformRef().ZAxisWorldCenterRight();
				float RightLeft = _Right->GetTransformRef().ZAxisWorldCenterLeft();
				_Right->GetActor()->AddActorLocation(FVector(LeftEndArea - RightLeft, 0.0f, 0.0f));
			});

		EndArea.insert({ "Left", Collision.get() });
	}
	{
		std::shared_ptr<UMyCollision> Collision = CreateDefaultSubObject<UMyCollision>();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("EndArea");
		Collision->SetRelativeScale3D(FVector(600.0f, MapSize.Y, 1.0f));
		Collision->AddRelativeLocation(FVector(MapSize.hX() + 300.0f, 0.0f));
		Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
			{
				float RightEndArea = _Left->GetTransformRef().ZAxisWorldCenterLeft();
				float RightLeft = _Right->GetTransformRef().ZAxisWorldCenterRight();
				_Right->GetActor()->AddActorLocation(FVector(RightEndArea - RightLeft, 0.0f, 0.0f));
			});
		EndArea.insert({ "Right", Collision.get() });
	}

	{
		std::shared_ptr<UMyCollision> Collision = CreateDefaultSubObject<UMyCollision>();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("EndArea");
		Collision->SetRelativeScale3D(FVector(MapSize.X, 100.0f, 1.0f));
		Collision->AddRelativeLocation(FVector(0.0f, -MapSize.hY() + 76.0f));

		Collision->SetCollisionEnter([this](UCollision* _Left, UCollision* _Right)
			{
				if (_Right->GetCollisionProfileName() == "PLAYER")
				{
					APlayer* Player = dynamic_cast<APlayer*>(_Right->GetActor());
					if (Player == nullptr)
					{
						return;
					}
					UPhysicsComponent* Component = Player->GetPysicComponent();
					if (Component == nullptr)
					{
						return;
					}
					if (!Component->IsFalling())
					{
						return;
					}
					Component->SetGroundTrue();
					Component->SetVelocityY(0.0f);
					float DownEndAreaTop = _Left->GetTransformRef().ZAxisWorldCenterTop();
					float PlayerBottom = _Right->GetTransformRef().ZAxisWorldCenterBottom();
					Player->AddActorLocation(FVector(0.0f, DownEndAreaTop - PlayerBottom, 0.0f));
				}
			});
		Collision->SetCollisionEnd([this](UCollision* _Left, UCollision* _Right)
			{
				if (_Right->GetCollisionProfileName() == "PLAYER")
				{
					APlayer* Player = dynamic_cast<APlayer*>(_Right->GetActor());
					if (Player == nullptr)
					{
						return;
					}
					UPhysicsComponent* Component = Player->GetPysicComponent();
					if (Component == nullptr)
					{
						return;
					}
					Component->SetGroundFalse();
				}
			});
		EndArea.insert({ "Down", Collision.get() });
	}


	{

		std::shared_ptr<USpriteRenderer> SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetupAttachment(RootComponent);
		SpriteRenderer->SetRelativeLocation(FVector(0.0f, -400.0f, UContentsConst::FOOTHOLD_ZPOS));
		SpriteRenderer->SetTexture("DunkelMapFootHold.png", true);

		FootHoldRenderer = SpriteRenderer.get();
	}

	{

		std::shared_ptr<USpriteRenderer> SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetupAttachment(RootComponent);
		SpriteRenderer->SetRelativeLocation(FVector(0.0f, 100.0f, UContentsConst::MAPOBJECT_FAR_ZPOS));
		SpriteRenderer->CreateAnimation("DunkelMapObject_Sphere", "DunkelMapObject_Sphere", 0, 15);
		SpriteRenderer->ChangeAnimation("DunkelMapObject_Sphere");

		ObjectRenderers.push_back(SpriteRenderer.get());
	}
	{

		std::shared_ptr<USpriteRenderer> SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetupAttachment(RootComponent);
		SpriteRenderer->SetRelativeLocation(FVector(0.0f, -110.0f, UContentsConst::MAPOBJECT_MIDDLE_ZPOS));
		SpriteRenderer->CreateAnimation("DunkelMapObject_Stone", "DunkelMapObject_Stone", 0, 13);
		SpriteRenderer->ChangeAnimation("DunkelMapObject_Stone");
		ObjectRenderers.push_back(SpriteRenderer.get());
	}


	GetWorld()->LinkCollisionProfile("EndArea", "Player");
	GetWorld()->LinkCollisionProfile("EndArea", "Boss");
	GetWorld()->LinkCollisionProfile("EndArea", "Monster");
	GetWorld()->LinkCollisionProfile("EndArea", "EliteMonster");

}

ADunkel_Map::~ADunkel_Map()
{

}
