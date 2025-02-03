#include "PreCompile.h"
#include "Player.h"

#include "MyCollision.h"
#include <EngineCore/EngineCore.h>

#include "PlayerFuncManager.h"
#include "PhysicsComponent.h"


#include "Job_Phantom.h"

#include "DamageSkinFactory.h"
#include "MyGameInstance.h"





APlayer::APlayer()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();

	//Sprite
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>().get();
	SpriteRenderer->SetupAttachment(RootComponent);
	SpriteRenderer->CreateAnimation("Stand", "Player_Stand.png", 0, 2);
	SpriteRenderer->CreateAnimation("Walk", "Player_Walk.png", 0, 3);
	SpriteRenderer->CreateAnimation("Jump", "Player_Jump.png", 0, 0);
	SpriteRenderer->CreateAnimation("Prone", "Player_Prone.png", 0, 0);
	SpriteRenderer->CreateAnimation("UltimateDrive", "Player_UltimateDrive_KeyDown.png", 0, 5);
	SpriteRenderer->SetRelativeLocation(FVector(0.0f,0.0f,UContentsConst::PLAYER_ZPOS));

	//Collision
	Collision = CreateDefaultSubObject<UMyCollision>().get();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Player");
	Collision->SetRelativeScale3D(FVector(30.0f, 60.0f, 1.0f));
	Collision->SetRelativeLocation(FVector(-10.0f, 30.0f));

	PlayerFuncManager = CreateDefaultSubObject<UPlayerFuncManager>().get();
	JobComponent = CreateDefaultSubObject<UJob_Phantom>().get();
	PysicsComponent = CreateDefaultSubObject<UPhysicsComponent>().get();

	FSM.CreateState(EPlayer_State::None, [](float) {}, []() {});
	FSM.CreateState(EPlayer_State::Idle, std::bind(&APlayer::Update_Idle,this,std::placeholders::_1), std::bind(&APlayer::Start_Idle, this));
	FSM.CreateState(EPlayer_State::Prone, std::bind(&APlayer::Update_Prone, this, std::placeholders::_1), std::bind(&APlayer::Start_Prone, this));
	FSM.CreateState(EPlayer_State::Move_Left, std::bind(&APlayer::Update_Move_Left, this, std::placeholders::_1), std::bind(&APlayer::Start_Move_Left, this));
	FSM.CreateState(EPlayer_State::Move_Right, std::bind(&APlayer::Update_Move_Right, this, std::placeholders::_1), std::bind(&APlayer::Start_Move_Right, this));
	FSM.CreateState(EPlayer_State::Swift_Phantom, std::bind(&APlayer::Update_Swift_Phantom, this, std::placeholders::_1), std::bind(&APlayer::Start_Swift_Phantom, this));
	FSM.CreateState(EPlayer_State::Ultimate_Drive, std::bind(&APlayer::Update_Ultimate_Drive, this, std::placeholders::_1), std::bind(&APlayer::Start_Ultimate_Drive, this));
	FSM.CreateState(EPlayer_State::Rift_Break, std::bind(&APlayer::Update_Rift_Break, this, std::placeholders::_1), std::bind(&APlayer::Start_Rift_Break, this));
	FSM.CreateState(EPlayer_State::Defying_Fate, std::bind(&APlayer::Update_Defying_Fate, this, std::placeholders::_1), std::bind(&APlayer::Start_Defying_Fate, this));
	
}

APlayer::~APlayer()
{

}

void APlayer::BeginPlay()
{
	AActor::BeginPlay();	
	FSM.ChangeState(EPlayer_State::Idle);
	
}

void APlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
}

void APlayer::ProneCollision()
{
	Collision->SetRelativeScale3D(FVector(60.0f,30.0f,1.0f));
	Collision->SetRelativeLocation(FVector(0.0f, 15.0f));
}

void APlayer::StandCollision() 
{
	Collision->SetRelativeScale3D(FVector(30.0f, 60.0f, 1.0f));
	Collision->SetRelativeLocation(FVector(-10.0f, 30.0f));
}













