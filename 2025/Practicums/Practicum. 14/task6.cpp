#include <iostream>
#include <fstream>

namespace HELPERS
{

	static constexpr uint32_t COUNT_OF_BITS = 32;

	static constexpr size_t MAX_DATA_INFO_SIZE = 100;

	static void reverseKBits(uint32_t& number, int K)
	{

		uint32_t mult1 = (1 << K) - 1;
		uint32_t mult2 = ((1 << K) - 1) << (HELPERS::COUNT_OF_BITS - K);

		uint32_t leftKBits = (number & mult2) >> (HELPERS::COUNT_OF_BITS - K);
		uint32_t rightKBits = (number & mult1) << (HELPERS::COUNT_OF_BITS - K);

		number &= ~mult1;
		number &= ~mult2;

		number |= leftKBits;
		number |= rightKBits;

	}

	static void flipKBits(uint32_t& number, int M)
	{

		for (int i = 0; i < M; i++)
		{

			if ((1 << i) & number) number &= ~(1 << i);
			else number |= (1 << i);

		}

	}

	static size_t getFileSize(std::ifstream& file)
	{

		size_t currentPos = file.tellg();
		file.seekg(0, std::ios::end);
		size_t result = file.tellg();

		file.clear();
		file.seekg(currentPos, std::ios::beg);

		return result;

	}

}

enum class FunctionType
{

	ShiftLeftFunction,
	XorFunction,
	ReverseBitsFunction,
	FlipBitsFunction,
	ReverseFlipBits

};

class Uint
{
public:

	virtual uint32_t operator ()(uint32_t number) const = 0;

	virtual void deserialize(const char* fileName) = 0;

	virtual void serialize(const char* fileName) const = 0;

	virtual Uint* clone() const = 0;

	virtual ~Uint() = default;

};

class ShiftLeftFunction : public Uint
{
private:

	uint32_t N = 0;

public:

	ShiftLeftFunction(uint32_t N) : Uint(), N(N) {}

	uint32_t operator ()(uint32_t number) const override
	{

		number <<= N;
		return number;

	}

	void deserialize(const char* fileName) override
	{

		if (!fileName) return;

		std::ifstream file(fileName, std::ios::binary);
		if (!file.is_open()) return;

		int type = 0;
		file.read((char*)&type, sizeof(FunctionType) * sizeof(char));
		file.read((char*)&N, sizeof(uint32_t) * sizeof(char));
		file.close();

	}

	void serialize(const char* fileName) const override
	{

		if (!fileName) return;

		std::ofstream file(fileName, std::ios::binary);
		if (!file.is_open()) return;

		int type = (int)FunctionType::ShiftLeftFunction;
		file.write((const char*)&type, sizeof(FunctionType) * sizeof(char));
		file.write((const char*)&N, sizeof(uint32_t) * sizeof(char));
		file.close();

	}

	Uint* clone() const override
	{

		return new ShiftLeftFunction(*this);

	}

};

class XorFunction: public Uint
{
private:

	uint32_t* data = nullptr;
	size_t size = 0;

	void free()
	{

		delete[] data;
		data = nullptr;
		size = 0;

	}

	void copyFrom(const XorFunction& other)
	{

		data = new uint32_t[other.size];
		size = other.size;

		for (int i = 0; i < size; i++)
		{

			data[i] = other.data[i];

		}

	}

	void moveTo(XorFunction&& other)
	{

		data = other.data;
		size = other.size;

		other.data = nullptr;
		other.size = 0;

	}

public:

	XorFunction(const uint32_t* data, size_t size) : Uint()
	{

		if (!data || size <= 0) throw std::logic_error("Error");

		this->data = new uint32_t[size];
		this->size = size;

		for (int i = 0; i < size; i++)
		{

			this->data[i] = data[i];

		}

	}

	XorFunction(const XorFunction& other)
	{

		copyFrom(other);

	}

	XorFunction(XorFunction&& other) noexcept
	{

		moveTo(std::move(other));

	}

