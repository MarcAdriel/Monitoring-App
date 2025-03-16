cmake_minimum_required(VERSION 3.25)
project(CRUD)

set(CMAKE_CXX_STANDARD 20)

set(ENV{PKG_CONFIG_PATH} "/opt/homebrew/Cellar/libpqxx/7.10.0/lib/pkgconfig")

find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

include_directories(${PQXX_INCLUDE_DIRS})
link_directories(${PQXX_LIBRARY_DIRS})
add_definitions(${PQXX_CFLAGS_OTHER})

# Manually set Pistache include and library paths
include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib /opt/homebrew/Cellar/libpq/16.1/lib)

add_executable(
        CRUD
        src/main.cpp
        src/Header/Database.h
        src/Include/Database.cpp
        src/Header/Server.h
        src/Include/Server.cpp
)

target_link_libraries(CRUD ${PQXX_LIBRARIES} pqxx pq pistache)
