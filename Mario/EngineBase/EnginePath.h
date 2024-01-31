#pragma once
#include <string>
#include <filesystem> 

// Ό³Έν : 
class UEnginePath
{
public:
	// constrcuter destructer
	UEnginePath();
	UEnginePath(std::filesystem::path _Path);
	~UEnginePath();

	bool IsFile();
	bool IsDirectory();

	bool IsExists();

	std::string GetFileName();
	std::string GetExtension();

	void MoveParent();
	void Move(std::string_view _Path);

	std::string GetFullPath()
	{
		return Path.string();
	}

protected:
	std::filesystem::path Path;

private:
};

