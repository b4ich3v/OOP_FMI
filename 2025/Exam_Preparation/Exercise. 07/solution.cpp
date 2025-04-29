#include <iostream>
#include <cstring>
#include <unordered_map>
#include <vector>

class Observer
{
public:

    virtual void update(const std::string& currency, const std::string& value) const = 0;

    virtual ~Observer() = default;

};

class ConcreteObserver : public Observer
{
private:

    std::string name;

public:

    ConcreteObserver(const std::string& name) : name(name) {}

    void update(const std::string& currency, const std::string& value) const override
    {

        std::cout << name << ":" << currency << "," << value << std::endl;

    }

};

class CentralBank 
{
private:

    std::string name;
    std::unordered_map<std::string, std::string> container;
    std::vector<const Observer*> observers;

    void resetContainer() 
    {

        setContainer(container.size());

    }

    void setContainer(int size) 
    {

        std::string defaultCurrency = "noCurrency";
        std::string defaultValue = "noValue";

        for (int i = 0; i < size; i++)
        {

            container[defaultCurrency + std::to_string(i)] = defaultValue;

        }

    }

public:

    CentralBank(): name("default") {}

    CentralBank(const std::string& name) : name(name) { setContainer(25); }

    void addCurrency(const std::string& currency)
    {

        notify(currency, "noValue");
        container[currency] = "noValue";

    }

    void setRate(const std::string& currency, const std::string& value)
    {

        notify(currency, value);
        container[currency] = value;

    }

    void deleteCurrency(const std::string& currency)
    {

        notify(currency, "noValue");
        container[currency] = "noValue";

    }

    void registerObserver(const Observer* ptr) 
    {

        if (!ptr) throw std::logic_error("Error");

        for (int i = 0; i < observers.size(); i++)
        {

            if (ptr == observers[i]) return;

        }

        observers.push_back(ptr);

    }

    void unRegisterObserver(const Observer* ptr)
    {

        if (!ptr) throw std::logic_error("Error");

        for (int i = 0; i < observers.size(); i++)
        {

            if (ptr == observers[i]) 
            {

                std::swap(observers[i], observers[observers.size() - 1]);
                observers.pop_back();
                break;

            }

        }

    }

    void notify(const std::string& currency, const std::string& value) const
    {

        for (int i = 0; i < observers.size(); i++)
        {

            observers[i]->update(currency, value);

        }

    }

};

int main() 
{

    CentralBank bank("BNB");

    bank.addCurrency("USD");
    bank.addCurrency("EUR");
    bank.addCurrency("GBP");

    ConcreteObserver obs1("Yoan Baychev");
    ConcreteObserver obs2("Ilian Zaprqnov");
    ConcreteObserver obs3("Kaloyan Markov");
    ConcreteObserver obs4("Ivailo Kunchev");

    bank.registerObserver(&obs1);
    bank.registerObserver(&obs2);
    bank.registerObserver(&obs3);
    bank.registerObserver(&obs4);

    bank.setRate("USD", "1.10");
    bank.unRegisterObserver(&obs2);
    std::cout << std::endl;
    bank.setRate("EUR", "0.90");

    return 0;

}

