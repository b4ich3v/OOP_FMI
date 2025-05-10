#include "User.h"
#include "Course.h"
#include "Assignment.h"
#include "Submission.h"
#include "Grade.h"
#include "Admin.h"
#include "Message.h"
#include "Student.h"
#include "Teacher.h"
#include "Admin.h"
#include "MyVector.hpp"
#include <fstream>
#pragma once

class Service 
{
private:

    Service() = default;

    ~Service() = default;

    Service(const Service&) = delete;

    Service& operator = (const Service&) = delete;

    void loadUsers();

    void saveUsers() const;

    void loadCourses();

    void saveCourses() const;

    void loadAssignments();

    void saveAssignments() const;

    void loadSubmissions();

    void saveSubmissions() const;

    void loadGrades();

    void saveGrades() const;

    void loadMessages();

    void saveMessages() const;

public:

    static Service& instance();

    void loadAll();

    void saveAll() const;

};
