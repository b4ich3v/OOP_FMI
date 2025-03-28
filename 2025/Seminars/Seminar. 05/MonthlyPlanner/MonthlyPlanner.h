#pragma once
#include "Task.h"
#include <cstdint>

namespace HELPING_CONSTANS
{

    const int MAX_COUNT_OF_TASKS = 10;
    const int COUNT_OF_MONTHS = 12;
    const int COUNT_OF_DAYS_IN_MONTH = 31;
    const int COUNT_OF_BITS_IN_INT = 32;

    inline bool isIndexOfUpperBit(uint32_t number, int index)
    {
        
        return (number & (1U << index)) != 0;

    }

}

enum class Month
{

    January = 0,
    February = 1,
    March = 2,
    April = 3,
    May = 4,
    June = 5,
    July = 6,
    August = 7,
    September = 8,
    October = 9,
    November = 10,
    December = 11

};

class MonthlyPlanner
{
private:
   
    Task tasksPerMonth[HELPING_CONSTANS::COUNT_OF_MONTHS]
        [HELPING_CONSTANS::COUNT_OF_DAYS_IN_MONTH]
        [HELPING_CONSTANS::MAX_COUNT_OF_TASKS];

    int countOfTasks[HELPING_CONSTANS::COUNT_OF_MONTHS]
        [HELPING_CONSTANS::COUNT_OF_DAYS_IN_MONTH] = { {0} };

    void sortTasksByPriority();

public:

    MonthlyPlanner() = default;

    void addTasks(Month month, uint32_t day, const Task& task);

    void removeTasks(Month month, uint32_t day);

    void setTaskDone(const Task& task);

    void printDoneTasks() const;

};
