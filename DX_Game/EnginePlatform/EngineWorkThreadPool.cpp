#include "PreCompile.h"
#include "EngineWorkThreadPool.h"

class UWork
{
public:
	std::function<void()> Function;
};

UEngineWorkThreadPool::UEngineWorkThreadPool()
{
}

UEngineWorkThreadPool::~UEngineWorkThreadPool()
{
	IsWork = false;

	// �����带 �����϶�� ���ڰ� -1

	while (0 < RunningCount)
	{
		PostQueuedCompletionStatus(IOCPHandle, static_cast<DWORD>(EThreadStatus::Destroy), 0, nullptr);
	}

}

void UEngineWorkThreadPool::WorkQueue(std::function<void()> _Work)
{
	UWork* NewWork = new UWork();
	NewWork->Function = _Work;

	// ������Ǯ�� ���鶧�� �̰� ���� �ٽ� �Լ��̴�.
	// IOCP �������� ���� ������ �����带 ������.
	PostQueuedCompletionStatus(IOCPHandle, static_cast<DWORD>(EThreadStatus::Work), reinterpret_cast<ULONG_PTR>(NewWork), nullptr);

	// �̰� �ϸ� 
}

void UEngineWorkThreadPool::Initialize(std::string_view ThreadName /*= "WorkThread"*/, int Count /*= 0*/)
{
	ThreadCount = Count;

	if (0 >= Count)
	{
		SYSTEM_INFO Info;
		GetSystemInfo(&Info);
		// �� ��ǻ���� �ھ� ����
		ThreadCount = Info.dwNumberOfProcessors;
	}

	RunningCount = ThreadCount;

	// IOCP�� �ٽ��Լ���
	// CreateIoCompletionPort ������� �� �������� ������ �����ҷ� 
	// IOCP ���� �;�.
	// �̰� 2���� �ǹ̰� �ֽ��ϴ�.
	// ���� �ƹ��͵� ����

	// ������ IOCP �����ϰ� �;�
	// IOCP �����ڵ� �������.
	IOCPHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);

	// ���� ���հ����� �ϰ� �ʹٰ� �ص� IOCP �����ڵ� �������.
	/*FILE* FILE;
	SOCKET Socket;
	CreateIoCompletionPort(IOCPHandle, Socket, 0, 0);*/

	// ��������� �ϸ� �̰� ����ؼ� �� ������ �����ϰ� 
	// CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);

	if (nullptr == IOCPHandle)
	{
		MSGASSERT("IOCP �ڵ� ������ �����߽��ϴ�.");
	}

	// IOCPHandle
	Threads.resize(ThreadCount);
	for (size_t i = 0; i < ThreadCount; i++)
	{
		Threads[i] = std::make_shared<UEngineThread>();

		Threads[i]->Start(std::string(ThreadName) + std::to_string(i), std::bind(ThreadQueueFunction, IOCPHandle, this));
	}
}

void UEngineWorkThreadPool::ThreadQueueFunction(HANDLE _IOCPHandle, UEngineWorkThreadPool* _JobQueue)
{
	/*_Out_ LPDWORD lpNumberOfBytesTransferred,
	_Out_ PULONG_PTR lpCompletionKey,
	_Out_ LPOVERLAPPED* lpOverlapped,
	_In_ DWORD dwMilliseconds*/

	// �̰� ���� ����������̸� ���� ����Ʈ ũ��
	unsigned long Byte = 0;
	unsigned __int64 Ptr;

	// ���� ���� ����.
	// ���� �����̳� ������ �󸶳� �о�� ���� ������ 
	LPOVERLAPPED OverPtr = nullptr;

	// �����带 ������ �ʰ� ��� ����α� ���ؼ� while�ɾ���.
	while (_JobQueue->IsWork)
	{
		// ���� ���������� �ܴ�.
		// _IOCPHandle <= ��ü ���������� ���� 
		// ������ ���ڴ� 1000�� �ð��� ������ �׳� �ƹ��� ��� �Ͼ
		// GetQueuedCompletionStatus(_IOCPHandle, &Byte, &Ptr, &OverPtr, 1000);

		// ����ɼ� �ֳ��� ������?
		GetQueuedCompletionStatus(_IOCPHandle, &Byte, &Ptr, &OverPtr, INFINITE);

		EThreadStatus WorkType = static_cast<EThreadStatus>(Byte);

		if (EThreadStatus::Destroy == WorkType)
		{
			break;
		}

		if (EThreadStatus::Work == WorkType)
		{
			UWork* Work = reinterpret_cast<UWork*>(Ptr);

			if (nullptr != Work)
			{
				Work->Function();
			}

			delete Work;
		}
	}

	_JobQueue->RunningCount -= 1;
}