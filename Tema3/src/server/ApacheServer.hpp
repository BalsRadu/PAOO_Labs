#pragma once

// Include clasele și bibliotecile necesare
#include "User.hpp"
#include "UserRegister.hpp"
#include "Logger.hpp"

#include <thread>
#include <vector>
#include <memory>
#include <atomic>
#include <sys/socket.h>
#include <netinet/in.h>
#include <mutex>
#include <semaphore.h>

// Clasa ApacheServer reprezintă un server simplificat
class ApacheServer {
public:
    // Constructor și destructor
    ApacheServer(int port);
    ~ApacheServer();

    // Metode pentru pornirea și oprirea serverului
    void start();
    void stop();

private:
    // Metode private pentru gestionarea conexiunilor și a serverului
    void handleUser(int userSocket);
    void serverLoop();
    void initiateShutdown();
    int getUserIdFromRequest(char* request);
    std::string getUserNameFromRequest(char* request);

    // Variabile pentru socketul serverului, port, și controlul fluxului
    int serverSocket_;
    int shutdownSocket_;
    int port_;
    std::atomic<bool> running_;
    std::vector<std::thread> threads_;
    std::thread serverLoopThread;
    std::mutex resourceMutex_;
    std::shared_ptr<Logger> serverLogger_;
    sem_t connectionSemaphore_;
    std::vector<std::shared_ptr<User>> users_;
    std::shared_ptr<UserRegister> userRegister_;
};