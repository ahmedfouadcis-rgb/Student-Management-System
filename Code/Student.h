#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"
#include "course.h"
#include <vector>
#include <string>
using namespace std;

class Student : public Person
{
private:
    int id;

public:
    vector<Course> courses;
    vector<Student> students;

    Student(int id = 0, string name = "");

    int getId() const;
    double getGpa() const;

    void addCourse(int cid, string cname, double grade);
    void display() const;

    Student* searchStudent(int sid);
    void addStudent();
    void removeStudent();
    void displayAll();
    void enrollCourse();
    void showCourses();
    void updateStudent();
    void editOrRemoveCourse();
    void sortByGPA();

    void saveToFile();
    void loadFromFile();
};

#endif
