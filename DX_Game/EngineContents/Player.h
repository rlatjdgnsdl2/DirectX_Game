#pragma once
#include <EngineCore/Pawn.h>


//	설명:
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

	class UJob* GetPlayerJob()
	{
		return Job;
	}

	void ChangeAnimation(std::string_view _Name)
	{
		SpriteRenderer->ChangeAnimation(_Name);
	}

	


protected:

private:
	FPlayerLogic PlayerLogic;
	class USpriteRenderer* SpriteRenderer;
	class UMyCollision* Collision;
	class UJob* Job;

	

	//	방향키
	std::map<std::string, class APlayerFunction*> DirFunctionMap;
	//  방향키 제외키
	class UPlayerFuncManager* PlayerFuncManager;

	void CheckKey(float _DeltaTime);
	void Gravity(float _DeltaTime);
	void MoveUpdate(float _DeltaTime);

};

