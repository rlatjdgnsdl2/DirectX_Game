#pragma once
#include <EngineBase/Object.h>
#include <EngineBase/EnginePath.h>
#include <EngineBase/EngineString.h>



class UEngineResources : public UObject
{
public:
	// constrcuter destructer
	ENGINEAPI UEngineResources() {

	}
	ENGINEAPI virtual ~UEngineResources() {

	}

	// delete Function
	UEngineResources(const UEngineResources& _Other) = delete;
	UEngineResources(UEngineResources&& _Other) noexcept = delete;
	UEngineResources& operator=(const UEngineResources& _Other) = delete;
	UEngineResources& operator=(UEngineResources&& _Other) noexcept = delete;

	ENGINEAPI static std::string ToUpperName(std::string_view _Name)
	{
		return UEngineString::ToUpper(_Name);
	}

	template<typename ResType>
	ENGINEAPI static std::shared_ptr<ResType> Find(std::string_view _Name)
	{
		const type_info& Info = typeid(ResType);
		return std::dynamic_pointer_cast<ResType>(Find(Info.name(), _Name.data()));
	}

	ENGINEAPI static std::shared_ptr<UEngineResources> Find(std::string_view _ResName, std::string_view _Name);

	ENGINEAPI static bool Contains(std::string_view _Name)
	{
		return ResMap.contains(_Name.data());
	}

	ENGINEAPI static void Release()
	{
		ResMap.clear();
	}

	template<typename ResType>
	ENGINEAPI static void PushRes(std::string_view _Name, std::string_view _Path, std::shared_ptr<UEngineResources> _Res)
	{
		const type_info& Info = typeid(ResType);
		PushRes(Info.name(), _Name, _Path, _Res);
	}
	ENGINEAPI static void PushRes(const std::string_view _Info, std::string_view _Name, std::string_view _Path, std::shared_ptr<UEngineResources> _Res);





	ENGINEAPI UEnginePath GetPath()
	{
		return Path;
	}

protected:
	UEnginePath Path;

private:
	ENGINEAPI static inline std::map<std::string, std::map<std::string, std::shared_ptr<UEngineResources>>> ResMap;
};


