cmake_minimum_required(VERSION 3.20)

project(game)

include_directories(include)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

file(GLOB SRCS "${SRC_DIR}/*.cpp")

add_executable(game ${SRCS})

add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:game>/assets
)