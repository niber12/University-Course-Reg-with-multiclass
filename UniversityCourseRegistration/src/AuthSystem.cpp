#include "AuthSystem.h"

bool AuthSystem::studentLogin(const std::string& id,
                              const std::string& password) const {
    const auto passwords = fileManager.loadStudentPasswords();
    auto account = passwords.find(id);
    return account != passwords.end() && account->second == password;
}

bool AuthSystem::changeStudentPassword(const std::string& id,
                                       const std::string& currentPassword,
                                       const std::string& newPassword) const {
    auto passwords = fileManager.loadStudentPasswords();
    auto account = passwords.find(id);
    if (account == passwords.end() || account->second != currentPassword)
        return false;
    if (newPassword.size() < 4 || newPassword.find('|') != std::string::npos ||
        newPassword.find('\n') != std::string::npos ||
        newPassword.find('\r') != std::string::npos ||
        newPassword == currentPassword)
        return false;

    account->second = newPassword;
    fileManager.saveStudentPasswords(passwords);
    return true;
}

bool AuthSystem::adminLogin(const std::string& id,
                            const std::string& password) const {
    return id == "A1001" && password == "admin123";
}


bool AuthSystem::studentAccountExists(const std::string& id) const {
    const auto passwords = fileManager.loadStudentPasswords();
    return passwords.find(id) != passwords.end();
}

bool AuthSystem::addStudentAccount(const std::string& id,
                                  const std::string& password) const {
    if (id.empty() || password.size() < 4 ||
        password.find('|') != std::string::npos ||
        password.find('\n') != std::string::npos ||
        password.find('\r') != std::string::npos)
        return false;

    auto passwords = fileManager.loadStudentPasswords();
    if (passwords.find(id) != passwords.end()) return false;
    passwords[id] = password;
    fileManager.saveStudentPasswords(passwords);
    return true;
}


bool AuthSystem::removeStudentAccount(const std::string& id) const {
    auto passwords = fileManager.loadStudentPasswords();
    auto account = passwords.find(id);
    if (account == passwords.end()) return false;
    passwords.erase(account);
    fileManager.saveStudentPasswords(passwords);
    return true;
}
