#include "PreCompile.h"
#include "EngineCore.h"
#include <EngineBase/EngineDebug.h>
#include <EnginePlatform/EngineWindow.h>
#include "IContentsCore.h"
#include "EngineResources.h"
#include "EngineGUI.h"
#include "Level.h"

UEngineGraphicDevice UEngineCore::Device;
UEngineWindow UEngineCore::MainWindow;
HMODULE UEngineCore::ContentsDLL = nullptr;
std::shared_ptr<IContentsCore> UEngineCore::Core;
UEngineInitData UEngineCore::Data;
UEngineTimer UEngineCore::Timer;


std::shared_ptr<class ULevel> UEngineCore::NextLevel;
std::shared_ptr<class ULevel> UEngineCore::CurLevel = nullptr;

std::map<std::string, std::shared_ptr<class ULevel>> UEngineCore::LevelMap;

FVector UEngineCore::GetScreenScale()
{
	return Data.WindowSize;
}

UEngineCore::UEngineCore()
{
}

UEngineCore::~UEngineCore()
{
}

void UEngineCore::WindowInit(HINSTANCE _Instance)
{
	UEngineWindow::EngineWindowInit(_Instance);
	MainWindow.Open("MainWindow");
}

void UEngineCore::LoadContents(std::string_view _DllName)
{
	UEngineDirectory Dir;

	Dir.MoveParentToDirectory("Build");
	Dir.Move("bin/x64");

	// ���� ��Ȳ�� ���� ��� ����
#ifdef _DEBUG
	Dir.Move("Debug");
#else
	Dir.Move("Release");
#endif

	UEngineFile File = Dir.GetFile(_DllName);

	std::string FullPath = File.GetPathToString();
	// ��Ģ�� ������ۿ� ����.
	ContentsDLL = LoadLibraryA(FullPath.c_str());

	if (nullptr == ContentsDLL)
	{
		MSGASSERT("������ ����� �ε��Ҽ��� �����ϴ�.");
		return;
	}

	INT_PTR(__stdcall * Ptr)(std::shared_ptr<IContentsCore>&) = (INT_PTR(__stdcall*)(std::shared_ptr<IContentsCore>&))GetProcAddress(ContentsDLL, "CreateContentsCore");

	if (nullptr == Ptr)
	{
		MSGASSERT("������ �ھ� ���ο� CreateContentsCoreDefine�� �������� �ʾҽ��ϴ�.");
		return;
	}

	Ptr(Core);

	if (nullptr == Core)
	{
		MSGASSERT("������ �ھ� ������ �����߽��ϴ�.");
		return;
	}
}

void UEngineCore::EngineStart(HINSTANCE _Instance, std::string_view _DllName)
{
	UEngineDebug::LeakCheck();

	WindowInit(_Instance);

	LoadContents(_DllName);

	// ������ʹ� �����մϴ�.
	UEngineWindow::WindowMessageLoop(
		[]()
		{
			// ��򰡿��� �̰� ȣ���ϸ� �ܼ�â�� �߰� �� �ڷδ� std::cout �ϸ� �� �ܼ�â�� �޼����� ��̴ϴ�.
			// UEngineDebug::StartConsole();
			// ���� ����̽� �����
			Device.CreateDeviceAndContext();
			// �ε��ϰ�
			Core->EngineStart(Data);
			// ������ �����Ҽ� �ִ�.
			MainWindow.SetWindowPosAndScale(Data.WindowPos, Data.WindowSize);
			Device.CreateBackBuffer(MainWindow);
			// ����̽��� ��������� ������ ���ҽ� �ε嵵 �Ҽ��� ����.
			// ������� ���ҽ� �ε尡 �����ϴ�.

			UEngineGUI::Init();
		},
		[]()
		{
			EngineFrame();
			// ������ ���ư��� �ϰ� ������
		},
		[]()
		{
			// static���� ���ڰ� �߽��ϴ�.
			// �̶� ������ �� delete�� �Ǿ�� �Ѵ�.
			// ���۷��� ī��Ʈ�� �����Ǹ� �� ���۷��� ī��Ʈ�� ���� ���� �־��.
			EngineEnd();
		});


	// ���� ������ ���۵Ǿ���.
	// ������â�� ������ �˾Ƽ� ������ �ϰ�.

	// Window ������ �Ѵ�.


}

// ��� ��ȯ ������ ���� ���� �Լ��и�
std::shared_ptr<ULevel> UEngineCore::NewLevelCreate(std::string_view _Name)
{
	// ����⸸ �ϰ� ������ ���ϸ� �� �׳� �������ϴ�. <= 

	// ����� �ʿ� �־ ���۷��� ī��Ʈ�� ������ŵ�ϴ�.
	// UObject�� ����̾����ϴ�.
	std::shared_ptr<ULevel> Ptr = std::make_shared<ULevel>();
	Ptr->SetName(_Name);

	LevelMap.insert({ _Name.data(), Ptr });

	std::cout << "NewLevelCreate" << std::endl;

	return Ptr;
}

void UEngineCore::OpenLevel(std::string_view _Name)
{
	if (false == LevelMap.contains(_Name.data()))
	{
		MSGASSERT("������ ���� ������ �����Ϸ��� �߽��ϴ�." + std::string(_Name));
		return;
	}


	NextLevel = LevelMap[_Name.data()];
}

void UEngineCore::EngineFrame()
{
	if (nullptr != NextLevel)
	{
		if (nullptr != CurLevel)
		{
			CurLevel->LevelChangeEnd();
		}

		CurLevel = NextLevel;

		CurLevel->LevelChangeStart();
		NextLevel = nullptr;
		Timer.TimeStart();
	}

	Timer.TimeCheck();
	float DeltaTime = Timer.GetDeltaTime();

	CurLevel->Tick(DeltaTime);
	CurLevel->Render(DeltaTime);
	// GUI�������� ���� �������� �� ������ ���ִ°� ����.

}

void UEngineCore::EngineEnd()
{

	UEngineGUI::Release();

	// ���ҽ� ������ ���⼭ �Ұ̴ϴ�.
	Device.Release();

	UEngineResources::Release();

	CurLevel = nullptr;
	NextLevel = nullptr;
	LevelMap.clear();



}