#pragma once
#include <EngineCore/Pawn.h>


//	����:
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

	class UJobComponent* GetPlayerJob()
	{
		return JobComponent;
	}

	void ChangeAnimation(std::string_view _Name)
	{
		SpriteRenderer->ChangeAnimation(_Name);
	}

	void ProneCollision();
	void StandCollision();

	void SetPysicComponent(class UPhysicComponent* _PysicComponent);
	void SetVelocity(FVector _Velocity);
	void AddVelocity(FVector _Velocity);


protected:

private:
	FPlayerLogic PlayerLogic;
	class USpriteRenderer* SpriteRenderer = nullptr;
	class UMyCollision* Collision = nullptr;
	class UJobComponent* JobComponent = nullptr;
	class UPhysicComponent* PysicComponent = nullptr;

	

	//	����Ű
	std::map<std::string, class APlayerFunction*> DirFunctionMap;
	//  ����Ű ����Ű
	class UPlayerFuncManager* PlayerFuncManager;

	void CheckKey(float _DeltaTime);
	void Gravity(float _DeltaTime);
	void MoveUpdate(float _DeltaTime);

};

