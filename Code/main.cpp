#include "student.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

Student::Student(int id, string name) : Person(name)
{
    this->id = id;
}

int Student::getId() const { return id; }

double Student::getGpa() const
{
    if (courses.empty()) return 0;
    double sum = 0;
    for (auto& c : courses) sum += c.getGrade();
    return sum / courses.size();
}

void Student::addCourse(int cid, string cname, double grade)
{
    for (auto& c : courses)
    {
        if (c.getId() == cid)
        {
            c.setGrade(grade);
            cout << "Course already exists. Grade updated to " << grade << endl;
            return;
        }
    }
    courses.push_back(Course(cid, cname, grade));
    cout << "Course added\n";
}

void Student::display() const
{
    cout << "ID: " << id << " Name: " << name
        << " GPA: " << fixed << setprecision(2) << getGpa() << endl;
    for (auto& c : courses)
    {
        cout << "\t";
        c.display();
    }
}

Student* Student::searchStudent(int sid)
{
    for (auto& s : students)
        if (s.getId() == sid)
            return &s;
    return nullptr;
}

void Student::addStudent()
{
    int id;
    string name;
    cout << "Enter ID: ";
    cin >> id;

    if (searchStudent(id))
    {
        cout << "ID already exists\n";
        return;
    }

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);

    students.push_back(Student(id, name));
    cout << "Student added\n";
}

void Student::removeStudent()
{
    int id;
    cout << "Enter ID: ";
    cin >> id;

    for (size_t i = 0; i < students.size(); i++)
    {
        if (students[i].getId() == id)
        {
            students.erase(students.begin() + i);
            cout << "Student removed\n";
            return;
        }
    }
    cout << "Student not found\n";
}

void Student::displayAll()
{
    if (students.empty())
    {
        cout << "No students available\n";
        return;
    }
    for (auto& s : students)
    {
        s.display();
        cout << "\n";
    }
}

void Student::enrollCourse()
{
    int id;
    cout << "Enter Student ID: ";
    cin >> id;

    Student* s = searchStudent(id);
    if (!s)
    {
        cout << "Student not found\n";
        return;
    }

    int cid;
    cout << "Course ID: ";
    cin >> cid;

    string cname;

    auto it = find_if(s->courses.begin(), s->courses.end(),
        [cid](const Course& c) { return c.getId() == cid; });

    if (it != s->courses.end())
    {
        cname = it->getName();
        cout << "Course already exists for this student. Current name: " << cname << endl;
    }
    else
    {
        bool found = false;
        for (auto& other : students)
        {
            if (other.getId() == id) continue;
            auto it2 = find_if(other.courses.begin(), other.courses.end(),
                [cid](const Course& c) { return c.getId() == cid; });
            if (it2 != other.courses.end())
            {
                cname = it2->getName();
                cout << "Course already exists in another student. Using name: " << cname << endl;
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "Course Name: ";
            cin.ignore();
            getline(cin, cname);
        }
    }

    double grade;
    do {
        cout << "Grade (0.0 - 4.0): ";
        cin >> grade;
        if (grade < 0 || grade > 4)
            cout << "Invalid grade! Enter a value between 0 and 4.\n";
    } while (grade < 0 || grade > 4);

    s->addCourse(cid, cname, grade);
}

void Student::showCourses()
{
    if (students.empty())
    {
        cout << "No students available\n";
        return;
    }

    struct CourseInfo
    {
        string name;
        vector<pair<string, double>> students; 
    };

    vector<int> courseIds; 
    vector<CourseInfo> courseInfos;

    for (auto& s : students)
    {
        for (auto& c : s.courses)
        {
            auto it = find(courseIds.begin(), courseIds.end(), c.getId());
            if (it != courseIds.end())
            {
                size_t idx = it - courseIds.begin();
                courseInfos[idx].students.push_back({ s.getName(), c.getGrade() });
            }
            else
            {
                courseIds.push_back(c.getId());
                CourseInfo ci;
                ci.name = c.getName();
                ci.students.push_back({ s.getName(), c.getGrade() });
                courseInfos.push_back(ci);
            }
        }
    }

    for (size_t i = 0; i < courseIds.size(); ++i)
    {
        int cid = courseIds[i];
        auto& ci = courseInfos[i];

        double sum = 0;
        for (auto& p : ci.students) sum += p.second;
        double avg = sum / ci.students.size();

        cout << "Course ID: " << cid << " Name: " << ci.name << endl;
        cout << "\tStudents: ";
        for (size_t j = 0; j < ci.students.size(); ++j)
        {
            cout << ci.students[j].first << " (" << ci.students[j].second << ")";
            if (j != ci.students.size() - 1) cout << ", ";
        }
        cout << " Average grade: " << avg << endl << endl;
    }
}

void Student::updateStudent()
{
    int id;
    cout << "Enter Student ID: ";
    cin >> id;

    Student* s = searchStudent(id);
    if (!s)
    {
        cout << "Student not found\n";
        return;
    }

    string newName;
    cout << "Enter new name: ";
    cin.ignore();
    getline(cin, newName);
    s->setName(newName);
}

void Student::editOrRemoveCourse()
{
    int id;
    cout << "Enter Student ID: ";
    cin >> id;

    Student* s = searchStudent(id);
    if (!s)
    {
        cout << "Student not found\n";
        return;
    }

    int cid;
    cout << "Enter Course ID: ";
    cin >> cid;

    for (size_t i = 0; i < s->courses.size(); i++)
    {
        if (s->courses[i].getId() == cid)
        {
            int choice;
            cout << "1 Edit Grade\n2 Remove Course\nChoice: ";
            cin >> choice;

            if (choice == 1)
            {
                double g;
                do {
                    cout << "New Grade (0.0 - 4.0): ";
                    cin >> g;
                    if (g < 0.0 || g > 4.0)
                        cout << "Invalid grade! Enter a value between 0.0 and 4.0\n";
                } while (g < 0.0 || g > 4.0);
                s->courses[i].setGrade(g);
            }
            else
            {
                s->courses.erase(s->courses.begin() + i);
            }
            return;
        }
    }
    cout << "Course not found\n";
}

void Student::sortByGPA()
{
    sort(students.begin(), students.end(),
        [](Student a, Student b) { return a.getGpa() > b.getGpa(); });
    cout << "Students sorted by GPA\n";
}


void Student::saveToFile()
{
    ofstream out("Students_Data.csv");
    for (auto& s : students)
    {
        out << s.getId() << "," << s.getName();
        for (auto& c : s.courses)
            out << "," << c.getId() << ":" << c.getName() << ":" << c.getGrade();
        out << endl;
    }
    out.close();
}

void Student::loadFromFile()
{
    ifstream in("Students_Data.csv");
    if (!in) return;

    string line;
    while (getline(in, line))
    {
        if (line.empty()) continue;

        vector<string> entries;
        string temp;
        for (char ch : line)
        {
            if (ch == ',') { entries.push_back(temp); temp = ""; }
            else temp += ch;
        }
        entries.push_back(temp);

        int id = stoi(entries[0]);
        string name = entries[1];
        Student s(id, name);

        for (size_t i = 2; i < entries.size(); ++i)
        {
            string part = entries[i];
            size_t p1 = part.find(':');
            size_t p2 = part.find(':', p1 + 1);

            int cid = stoi(part.substr(0, p1));
            string cname = part.substr(p1 + 1, p2 - p1 - 1);
            double grade = stod(part.substr(p2 + 1));

            s.courses.push_back(Course(cid, cname, grade));
        }

        students.push_back(s);
    }
    in.close();
}
