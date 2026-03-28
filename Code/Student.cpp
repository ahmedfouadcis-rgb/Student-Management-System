#include "student.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

Student::Student(int id, string name) : Person(name)
{
    this->id = id;
}

int Student::getId() const
{
    return id;
}

double Student::getGpa() const
{
    if (courses.empty()) return 0;

    double sum = 0;

    for (auto& c : courses)
        sum += c.getGrade();

    return sum / courses.size();
}

void Student::addCourse(int cid, string cname, double grade)
{
    Course newCourse(cid, cname, grade);

    auto result = courses.insert(newCourse);

    if (!result.second)
    {
        courses.erase(newCourse);
        courses.insert(Course(cid, cname, grade));
        cout << "Course already exists. Grade updated\n";
    }
    else
    {
        cout << "Course added\n";
    }
}

void Student::display() const
{
    cout << "ID: " << id
        << " Name: " << name
        << " GPA: " << fixed << setprecision(2)
        << getGpa() << endl;

    for (auto& c : courses)
    {
        cout << "\t";
        c.display();
    }
}

Student* Student::searchStudent(int sid)
{
    auto it = students.find(sid);

    if (it != students.end())
        return &it->second;

    return nullptr;
}

void Student::addStudent()
{
    int id;
    string name;

    cout << "Enter ID: ";
    cin >> id;

    if (students.find(id) != students.end())
    {
        cout << "ID already exists\n";
        return;
    }

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);

    students[id] = Student(id, name);

    cout << "Student added\n";
}

void Student::removeStudent()
{
    int id;
    cout << "Enter ID: ";
    cin >> id;

    if (students.erase(id))
        cout << "Student removed\n";
    else
        cout << "Student not found\n";
}

void Student::displayAll()
{
    if (students.empty())
    {
        cout << "No students available\n";
        return;
    }

    for (auto& pair : students)
    {
        pair.second.display();
        cout << endl;
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

    for (auto& pair : students)
    {
        for (auto& c : pair.second.courses)
        {
            if (c.getId() == cid)
                cname = c.getName();
        }
    }

    if (cname.empty())
    {
        cout << "Course Name: ";
        cin.ignore();
        getline(cin, cname);
    }

    double grade;

    do
    {
        cout << "Grade (0-4): ";
        cin >> grade;

    } while (grade < 0 || grade > 4);

    s->addCourse(cid, cname, grade);
}

void Student::showCourses()
{
    map<int, vector<pair<string, double>>> courseStudents;
    map<int, string> courseNames;

    for (auto& pair : students)
    {
        Student& s = pair.second;

        for (auto& c : s.courses)
        {
            courseNames[c.getId()] = c.getName();

            courseStudents[c.getId()].push_back(
                { s.getName(), c.getGrade() });
        }
    }

    for (auto& pair : courseStudents)
    {
        int cid = pair.first;
        auto& list = pair.second;

        double sum = 0;

        for (auto& p : list)
            sum += p.second;

        double avg = sum / list.size();

        cout << "Course ID: " << cid
            << " Name: " << courseNames[cid] << endl;

        cout << "\tStudents: ";

        for (size_t i = 0; i < list.size(); i++)
        {
            cout << list[i].first
                << " (" << list[i].second << ")";

            if (i != list.size() - 1)
                cout << ", ";
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

    for (auto& c : s->courses)
    {
        if (c.getId() == cid)
        {
            int choice;

            cout << "1 Edit Grade\n2 Remove Course\nChoice: ";
            cin >> choice;

            if (choice == 1)
            {
                double g;

                do
                {
                    cout << "New Grade (0-4): ";
                    cin >> g;

                } while (g < 0 || g > 4);
            }

            return;
        }
    }

    cout << "Course not found\n";
}

void Student::sortByGPA()
{
    vector<Student> temp;

    for (auto& pair : students)
        temp.push_back(pair.second);

    sort(temp.begin(), temp.end(),
        [](Student a, Student b)
        {
            return a.getGpa() > b.getGpa();
        });

    cout << "Students sorted by GPA\n";

    for (auto& s : temp)
        s.display();
}

void Student::saveToFile()
{
    ofstream out("Students_Data.csv");

    for (auto& pair : students)
    {
        Student& s = pair.second;

        out << s.getId() << "," << s.getName();

        for (auto& c : s.courses)
            out << "," << c.getId()
            << ":" << c.getName()
            << ":" << c.getGrade();

        out << endl;
    }
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
            if (ch == ',')
            {
                entries.push_back(temp);
                temp = "";
            }
            else temp += ch;
        }

        entries.push_back(temp);

        int id = stoi(entries[0]);
        string name = entries[1];

        Student s(id, name);

        for (size_t i = 2; i < entries.size(); i++)
        {
            string part = entries[i];

            size_t p1 = part.find(':');
            size_t p2 = part.find(':', p1 + 1);

            int cid = stoi(part.substr(0, p1));
            string cname = part.substr(p1 + 1, p2 - p1 - 1);
            double grade = stod(part.substr(p2 + 1));

            s.courses.insert(Course(cid, cname, grade));
        }

        students[id] = s;
    }
}