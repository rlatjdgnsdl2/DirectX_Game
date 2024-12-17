#include "PreCompile.h"
#include "ContentsCore.h"

#include "TempGameMode.h"
#include "TempPawn.h"



CreateContentsCoreDefine(UContentsCore);
//STDAPI_(__declspec(dllexport) INT_PTR) CreateContentsCore(std::shared_ptr<IContentsCore>& _Test)
//{ 
//	_Test = std::make_shared<UContentsCore>();
//	if (nullptr == _Test) 
//	{ 
//		MSGASSERT("컨텐츠 모듈 생성에 실패했습니다."); 
//	} 
//	return 0; 
//}

UContentsCore::UContentsCore()
{
}

UContentsCore::~UContentsCore()
{
}

void UContentsCore::EngineStart(UEngineInitData& _Data)
{
	_Data.WindowPos = { 100, 100 };
	_Data.WindowSize = { 300, 300 };
	UEngineCore::CreateLevel<TempGameMode, TempPawn>("TempLevel");
	UEngineCore::OpenLevel("TempLevel");
}

void UContentsCore::EngineTick(float _DeltaTime)
{

}

void UContentsCore::EngineEnd()
{

}