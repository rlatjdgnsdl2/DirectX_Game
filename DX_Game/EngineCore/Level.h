#pragma once

#include <EngineBase/Object.h>
#include <EngineBase/EngineDebug.h>

// ���� :
class ULevel : public UObject
{
	friend class UCollision;

public:
	// constrcuter destructer
	ENGINEAPI ULevel();
	ENGINEAPI ~ULevel();

	// delete Function
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	// ���� ���� ����Ǵ� ������ �Ǿ�����
	void LevelChangeStart();
	// ���� ��ü ��������
	void LevelChangeEnd();


	void Tick(float _DeltaTime);
	void Render(float _DeltaTime);
	void Collision(float _DeltaTime);
	void Release(float _DeltaTime);

	std::shared_ptr<class ACameraActor> GetMainCamera()
	{
		return GetCamera(0);
	}

	std::shared_ptr<class ACameraActor> GetCamera(int _Order)
	{
		if (false == Cameras.contains(_Order))
		{
			MSGASSERT("�������� �ʴ� ī�޶� ����Ϸ��� �߽��ϴ�.");
		}

		return Cameras[_Order];
	}

	template<typename EnumType>
	std::shared_ptr<class ACameraActor> SpawnCamera(EnumType _Order)
	{
		return SpawnCamera(static_cast<int>(_Order));
	}

	std::shared_ptr<class ACameraActor> SpawnCamera(int _Order);

	template<typename ActorType>
	std::shared_ptr<ActorType> SpawnActor()
	{
		// AMonster : public AActor
		// SpawnActor<AMonster>();
		// std::shared_ptr<AMonster>

		static_assert(std::is_base_of_v<AActor, ActorType>, "���͸� ��ӹ��� ���� Ŭ������ SpawnActor�Ϸ��� �߽��ϴ�.");

		if (false == std::is_base_of_v<AActor, ActorType>)
		{
			MSGASSERT("���͸� ��ӹ��� ���� Ŭ������ SpawnActor�Ϸ��� �߽��ϴ�.");
			return nullptr;
			// static_assert
		}

		char* ActorMemory = new char[sizeof(ActorType)];


		AActor* ActorPtr = reinterpret_cast<ActorType*>(ActorMemory);
		ActorPtr->World = this;

		ActorType* NewPtr = reinterpret_cast<ActorType*>(ActorMemory);
		// �������� �����ϰ�
		// �÷��̽���Ʈ new 
		std::shared_ptr<ActorType> NewActor(NewPtr = new(ActorMemory) ActorType());

		//�����Ϸ��� �װ� �𸥴�.
		BeginPlayList.push_back(NewActor);

		return NewActor;
	}

	//                           0              100�׷�
	ENGINEAPI void ChangeRenderGroup(int _CameraOrder, int _PrevGroupOrder, std::shared_ptr<class URenderer> _Renderer);

	ENGINEAPI void ChangeCollisionProfileName(std::string_view _ProfileName, std::string_view _PrevProfileName, std::shared_ptr<class UCollision> _Collision);

	ENGINEAPI void PushCollisionProfileEvent(std::shared_ptr<class URenderer> _Renderer);

	ENGINEAPI void CreateCollisionProfile(std::string_view _ProfileName);

	ENGINEAPI void LinkCollisionProfile(std::string_view _LeftProfileName, std::string_view _RightProfileName);


protected:

private:
	std::list<std::shared_ptr<class AActor>> BeginPlayList;

	std::list<std::shared_ptr<class AActor>> AllActorList;

	// 0���� mainamera��� �Ҹ��� �ָ� �����.
	std::map<int, std::shared_ptr<class ACameraActor>> Cameras;

	// �����ϱ����� string Hashȭ ��� �۾��� ���ؼ� �� ���ڷ� 
	// ������ �ϱ� ���� �̾߱�
	std::map<std::string, std::list<std::shared_ptr<class UCollision>>> Collisions;

	// �̺�Ʈ�� �����ϴ� �ֵ鸸 �浹 üũ�Ϸ���.
	std::map<std::string, std::list<std::shared_ptr<class UCollision>>> CheckCollisions;

	std::map<std::string, std::list<std::string>> CollisionLinks;
};

