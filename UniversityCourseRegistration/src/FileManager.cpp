#include "FileManager.h"
#include "RegistrationException.h"
#include <fstream>
#include <sstream>

using namespace std;

FileManager::FileManager(const string& coursesPath,
                         const string& registrationsPath,
                         const string& studentPasswordsPath,
                         const string& studentsPath)
    : coursesFile(coursesPath), registrationsFile(registrationsPath),
      studentPasswordsFile(studentPasswordsPath), studentsFile(studentsPath) {}

vector<Course> FileManager::loadCourses() const {
    vector<Course> courses;
    ifstream file(coursesFile);
    if (!file) return courses; // First run: the system will use its default courses.

    string line;
    while (getline(file, line)) {
        string id, title, creditText, capacityText;
        stringstream row(line);
        if (getline(row, id, '|') && getline(row, title, '|') &&
            getline(row, creditText, '|') && getline(row, capacityText)) {
            try {
                int credits = stoi(creditText);
                int capacity = stoi(capacityText);
                if (!id.empty() && !title.empty() && credits > 0 && capacity > 0)
                    courses.emplace_back(id, title, credits, capacity);
            } catch (...) {
                // Ignore an invalid TXT row and continue loading valid rows.
            }
        }
    }
    return courses;
}

void FileManager::saveCourses(const vector<Course>& courses) const {
    ofstream file(coursesFile);
    if (!file) throw RegistrationException("Cannot save " + coursesFile);

    for (const auto& course : courses) {
        file << course.getCourseId() << '|'
             << course.getTitle() << '|'
             << course.getCredits() << '|'
             << course.getCapacity() << '\n';
    }
    if (!file) throw RegistrationException("Error writing " + coursesFile);
}

vector<Registration> FileManager::loadRegistrations() const {
    vector<Registration> registrations;
    ifstream file(registrationsFile);
    if (!file) return registrations;

    string line;
    while (getline(file, line)) {
        string studentId, courseId;
        stringstream row(line);
        if (getline(row, studentId, '|') && getline(row, courseId) &&
            !studentId.empty() && !courseId.empty()) {
            registrations.emplace_back(studentId, courseId);
        }
    }
    return registrations;
}

void FileManager::saveRegistrations(
    const vector<Registration>& registrations) const {
    ofstream file(registrationsFile);
    if (!file) throw RegistrationException("Cannot save " + registrationsFile);

    for (const auto& registration : registrations) {
        file << registration.getStudentId() << '|'
             << registration.getCourseId() << '\n';
    }
    if (!file) throw RegistrationException("Error writing " + registrationsFile);
}


bool FileManager::studentsFileExists() const {
    ifstream file(studentsFile);
    return file.good();
}

vector<Student> FileManager::loadStudents() const {
    vector<Student> students;
    ifstream file(studentsFile);
    if (!file) return students;

    string line;
    while (getline(file, line)) {
        string id, name, major;
        stringstream row(line);
        if (getline(row, id, '|') && getline(row, name, '|') &&
            getline(row, major) && !id.empty() && !name.empty() && !major.empty()) {
            students.emplace_back(id, name, major);
        }
    }
    return students;
}

void FileManager::saveStudents(const vector<Student>& students) const {
    ofstream file(studentsFile);
    if (!file) throw RegistrationException("Cannot save " + studentsFile);
    for (const auto& student : students) {
        file << student.getId() << '|' << student.getName() << '|'
             << student.getMajor() << '\n';
    }
    if (!file) throw RegistrationException("Error writing " + studentsFile);
}

map<string, string> FileManager::loadStudentPasswords() const {
    map<string, string> passwords;
    ifstream file(studentPasswordsFile);
    const bool passwordFileExists = file.good();
    if (file) {
        string line;
        while (getline(file, line)) {
            string id, password;
            stringstream row(line);
            if (getline(row, id, '|') && getline(row, password) &&
                !id.empty() && !password.empty()) {
                passwords[id] = password;
            }
        }
    }

    // Create the original demonstration accounts only when the file does not exist.
    // An existing but empty file means the admin intentionally removed all accounts.
    if (!passwordFileExists) {
        passwords["20253623"] = "1234";
        passwords["20253633"] = "2345";
        passwords["20253657"] = "3456";
        passwords["20253638"] = "4567";
        saveStudentPasswords(passwords);
    }
    return passwords;
}

void FileManager::saveStudentPasswords(
    const map<string, string>& passwords) const {
    ofstream file(studentPasswordsFile);
    if (!file) throw RegistrationException("Cannot save " + studentPasswordsFile);
    for (const auto& account : passwords)
        file << account.first << '|' << account.second << '\n';
    if (!file) throw RegistrationException("Error writing " + studentPasswordsFile);
}
