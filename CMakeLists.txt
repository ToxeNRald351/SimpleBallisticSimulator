cmake_minimum_required(VERSION 3.16)
project(SimpleBallisticSimulator VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "/usr/local/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg")

# Specify vcpkg triplet (for example, for Linux)
set(VCPKG_TARGET_TRIPLET "x64-linux")

# Set entt_DIR to vcpkg installation directory
set(EnTT_DIR "/usr/local/vcpkg/installed/x64-linux/share/entt" CACHE STRING "EnTT directory")
set(Catch2_DIR "/usr/local/vcpkg/installed/x64-linux/share/catch2" CACHE STRING "Catch2 directory")

# Find packages installed via vcpkg
find_package(EnTT CONFIG REQUIRED)

# Find Catch2 package
find_package(Catch2 CONFIG REQUIRED)

# Add executable for your main application
add_executable(main main.cpp simulation.cpp)

# Add executable for your test suite
add_executable(tests test.cpp simulation.cpp)

# Link libraries to the executables
target_link_libraries(main PRIVATE EnTT::EnTT)
target_link_libraries(tests PRIVATE Catch2::Catch2 EnTT::EnTT)

# Include directories
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
