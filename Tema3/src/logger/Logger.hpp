#pragma once

// Include bibliotecile necesare
#include <string>
#include <mutex>
#include <memory>
#include <fstream>

// Definirea clasei Logger
class Logger {
public:
    // Constructor care acceptă numele fișierului de log
    Logger(const std::string& file_name);
    // Destructor
    ~Logger();

    // Funcție pentru logarea unui mesaj
    void log(const std::string& message);

private:
    // Mutex pentru a asigura thread-safety la scrierea în fișier
    std::mutex mutex_;
    // Stream pentru fișierul de log
    std::ofstream log_file_;
};
