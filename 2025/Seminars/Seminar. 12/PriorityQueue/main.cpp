#include "PriorityQueue.hpp"
#include "MyString.h"

int main() 
{

	try
	{

        PriorityQueue<MyString, int> pq1;
        pq1.push("A", 5);
        pq1.push("B", 10);
        pq1.push("C", 5);

        while (!pq1.empty())
        {

            std::cout << pq1.top() << " ";
            pq1.pop();

        }

        PriorityQueue<double, int> pq2;
        pq2.push(3.14, 3);
        pq2.push(5.7, 2);
        pq2.push(1.0, 1);

        while (!pq2.empty())
        {

            std::cout << pq2.top() << " ";
            pq2.pop();

        }

	}
	catch (const std::exception& e)
	{

        std::cout << e.what() << std::endl;

	}

    return 0;

}
