#pragma once
#include <string>
#include "EngineDefine.h"

// ���� : ���ڿ��� ���õ� static �Լ�
class UEngineString
{
public:
	// constrcuter destructer
	~UEngineString();

	// delete Function
	UEngineString(const UEngineString& _Other) = delete;
	UEngineString(UEngineString&& _Other) noexcept = delete;
	UEngineString& operator=(const UEngineString& _Other) = delete;
	UEngineString& operator=(UEngineString&& _Other) noexcept = delete;

	ENGINEAPI static std::string ToUpper(std::string_view);
	ENGINEAPI static std::wstring AnsiToUnicode(std::string_view _Name);
	ENGINEAPI static std::string InterString(const std::string& _Text, std::string_view _Start, std::string_view _End, size_t& _Offset);

private:
	UEngineString();
};

