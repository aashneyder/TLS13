cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(TLS13 LANGUAGES C)

add_executable(${PROJECT_NAME} main.c TLSTransport.c TLSTransport.h Base.h)

set_target_properties(${PROJECT_NAME} PROPERTIES C_EXTENSIONS OFF)
target_compile_features(${PROJECT_NAME} PRIVATE c_std_99)

set(CMAKE_C_COMPILER /usr/bin/clang)
