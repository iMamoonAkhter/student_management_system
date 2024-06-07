#include <iostream>
#include <vector>
#include <windows.h>
#include <string>
#include <map>

using namespace std;

class User {
protected:
    string username;
    string password;
    string role;
    int id;

public:
    User(string username, string password, string role, int id)
        : username(username), password(password), role(role), id(id) {}

    virtual ~User() {
        cout << "User destructor called";
    } // Virtual destructor

    string getUsername() const { return username; }
    string getRole() const { return role; }
    int getId() const { return id; }
    string getPassword() const { return password; }  // Added getPassword method

    // Pure virtual function to be implemented by derived classes
    virtual void portal() = 0;

    // Friend function for displaying user information
    friend ostream& operator<<(ostream& os, const User& user);
};

ostream& operator<<(ostream& os, const User& user) {
    os << "Username: " << user.username << ", Role: " << user.role << ", ID: " << user.id;
    return os;
}

class School;

class Teacher : public User {
private:
    School* school;

public:
    Teacher(string username, string password, int id, School* school)
        : User(username, password, "teacher", id), school(school) {}

    void portal() override;
void addNotification();
    void addQuizMarks();
    void addReport();
    void addLecture();
    void addAssignment();
    void addQuiz();

    School* getSchool() const { return school; }
};

class Student : public User {
private:
    School* school;

public:
    Student(string username, string password, int id, School* school)
        : User(username, password, "student", id), school(school) {}

    void portal() override;
void displayNotifications() const;
    void displayQuizMarks() const;
    void displayReport() const;
    void displayLectures() const;
    void displayAssignments() const;
    void displayQuiz() const;

    School* getSchool() const { return school; }
};

class Course {
public:
    int id;
    string name;

    Course(int id, string name) : id(id), name(name) {}

    friend ostream& operator<<(ostream& os, const Course& course) {
        os << "Course ID: " << course.id << ", Name: " << course.name;
        return os;
    }
};

class Admin : public User {
private:
    School* school;

public:
    Admin(string username, string password, int id, School* school)
        : User(username, password, "admin", id), school(school) {}
void addNotification();
    void portal() override;
};

class School {
private:
    map<string, User*> users;
    vector<Course> courses;
    map<string, map<string, int> > quizMarks;
    map<string, map<string, string> > lectures;
    map<string, map<string, string> > assignments;
    map<string, map<string, string> > reports;
    map<string, map<string, string> > quizzes;
    map<string, map<string, string> > notifications;

public:
    ~School() {
        for (auto& user : users) {
            delete user.second;
        }
    }

    void addUser(User* user) {
        users[user->getUsername()] = user;
    }

    void addCourse(const Course& course) {
        courses.push_back(course);
    }

    void displayCourses() const {
        for (const auto& course : courses) {
            cout << course << endl;
        }
    }

    void addQuiz(const string& studentUsername, const string& subject, const string& quiz) {
        quizzes[studentUsername][subject] = quiz;
    }

    void addReport(const string& studentUsername, const string& subject, const string& report) {
        reports[studentUsername][subject] = report;
    }

    void addLecture(const string& studentUsername, const string& subject, const string& lecture) {
        lectures[studentUsername][subject] = lecture;
    }

    void addAssignment(const string& studentUsername, const string& subject, const string& assignment) {
        assignments[studentUsername][subject] = assignment;
    }

    void addQuizMark(const string& studentUsername, const string& subject, int mark) {
        quizMarks[studentUsername][subject] = mark;
    }
    void addNotification(const string& studentUsername, const string& subject, const string& notification) {
        notifications[studentUsername][subject] = notification;
    }

    const map<string, string>* getNotifications(const string& studentUsername) const {
        auto it = notifications.find(studentUsername);
        if (it != notifications.end()) {
            return &it->second;
        }
        return nullptr;
    }
    const map<string, int>* getQuizMarks(const string& studentUsername) const {
        auto it = quizMarks.find(studentUsername);
        if (it != quizMarks.end()) {
            return &it->second;
        }
        return nullptr;
    }

    const map<string, string>* getReports(const string& studentUsername) const {
        auto it = reports.find(studentUsername);
        if (it != reports.end()) {
            return &it->second;
        }
        return nullptr;
    }

    const map<string, string>* getLectures(const string& studentUsername) const {
        auto it = lectures.find(studentUsername);
        if (it != lectures.end()) {
            return &it->second;
        }
        return nullptr;
    }

    const map<string, string>* getAssignments(const string& studentUsername) const {
        auto it = assignments.find(studentUsername);
        if (it != assignments.end()) {
            return &it->second;
        }
        return nullptr;
    }

    const map<string, string>* getQuizzes(const string& studentUsername) const {
        auto it = quizzes.find(studentUsername);
        if (it != quizzes.end()) {
            return &it->second;
        }
        return nullptr;
    }

