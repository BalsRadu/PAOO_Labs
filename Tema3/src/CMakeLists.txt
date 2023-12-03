# Setarea versiunii minime de CMake necesare pentru a rula acest script
cmake_minimum_required(VERSION 3.10)

# Definirea numelui și versiunii proiectului
project(DummyApacheModel VERSION 1.0)

# Adăugarea subdirectorului care conține implementarea serverului Apache
add_subdirectory(server)

# Adăugarea subdirectorului care conține implementarea user
add_subdirectory(user)

# Adăugarea subdirectorului care conține implementarea resursei
add_subdirectory(resursa)

# Adăugarea subdirectorului care conține implementarea logger
add_subdirectory(logger)

# Crearea executabilului principal al proiectului
add_executable(DummyApacheModel main.cpp)

# Linking (legarea) executabilului cu bibliotecile create
target_link_libraries(DummyApacheModel PUBLIC server user resursa logging)

# Configurarea directoriilor de include pentru a permite proiectului să găsească fișierele header necesare
target_include_directories(DummyApacheModel PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/server"
                           "${PROJECT_SOURCE_DIR}/user"
                           "${PROJECT_SOURCE_DIR}/resursa"
                           "${PROJECT_SOURCE_DIR}/logger"
                           )

# Setarea standardului C++ la C++17
set_target_properties(DummyApacheModel PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
)

