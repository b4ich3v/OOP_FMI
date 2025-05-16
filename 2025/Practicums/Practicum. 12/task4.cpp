#include <iostream>
#include <cmath>
#include "MyString.h"
#include "MyVector.hpp"
#include "HeterogeneousContainer.hpp"

class SubjectInFMI 
{
private:

    MyString nameOfSubject;
    MyString  nameOfLector;
    MyVector<MyString> assistants;
    int totalPoints;

public:

    SubjectInFMI(const MyString& lector,
        const MyString& subject,
        const MyVector<MyString>& assts,
        int points):
        nameOfSubject(subject),
        nameOfLector(lector),
        assistants(assts),
        totalPoints(points) {}

    virtual ~SubjectInFMI() = default;

    virtual int gradeToPass() const = 0;

    virtual void getSubjectName() const 
    {

        std::cout << nameOfSubject << '\n';

    }

    virtual SubjectInFMI* clone() const = 0;

    int getTotalPoints() const 
    {

        return totalPoints;

    }

    const MyString& getName() const 
    {

        return nameOfSubject;

    }

};

class DIS: public SubjectInFMI 
{
public:

    DIS(const MyString& lect, const MyString& subj,
        const MyVector<MyString>& a, int pts): 
        SubjectInFMI(lect, subj, a, pts) {}

    int gradeToPass() const override 
    {
        
        return (int)(std::ceil(0.7 * getTotalPoints()));

    }

    SubjectInFMI* clone() const override 
    {

        return new DIS(*this);

    }

};

class OOP: public SubjectInFMI 
{
private:

    int bonusPoints;

public:

    OOP(const MyString& lect, const MyString& subj,
        const MyVector<MyString>& a, int pts,
        int bonus): 
        SubjectInFMI(lect, subj, a, pts),
        bonusPoints(bonus){}

    int gradeToPass() const override 
    {
    
        double req = 0.8 * getTotalPoints() - bonusPoints;
        if (req < 0) return 0;
        return (int)(std::ceil(req));

    }

    SubjectInFMI* clone() const override 
    {

        return new OOP(*this);

    }

};

class DSTR2: public SubjectInFMI
{
public:

    DSTR2(const MyString& lect, const MyString& subj,
        const MyVector<MyString>& a, int pts): 
        SubjectInFMI(lect, subj, a, pts) {}

    int gradeToPass() const override 
    {

        return (int)(std::ceil(0.6 * getTotalPoints()));

    }

    SubjectInFMI* clone() const override 
    {

        return new DSTR2(*this);

    }

};

class UP: public SubjectInFMI 
{
public:

    UP(const MyString& lect, const MyString& subj,
        const MyVector<MyString>& a, int pts): 
        SubjectInFMI(lect, subj, a, pts) {}

    int gradeToPass() const override
    {

        return (int)(std::ceil(0.5 * getTotalPoints()));

    }

    SubjectInFMI* clone() const override 
    {

        return new UP(*this);

    }

};

class GEOMETRY: public SubjectInFMI 
{
public:

    GEOMETRY(const MyString& lect, const MyString& subj,
        const MyVector<MyString>& a, int pts): 
        SubjectInFMI(lect, subj, a, pts) {}

    int gradeToPass() const override 
    {

        return (int)(std::ceil(0.75 * getTotalPoints()));

    }

    SubjectInFMI* clone() const override 
    {

        return new GEOMETRY(*this);

    }
};

struct FMISubjectManager 
{

    HeterogeneousContainer<SubjectInFMI> container;

    void addSubject(SubjectInFMI* subj) 
    {

        container.addElement(subj);

    }

    size_t size() const 
    {

        return container.getSize();

    }

    const SubjectInFMI* mostFrequentSubject() const
    {

        size_t size = container.getSize();
        if (size == 0) return nullptr;

        const SubjectInFMI* best = container[0];
        size_t bestCount = 0;

        for (size_t i = 0; i < size; i++) 
        {

            const MyString& nameForCurrentIndex = container[i]->getName();
            size_t count = 0;

            for (size_t j = 0; j < size; j++)
            {

                if (container[j]->getName() == nameForCurrentIndex) count += 1;
                   
            }

            if (count > bestCount) 
            {

                bestCount = count;
                best = container[i];

            }

        }

        return best;

    }

};


int main()
{

    MyVector<MyString> ass;
    ass.push_back("Ivan");
    ass.push_back("Georgi");

    DIS dis("Dr. Petrov", "Calculus", ass, 100);
    OOP oop("Dr. Ivanov", "OOP", ass, 100, 5);
    DSTR2 dstr2("Dr. Georgiev", "DSTR2", ass, 100);
    UP up("Dr. Dimov", "UP", ass, 100);
    GEOMETRY geo("Dr. Stefanov", "Geometry", ass, 100);

    FMISubjectManager mgr;
    mgr.addSubject(&dis);
    mgr.addSubject(&oop);
    mgr.addSubject(&dstr2);
    mgr.addSubject(&up);
    mgr.addSubject(&geo);

    mgr.addSubject(&dis);
    mgr.addSubject(&oop);

    std::cout << mgr.size() << std::endl;

    auto* most = mgr.mostFrequentSubject();
    std::cout << "Most frequent subject: ";
    if (most) most->getSubjectName();

    std::cout << dis.gradeToPass() << std::endl;
    std::cout << oop.gradeToPass() << std::endl;
    std::cout << dstr2.gradeToPass() << std::endl;
    std::cout << up.gradeToPass() << std::endl;
    std::cout << geo.gradeToPass() << std::endl;

    return 0;

}