    void login() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        for (int i = 0; i < 3; i++) {
            cout << ".";
            Sleep(1000);
        }
        cout << endl;

        if (users.find(username) != users.end() && users[username]->getPassword() == password) {
            User* user = users[username];
            cout << "Welcome " << user->getUsername() << " (ID: " << user->getId() << ")\n";
            user->portal();
        } else {
            cout << "Invalid username or password.\n";
        }
    }

    void clearConsole() const {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }
};

void Teacher::portal() {
    int choice;
    do {
        cout << "\nTeacher Portal\n";
        cout << "1. Lectures\n";
        cout << "2. Quizzes\n";
        cout << "3. Assignments\n";
        cout << "4. Student Reports\n";
        cout << "5. Notifications\n";
        cout << "6. Manage Grades\n";
        cout << "0. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Lectures Section\n";
                addLecture();
                break;
            case 2:
                cout << "Quizzes Section\n";
                addQuiz();
                break;
            case 3:
                cout << "Assignments Section\n";
                addAssignment();
                break;
            case 4:
                cout << "Student Reports Section\n";
                addReport();
                break;
            case 5:
                cout << "Notifications Section\n";
                addNotification();
                break;
            case 6:
                cout << "Manage Grades Section\n";
                addQuizMarks();
                break;
            case 0:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

void Teacher::addQuizMarks() {
    string studentUsername, subject;
    int mark;
    cout << "Enter student username: ";
    cin >> studentUsername;
    cout << "Enter subject: ";
    cin >> subject;
    cout << "Enter mark: ";
    cin >> mark;
    school->addQuizMark(studentUsername, subject, mark);
    cout << "Quiz mark added successfully.\n";
}

void Teacher::addReport() {
    string studentUsername, subject, report;
    cout << "Enter student username: ";
    cin >> studentUsername;
    cout << "Enter subject: ";
    cin >> subject;
    cout << "Enter report: ";
    cin.ignore();
    getline(cin, report);
    school->addReport(studentUsername, subject, report);
    cout << "Report added successfully.\n";
}

void Teacher::addLecture() {
    string studentUsername, subject, lecture;
    cout << "Enter student username: ";
    cin >> studentUsername;
    cout << "Enter subject: ";
    cin >> subject;
    cout << "Enter lecture: ";
    cin.ignore();
    getline(cin, lecture);
    school->addLecture(studentUsername, subject, lecture);
    cout << "Lecture added successfully.\n";
}

void Teacher::addAssignment() {
    string studentUsername, subject, assignment;
    cout << "Enter student username: ";
    cin >> studentUsername;
    cout << "Enter subject: ";
    cin >> subject;
    cout << "Enter assignment: ";
    cin.ignore();
    getline(cin, assignment);
    school->addAssignment(studentUsername, subject, assignment);
    cout << "Assignment added successfully.\n";
}

void Teacher::addQuiz() {
    string studentUsername, subject, quiz;
    cout << "Enter student username: ";
    cin >> studentUsername;
    cout << "Enter subject: ";
    cin >> subject;
    cout << "Enter quiz: ";
    cin.ignore();
    getline(cin, quiz);
    school->addQuiz(studentUsername, subject, quiz);
    cout << "Quiz added successfully.\n";
}
void Teacher::addNotification() {
    string studentUsername, subject, notification;
    cout << "Enter student username: ";
    cin >> studentUsername;
    cout << "Enter subject: ";
    cin >> subject;
    cout << "Enter notification: ";
    cin.ignore();
    getline(cin, notification);
    school->addNotification(studentUsername, subject, notification);
    cout << "Notification added successfully.\n";
}


void Student::portal() {
    int choice;
    do {
        cout << "\nStudent Portal\n";
        cout << "1. Lectures\n";
        cout << "2. Quizzes\n";
        cout << "3. Assignments\n";
        cout << "4. Grades\n";
        cout << "5. Reports\n";
        cout<<"6. notification\n";
        cout << "0. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Lectures Section\n";
                displayLectures();
                break;
            case 2:
                cout << "Quizzes Section\n";
                displayQuiz();
                break;
            case 3:
                cout << "Assignments Section\n";
                displayAssignments();
                break;
            case 4:
                cout << "Grades Section\n";
                displayQuizMarks();
                break;
            case 5:
                cout << "Reports Section\n";
                displayReport();
                break;
                case 6:
                cout << "notification Section\n";
                displayNotifications();


            case 0:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

void Student::displayQuizMarks() const {
    const map<string, int>* marks = school->getQuizMarks(getUsername());
    if (marks) {
        cout << "Quiz Marks:\n";
        for (const auto& pair : *marks) {
            cout << "Subject: " << pair.first << ", Mark: " << pair.second << endl;
        }
    } else {
        cout << "No quiz marks found.\n";
    }
}

void Student::displayReport() const {
    const map<string, string>* report = school->getReports(getUsername());
    if (report) {
        cout << "Reports:\n";
        for (const auto& pair : *report) {
            cout << "Subject: " << pair.first << ", Report: " << pair.second << endl;
        }
    } else {
        cout << "No reports found.\n";
    }
}

void Student::displayLectures() const {
    const map<string, string>* lectures = school->getLectures(getUsername());
    if (lectures) {
        cout << "Lectures:\n";
        for (const auto& pair : *lectures) {
            cout << "Subject: " << pair.first << ", Lecture: " << pair.second << endl;
        }
    } else {
        cout << "No lectures found.\n";
    }
}

void Student::displayAssignments() const {
    const map<string, string>* assignments = school->getAssignments(getUsername());
    if (assignments) {
        cout << "Assignments:\n";
        for (const auto& pair : *assignments) {
            cout << "Subject: " << pair.first << ", Assignment: " << pair.second << endl;
        }
    } else {
        cout << "No assignments found.\n";
    }
}

void Student::displayQuiz() const {
    const map<string, string>* quizzes = school->getQuizzes(getUsername());
    if (quizzes) {
        cout << "Quizzes:\n";
        for (const auto& pair : *quizzes) {
            cout << "Subject: " << pair.first << ", Quiz: " << pair.second << endl;
        }
    } else {
        cout << "No quizzes found.\n";
    }
}
void Student::displayNotifications() const {
    const map<string, string>* notifications = school->getNotifications(getUsername());
    if (notifications) {
        cout << "Notifications:\n";
        for (const auto& pair : *notifications) {
            cout << "Subject: " << pair.first << ", Notification: " << pair.second << endl;
        }
    } else {
        cout << "No notifications found.\n";
    }
}
void Admin::portal() {
    int choice;
    do {
        cout << "\nAdmin Portal\n";
        cout << "1. Add Course\n";
        cout << "2. Add Teacher\n";
        cout << "3. Add Student\n";
        cout << "4. Display Courses\n";
        cout << "0. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                int courseId;
                string courseName;
                cout << "Enter course ID: ";
                cin >> courseId;
                cout << "Enter course name: ";
                cin.ignore();
                getline(cin, courseName);
                school->addCourse(Course(courseId, courseName));
                cout << "Course added successfully.\n";
                break;
            }
            case 2: {
                string username, password;
                int id;
                cout << "Enter teacher username: ";
                cin >> username;
                cout << "Enter teacher password: ";
                cin >> password;
                cout << "Enter teacher ID: ";
                cin >> id;
                User* teacher = new Teacher(username, password, id, school);
                school->addUser(teacher);
                cout << "Teacher added successfully.\n";
                break;
            }
            case 3: {
                string username, password;
                int id;
                cout << "Enter student username: ";
                cin >> username;
                cout << "Enter student password: ";
                cin >> password;
                cout << "Enter student ID: ";
                cin >> id;
                User* student = new Student(username, password, id, school);
                school->addUser(student);
                cout << "Student added successfully.\n";
                break;
            }
            case 4:
                cout << "Courses:\n";
                school->displayCourses();
                break;
            case 0:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

int main() {
    cout << "                                               _______________________" << endl;
    cout << "                                              /                       \\" << endl;
    cout << "                                             /         BULC            \\" << endl;
    cout << "                                            /___________________________\\" << endl;
    cout << "                                            |     _________  _________  |" << endl;
    cout << "                                            |    |         ||         | |" << endl;
    cout << "                                            |    |  _   _  ||  _   _  | |" << endl;
    cout << "                                            |    | | | | | || | | | | | |" << endl;
    cout << "                                            |    | |_| |_| || |_| |_| | |" << endl;
    cout << "                                            |    |         ||         | |" << endl;
    cout << "                                            |    |_________||_________| |" << endl;
    cout << "                                            |                           |" << endl;
    cout << "                                            |  _ _ _ _ _ _ _ _ _ _ _ _  |" << endl;
    cout << "                                            | |           |           | |" << endl;
    cout << "                                            | |    ]      |   ]       | |" << endl;
    cout << "                                            |_|___________|___________|_|" << endl;
    cout << "                                           /                             \\" << endl;
    cout << "                                          /          OOP PROJECT          \\" << endl;
    cout << "                                         /_________________________________\\" << endl;
    cout << "                                         |_________________________________|" << endl;

    School school;

    // Adding some test users
    school.addUser(new Student("student1", "pass123", 101, &school));
    school.addUser(new Teacher("teacher1", "pass456", 201, &school));
    school.addUser(new Admin("admin1", "pass789", 301, &school));

    // Adding some test courses
    school.addCourse(Course(1, "Mathematics"));
    school.addCourse(Course(2, "Physics"));
    school.addCourse(Course(3, "Chemistry"));

    int choice;
    do {
        cout << "\nSchool Management System\n";
        cout << "1. Login\n";
        cout << "2. Display Courses\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                school.login();
                break;
            case 2:
                school.displayCourses();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
  while (choice != 0);
return 0;
}


