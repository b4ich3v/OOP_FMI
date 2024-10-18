#pragma once
#include "StringView.h"
#include "MyString.h"

class FilePath
{
	StringView name;
	StringView extension;

public:
	FilePath(const MyString& fileName);

	const StringView& getName() const;
	const StringView& getExtension() const;
};
