#pragma once
#include <filesystem>
#include "EngineDefine.h"

// 설명 :
class UEnginePath
{
public:
	ENGINEAPI UEnginePath();
	ENGINEAPI UEnginePath(std::string_view _Path);
	ENGINEAPI UEnginePath(std::filesystem::path _Path);
	ENGINEAPI virtual ~UEnginePath();


	bool IsExists();
	void MoveParent();

	ENGINEAPI std::string GetPathToString();

	// 파일명 + 확장자 포함
	std::string GetFileName();

	// 파일명 + 확장자 포함
	std::string GetDirectoryName();

	// 확장자
	std::string GetExtension();


	ENGINEAPI bool MoveParentToDirectory(std::string_view _Path);

	ENGINEAPI bool Move(std::string_view _Path);

	bool IsDirectory();

	bool IsFile();

	void Append(std::string_view _AppendName);


protected:
	std::filesystem::path Path;

private:
};

