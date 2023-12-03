#include "ApacheServer.hpp"
#include <iostream>
#include <unistd.h> // pentru close
#include <cstring>  // pentru memset
#include <arpa/inet.h>

ApacheServer::ApacheServer(int port) : port_(port), running_(false), shutdownSocket_(-1) {
    // Inițializarea logger-ului
    serverLogger_ = std::make_shared<Logger>("server.log");

    // Inițializarea semaforului pentru gestionarea conexiunilor
    sem_init(&connectionSemaphore_, 0, 10); // Limita de 10 conexiuni simultane

    // Inițializarea registru de clienți
    userRegister_ = std::make_unique<UserRegister>();

    // Inițializarea socketului serverului
    serverSocket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket_ == -1) {
        serverLogger_->log("EROARE: Nu s-a putut crea socketul");
        exit(EXIT_FAILURE);
    }

    // Setarea adresei socketului
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port_);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Legarea socketului
    if (bind(serverSocket_, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        serverLogger_->log("EROARE: Legarea socketului a eșuat");
        exit(EXIT_FAILURE);
    }

    // Ascultarea pe socket
    if (listen(serverSocket_, 10) < 0) {
        serverLogger_->log("EROARE: Eroare la ascultarea pe socket");
        exit(EXIT_FAILURE);
    }

    // Logarea inițializării serverului
    serverLogger_->log("Serverul a fost inițializat.");
}

ApacheServer::~ApacheServer() {
    stop();

    if (serverSocket_ != -1) {
        close(serverSocket_);
    }

    if (shutdownSocket_ != -1) {
        close(shutdownSocket_);
    }
    sem_destroy(&connectionSemaphore_); // Distruge semaforul
}

void ApacheServer::start() {
    running_ = true;
    serverLoopThread = std::thread(&ApacheServer::serverLoop, this);  // Change this line

}


void ApacheServer::stop() {
    serverLogger_->log("Serverul se închide.");

    initiateShutdown();
    running_ = false;

    for (auto& thread : threads_) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    if (serverLoopThread.joinable()) {
        serverLoopThread.join();
    }

}

void ApacheServer::initiateShutdown() {
    shutdownSocket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (shutdownSocket_ == -1) {
        serverLogger_->log("EROARE: Nu s-a putut crea socketul de shutdown");
        return;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port_);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(shutdownSocket_, (struct sockaddr*)&addr, sizeof(addr));
}



void ApacheServer::serverLoop() {
    while (running_) {
        struct sockaddr_in userAddr;
        socklen_t userAddrLen = sizeof(userAddr);
        int userSocket = accept(serverSocket_, (struct sockaddr *)&userAddr, &userAddrLen);

        if (userSocket < 0) {
            serverLogger_->log("EROARE: Eroare la acceptarea conexiunii userului");
            continue;
        }
        if (!running_) {
            break;
        }

        threads_.emplace_back(&ApacheServer::handleUser, this, userSocket);
    }
}


int ApacheServer::getUserIdFromRequest(char* request) {
    char *requestCopy = new char[strlen(request) + 1];
    strcpy(requestCopy, request);

    char* idStr = strtok(requestCopy, " ");
    if (idStr == NULL) {
        return -1;
    }
    int userId = std::stoi(idStr);
    return userId;
}

std::string ApacheServer::getUserNameFromRequest(char* request) {
    char *requestCopy = new char[strlen(request) + 1];
    strcpy(requestCopy, request);

    strtok(requestCopy, " "); // Ignoră ID-ul
    char* userName = strtok(NULL, " ");
    if (userName == NULL) {
        return "Unknown";
    }

    return std::string(userName);
}


void ApacheServer::handleUser(int userSocket) {
    sem_wait(&connectionSemaphore_); // Așteaptă până când un slot devine disponibil

    // Logare la începutul gestionării unui user
    serverLogger_->log("A new user is being handled.");

    char buffer[1024] = {0};
    recv(userSocket, buffer, sizeof(buffer), 0);

    int userId = getUserIdFromRequest(buffer);
    std::string userName = getUserNameFromRequest(buffer);

    auto user = std::make_shared<User>(userId, userName);
    users_.push_back(user);

    if (!userRegister_->isUserRegistered(user->getId())) {
        userRegister_->addUser(user->getId(), user->getName());
    }

    // Procesează solicitarea și generează un răspuns
    std::string response = "The user " + user->getName() + " with ID " + std::to_string(user->getId()) + " has been processed.";
    send(userSocket, response.c_str(), response.length(), 0);

    // Logare la încheierea gestionării userului
    serverLogger_->log("Userul a fost gestionat și deconectat.");

    sem_post(&connectionSemaphore_); // Eliberează slotul
}
