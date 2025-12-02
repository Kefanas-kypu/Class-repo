cmake_minimum_required(VERSION 3.20)
project(StudentuRusiavimas VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Biblioteka su pagrindine logika
add_library(studentu_lib
    src/Studentas.cpp
    src/Zmogus.cpp
    src/Funkcijos.cpp
)

target_include_directories(studentu_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Pagrindinė vykdomoji programa
add_executable(studentu_app
    src/main.cpp
)

target_link_libraries(studentu_app
    PRIVATE
        studentu_lib
)

# ---- Unit testai su Catch2 ----
include(FetchContent)

FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.6.0
)

FetchContent_MakeAvailable(catch2)

enable_testing()

add_executable(studentu_tests
    tests/test_studentas.cpp
)

target_link_libraries(studentu_tests
    PRIVATE
        studentu_lib
        Catch2::Catch2WithMain
)

add_test(NAME studentu_tests COMMAND studentu_tests)
