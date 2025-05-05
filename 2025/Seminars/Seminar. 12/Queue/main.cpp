#include "Queue.hpp"

int main() 
{

    try 
    {
        
        Queue<int> q;

        q.push(10);
        q.push(20);
        q.push(30);

        std::cout << q.size() << " " << q.front() << std::endl;

        q.pop();
        std::cout << q.size() << " " << q.front() << std::endl;

        Queue<int> qCopy = q;
        std::cout  << qCopy.size() << " " << qCopy.front() << std::endl;

        qCopy.push(40);
        std::cout << qCopy.size() << " " << qCopy.front() << std::endl;

        Queue<int> qMoved = std::move(qCopy);
        std::cout << std::boolalpha << qCopy.empty() << std::endl;
        std::cout << qMoved.size()<< " " << qMoved.front() << std::endl;

        q = qMoved;
        std::cout << q.size() << " " << q.front() << std::endl;

        while (!q.empty())
        {

            std::cout << q.front() << std::endl;
            q.pop();

        }

        std::cout << q.empty() << std::endl;

    }
    catch (const std::exception& e) 
    {

        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;

}
