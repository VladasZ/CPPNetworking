cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(networking)

add_catalog_recursive(${PROJECT_SOURCE_DIR} /Source SOURCE)

add_library(${PROJECT_NAME} ${SOURCE})

link_project_at_path(cpp_utils ${cpp_utils_path})

