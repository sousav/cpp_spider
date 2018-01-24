# stop if cmake version below 3.0
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# project name
project(spider_server)


# location of additional cmake modules
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/CMake
)

# project version
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
string(STRIP ${CMAKE_BUILD_TYPE} BUILD_TYPE)
string(STRIP ${PROJECT_SOURCE_DIR} SOURCE_PATH)

find_package(Boost COMPONENTS system thread REQUIRED)

# configure header file
configure_file(
    ${PROJECT_SOURCE_DIR}/CMake/SpiderServer_Config.h.in
    ${PROJECT_BINARY_DIR}/Includes/SpiderServer_Config.h
)

# detect operating system
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    add_definitions(-DSYSTEM_LINUX)
endif()
if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    add_definitions(-DSYSTEM_DARWIN)
endif()
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_definitions(-DSYSTEM_WINDOWS)
endif()


# example how to set c++ compiler flags for GNU
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Werror")
    set(CMAKE_CXX_FLAGS         "-std=c++11 -pthread")
    set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3 -DDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
elseif(CMAKE_CXX_COMPILER_ID MATCHES Clang)
    set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Werror")
    set(CMAKE_CXX_FLAGS         "-std=c++11")
    set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3 -DDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()


link_directories(
    /usr/local/lib
)


set(SRC_FILES
    ${PROJECT_SOURCE_DIR}/Sources/main.cpp
    ${PROJECT_SOURCE_DIR}/Includes/main.hpp

    ${PROJECT_SOURCE_DIR}/Sources/ConnectionManager.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Connection.cpp
    ${PROJECT_SOURCE_DIR}/Sources/AApiHandler.cpp
    ${PROJECT_SOURCE_DIR}/Sources/ApiHandler.cpp
    ${PROJECT_SOURCE_DIR}/Sources/mime_types.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Reply.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Session.cpp
    ${PROJECT_SOURCE_DIR}/Sources/RequestHandler.cpp
    ${PROJECT_SOURCE_DIR}/Sources/RequestParser.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Server.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Database/AObject.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Database/BddEndPoint.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Database/Bdd.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Database/Int.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Database/Client.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Database/Mouselog.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Database/ExecInfo.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Database/DumpInfo.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Database/Keylog.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Database/String.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Database/Research.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Database/Bool.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Content/IContent.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Content/AContent.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Content/Status.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Content/Exec.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Content/Dump.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Content/Stealer.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Content/Mouse.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Content/Keyboard.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Content/Undefined.cpp

    ${PROJECT_SOURCE_DIR}/Includes/Message.hpp
    ${PROJECT_SOURCE_DIR}/Includes/ConnectionManager.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Connection.hpp
    ${PROJECT_SOURCE_DIR}/Includes/AApiHandler.hpp
    ${PROJECT_SOURCE_DIR}/Includes/ApiHandler.hpp
    ${PROJECT_SOURCE_DIR}/Includes/mime_types.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Session.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Header.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Reply.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Request.hpp
    ${PROJECT_SOURCE_DIR}/Includes/RequestHandler.hpp
    ${PROJECT_SOURCE_DIR}/Includes/RequestParser.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Server.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Database/IObject.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Database/AObject.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Database/BddEndPoint.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Database/Bdd.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Database/Int.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Database/Client.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Database/Mouselog.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Database/ExecInfo.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Database/DumpInfo.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Database/Keylog.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Database/String.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Database/Research.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Database/Bool.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Content/IContent.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Content/AContent.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Content/Status.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Content/Exec.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Content/Dump.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Content/Stealer.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Content/Mouse.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Content/Keyboard.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Content/Undefined.hpp
)


# build executable
add_executable(spider_server ${SRC_FILES})


target_link_libraries( spider_server
    boost_system
    boost_thread
)


# location of header files
include_directories(
    ${Boost_INCLUDE_DIRS}

    ${PROJECT_BINARY_DIR}/Includes
    ${PROJECT_SOURCE_DIR}/Includes
    ${PROJECT_SOURCE_DIR}/Includes/Content
)
