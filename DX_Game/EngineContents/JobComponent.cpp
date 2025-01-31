#include "PreCompile.h"
#include "JobComponent.h"

#include "LeftKey.h"
#include "RightKey.h"
#include "DownKey.h"
#include "UpKey.h"



UJobComponent::UJobComponent() 
{
	{
		APlayerFunction* DirFunc = GetWorld()->SpawnActor<ALeftKey>().get();
		DirFunc->SetOwner(GetActor());
		DirFunc->SetActiveFalse();
		DirFuncMap.insert(std::make_pair(EPlayer_Function::Left, DirFunc));
	}
	{
		APlayerFunction* DirFunc = GetWorld()->SpawnActor<ARightKey>().get();
		DirFunc->SetOwner(GetActor());
		DirFunc->SetActiveFalse();
		DirFuncMap.insert(std::make_pair(EPlayer_Function::Left, DirFunc));
	}
	{
		APlayerFunction* DirFunc = GetWorld()->SpawnActor<AUpKey>().get();
		DirFunc->SetOwner(GetActor());
		DirFunc->SetActiveFalse();
		DirFuncMap.insert(std::make_pair(EPlayer_Function::Left, DirFunc));
	}
	{
		APlayerFunction* DirFunc = GetWorld()->SpawnActor<ADownKey>().get();
		DirFunc->SetOwner(GetActor());
		DirFunc->SetActiveFalse();
		DirFuncMap.insert(std::make_pair(EPlayer_Function::Left, DirFunc));
	}

}

UJobComponent::~UJobComponent() 
{

}

void UJobComponent::BeginPlay()
{
	UActorComponent::BeginPlay();

	
}
