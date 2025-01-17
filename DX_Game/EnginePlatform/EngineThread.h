#pragma once
#include <thread>
#include <functional>

// ���� : �𸮾� ����� �ƴմϴ�.
// �𸮾󿡼� ����Ƽ�� �����鸣 ����Ϸ��� Run ���ñ� ����� �༮�� ����ؾ� �Ѵ�.
class UEngineThread
{
public:
	// constrcuter destructer
	ENGINEAPI UEngineThread();
	ENGINEAPI virtual ~UEngineThread();

	// delete Function
	UEngineThread(const UEngineThread& _Other) = delete;
	UEngineThread(UEngineThread&& _Other) noexcept = delete;
	UEngineThread& operator=(const UEngineThread& _Other) = delete;
	UEngineThread& operator=(UEngineThread&& _Other) noexcept = delete;

	ENGINEAPI bool Start(std::string _Name, std::function<void()> _Function);
	ENGINEAPI void Join();

protected:

private:
	std::string Name;
	std::thread ThreadInst;
	std::function<void()> ThreadFunction;

	static void ThreadBaseFunction(UEngineThread* _Thread);
};

