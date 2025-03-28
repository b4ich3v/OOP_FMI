#include <iostream>
#include "MonthlyPlanner.h"

int main()
{

    Task task1("Feed the dog", 2, 15, Time(7, 30, 0));
    Task task2("Team meeting", 3, 60, Time(9, 0, 0));
    Task task3("Gym workout", 1, 90, Time(18, 0, 0));
    Task task4("Cook dinner", 2, 40, Time(20, 0, 0));
    Task task5("Check e-mails", 1, 10, Time(6, 45, 0));
    Task task6("Write report", 4, 120, Time(14, 0, 0));
    Task task7("Lunch with team", 2, 30, Time(12, 30, 0));
    Task task8("Party time", 5, 180, Time(23, 0, 0));

    MonthlyPlanner planner;

    uint32_t dayMask1 = (1 << 1);
    uint32_t dayMask2 = (1 << 3) | (1 << 5);
    uint32_t dayMask3 = (1 << 0) | (1 << 2);
    uint32_t dayMask4 = (1 << 10);

    planner.addTasks(Month::January, dayMask1, task1);
    planner.addTasks(Month::January, dayMask2, task2);
    planner.addTasks(Month::January, dayMask2, task3);
    planner.addTasks(Month::January, (1 << 5), task4);

    planner.addTasks(Month::January, dayMask3, task5);
    planner.addTasks(Month::January, (1 << 5), task6);
    planner.addTasks(Month::January, dayMask2, task7);
    planner.addTasks(Month::January, (1 << 5), task8);

    planner.addTasks(Month::February, dayMask4, task1);
    planner.addTasks(Month::February, dayMask4, task8);

    planner.printDoneTasks();

    planner.setTaskDone(task2);
    planner.setTaskDone(task3);
    planner.setTaskDone(task8);

    planner.printDoneTasks();

    uint32_t removeMaskDay3 = (1 << 3);
    planner.removeTasks(Month::January, removeMaskDay3);
    planner.printDoneTasks();

    uint32_t removeMaskDay5 = (1 << 5);
    planner.removeTasks(Month::January, removeMaskDay5);
    planner.printDoneTasks();

    planner.removeTasks(Month::February, (1 << 10));
    planner.printDoneTasks();


    return 0;

}