	XorFunction& operator = (const XorFunction& other)
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	XorFunction& operator = (XorFunction&& other) noexcept
	{

		if (this != &other)
		{

			free();
			moveTo(std::move(other));

		}

		return *this;

	}

	~XorFunction()
	{

		free();

	}

	uint32_t operator ()(uint32_t number) const override
	{

		for (int i = 0; i < size; i++)
		{

			number ^= data[i];

		}

		return number;

	}

	void deserialize(const char* fileName) override
	{

		if (!fileName) return;

		std::ifstream file(fileName, std::ios::binary);
		if (!file.is_open()) return;

		int type = 0;
		file.read((char*)&type, sizeof(FunctionType) * sizeof(char));
		file.read((char*)&size, sizeof(size_t) * sizeof(char));
		data = new uint32_t[size];
		file.read((char*)data, size * sizeof(uint32_t));
		delete[] data;
		file.close();

	}

	void serialize(const char* fileName) const override
	{

		if (!fileName) return;

		std::ofstream file(fileName, std::ios::binary);
		if (!file.is_open()) return;

		int type = (int)FunctionType::XorFunction;
		file.write((const char*)&type, sizeof(FunctionType) * sizeof(char));
		file.write((const char*)&size, sizeof(uint32_t) * sizeof(char));
		file.write((const char*)data, size * sizeof(uint32_t));
		file.close();

	}

	Uint* clone() const override
	{

		return new XorFunction(*this);

	}

};

class ReverseBitsFunction : virtual public Uint
{
protected:

	uint32_t K = 0;

public:

	ReverseBitsFunction(uint32_t K) : Uint(), K(K) {}

	uint32_t operator ()(uint32_t number) const override
	{

		HELPERS::reverseKBits(number, K);
		return number;

	}

	void deserialize(const char* fileName) override
	{

		if (!fileName) return;

		std::ifstream file(fileName, std::ios::binary);
		if (!file.is_open()) return;

		int type = 0;
		file.read((char*)&type, sizeof(FunctionType) * sizeof(char));
		file.read((char*)&K, sizeof(uint32_t) * sizeof(char));
		file.close();

	}

	void serialize(const char* fileName) const override
	{

		if (!fileName) return;

		std::ofstream file(fileName, std::ios::binary);
		if (!file.is_open()) return;

		int type = (int)FunctionType::ReverseBitsFunction;
		file.write((const char*)&type, sizeof(FunctionType) * sizeof(char));
		file.write((const char*)&K, sizeof(uint32_t) * sizeof(char));
		file.close();

	}

	Uint* clone() const override
	{

		return new ReverseBitsFunction(*this);

	}

};

class FlipBitsFunction : virtual public Uint
{
protected:

	uint32_t M = 0;

public:

	FlipBitsFunction(uint32_t M) : Uint(), M(M) {}

	uint32_t operator ()(uint32_t number) const override
	{

		HELPERS::flipKBits(number, M);
		return number;

	}

	void deserialize(const char* fileName) override
	{

		if (!fileName) return;

		std::ifstream file(fileName, std::ios::binary);
		if (!file.is_open()) return;

		int type = 0;
		file.read((char*)&type, sizeof(FunctionType) * sizeof(char));
		file.read((char*)&M, sizeof(uint32_t) * sizeof(char));
		file.close();

	}

	void serialize(const char* fileName) const override
	{

		if (!fileName) return;

		std::ofstream file(fileName, std::ios::binary);
		if (!file.is_open()) return;

		int type = (int)FunctionType::FlipBitsFunction;
		file.write((const char*)&type, sizeof(FunctionType) * sizeof(char));
		file.write((const char*)&M, sizeof(uint32_t) * sizeof(char));
		file.close();

	}

	Uint* clone() const override
	{

		return new FlipBitsFunction(*this);

	}

};

class ReverseFlipBits : public ReverseBitsFunction, public FlipBitsFunction
{
public:

