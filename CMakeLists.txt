cmake_minimum_required(VERSION 3.15)
project(DapperApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2 packages
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Include directories
include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/include
)

# Collect sources for DapperUI library
file(GLOB_RECURSE DAPPERUI_SOURCES
        src/UI/*.cpp
        src/Systems/*.cpp
        src/Scenes/*.cpp
        src/DapperCore.cpp
        src/ElementManager.cpp
)

file(GLOB_RECURSE DAPPERUI_HEADERS
        include/DapperUI/*.h
)

# Build static library
add_library(DapperUI STATIC
        ${DAPPERUI_SOURCES}
        ${DAPPERUI_HEADERS}  # headers are optional here
)

target_link_libraries(DapperUI
        ${SDL2_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
)

# Link pthread if Unix
if(UNIX)
    target_link_libraries(DapperUI pthread)
endif()

# Build your executable
add_executable(myapp testMain.cpp)

# Link executable against DapperUI and SDL libraries
target_link_libraries(myapp
        DapperUI
        ${SDL2_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
)

# Add include directories for myapp target (modern CMake way)
target_include_directories(myapp PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

install(DIRECTORY include/DapperUI DESTINATION include)
install(TARGETS DapperUI ARCHIVE DESTINATION lib)
