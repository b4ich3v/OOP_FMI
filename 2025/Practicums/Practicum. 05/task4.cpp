#include <iostream>
#include <fstream>
#include <cstring>

namespace HELPERS 
{

	const int MAX_SIZE_NAME = 15;
	const int MAX_SIZE_BANK_CODE = 30;

}

class BankAccount
{
private:

	char name[HELPERS::MAX_SIZE_NAME + 1] = "";
	char code[HELPERS::MAX_SIZE_BANK_CODE + 1] = "";
	double availableMoney = 0;

	void setName(const char* name) 
	{

		if (name == nullptr) return;

		strncpy(this->name, name, strlen(name));
		this->name[strlen(name)] = '\0';

	}

	void setCode(const char* code)
	{

		if (code == nullptr) return;

		strncpy(this->code, code, strlen(code));
		this->code[strlen(code)] = '\0';

	}

	void setAvailableMoney(double availableMoney) 
	{

		if (availableMoney < 0) return;

		this->availableMoney = availableMoney;

	}

public:

	BankAccount() = default;

	BankAccount(const char* name, const char* code, double availableMoney) 
	{

		setName(name);
		setCode(code);
		setAvailableMoney(availableMoney);

	}

	BankAccount(const char* name, const char* code)
	{

		setName(name);
		setCode(code);
		setAvailableMoney(0);

	}

	double draw(double money)
	{

		if (money > availableMoney) return 0;

		availableMoney -= money;
		return money;

	}

	void deposit(double money)
	{

		if (money < 0) return;
		availableMoney += money;

	}

	void print(std::ostream& os) const
	{

		os << name << " ";
		os << code << " ";
		os << availableMoney << std::endl;

	}

};

int main()
{

	BankAccount b1("Yoan Baychev", "1234", 3200);
	BankAccount b2("Ivailo Kunchev", "0000");
	BankAccount b3;

	b2.deposit(1000);
	b1.draw(200);

	b1.print(std::cout);
	b2.print(std::cout);
	b3.print(std::cout);

	return 0;

}
