#ifndef UNIVERSITY_SYSTEM_H
#define UNIVERSITY_SYSTEM_H
#include "Course.h"
#include "Student.h"
#include "Registration.h"
#include "FileManager.h"
#include <vector>
#include <string>

class UniversitySystem {
private:
    std::vector<Course> courses;
    std::vector<Student> students;
    std::vector<Registration> registrations;
    FileManager fileManager;

    Course* findCourse(const std::string& id);
    bool studentExists(const std::string& id) const;
    int registeredCount(const std::string& courseId) const;

public:
    UniversitySystem();
    void showCourses() const;
    void showStudents() const;
    bool hasStudent(const std::string& id) const;
    void addStudent(const Student& student);
    void removeStudent(const std::string& id);
    void registerCourse(const std::string& studentId, const std::string& courseId);
    void dropCourse(const std::string& studentId, const std::string& courseId);
    void showSchedule(const std::string& studentId) const;
    void addCourse(const Course& course);
    void updateCourse(const std::string& id, const std::string& title,
                      int credits, int capacity);
    void deleteCourse(const std::string& id);
};
#endif
