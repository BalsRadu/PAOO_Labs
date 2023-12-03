# Definirea bibliotecii
add_library(logging STATIC Logger.cpp Logger.hpp)

# Setarea directoriilor de include pentru această bibliotecă
target_include_directories(logging PUBLIC
                           "${PROJECT_SOURCE_DIR}/logger"
                           )
