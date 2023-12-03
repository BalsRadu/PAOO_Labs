#include "UserRegister.hpp"
#include <iostream>

// Constructorul clasei UserRegister
UserRegister::UserRegister() {
    // Inițializează logger-ul pentru înregistrarea utilizatorilor
    registerLogger_ = std::make_shared<Logger>("register.log");
}

// Metodă pentru adăugarea unui nou utilizator
void UserRegister::addUser(int userId, const std::string& userName) {
    std::lock_guard<std::mutex> lock(mutex_);
    userNames_[userId] = userName;

    // Loghează adăugarea utilizatorului
    registerLogger_->log("Utilizatorul cu ID-ul " + std::to_string(userId) + " și numele " + userName + " a fost adăugat.");
}

// Metodă pentru ștergerea unui utilizator
void UserRegister::removeUser(int userId) {
    std::lock_guard<std::mutex> lock(mutex_);
    userNames_.erase(userId);

    // Loghează ștergerea utilizatorului
    registerLogger_->log("Utilizatorul cu ID-ul " + std::to_string(userId) + " a fost șters.");
}

// Metodă pentru actualizarea numelui unui utilizator
void UserRegister::updateUser(int userId, const std::string& newUserName) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (userNames_.find(userId) != userNames_.end()) {
        userNames_[userId] = newUserName;

        // Loghează actualizarea numelui utilizatorului
        registerLogger_->log("Numele utilizatorului cu ID-ul " + std::to_string(userId) + " a fost actualizat cu: " + newUserName);
    }
}

// Verifică dacă un utilizator este înregistrat
bool UserRegister::isUserRegistered(int userId) {
    std::lock_guard<std::mutex> lock(mutex_);
    return userNames_.find(userId) != userNames_.end();
}

// Returnează numele utilizatorului, dacă acesta este înregistrat
std::string UserRegister::getUserName(int userId) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (userNames_.find(userId) != userNames_.end()) {
        return userNames_[userId];
    }
    // Dacă nu este găsit, returnează un mesaj corespunzător
    return "Numele utilizatorului nu este disponibil.";
}