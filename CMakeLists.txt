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
    src/Porta.cpp
    src/GPIO.cpp
    src/PortaManager.cpp
    src/Evento.cpp
    src/EventoManager.cpp
    src/CurlHTTPCliente.cpp
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(CURL REQUIRED libcurl)

target_include_directories(asseguro PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CURL_INCLUDE_DIRS}
)

target_link_libraries(asseguro PRIVATE ${CURL_LIBRARIES})
