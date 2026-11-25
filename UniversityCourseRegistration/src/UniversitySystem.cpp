#include "UniversitySystem.h"
#include "RegistrationException.h"
#include <iostream>
#include <algorithm>

using namespace std;

Course* UniversitySystem::findCourse(const string& id) {
    for (auto& course : courses)
        if (course.getCourseId() == id) return &course;
    return nullptr;
}

bool UniversitySystem::studentExists(const string& id) const {
    for (const auto& student : students)
        if (student.getId() == id) return true;
    return false;
}

int UniversitySystem::registeredCount(const string& id) const {
    int count = 0;
    for (const auto& r : registrations)
        if (r.getCourseId() == id) ++count;
    return count;
}

UniversitySystem::UniversitySystem() {
    const bool studentFileAlreadyExists = fileManager.studentsFileExists();
    students = fileManager.loadStudents();
    if (!studentFileAlreadyExists) {
        students.emplace_back("20253623","Hossain Md Niber","Intelligence Computing");
        students.emplace_back("20253633","Ahmed Md Miraj","Intelligence Computing");
        students.emplace_back("20253657","Gautam Dilip","Intelligence Computing");
        students.emplace_back("20253638","Thapa Rabin","Intelligence Computing");
        fileManager.saveStudents(students);
    }

    courses.emplace_back("WP2002","Web Programming 2",3,30);
    courses.emplace_back("OOP2002","Object Oriented Programming 2",3,25);
    courses.emplace_back("DS004","Data Structures",3,20);
    courses.emplace_back("LA001","Linear Algebra",3,35);

    vector<Course> savedCourses = fileManager.loadCourses();
    if (!savedCourses.empty()) courses = savedCourses;

    vector<Registration> savedRegistrations = fileManager.loadRegistrations();
    for (const auto& registration : savedRegistrations) {
        if (studentExists(registration.getStudentId()) &&
            findCourse(registration.getCourseId())) {
            registrations.push_back(registration);
        }
    }
}

void UniversitySystem::showCourses() const {
    cout << "\n===== AVAILABLE COURSES =====\n";
    if (courses.empty()) cout << "No courses available.\n";
    for (const auto& c : courses)
        c.display(registeredCount(c.getCourseId()));
}

bool UniversitySystem::hasStudent(const string& id) const {
    return studentExists(id);
}

void UniversitySystem::addStudent(const Student& student) {
    if (student.getId().empty() || student.getName().empty() ||
        student.getMajor().empty())
        throw RegistrationException("Student information cannot be empty!");
    if (studentExists(student.getId()))
        throw RegistrationException("Student ID already exists!");
    students.push_back(student);
    fileManager.saveStudents(students);
    cout << "Student added successfully!\n";
}

void UniversitySystem::removeStudent(const string& id) {
    if (!studentExists(id))
        throw RegistrationException("Student not found!");

    // Remove the student's course registrations as well as the profile.
    registrations.erase(remove_if(registrations.begin(), registrations.end(),
        [&](const Registration& r) { return r.getStudentId() == id; }),
        registrations.end());
    students.erase(remove_if(students.begin(), students.end(),
        [&](const Student& student) { return student.getId() == id; }),
        students.end());

    fileManager.saveStudents(students);
    fileManager.saveRegistrations(registrations);
    cout << "Student and their course registrations removed successfully!\n";
}

void UniversitySystem::showStudents() const {
    cout << "\n===== STUDENTS =====\n";
    for (const auto& s : students) s.displayInfo();
}

void UniversitySystem::registerCourse(const string& sid, const string& cid) {
    if (!studentExists(sid)) throw RegistrationException("Student not found!");
    Course* course = findCourse(cid);
    if (!course) throw RegistrationException("Course not found!");
    for (const auto& r : registrations)
        if (r.getStudentId() == sid && r.getCourseId() == cid)
            throw RegistrationException("Already registered!");
    if (registeredCount(cid) >= course->getCapacity())
        throw RegistrationException("Course is full!");
    registrations.emplace_back(sid,cid);
    fileManager.saveRegistrations(registrations);
    cout << "Registration successful!\n";
}

void UniversitySystem::dropCourse(const string& sid, const string& cid) {
    auto it = find_if(registrations.begin(), registrations.end(),
        [&](const Registration& r) {
            return r.getStudentId() == sid && r.getCourseId() == cid;
        });
    if (it == registrations.end())
        throw RegistrationException("Registration not found!");
    registrations.erase(it);
    fileManager.saveRegistrations(registrations);
    cout << "Course dropped successfully!\n";
}

void UniversitySystem::showSchedule(const string& sid) const {
    cout << "\n===== MY SCHEDULE =====\n";
    bool found = false;
    for (const auto& r : registrations) {
        if (r.getStudentId() == sid) {
            for (const auto& c : courses) {
                if (c.getCourseId() == r.getCourseId()) {
                    c.display(registeredCount(c.getCourseId()));
                    found = true;
                }
            }
        }
    }
    if (!found) cout << "No registered courses.\n";
}

void UniversitySystem::addCourse(const Course& course) {
    if (course.getCourseId().empty() || course.getTitle().empty() ||
        course.getCredits() < 1 || course.getCredits() > 6 ||
        course.getCapacity() < 1)
        throw RegistrationException("Invalid course data!");
    if (findCourse(course.getCourseId()))
        throw RegistrationException("Course already exists!");
    courses.push_back(course);
    fileManager.saveCourses(courses);
    cout << "Course added successfully!\n";
}

void UniversitySystem::updateCourse(const string& id, const string& title,
                                    int credits, int capacity) {
    Course* course = findCourse(id);
    if (!course) throw RegistrationException("Course not found!");
    if (title.empty() || credits < 1 || credits > 6 ||
        capacity < registeredCount(id) || capacity < 1)
        throw RegistrationException("Invalid course information!");
    course->setTitle(title);
    course->setCredits(credits);
    course->setCapacity(capacity);
    fileManager.saveCourses(courses);
    cout << "Course updated successfully!\n";
}

void UniversitySystem::deleteCourse(const string& id) {
    if (!findCourse(id)) throw RegistrationException("Course not found!");
    if (registeredCount(id) > 0)
        throw RegistrationException("Students are registered. Drop them first!");
    courses.erase(remove_if(courses.begin(), courses.end(),
        [&](const Course& c) { return c.getCourseId() == id; }), courses.end());
    fileManager.saveCourses(courses);
    cout << "Course deleted successfully!\n";
}
