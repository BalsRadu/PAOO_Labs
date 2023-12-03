#pragma once

// Include fișierul header pentru Logger și alte biblioteci necesare
#include "Logger.hpp"
#include <string>
#include <mutex>
#include <unordered_map>

// Clasa UserRegister gestionează înregistrarea utilizatorilor
class UserRegister {
public:
    // Constructorul clasei
    UserRegister();
    // Metodă pentru adăugarea unui nou utilizator
    void addUser(int userId, const std::string& userName);
    // Metodă pentru ștergerea unui utilizator
    void removeUser(int userId);
    // Metodă pentru actualizarea numelui unui utilizator
    void updateUser(int userId, const std::string& newUserName);
    // Metodă pentru verificarea dacă un utilizator este înregistrat
    bool isUserRegistered(int userId);
    // Metodă pentru obținerea numelui unui utilizator
    std::string getUserName(int userId);

private:
    // Un map pentru stocarea perechilor de ID-uri și nume ale utilizatorilor
    std::unordered_map<int, std::string> userNames_;
    // Mutex pentru asigurarea thread-safety în operațiunile de actualizare a înregistrărilor
    std::mutex mutex_;
    // Un shared pointer pentru logger, folosit pentru înregistrarea activităților
    std::shared_ptr<Logger> registerLogger_;
};