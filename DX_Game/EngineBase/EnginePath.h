#pragma once
#include <filesystem>

// Ό³Έν :
class UEnginePath
{
public:
	// constrcuter destructer
	ENGINEAPI UEnginePath();
	ENGINEAPI UEnginePath(std::string_view _Path);
	ENGINEAPI UEnginePath(std::filesystem::path _Path);
	ENGINEAPI virtual ~UEnginePath();

	ENGINEAPI bool IsExists();
	ENGINEAPI void MoveParent();

	ENGINEAPI std::string GetPathToString();

	ENGINEAPI std::string GetFileName();

	ENGINEAPI std::string GetDirectoryName();

	ENGINEAPI std::string GetExtension();


	ENGINEAPI bool MoveParentToDirectory(std::string_view _Path);

	ENGINEAPI bool Move(std::string_view _Path);

	ENGINEAPI bool IsDirectory();

	ENGINEAPI bool IsFile();

	ENGINEAPI void Append(std::string_view _AppendName);
	ENGINEAPI void BackDir();


protected:
	std::filesystem::path Path;

private:
};

