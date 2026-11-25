#include "Menu.h"
#include "InputHelper.h"
#include "RegistrationException.h"
#include <iostream>
#include <limits>

using namespace std;

void studentMenu(UniversitySystem& system, AuthSystem& auth, const string& sid) {
    int choice = -1;
    do {
        cout << "\n===== STUDENT MENU =====\n"
             << "1. View Courses\n2. Register Course\n3. Drop Course\n"
             << "4. View My Schedule\n5. Change Password\n0. Logout\n";
        choice = readInt("Enter choice: ");
        try {
            string cid;
            switch (choice) {
                case 1: system.showCourses(); break;
                case 2:
                    system.showCourses();
                    cout << "Enter Course ID: "; cin >> cid;
                    system.registerCourse(sid,cid); break;
                case 3:
                    system.showSchedule(sid);
                    cout << "Enter Course ID: "; cin >> cid;
                    system.dropCourse(sid,cid); break;
                case 4: system.showSchedule(sid); break;
                case 5: {
                    string currentPassword, newPassword, confirmPassword;
                    cout << "Current Password: "; cin >> currentPassword;
                    cout << "New Password (at least 4 characters): "; cin >> newPassword;
                    cout << "Confirm New Password: "; cin >> confirmPassword;
                    if (newPassword != confirmPassword) {
                        cout << "New passwords do not match!\n";
                    } else if (auth.changeStudentPassword(sid, currentPassword, newPassword)) {
                        cout << "Password changed successfully! Please use your new password next time.\n";
                    } else {
                        cout << "Password change failed. Check your current password and ensure the new password has at least 4 characters and is different.\n";
                    }
                    break;
                }
                case 0: cout << "Logging out...\n"; break;
                default: cout << "Invalid choice!\n";
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << '\n';
        }
    } while (choice != 0);
}

void adminMenu(UniversitySystem& system, AuthSystem& auth) {
    int choice = -1;
    do {
        cout << "\n===== ADMIN MENU =====\n"
             << "1. View Courses\n2. Add Course\n3. Update Course\n"
             << "4. Delete Course\n5. View Students\n6. Add Student\n"
             << "7. Remove Student\n0. Logout\n";
        choice = readInt("Enter choice: ");
        try {
            string id, title;
            int credits, capacity;
            switch (choice) {
                case 1: system.showCourses(); break;
                case 2:
                    cout << "Course ID: "; cin >> id;
                    cout << "Course Title: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin,title);
                    credits = readInt("Credits: ");
                    capacity = readInt("Capacity: ");
                    system.addCourse(Course(id,title,credits,capacity)); break;
                case 3:
                    system.showCourses();
                    cout << "Course ID: "; cin >> id;
                    cout << "New Title: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin,title);
                    credits = readInt("New Credits: ");
                    capacity = readInt("New Capacity: ");
                    system.updateCourse(id,title,credits,capacity); break;
                case 4:
                    system.showCourses();
                    cout << "Course ID to delete: "; cin >> id;
                    system.deleteCourse(id); break;
                case 5: system.showStudents(); break;
                case 6: {
                    string studentId, studentName, major, password, confirmPassword;
                    cout << "New Student ID: "; cin >> studentId;
                    cout << "Student Full Name: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, studentName);
                    cout << "Department / Major: "; getline(cin, major);
                    cout << "Initial Password (at least 4 characters): "; cin >> password;
                    cout << "Confirm Password: "; cin >> confirmPassword;

                    if (password != confirmPassword) {
                        cout << "Passwords do not match! Student was not added.\n";
                    } else if (system.hasStudent(studentId) || auth.studentAccountExists(studentId)) {
                        cout << "Student ID already exists! Student was not added.\n";
                    } else if (password.size() < 4 || password.find('|') != string::npos) {
                        cout << "Password must be at least 4 characters and cannot contain |.\n";
                    } else {
                        system.addStudent(Student(studentId, studentName, major));
                        if (!auth.addStudentAccount(studentId, password))
                            cout << "Could not create the student login account.\n";
                        else
                            cout << "Student login account created successfully!\n";
                    }
                    break;
                }
                case 7: {
                    system.showStudents();
                    string studentId;
                    cout << "Student ID to remove: "; cin >> studentId;
                    if (!system.hasStudent(studentId)) {
                        cout << "Student not found.\n";
                        break;
                    }
                    char confirm;
                    cout << "Remove this student and all their registrations? (y/n): ";
                    cin >> confirm;
                    if (confirm == 'y' || confirm == 'Y') {
                        // Remove the login first, then the profile and related registrations.
                        if (!auth.removeStudentAccount(studentId)) {
                            cout << "Student login account not found; no profile was removed.\n";
                        } else {
                            system.removeStudent(studentId);
                        }
                    } else {
                        cout << "Removal cancelled.\n";
                    }
                    break;
                }
                case 0: cout << "Logging out...\n"; break;
                default: cout << "Invalid choice!\n";
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << '\n';
        }
    } while (choice != 0);
}
