#pragma once
#include "EnginePath.h"

// Ό³Έν : 
class UEngineFile;
class UEngineDirectory;

class UEngineDirectory : public UEnginePath
{
public:
	ENGINEAPI UEngineDirectory();
	ENGINEAPI UEngineDirectory(std::string_view _Path);
	ENGINEAPI UEngineDirectory(std::filesystem::path _Path);
	ENGINEAPI ~UEngineDirectory();

	ENGINEAPI UEngineFile GetFile(std::string_view _FileName);
	ENGINEAPI std::vector<UEngineFile> GetAllFile(bool _IsRecursive = true);
	ENGINEAPI std::vector<UEngineDirectory> GetAllDirectory();

protected:

private:
	void GetAllFileRecursive(std::filesystem::path _Path, std::vector<UEngineFile>& _Result);
};

