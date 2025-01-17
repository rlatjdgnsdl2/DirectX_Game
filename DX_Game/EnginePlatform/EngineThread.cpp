#include "PreCompile.h"
#include "EngineThread.h"
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineString.h>

UEngineThread::UEngineThread()
{
}

UEngineThread::~UEngineThread()
{
	Join();
}

void UEngineThread::ThreadBaseFunction(UEngineThread* _Thread)
{
	// �� �Լ��� ������� ����Ǵ� ���̴�.

	std::wstring WName = UEngineString::AnsiToUnicode(_Thread->Name);
	SetThreadDescription(GetCurrentThread(), WName.c_str());

	_Thread->ThreadFunction();

	// ������� ����� �Լ� �������� �̸��� �ٲܼ��� �ֽ��ϴ�.
}

bool UEngineThread::Start(std::string _Name, std::function<void()> _Function)
{
	// ���� ThreadInst ���� ���� �ִ� �������� �ȵȴ�.
	if (true == ThreadInst.joinable())
	{
		return false;
	}

	if (nullptr == _Function)
	{
		MSGASSERT("�Լ��� �������� ���� ������� start �Ҽ� �����ϴ�.");
		return false;
	}

	Name = _Name;
	ThreadFunction = _Function;
	ThreadInst = std::thread(std::bind(ThreadBaseFunction, this));
	return true;
}

void UEngineThread::Join()
{
	ThreadInst.join();
}
