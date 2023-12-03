# Definirea bibliotecii
add_library(server STATIC ApacheServer.cpp ApacheServer.hpp)

# Setarea directoriilor de include pentru această bibliotecă
target_include_directories(server PUBLIC
                           "${PROJECT_SOURCE_DIR}/server"
                           "${PROJECT_SOURCE_DIR}/logger"
                           "${PROJECT_SOURCE_DIR}/user"
                           "${PROJECT_SOURCE_DIR}/resursa"
                           )

# Linking (legarea) bibliotecii server cu bibliotecile de care depinde
target_link_libraries(server PUBLIC logging user resursa)
