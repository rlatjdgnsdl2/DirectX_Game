#include "PreCompile.h"
#include "EngineResources.h"
#include "EngineTexture.h"
#include <mutex>


// EngineCoreDll�� �����Դϴ�.

std::mutex ResCritical_Section;

std::shared_ptr<UEngineResources> UEngineResources::Find(std::string_view _ResName, std::string_view _Name)
{
	std::string UpperString = UEngineString::ToUpper(_Name);

	if (false == ResMap[_ResName.data()].contains(UpperString))
	{
		return nullptr;
	}

	return ResMap[_ResName.data()][UpperString];
}

void UEngineResources::PushRes(std::shared_ptr<UEngineResources> _Res, const std::string_view _Info, std::string_view _Name, std::string_view _Path)
{
	std::string UpperName = UEngineString::ToUpper(_Name);
	//       �ؽ�ó��                  Player.png�� ����ִ��� Ȯ��.
	if (true == ResMap[_Info.data()].contains(UpperName))
	{
		MSGASSERT("�̹� �ε��� ���ҽ��� �� �ε� �Ϸ��� �߽��ϴ�" + std::string(_Info.data()) + "  " + _Name.data());
		return;
	}

	// �̰� ȣ���� ���� �������� ������ �ȴ�.

	_Res->SetName(UpperName);
	_Res->Path = _Path;

	// ���⿡�ٰ� �׳� ����ȭ�� �ɸ� �˴ϴ�.
	ResMap[_Info.data()].insert({ UpperName, _Res });

	return;
}

void UEngineResources::ThreadSafePushRes(std::shared_ptr<UEngineResources> _Res, const std::string_view _Info, std::string_view _Name, std::string_view _Path)
{
	std::string UpperName = UEngineString::ToUpper(_Name);
	_Res->SetName(UpperName);
	_Res->Path = _Path;


	{
		// �������� �����尡 �����Ҷ�
		// �̰� 3�� �޶����ŷ� ��� ������ ���̴�. 
		// ���� ����Ҽ� �ִ°� �� 1���� ������ ���̴�.
		std::lock_guard<std::mutex> Lock(ResCritical_Section);

		// ResMap <= �Ӱ迵���̶�� �����ϴ� ���̴�.

		//       �ؽ�ó��                  Player.png�� ����ִ��� Ȯ��.
		if (true == ResMap[_Info.data()].contains(UpperName))
		{
			MSGASSERT("�̹� �ε��� ���ҽ��� �� �ε� �Ϸ��� �߽��ϴ�" + std::string(_Info.data()) + "  " + _Name.data());
			return;
		}

		// �̰� ȣ���� ���� �������� ������ �ȴ�.
		// ResCritical_Section.lock();
		ResMap[_Info.data()].insert({ UpperName, _Res });
		// ResCritical_Section.unlock();
	}
	return;
}
