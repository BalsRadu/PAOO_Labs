#include "User.hpp"

#include <unistd.h>  // pentru funcția close
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Constructorul clasei User
User::User(int id, const std::string& name) : id_(id), name_(name), serverSocket_(-1) {
    // Inițializează logger-ul pentru utilizator
    userLogger_ = std::make_shared<Logger>("user.log");
}

// Metoda pentru conectarea la un server
void User::connectToServer(const std::string& serverAddress, int serverPort) {
    // Creează un socket pentru conexiune
    serverSocket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket_ == -1) {
        // Loghează eroarea dacă socketul nu poate fi creat
        userLogger_->log("EROARE: Eroare la crearea socketului utilizatorului");
        return;
    }

    // Setează adresa și portul serverului
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    inet_pton(AF_INET, serverAddress.c_str(), &serverAddr.sin_addr);

    // Încearcă să se conecteze la server
    if (connect(serverSocket_, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        // Loghează eroarea dacă conexiunea eșuează
        userLogger_->log("EROARE: Conectarea la server a eșuat");
        return;
    }

    // Loghează succesul conexiunii
    userLogger_->log("Utilizatorul " + name_ + " s-a conectat la serverul " + serverAddress);
}

// Metoda pentru efectuarea unei acțiuni și comunicarea cu serverul
void User::performAction(const std::string& action) {
    // Trimite acțiunea la server
    send(serverSocket_, action.c_str(), action.length(), 0);
    char buffer[1024] = {0};
    // Primește răspunsul de la server
    recv(serverSocket_, buffer, 1024, 0);

    // Loghează răspunsul primit
    userLogger_->log("Răspuns primit de la server: " + std::string(buffer));

    // Închide socketul după finalizarea acțiunii
    close(serverSocket_);
}

// Getter pentru ID-ul utilizatorului
int User::getId() const {
    return id_;
}

// Getter pentru numele utilizatorului
std::string User::getName() const {
    return name_;
}