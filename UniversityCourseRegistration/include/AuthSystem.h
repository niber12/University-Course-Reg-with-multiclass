#ifndef AUTH_SYSTEM_H
#define AUTH_SYSTEM_H
#include "FileManager.h"
#include <string>
#include <map>

class AuthSystem {
private:
    FileManager fileManager;
public:
    bool studentLogin(const std::string& id, const std::string& password) const;
    bool changeStudentPassword(const std::string& id,
                               const std::string& currentPassword,
                               const std::string& newPassword) const;
    bool adminLogin(const std::string& id, const std::string& password) const;
    bool studentAccountExists(const std::string& id) const;
    bool addStudentAccount(const std::string& id, const std::string& password) const;
    bool removeStudentAccount(const std::string& id) const;
};
#endif
