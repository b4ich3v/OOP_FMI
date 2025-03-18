#include <iostream>
#include <fstream>
#include <cstring>

namespace HELPERS 
{

	const int MAX_SIZE_NAME = 15;
	const int MAX_SIZE_BANK_CODE = 30;
	const int MAX_SIZE_BUFFER = 1024;

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

	void read(std::istream& is) 
	{

		is >> name;
		is >> code;
		is >> availableMoney;
		is.ignore();

	}

	const char* getName() const 
	{

		return name;

	}

	const char* getCode() const 
	{

		return code;

	}

	double getAvailableMoney() const 
	{

		return availableMoney;

	}

};

class Bank
{
private:

	BankAccount* accounts = nullptr;
	int countOfAccounts = 0;
	int capacity = 8;

	void resize(int newCapacity) 
	{

		if (newCapacity <= capacity) return;

		BankAccount* newAccounts = new BankAccount[newCapacity];

		for (int i = 0; i < countOfAccounts; i++)
		{

			newAccounts[i] = accounts[i];

		}

		delete[] accounts;
		accounts = newAccounts;
		capacity = newCapacity;

	}

	void free() 
	{

		delete[] accounts;
		accounts = nullptr;
		countOfAccounts = 0;
		capacity = 8;

	}

public:

	Bank() 
	{

		countOfAccounts = 0;
		capacity = 8;
		accounts = new BankAccount[capacity];

	}

	Bank(std::ifstream& file) 
	{

		capacity = 8; 
		accounts = new BankAccount[capacity];

		file >> countOfAccounts;
		file.ignore(1);

		if (countOfAccounts > capacity) resize(capacity * 2);

		for (int i = 0; i < countOfAccounts; i++)
		{

			accounts[i].read(file);

		}

		file.close();

	}

	~Bank() 
	{

		free();

	}

	Bank(const Bank& other) = delete;

	Bank& operator = (const Bank& other) = delete;

	void saveInfo(std::ostream& os) 
	{

		os << countOfAccounts;
		os << std::endl;

		for (int i = 0; i < countOfAccounts; i++)
		{

			accounts[i].print(os);

		}

	}

	bool checkIfAlreadyHas(const BankAccount& acc) const 
	{

		for (int i = 0; i < countOfAccounts; i++)
		{

			if(!strcmp(accounts[i].getName(), acc.getName()) &&
				!strcmp(accounts[i].getCode(), acc.getCode())) 
			{

				return true;

			}

		}

		return false;

	}

	void print(std::ostream& os) const
	{

		for (int i = 0; i < countOfAccounts; i++)
		{

			accounts[i].print(os);

		}

		os << std::endl;

	}

	void addBankAccount(const BankAccount& acc) 
	{

		if (countOfAccounts == capacity) resize(capacity * 2);
		if (checkIfAlreadyHas(acc)) return;

		accounts[countOfAccounts] = acc;
		countOfAccounts += 1;

	}

	void removeBankAccount(const char* code) 
	{

		if (code == nullptr) return;

		for (int i = 0; i < countOfAccounts; i++)
		{

			if (!strcmp(accounts[i].getCode(), code)) 
			{

				std::swap(accounts[i], accounts[countOfAccounts - 1]);
				countOfAccounts -= 1;
				break;

			}

		}

	}

	double getAvailableMoneyByCode(const char* code)
	{

		if (code == nullptr) return 0;

		for (int i = 0; i < countOfAccounts; i++)
		{

			if (!strcmp(accounts[i].getCode(), code)) 
			{

				return accounts[i].getAvailableMoney();

			}

		}

		return 0;
		
	}

	double getAvailableMoneyByNameForAllAcc(const char* name)
	{

		if (name == nullptr) return 0;

		double result = 0;

		for (int i = 0; i < countOfAccounts; i++)
		{

			if (!strcmp(accounts[i].getName(), name))
			{

				result += accounts[i].getAvailableMoney();

			}

		}

		return result;
	}

};

int main()
{

	BankAccount b1("Yoan_Baychev", "1234", 3200);
	BankAccount b2("Ivailo_Kunchev", "0000");
	BankAccount b3("Ilian_Zaprqnov", "3333", 3000);
	BankAccount b4("Kaloyan_Markov", "7891", 2670);

	b2.deposit(1000);
	b1.draw(200);

	b1.print(std::cout);
	b2.print(std::cout);
	b3.print(std::cout);
	b4.print(std::cout);

	std::ofstream file1("../test.txt");

	file1 << 4;
	file1 << std::endl;

	b1.print(file1);
	b2.print(file1);
	b3.print(file1);
	b4.print(file1);

	file1.close();
	std::cout << std::endl;

	std::ifstream file2("../test.txt");

	Bank bank(file2);
	bank.print(std::cout);

	BankAccount b5("HACKER", "7777");
	BankAccount b6("Yoan_Baychev", "1312", 100);

	bank.addBankAccount(b5);
	bank.addBankAccount(b6);
	bank.addBankAccount(b1);
	bank.removeBankAccount("0000");
	bank.print(std::cout);

	std::cout << bank.getAvailableMoneyByNameForAllAcc("Yoan_Baychev") << std::endl;
	std::cout << bank.getAvailableMoneyByCode("3333") << std::endl;

	std::ofstream file3("../result.txt");
	bank.saveInfo(file3);
	file3.close();

	return 0;

}
