# Definirea bibliotecii
add_library(user STATIC User.cpp User.hpp)

# Setarea directoriilor de include pentru această bibliotecă
target_include_directories(user PUBLIC
                           "${PROJECT_SOURCE_DIR}/user"
                           "${PROJECT_SOURCE_DIR}/logger"
                           )
# Linkarea bibliotecii cu alte biblioteci
target_link_libraries(user PUBLIC logging)