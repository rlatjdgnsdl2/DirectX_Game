#pragma once
#include <EngineCore/Pawn.h>


//	Ό³Έν:
class APlayer : public APawn
{
public:
	APlayer();
	virtual ~APlayer();
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

	FPlayerLogic& GetPlayerLogic()
	{
		return PlayerLogic;
	}

	class UPlayerFuncManager* GetPlayerFuncManager()
	{
		return PlayerFuncManager;
	}

	class UMyCollision* GetCollision()
	{
		return Collision;
	}

	class USpriteRenderer* GetSpriteRenderer()
	{
		return SpriteRenderer;
	}

	class UJobComponent* GetJobComponent()
	{
		return JobComponent;
	}
	class UPhysicsComponent* GetPysicComponent()
	{
		return PysicsComponent;
	}

	void ChangeAnimation(std::string_view _Name)
	{
		SpriteRenderer->ChangeAnimation(_Name);
	}

	UFSMStateManager& GetFSM()
	{
		return FSM;
	}

	void ProneCollision();
	void StandCollision();

protected:

private:
	FPlayerLogic PlayerLogic;
	UFSMStateManager FSM;

	class USpriteRenderer* SpriteRenderer = nullptr;
	class UMyCollision* Collision = nullptr;

	class UJobComponent* JobComponent = nullptr;
	class UPhysicsComponent* PysicsComponent = nullptr;

	class UPlayerFuncManager* PlayerFuncManager;

	
	/*void Gravity(float _DeltaTime);
	void MoveUpdate(float _DeltaTime);*/

	void Start_Idle();
	void Update_Idle(float _DeltaTime);

	void Start_Move_Left();
	void Update_Move_Left(float _DeltaTime);

	void Start_Move_Right();
	void Update_Move_Right(float _DeltaTime);
	
	void Start_Swift_Phantom();
	void Update_Swift_Phantom(float _DeltaTime);

	void Start_Prone();
	void Update_Prone(float _DeltaTime);

	void Start_Ultimate_Drive();
	void Update_Ultimate_Drive(float _DeltaTime);

};

