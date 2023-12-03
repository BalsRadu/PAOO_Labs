#pragma once

// Include fișierul header pentru Logger și alte biblioteci necesare
#include "Logger.hpp"
#include <string>
#include <iostream>

// Clasa User reprezintă un utilizator în aplicație
class User {
public:
    // Constructor care inițializează un utilizator cu un ID și un nume
    User(int id, const std::string& name);
    // Metoda pentru conectarea la un server
    void connectToServer(const std::string& serverAddress, int serverPort);
    // Metoda pentru efectuarea unei acțiuni și trimiterea acesteia la server
    void performAction(const std::string& action);

    // Getter pentru ID-ul utilizatorului
    int getId() const;
    // Getter pentru numele utilizatorului
    std::string getName() const;

private:
    // Variabile private pentru stocarea detaliilor utilizatorului și a conexiunii sale
    int id_;
    std::string name_;
    int serverSocket_;
    // Un shared pointer pentru logger, folosit pentru înregistrarea activităților
    std::shared_ptr<Logger> userLogger_;
};