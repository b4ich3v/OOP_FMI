#include "Student.h"

int main()
{

    double* grades1 = new double[3];
    grades1[0] = 5.75;
    grades1[1] = 6.00;
    grades1[2] = 5.50;

    double* grades2 = new double[5];
    grades2[0] = 4.33;
    grades2[1] = 6.00;
    grades2[2] = 2.00;
    grades2[3] = 3.80;
    grades2[4] = 4.50;

    Student st1("Yoan Baychev", "No mercy", grades1, 3);
    Student st2("Ivailo Kunchev", "Ok", grades2, 5);

    st1.printStudent();
    st2.printStudent();

    for (int i = 0; i < 7; i++) st1.addGrade(6.00);

    st1.printStudent();
    Student st1Copy = st1;
    st1Copy.printStudent();
    st1Copy = st2;
    st1Copy.printStudent();

    delete[] grades1;
    delete[] grades2;

    return 0;

}
