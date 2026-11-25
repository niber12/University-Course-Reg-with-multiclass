#include "Student.h"
#include <iostream>

Student::Student(const std::string& id, const std::string& name,
                 const std::string& m)
    : User(id, name), major(m) {}

std::string Student::getMajor() const { return major; }

void Student::displayInfo() const {
    std::cout << "Student ID: " << getId()
              << " | Name: " << getName()
              << " | Major: " << major << '\n';
}
