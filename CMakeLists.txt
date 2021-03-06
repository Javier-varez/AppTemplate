cmake_minimum_required(VERSION 3.16)

set(APPLICATION_NAME nrf52_app)
set(CHIP_NAME nRF52840_xxAA)

project(${APPLICATION_NAME})

include(cmake/cortex-m_hal.cmake)
include(cmake/cortex-m_startup.cmake)
include(cmake/ditto.cmake)
include(cmake/postform.cmake)

add_executable(
    ${APPLICATION_NAME}
    src/main.cpp
    src/postform_config.cpp)

target_include_directories(
    ${APPLICATION_NAME}
    PRIVATE
    include)

target_compile_options(
    ${APPLICATION_NAME}
    PRIVATE
    -Os
    -Wall
    -Wextra
    -Werror
    -Wno-gnu-string-literal-operator-template)

target_link_libraries(
    ${APPLICATION_NAME}
    PRIVATE
    cortex-m_startup
    cortex-m_hal
    Ditto
    postform)

target_link_options(
    ${APPLICATION_NAME}
    PRIVATE
    "SHELL:-Wl,-T ${CMAKE_CURRENT_SOURCE_DIR}/memory.ld"
    "-Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${APPLICATION_NAME}.map")

set_target_properties(
    ${APPLICATION_NAME}
    PROPERTIES
    LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/memory.ld)

add_custom_target(
    run
    COMMAND postform_rtt --chip ${CHIP_NAME} ${CMAKE_BINARY_DIR}/${APPLICATION_NAME}
    DEPENDS ${APPLICATION_NAME}
    USES_TERMINAL)

add_custom_target(
    attach
    COMMAND postform_rtt --attach --chip ${CHIP_NAME} ${CMAKE_BINARY_DIR}/${APPLICATION_NAME}
    DEPENDS ${APPLICATION_NAME}
    USES_TERMINAL)
