cmake_minimum_required(VERSION 3.15)

project(P2PDcsDcpsFileData LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(fastrtps REQUIRED)

include_directories(
    include
    ${fastrtps_INCLUDE_DIRS}
)

set(SOURCES
    src/Main.cpp
    src/FileDataChangeApplicationConsumerSupplier.cpp
    src/FileDataChangeAvailableConsumer.cpp
    src/FileDataChangeConsumerSupplier.cpp
    generated/FileData.cxx
    generated/FileDataPubSubTypes.cxx
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} fastrtps fastcdr)
