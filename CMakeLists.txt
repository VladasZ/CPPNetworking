cmake_minimum_required(VERSION 3.9.2 FATAL_ERROR)

include(configuration/sources_parsing.cmake)

project(CPPNetworking)

add_subdirectory(source/Server)
add_subdirectory(source/Client)
add_subdirectory(source/Common)
