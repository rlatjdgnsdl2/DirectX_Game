#pragma once
#include <string>

// 설명 : 문자열에 도움주는 헬퍼 클래스
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

	//	문자열 대문자변환함수
	static std::string ToUpper(std::string_view);

	//	ANSI -> 유니코드 변환 함수
	ENGINEAPI static std::wstring AnsiToUnicode(std::string_view _Name);

private:
	UEngineString();
};

