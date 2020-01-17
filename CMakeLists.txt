cmake_minimum_required(VERSION 3.2.0)
project (linked_list)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Werror -Wpedantic -Wextra")

### Unity
include_directories("Unity/src")
set(UNITY_SRCS "Unity/src/unity.c")

### linked list
include_directories(".")
set(LINKED_LIST_SRCS linked_list.c)

### Example App
set(EXAMPLE_SRCS main.c ${LINKED_LIST_SRCS})
add_executable(linked_list_example ${EXAMPLE_SRCS})

### Testapp
set(TEST_SRCS tests.c ${UNITY_SRCS} ${LINKED_LIST_SRCS})
add_executable(linked_list_test ${TEST_SRCS})
