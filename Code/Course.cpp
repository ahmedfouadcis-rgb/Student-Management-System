#include "course.h"

Course::Course(int id, string name, double g)
{
    courseId = id;
    courseName = name;
    grade = g;
}

int Course::getId() const
{
    return courseId;
}

string Course::getName() const
{
    return courseName;
}

double Course::getGrade() const
{
    return grade;
}

void Course::setGrade(double g)
{
    grade = g;
}

void Course::display() const
{
    cout << "Course ID: " << courseId
        << " Name: " << courseName
        << " Grade: " << grade << endl;
}

bool Course::operator<(const Course& other) const
{
    return courseId < other.courseId;
}