#include "PreCompile.h"
#include "Dunkel_Map.h"
#include "Player.h"
#include "MyCollision.h"


ADunkel_Map::ADunkel_Map()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
	BackRenderer = CreateDefaultSubObject<USpriteRenderer>().get();
	BackRenderer->SetupAttachment(RootComponent);
	BackRenderer->SetZ(static_cast<float>(Z_ORDER::BackGround));
	BackRenderer->CreateAnimation("DunkelMapBackGround", "DunkelMapBackGround", 0, 9);
	BackRenderer->ChangeAnimation("DunkelMapBackGround");

	FVector MapSize = BackRenderer->GetWorldScale3D();
	SetActorLocation(FVector(0.0f, MapSize.hY() - 126.0f));

	{
		std::shared_ptr<UMyCollision> Collision = CreateDefaultSubObject<UMyCollision>();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("EndArea");
		Collision->SetRelativeScale3D(FVector(100.0f, MapSize.Y, 1.0f));
		Collision->AddRelativeLocation(FVector(-MapSize.hX() + 100.0f, 0.0f));
		Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
			{
				APlayer* Player = dynamic_cast<APlayer*>(_Right->GetActor());
				float LeftEndArea = _Left->GetTransformRef().ZAxisWorldCenterRight();
				float PlayerLeft = _Right->GetTransformRef().ZAxisWorldCenterLeft();
				Player->AddActorLocation(FVector(LeftEndArea - PlayerLeft, 0.0f, 0.0f));
			});

		EndArea.insert({ "Left", Collision.get()});
	}
	{
		std::shared_ptr<UMyCollision> Collision = CreateDefaultSubObject<UMyCollision>();
		Collision->SetupAttachment(RootComponent);
		Collision->SetCollisionProfileName("EndArea");
		Collision->SetRelativeScale3D(FVector(100.0f, MapSize.Y, 1.0f));
		Collision->AddRelativeLocation(FVector(MapSize.hX() - 60.0f, 0.0f));
		Collision->SetCollisionStay([this](UCollision* _Left, UCollision* _Right)
			{
				APlayer* Player = dynamic_cast<APlayer*>(_Right->GetActor());
				float RightEndArea = _Left->GetTransformRef().ZAxisWorldCenterLeft();
				float PlayerLeft = _Right->GetTransformRef().ZAxisWorldCenterRight();
				Player->AddActorLocation(FVector(RightEndArea - PlayerLeft, 0.0f, 0.0f));
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
				APlayer* Player = dynamic_cast<APlayer*>(_Right->GetActor());
				FPlayerLogic& LogicValue = Player->GetPlayerLogic();
				if (LogicValue.bIsFalling) {
					LogicValue.SetGroundTrue();
					float DownEndAreaTop = _Left->GetTransformRef().ZAxisWorldCenterTop();
					float PlayerBottom = _Right->GetTransformRef().ZAxisWorldCenterBottom();
					Player->AddActorLocation(FVector(0.0f, DownEndAreaTop - PlayerBottom, 0.0f));
					Player->GetPlayerLogic().SetGravityAccel(0.0f);
					Player->GetPlayerLogic().SetVelocityX(0.0f);
					Player->GetPlayerLogic().SetVelocityY(0.0f);
					Player->GetPlayerLogic().SetDownableFloor(false);
				}
			});
		Collision->SetCollisionEnd([this](UCollision* _Left, UCollision* _Right)
			{
				APlayer* Player = dynamic_cast<APlayer*>(_Right->GetActor());
				FPlayerLogic& LogicValue = Player->GetPlayerLogic();
				if (LogicValue.bIsGround) {
					LogicValue.bIsGround = false;
				}
			});
		EndArea.insert({ "Down", Collision.get() });
	}


	{

		std::shared_ptr<USpriteRenderer> SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetupAttachment(RootComponent);
		SpriteRenderer->SetZ(static_cast<float>(Z_ORDER::FootHold));
		SpriteRenderer->AddRelativeLocation(FVector(0.0f, -400.0f));
		SpriteRenderer->SetTexture("DunkelMapFootHold.png", true);

		FootHoldRenderer = SpriteRenderer.get();
	}

	{

		std::shared_ptr<USpriteRenderer> SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetupAttachment(RootComponent);
		SpriteRenderer->SetZ(static_cast<float>(Z_ORDER::MapObject_Far));
		SpriteRenderer->AddRelativeLocation(FVector(0.0f, 100.0f));
		SpriteRenderer->CreateAnimation("DunkelMapObject_Sphere", "DunkelMapObject_Sphere", 0, 15);
		SpriteRenderer->ChangeAnimation("DunkelMapObject_Sphere");

		ObjectRenderers.push_back(SpriteRenderer.get());
	}
	{

		std::shared_ptr<USpriteRenderer> SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetupAttachment(RootComponent);
		SpriteRenderer->SetZ(static_cast<float>(Z_ORDER::MapObject_Middle));
		SpriteRenderer->AddRelativeLocation(FVector(0.0f, -110.0f));
		SpriteRenderer->CreateAnimation("DunkelMapObject_Stone", "DunkelMapObject_Stone", 0, 13);
		SpriteRenderer->ChangeAnimation("DunkelMapObject_Stone");
		ObjectRenderers.push_back(SpriteRenderer.get());
	}


	GetWorld()->LinkCollisionProfile("EndArea", "Player");



}

ADunkel_Map::~ADunkel_Map()
{

}
