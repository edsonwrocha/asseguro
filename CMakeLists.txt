cmake_minimum_required(VERSION 3.16)
project(asseguro)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(asseguro
  src/main.cpp
  src/MenuUART.cpp
  src/UARTInterface.cpp
  src/UsuarioManager.cpp
  src/Usuario.cpp
)

target_include_directories(asseguro PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
