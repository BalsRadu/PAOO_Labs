#include "ApacheServer.hpp"
#include "User.hpp"
#include "UserRegister.hpp"
#include "Logger.hpp"

#include <iostream>
#include <memory>
#include <thread>
#include <vector>

int main() {
    // Inițializarea serverului
    ApacheServer server(8080);
    server.start();

    // Crearea și inițializarea unor utilizatori
    std::vector<std::shared_ptr<User>> users;
    for (int i = 1; i <= 5; ++i) {

        auto user = std::make_shared<User>(i, "User" + std::to_string(i));
        users.push_back(user);
        user->connectToServer("127.0.0.1", 8080);

        // Trimiterea ID-ului și numelui utilizatorului în formatul așteptat de server
        std::string userMessage = std::to_string(i) + " " + user->getName();
        user->performAction(userMessage);
    }

    return 0;
}
