cmake_minimum_required(VERSION 3.5)
project(typing_game VERSION 1.0.0 LANGUAGES CXX)

# Add your source files here
set(SOURCES
    src/main.cpp
    src/render.cpp
    src/gui.cpp
    # Add other source files as needed
)

# Specify the location of Raylib headers
include_directories(${CMAKE_SOURCE_DIR})

# Add the Raylib library
add_library(raylib STATIC IMPORTED)
set_target_properties(raylib PROPERTIES IMPORTED_LOCATION -lraylib)

# Create the executable
add_executable(typing_game ${SOURCES})

# Link your executable with the Raylib library
target_link_libraries(typing_game raylib)


# Set the installation directory
install(TARGETS typing_game DESTINATION bin)

# CPack configuration
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR NSIS)  # Set the generator to NSIS

include(CPack)
