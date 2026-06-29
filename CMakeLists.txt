cmake_minimum_required(VERSION 3.16)
project(computerVision LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile_commands.json for IDE code completion/resolve
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Print OpenCV details for confirmation
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

# Define executable and its source files
add_executable(computerVision
    src/main.cpp
    src/camera/Camera.cpp
    src/detection/FaceDetector.cpp
    src/tracking/FaceTracker.cpp
    src/control/PID.cpp
    src/control/Controller.cpp
    src/serial/Serial.cpp
    src/utils/FPSCounter.cpp
)

# Include directories
target_include_directories(computerVision PRIVATE include)

# Link OpenCV libraries
target_link_libraries(computerVision PRIVATE ${OpenCV_LIBS})
