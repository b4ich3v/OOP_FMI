#pragma once

class CommunicationPipe
{
private:

    size_t countOfSharedPtrs = 0;
    size_t countOfWeakPtrs = 0;

public:

    void addSharedPtr();

    void removeSharedPtr();

    void addWeakPtr();

    void removeWeakPtr();

    bool noOwners() const;

    bool noVisitors() const;

    size_t getCountOfSharedPtrs() const;

    size_t getCountOfWeakPtrs() const;

};