	ReverseFlipBits(uint32_t K, uint32_t M) : Uint(), ReverseBitsFunction(K), FlipBitsFunction(M) {}

	uint32_t operator ()(uint32_t number) const override
	{

		HELPERS::reverseKBits(number, K);
		HELPERS::flipKBits(number, M);
		return number;

	}

	void deserialize(const char* fileName) override
	{

		std::ifstream file(fileName, std::ios::binary);
		int type = 0;
		file.read((char*)&type, sizeof(FunctionType) * sizeof(char));
		file.close();

		ReverseBitsFunction::deserialize(fileName);
		FlipBitsFunction::deserialize(fileName);

	}

	void serialize(const char* fileName) const override
	{

		std::ofstream file(fileName, std::ios::binary);
		int type = (int)FunctionType::ReverseFlipBits;
		file.write((const char*)&type, sizeof(FunctionType) * sizeof(char));
		file.close();

		ReverseBitsFunction::serialize(fileName);
		FlipBitsFunction::serialize(fileName);

	}

	Uint* clone() const override
	{

		return new ReverseFlipBits(*this);

	}

};

template <class T>

class PolyContainer
{
private:

	T** data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void free()
	{

		for (int i = 0; i < capacity; i++)
		{

			if (data[i] == nullptr) continue;

			delete data[i];
			data[i] = nullptr;

		}

		delete[] data;
		data = nullptr;
		size = capacity = 0;

	}

	void copyFrom(const PolyContainer& other)
	{

		data = new T * [other.capacity] {nullptr};
		size = other.size;
		capacity = other.capacity;

		for (int i = 0; i < capacity; i++)
		{

			if (other.data[i] == nullptr) continue;

			data[i] = other.data[i]->clone();

		}

	}

	void moveTo(PolyContainer&& other)
	{

		data = other.data;
		size = other.size;
		capacity = other.capacity;

		other.data = nullptr;
		other.size = 0;
		other.capacity = 0;

	}

	void resize(size_t newCapacity)
	{

		if (newCapacity <= capacity) return;

		T** newData = new T * [newCapacity] {nullptr};

		for (int i = 0; i < capacity; i++)
		{

			newData[i] = data[i];
			data[i] = nullptr;

		}

		delete[] data;
		data = newData;
		capacity = newCapacity;

	}

public:

	PolyContainer()
	{

		capacity = 8;
		size = 0;
		data = new T * [capacity] { nullptr };

	}

	PolyContainer(const PolyContainer& other)
	{

		copyFrom(other);

	}

	PolyContainer(PolyContainer&& other) noexcept
	{

		moveTo(std::move(other));

	}

	PolyContainer& operator = (const PolyContainer& other)
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	PolyContainer& operator = (PolyContainer&& other) noexcept
	{

		if (this != &other)
		{

			free();
			moveTo(std::move(other));

		}

		return *this;

	}

	~PolyContainer()
	{

		free();

	}

	const T* operator [](size_t index) const
	{

		if (index >= size || data[index] == nullptr) throw std::logic_error("Error");
		return data[index];

	}

	T*& operator [](size_t index)
	{

		if (index >= size || data[index] == nullptr) throw std::logic_error("Error");
		return data[index];

	}

	void push_back(T* element)
	{

		if (!element) throw std::logic_error("Error");
		if (size == capacity) resize(capacity * 2);

		data[size++] = element;

	}

	void push_at(T* element, size_t index)
	{

		if (!element || index >= capacity) throw std::logic_error("Error");
		if (size == capacity) resize(capacity * 2);

		data[index] = element->clone();
		size += 1;

	}

	void pop_back()
	{

		if (!size) throw std::logic_error("Error");
		delete data[size - 1];
		data[size - 1] = nullptr;
		size -= 1;

	}

	size_t getSize() const
	{

		return size;

	}

	size_t getCapacity() const
	{

		return capacity;

	}

};

struct DataFileFormat
{
public:

	uint32_t first = 0;
	uint32_t second = 0;

};

class FunctionContainer
{
private:

