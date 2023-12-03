# Definirea bibliotecii
add_library(resursa STATIC UserRegister.cpp UserRegister.hpp)

# Setarea directoriilor de include pentru această bibliotecă
target_include_directories(resursa PUBLIC
                           "${PROJECT_SOURCE_DIR}/resursa"
                           "${PROJECT_SOURCE_DIR}/logger"
                           )

# Linkarea bibliotecii cu alte biblioteci
target_link_libraries(resursa PUBLIC logging)