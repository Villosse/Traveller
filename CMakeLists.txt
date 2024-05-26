# Minimum version of CMake required
cmake_minimum_required(VERSION 3.5)

# Project name
project(Travelling_SalesMan_Problem)

# auto add MOC, UIC and RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Make this a GUI application on Windows
if(WIN32)
  set(CMAKE_WIN32_EXECUTABLE ON)
endif()

# Find the QtWidgets library
find_package(Qt5 REQUIRED COMPONENTS Widgets)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "includes/*.h")

# Add the executable
add_executable(Travelling_SalesMan_Problem ${SOURCES} ${HEADERS})

# Set the output directory for the executable
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

# Add the Qt5 Widgets for linking
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

target_include_directories(${PROJECT_NAME}
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)
