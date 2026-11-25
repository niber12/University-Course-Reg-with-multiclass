#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "Course.h"
#include "Registration.h"
#include "Student.h"
#include <string>
#include <vector>
#include <map>

// The only class responsible for reading and writing the system's TXT files.
class FileManager {
private:
    std::string coursesFile;
    std::string registrationsFile;
    std::string studentPasswordsFile;
    std::string studentsFile;

public:
    FileManager(const std::string& coursesPath = "courses.txt",
                const std::string& registrationsPath = "registrations.txt",
                const std::string& studentPasswordsPath = "students.txt",
                const std::string& studentsPath = "student_profiles.txt");

    std::vector<Course> loadCourses() const;
    void saveCourses(const std::vector<Course>& courses) const;

    std::vector<Registration> loadRegistrations() const;
    void saveRegistrations(const std::vector<Registration>& registrations) const;

    std::vector<Student> loadStudents() const;
    bool studentsFileExists() const;
    void saveStudents(const std::vector<Student>& students) const;

    std::map<std::string, std::string> loadStudentPasswords() const;
    void saveStudentPasswords(const std::map<std::string, std::string>& passwords) const;
};

#endif
