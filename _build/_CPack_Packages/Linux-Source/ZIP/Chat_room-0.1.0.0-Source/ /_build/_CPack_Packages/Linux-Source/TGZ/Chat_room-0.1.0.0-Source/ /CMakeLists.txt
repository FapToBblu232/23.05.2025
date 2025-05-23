cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)

project(Chat_room)

set(PRINT_VERSION_PATCH 0)
set(PRINT_VERSION_MINOR 1)
set(PRINT_VERSION_MAJOR 0)
set(PRINT_VERSION_TWEAK 0)
set(PRINT_VERSION ${PRINT_VERSION_MAJOR}.${PRINT_VERSION_MINOR}.${PRINT_VERSION_PATCH}.${PRINT_VERSION_TWEAK})
set(PRINT_VERSION_STRING "v${PRINT_VERSION}")

set(Sources
    source/main.cpp
    source/chat_room.cpp
)

set(Sources_test
    tests/tests.cpp
)

add_library(Chat_room STATIC ${Sources})
target_include_directories(Chat_room PUBLIC source)

add_executable(chat_room ${Sources})
target_include_directories(chat_room PUBLIC 
    ./include
)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(third-party/gtest)
    add_executable(my_test ${Sources_test})
    target_link_libraries(my_test
        gtest_main
        Chat_room
    )
    target_include_directories(my_test PUBLIC 
        ./include
        ./third-party/gtest/googletest/include/gtest
    )
    add_test(NAME my_test COMMAND my_test)
endif()

install(TARGETS chat_room
RUNTIME DESTINATION bin
)

include(CPackConfig.cmake)