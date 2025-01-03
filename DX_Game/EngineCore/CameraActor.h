#pragma once
#include "Actor.h"

// ���� :
class ACameraActor : public AActor
{
public:
	// constrcuter destructer
	ACameraActor();
	~ACameraActor();

	// delete Function
	ACameraActor(const ACameraActor& _Other) = delete;
	ACameraActor(ACameraActor&& _Other) noexcept = delete;
	ACameraActor& operator=(const ACameraActor& _Other) = delete;
	ACameraActor& operator=(ACameraActor&& _Other) noexcept = delete;

	ENGINEAPI std::shared_ptr<class UEngineCamera> GetCameraComponent()
	{
		return CameraComponent;
	}

	void BeginPlay() override;
	void Tick(float _DeltaTime);

	ENGINEAPI FVector ScreenMousePosToWorldPos();

	// �׻� �߽��� 0,0 ���� ���� ���콺 ���� ��¹�
	ENGINEAPI FVector ScreenMousePosToWorldPosWithOutPos();

protected:

private:
	std::shared_ptr<class UEngineCamera> CameraComponent = nullptr;
};

