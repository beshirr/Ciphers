cmake_minimum_required(VERSION 3.26)
project(ciphers)

set(CMAKE_CXX_STANDARD 23)

add_executable(ciphers main.cpp
        Decryption.cpp
        Encryption.cpp
        Helpers.cpp)
