#include "Manager.h"
#include "Engineer.h"
#pragma once

class TechManager: public Manager, public Engineer 
{
public:

	TechManager(const MyString& name, const MyString& projectName, const MyString& techSpecialization);

	void printInfo() const override;

	void assignTask(const MyString& task) const;

};

