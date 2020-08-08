cmake_minimum_required(VERSION 3.16)
project(Leetcode)

set(CMAKE_CXX_STANDARD 14)

add_executable(List DataStructure/List.cpp)
add_executable(Tree DataStructure/Tree.cpp)
add_executable(stack_queue DataStructure/stack_queue.cpp)
add_executable(hash DataStructure/hash.cpp)
add_executable(string DataStructure/String.cpp)
add_executable(array DataStructure/array.cpp)
add_executable(graph DataStructure/Graph.cpp)
add_executable(bit DataStructure/Bit.cpp)
add_executable(double_pointer Algorithm/double_pointer.cpp)
add_executable(sort Algorithm/Sort.cpp)
add_executable(greed Algorithm/Greedy.cpp)
add_executable(binary_search Algorithm/BinarySearch.cpp)

