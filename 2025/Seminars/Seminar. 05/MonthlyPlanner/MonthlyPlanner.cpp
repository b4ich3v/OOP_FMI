#include "MonthlyPlanner.h"
#include <iostream>
#include <algorithm> 

void MonthlyPlanner::addTasks(Month month, uint32_t dayMask, const Task& task)
{

    int currentMonth = (int)month;

    for (int i = 0; i < HELPING_CONSTANS::COUNT_OF_BITS_IN_INT; i++)
    {

        if (HELPING_CONSTANS::isIndexOfUpperBit(dayMask, i))
        {

            int currentDay = i;
            if (currentDay < 0 || currentDay >= HELPING_CONSTANS::COUNT_OF_DAYS_IN_MONTH) continue;
                
            int& count = countOfTasks[currentMonth][currentDay];
            if (count >= HELPING_CONSTANS::MAX_COUNT_OF_TASKS) continue;
                
            tasksPerMonth[currentMonth][currentDay][count] = task;
            count += 1;

        }

    }

    sortTasksByPriority();

}

void MonthlyPlanner::removeTasks(Month month, uint32_t dayMask)
{

    int currentMonth = (int)month;

    for (int i = 0; i < HELPING_CONSTANS::COUNT_OF_BITS_IN_INT; i++)
    {

        if (HELPING_CONSTANS::isIndexOfUpperBit(dayMask, i))
        {

            int currentDay = i;
            if (currentDay < 0 || currentDay >= HELPING_CONSTANS::COUNT_OF_DAYS_IN_MONTH) continue;
                
            countOfTasks[currentMonth][currentDay] = 0;

        }

    }

}

void MonthlyPlanner::sortTasksByPriority()
{

    for (int m = 0; m < HELPING_CONSTANS::COUNT_OF_MONTHS; m++)
    {

        for (int d = 0; d < HELPING_CONSTANS::COUNT_OF_DAYS_IN_MONTH; d++)
        {

            int N = countOfTasks[m][d];  
            if (N < 2) continue;

            for (int pass = 0; pass < N - 1; pass++)
            {
                
                for (int n = 1; n < N - pass; n++)
                {
                    
                    if (tasksPerMonth[m][d][n].getPriority() <
                        tasksPerMonth[m][d][n - 1].getPriority())
                    {

                        std::swap(tasksPerMonth[m][d][n], tasksPerMonth[m][d][n - 1]);

                    }

                }

            }

        }

    }

}

void MonthlyPlanner::setTaskDone(const Task& task)
{

    for (int m = 0; m < HELPING_CONSTANS::COUNT_OF_MONTHS; m++)
    {

        for (int d = 0; d < HELPING_CONSTANS::COUNT_OF_DAYS_IN_MONTH; d++)
        {

            int N = countOfTasks[m][d];

            for (int t = 0; t < N; t++)
            {

                if (tasksPerMonth[m][d][t] == task)
                {

                    tasksPerMonth[m][d][t].setStatusTrue();

                }

            }

        }

    }

}

void MonthlyPlanner::printDoneTasks() const
{

    for (int m = 0; m < HELPING_CONSTANS::COUNT_OF_MONTHS; m++)
    {

        std::cout << "Tasks for month " << m + 1 << ":\n";

        for (int d = 0; d < HELPING_CONSTANS::COUNT_OF_DAYS_IN_MONTH; d++)
        {

            bool anyPrinted = false;

            for (int t = 0; t < countOfTasks[m][d]; t++)
            {

                if (tasksPerMonth[m][d][t].getStatus())
                {

                    if (!anyPrinted)
                    {

                        std::cout << "  Day " << d << ":\n";
                        anyPrinted = true;

                    }

                    std::cout << "    ";
                    tasksPerMonth[m][d][t].printTask();

                }

            }

        }

        std::cout << std::endl;
    }

    std::cout << std::endl;

}
