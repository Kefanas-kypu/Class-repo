cmake_minimum_required(VERSION 3.20)
project(StudentuRusiavimas VERSION 3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==========================
# DLL biblioteka "Skaiciavimai"
# ==========================
add_library(Skaiciavimai SHARED
    src/Skaiciavimai.cpp
)

target_include_directories(Skaiciavimai
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Šis define reikalingas, kad Skaiciavimai.h naudotų __declspec(dllexport)
target_compile_definitions(Skaiciavimai
    PRIVATE SKAICIAVIMAI_EXPORTS
)

# ==========================
# Pagrindinė logikos biblioteka
# ==========================
add_library(studentu_lib
    src/Studentas.cpp
    src/Zmogus.cpp
    src/Funkcijos.cpp
)

target_include_directories(studentu_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# studentu_lib priklauso nuo DLL (Skaiciavimai)
# PUBLIC -> visi, kurie linkina studentu_lib, automatiškai linkins ir Skaiciavimai
target_link_libraries(studentu_lib
    PUBLIC
        Skaiciavimai
)

# ==========================
# Vykdomoji programa
# ==========================
add_executable(studentu_app
    src/main.cpp
)

target_link_libraries(studentu_app
    PRIVATE
        studentu_lib
)

# Po build'o nukopijuojam DLL prie exe, kad viskas veiktų iš karto
add_custom_command(TARGET studentu_app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Skaiciavimai>
        $<TARGET_FILE_DIR:studentu_app>
)

# ==========================
# Unit testai su Catch2
# ==========================
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

# Kad testai irgi turėtų DLL prie savęs
add_custom_command(TARGET studentu_tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Skaiciavimai>
        $<TARGET_FILE_DIR:studentu_tests>
)

add_test(NAME studentu_tests COMMAND studentu_tests)
