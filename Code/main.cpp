#include "student.h"
#include <iostream>
using namespace std;

int main()
{
    Student students;
    students.loadFromFile();

    int command;
    do
    {
        cout << "\n1 Add Student\n2 Remove Student\n3 Search Student\n4 Display All Students\n";
        cout << "5 Enroll Course\n6 Show All Courses\n7 Sort Students by GPA\n8 Update Student\n";
        cout << "9 Edit/Remove Course\n10 Save & Exit\nCommand: ";
        cin >> command;

        switch (command)
        {
        case 1: 
            students.addStudent(); 
            break;
        case 2: 
            students.removeStudent(); 
            break;
        case 3:
        {
            int id;
            cout << "Enter ID: ";
            cin >> id;
            Student* s = students.searchStudent(id);
            if (s) s->display();
            else cout << "Student not found\n";
        }
        break;
        case 4: 
            students.displayAll(); 
            break;
        case 5: 
            students.enrollCourse(); 
            break;
        case 6: 
            students.showCourses(); 
            break;
        case 7: 
            students.sortByGPA();
            students.displayAll();
            break;
        case 8: 
            students.updateStudent(); 
            break;
        case 9: 
            students.editOrRemoveCourse(); 
            break;
        case 10:
            students.saveToFile();
            cout << "Saved. Exiting...\n";
            break;
        default: cout << "Invalid Command\n";
        }
    } 
    while (command != 10);

    return 0;
}