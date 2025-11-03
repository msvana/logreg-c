cmake_minimum_required(VERSION 3.10)
project(LogisticRegression C)

# Use C99
set(CMAKE_C_STANDARD 99)

# Build static logistic regression library
file(GLOB LIB_SOURCES "src/lib/*.c")
file(GLOB LIB_HEADERS "src/lib/*.h")

add_library(liblogreg STATIC ${LIB_SOURCES} ${LIB_HEADERS})
target_include_directories(liblogreg PUBLIC "src/lib/")

# Build logistic regression executable
add_executable(logreg "src/main.c")
target_link_libraries(logreg liblogreg)
