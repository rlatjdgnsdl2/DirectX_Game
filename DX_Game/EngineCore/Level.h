#pragma once

#include <EngineBase/Object.h>
#include <EngineBase/EngineDebug.h>

// 설명 :
class ULevel : public UObject
{
	friend class UCollision;
	friend class UEngineCore;

public:
	// constrcuter destructer
	ENGINEAPI ULevel();
	ENGINEAPI ~ULevel();

	// delete Function
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	
	ENGINEAPI void LevelChangeStart();
	
	ENGINEAPI void LevelChangeEnd();

	template<typename Type>
	Type* GetGameMode()
	{
		return dynamic_cast<Type*>(GameMode);
	}


	ENGINEAPI class AGameMode* GetGameMode()
	{
		return GameMode;
	}

	template<typename Type>
	Type* GetMainPawn()
	{
		return dynamic_cast<Type*>(MainPawn);
	}

	ENGINEAPI class APawn* GetMainPawn()
	{
		return MainPawn;
	}

	template<typename Type>
	Type* GetHUD()
	{
		return dynamic_cast<Type*>(HUD);
	}
	ENGINEAPI class AHUD* GetHUD()
	{
		return HUD;
	}



	void Tick(float _DeltaTime);
	void Render(float _DeltaTime);
	void Collision(float _DeltaTime);
	void Release(float _DeltaTime);

	ENGINEAPI std::shared_ptr<class ACameraActor> GetMainCamera()
	{
		return GetCamera(0);
	}

	ENGINEAPI std::shared_ptr<class ACameraActor> GetCamera(int _Order)
	{
		if (false == Cameras.contains(_Order))
		{
			MSGASSERT("존재하지 않는 카메라를 사용하려고 했습니다.");
		}

		return Cameras[_Order];
	}

	template<typename EnumType>
	ENGINEAPI std::shared_ptr<class ACameraActor> SpawnCamera(EnumType _Order)
	{
		return SpawnCamera(static_cast<int>(_Order));
	}

	std::shared_ptr<class ACameraActor> SpawnCamera(int _Order);

	template<typename ActorType>
	ENGINEAPI std::shared_ptr<ActorType> SpawnActor(std::string_view _Name = "")
	{


		static_assert(std::is_base_of_v<AActor, ActorType>, "액터를 상속받지 않은 클래스를 SpawnActor하려고 했습니다.");

		if (false == std::is_base_of_v<AActor, ActorType>)
		{
			MSGASSERT("액터를 상속받지 않은 클래스를 SpawnActor하려고 했습니다.");
			return nullptr;
			// static_assert
		}

		char* ActorMemory = new char[sizeof(ActorType)];


		AActor* ActorPtr = reinterpret_cast<ActorType*>(ActorMemory);
		ActorPtr->World = this;

		ActorType* NewPtr = reinterpret_cast<ActorType*>(ActorMemory);
		// 레벨먼저 세팅하고
		// 플레이스먼트 new 
		std::shared_ptr<ActorType> NewActor(NewPtr = new(ActorMemory) ActorType());

		ActorPtr->SetName(_Name);

		//컴파일러는 그걸 모른다.
		BeginPlayList.push_back(NewActor);

		return NewActor;
	}
	template<typename EnumType>
	std::shared_ptr<class ACameraActor> GetCamera(EnumType _Order)
	{
		return GetCamera(static_cast<int>(_Order));
	}

	//                           0              100그룹
	ENGINEAPI void ChangeRenderGroup(int _CameraOrder, int _PrevGroupOrder, std::shared_ptr<class URenderer> _Renderer);

	ENGINEAPI void ChangeCollisionProfileName(std::string_view _ProfileName, std::string_view _PrevProfileName, std::shared_ptr<class UCollision> _Collision);

	ENGINEAPI void PushCollisionProfileEvent(std::shared_ptr<class URenderer> _Renderer);

	ENGINEAPI void CreateCollisionProfile(std::string_view _ProfileName);

	ENGINEAPI void LinkCollisionProfile(std::string_view _LeftProfileName, std::string_view _RightProfileName);

	// #ifdef _DEBUG
		// 에디터에서는 빠른지 느린지를 따지지 않는다.
		// 에디터기능을 만들때는 최적화를 신경안쓰는 경우가 많다.
		// 실제 플레이와는 전혀 관련이 없으니까.
	template<typename ConvertType>
	ENGINEAPI std::list<std::shared_ptr<ConvertType>> GetAllActorListByClass()
	{
		std::list<std::shared_ptr<ConvertType>> List;

		for (std::shared_ptr<class AActor> Actor : AllActorList)
		{
			std::shared_ptr<ConvertType> Convert = std::dynamic_pointer_cast<ConvertType>(Actor);
			if (nullptr == Convert)
			{
				continue;
			}
			List.push_back(Convert);
		}

		return List;
	}

	template<typename ConvertType>
	ENGINEAPI std::vector<std::shared_ptr<ConvertType>> GetAllActorArrayByClass()
	{
		std::vector<std::shared_ptr<ConvertType>> List;

		for (std::shared_ptr<class AActor> Actor : AllActorList)
		{
			std::shared_ptr<ConvertType> Convert = std::dynamic_pointer_cast<ConvertType>(Actor);
			if (nullptr == Convert)
			{
				continue;
			}
			List.push_back(Convert);
		}

		return List;
	}
	// #endif

protected:

private:
	class AHUD* HUD = nullptr;

	class AGameMode* GameMode = nullptr;

	class APawn* MainPawn = nullptr;

	std::list<std::shared_ptr<class AActor>> BeginPlayList;

	std::list<std::shared_ptr<class AActor>> AllActorList;

	
	std::map<int, std::shared_ptr<class ACameraActor>> Cameras;

	std::shared_ptr<class UEngineRenderTarget> LastRenderTarget;

	std::map<std::string, std::list<std::shared_ptr<class UCollision>>> Collisions;

	std::map<std::string, std::list<std::shared_ptr<class UCollision>>> CheckCollisions;
	std::map<std::string, std::list<std::string>> CollisionLinks;
	std::map<int, std::list<std::shared_ptr<class UWidget>>> Widgets;

	ENGINEAPI void InitLevel(class AGameMode* _GameMode, class APawn* _Pawn, class AHUD* _HUD);
};

