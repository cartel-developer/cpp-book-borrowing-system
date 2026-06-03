cmake_minimum_required(VERSION 3.17)
project(Library)

set(CMAKE_CXX_STANDARD 17)

add_executable(Library
        main.cpp
        src/application/BorrowBookService.cpp
        src/adapters/InMemoryLibraryRepository.cpp
        src/infrastructure/ConsoleUi.cpp)


target_include_directories(Library PRIVATE src)