#pragma once
#include <string>
#include <filesystem> 

// ���� : 
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

	std::string GetFileName() const;
	std::string GetExtension() const;

	bool IsRoot();

	void MoveParent();
	void Move(std::string_view _Path);

	std::string AppendPath(std::string_view _Path);

	std::string GetFullPath() const
	{
		return Path.string();
	}

protected:
	std::filesystem::path Path;

private:
};

