#pragma once
#include "EnginePath.h"
#include "EngineSerializer.h"

enum class IOOpenMode
{
	Write,
	Read,
};

enum class IODataType
{
	Binary,
	Text,
};


// Ό³Έν :
class UEngineFile : public UEnginePath
{
public:
	// constrcuter destructer
	UEngineFile();
	UEngineFile(std::filesystem::path _Path);
	~UEngineFile();

	// delete Function
	//UEngineFile(const UEngineFile& _Other) = delete;
	//UEngineFile(UEngineFile&& _Other) noexcept = delete;
	//UEngineFile& operator=(const UEngineFile& _Other) = delete;
	//UEngineFile& operator=(UEngineFile&& _Other) noexcept = delete;

	void Open(IOOpenMode _OpenType, IODataType _DataType);
	void Save(UEngineSerializer& _Data);
	void Close();

protected:

private:
	FILE* FileHandle = nullptr;
};

