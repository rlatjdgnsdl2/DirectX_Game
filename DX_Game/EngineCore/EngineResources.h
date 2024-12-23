#pragma once
#include <EngineBase/Object.h>
#include <EngineBase/EnginePath.h>
#include <EngineBase/EngineString.h>

// �̷��� ���ø� Ŭ������ �ƿ� ������� �� �����ع����°� �� �����Ҽ� �ִ�.
template<typename ResType>
class UEngineResources : public UObject
{
public:
	// constrcuter destructer
	UEngineResources() {

	}
	~UEngineResources() {

	}

	// delete Function
	UEngineResources(const UEngineResources& _Other) = delete;
	UEngineResources(UEngineResources&& _Other) noexcept = delete;
	UEngineResources& operator=(const UEngineResources& _Other) = delete;
	UEngineResources& operator=(UEngineResources&& _Other) noexcept = delete;

	static std::string ToUpperName(std::string_view _Name)
	{
		return UEngineString::ToUpper(_Name);
	}

	static std::shared_ptr<ResType> Find(std::string_view _Name)
	{
		void* Ptr = &ResMap;

		if (false == ResMap.contains(_Name.data()))
		{
			return nullptr;
		}

		return ResMap[_Name.data()];
	}

	static bool Contains(std::string_view _Name)
	{
		return ResMap.contains(_Name.data());
	}

	static void Release()
	{
		ResMap.clear();
	}

	ENGINEAPI static std::shared_ptr<ResType> MakeRes(std::string_view _Name, std::string_view _Path)
	{
		std::string UpperName = UEngineString::ToUpper(_Name);

		std::shared_ptr<ResType> NewRes = std::make_shared<ResType>();
		NewRes->SetName(UpperName);
		NewRes->Path = _Path;
		ResMap.insert({ UpperName, NewRes });

		void* Ptr = &ResMap;

		return NewRes;
	}

protected:
	UEnginePath Path;

private:

	// dll �޸� �и���Ȳ�� ���� �ذ�å
	// ��������� => �ڷᱸ������ �޸� �Ҵ��Ҷ� �� �޸𸮸� ��� �Ҵ��Ұž߸� 
	// �޸�Ǯ�̳� �̷��͵��� ���� �ڽ��� �躸�� ����� �� ū ��Ȳ�� �ȴ�.
	// std::vector<int, ���������>

	inline static std::map<std::string, std::shared_ptr<ResType>> ResMap;
};

// ���ø� static �ʱ�ȭ ���
//template<typename ResType>
//std::map<std::string, std::shared_ptr<ResType>> UEngineResources<ResType>::ResMap;


