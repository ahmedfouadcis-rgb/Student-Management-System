#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <iostream>
using namespace std;

class Course
{
private:
    int courseId;
    string courseName;
    double grade;

public:
    Course(int id = 0, string name = "", double g = 0);

    int getId() const;
    string getName() const;
    double getGrade() const;

    void setGrade(double g);

    void display() const;

    bool operator<(const Course& other) const;
};

#endif