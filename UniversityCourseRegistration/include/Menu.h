#ifndef MENU_H
#define MENU_H
#include "UniversitySystem.h"
#include "AuthSystem.h"
#include <string>

void studentMenu(UniversitySystem& system, AuthSystem& auth, const std::string& studentId);
void adminMenu(UniversitySystem& system, AuthSystem& auth);
#endif