	PolyContainer<Uint> data;
	DataFileFormat dataInfo[HELPERS::MAX_DATA_INFO_SIZE];
	size_t sizeOfDataInfo = 0;

public:

	void operator += (Uint* element)
	{

		data.push_back(element);

	}

	uint32_t evalAt(size_t index, uint32_t number) const
	{

		return (*data[index])(number);

	}

	void deserialize(const char* fileName)
	{

		if (!fileName) return;

		std::ifstream file(fileName, std::ios::binary);
		if (!file.is_open()) return;

		sizeOfDataInfo = HELPERS::getFileSize(file) / sizeof(DataFileFormat);
		file.read((char*)dataInfo, sizeOfDataInfo * sizeof(DataFileFormat));
		file.close();

	}

	void serialize(const char* fileName) const
	{

		if (!fileName) return;

		std::ofstream file(fileName, std::ios::binary | std::ios::trunc);
		if (!file.is_open()) return;

		for (int i = 0; i < sizeOfDataInfo; i++)
		{

			uint32_t number = dataInfo[i].first;
			uint32_t index = dataInfo[i].second;

			if (index >= data.getCapacity())
			{

				file.write((const char*)&dataInfo[i].first, sizeof(uint32_t) * sizeof(char));

			}
			else
			{

				uint32_t result = evalAt(index, number);
				file.write((const char*)&result, sizeof(uint32_t) * sizeof(char));

			}

		}

		file.close();

	}

};

class FunctionFactory
{
public:

	static Uint* createFuncion()
	{

		size_t choiceMask = 0;
		std::cin >> choiceMask;
		FunctionType choice = (FunctionType)choiceMask;

		switch (choice)
		{

		case FunctionType::ShiftLeftFunction:
		{

			uint32_t N = 0;
			std::cin >> N;
			return new ShiftLeftFunction(N);
			break;

		}
		case FunctionType::XorFunction:
		{

			size_t size = 0;
			std::cin >> size;
			uint32_t* data = new uint32_t[size];

			for (int i = 0; i < size; i++)
			{

				std::cin >> data[i];

			}

			Uint* result = new XorFunction(data, size);
			delete[] data;
			return result;
			break;

		}
		case FunctionType::ReverseBitsFunction:
		{

			uint32_t K = 0;
			std::cin >> K;
			return new ReverseBitsFunction(K);
			break;

		}
		case FunctionType::FlipBitsFunction:
		{

			uint32_t M = 0;
			std::cin >> M;
			return new FlipBitsFunction(M);
			break;

		}
		case FunctionType::ReverseFlipBits:
		{

			uint32_t K = 0;
			uint32_t M = 0;
			std::cin >> K >> M;
			return new ReverseFlipBits(K, M);
			break;

		}
		default:
		{

			return nullptr;
			break;

		}

		}

		return nullptr;

	}

};

int main()
{

	//DataFileFormat data[9] =
	//{

	//	{0, 0}, {1, 1}, {2, 2},
	//	{3, 3}, {111, 111}, {4, 4},

	//};

	//std::ofstream file("file.txt", std::ios::binary);
	//file.write((const char*)data, sizeof(data) * sizeof(char));
	//file.close();

	Uint* shiftLeftFunction = FunctionFactory::createFuncion();
	Uint* xorFunction = FunctionFactory::createFuncion();
	Uint* reverseBitsFunction = FunctionFactory::createFuncion();
	Uint* flipBitsFunction = FunctionFactory::createFuncion();
	Uint* reverseFlipBits = FunctionFactory::createFuncion();

	FunctionContainer container;
	container += shiftLeftFunction;
	container += xorFunction;
	container += reverseBitsFunction;
	container += flipBitsFunction;
	container += reverseFlipBits;

	container.deserialize("file.txt");
	container.serialize("result.txt");

	delete shiftLeftFunction;
	delete xorFunction;
	delete reverseBitsFunction;
	delete flipBitsFunction;
	delete reverseFlipBits;

	return 0;

}
