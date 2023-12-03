#include "Logger.hpp"
#include <filesystem>
#include <iostream>

// Constructor
Logger::Logger(const std::string& file_name) {
    // Extrage numele folderului din calea fișierului
    std::filesystem::path logPath(file_name);
    auto logDir = logPath.parent_path();

    // Creați folderul dacă nu există
    if (!logDir.empty() && !std::filesystem::exists(logDir)) {
        std::filesystem::create_directories(logDir);
    }

    // Deschideți fișierul de log
    log_file_.open(file_name, std::ios::app);
    if (!log_file_.is_open()) {
        // Afisează un mesaj de eroare dacă fișierul nu poate fi deschis
        std::cerr << "Eroare: Nu s-a putut deschide fișierul de log: " << file_name << std::endl;
    }
}

// Destructor
Logger::~Logger() {
    // Închide fișierul de log dacă este deschis
    if (log_file_.is_open()) {
        log_file_.close();
    }
}

// Funcție pentru logarea unui mesaj
void Logger::log(const std::string& message) {
    // Blochează mutex-ul în timpul scrierii pentru a evita conflictele între thread-uri
    std::lock_guard<std::mutex> lock(mutex_);
    if (log_file_.is_open()) {
        // Scrie mesajul în fișier
        log_file_ << message << std::endl;
    } else {
        // Afisează un mesaj de eroare dacă fișierul de log nu este deschis
        std::cerr << "Eroare: Fișierul de log nu este deschis. Mesaj: " << message << std::endl;
    }
}