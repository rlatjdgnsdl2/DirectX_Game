#pragma once
#include <EngineBase/Object.h>

// ���� :
class UEngineGUIWindow : public UObject
{
	friend class UEngineGUI;

public:
	// constrcuter destructer
	ENGINEAPI UEngineGUIWindow();
	ENGINEAPI ~UEngineGUIWindow();

	// delete Function
	UEngineGUIWindow(const UEngineGUIWindow& _Other) = delete;
	UEngineGUIWindow(UEngineGUIWindow&& _Other) noexcept = delete;
	UEngineGUIWindow& operator=(const UEngineGUIWindow& _Other) = delete;
	UEngineGUIWindow& operator=(UEngineGUIWindow&& _Other) noexcept = delete;

	virtual void BeginPlay() {}
	virtual void OnGUI() = 0;


	template<typename Type>
	Type* GetGameInstance()
	{
		return dynamic_cast<Type*>(GetGameInstance());
	}

	ENGINEAPI class UGameInstance* GetGameInstance();


	ULevel* GetWorld()
	{
		return World;
	}

protected:

private:
	ULevel* World;

};

