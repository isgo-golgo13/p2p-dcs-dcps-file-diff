cmake_minimum_required(VERSION 3.15)
project(OpenDDSProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find OpenDDS
find_package(OpenDDS REQUIRED)

# Include directories
include_directories(
    ${OPENDDS_INCLUDE_DIRS}
    include
)

# Source files
set(SOURCES
    src/Main.cpp
    src/FileDataChangeConsumerSupplier.cpp
    src/FileDataChangeApplicationConsumerSupplier.cpp
    generated/FileDataTypeSupportImpl.cpp  # Generated from IDL
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} ${OPENDDS_LIBRARIES})
