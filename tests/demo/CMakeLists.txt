
add_compile_definitions(SFML_STATIC)
add_executable(
    Demo
    ${CMAKE_SOURCE_DIR}/tests/demo/Demo.cpp
    ${CMAKE_SOURCE_DIR}/tests/demo/main.cpp
)
ARC_INCLUDE_ARC(Demo)
ARC_INCLUDE_SFML(Demo)
ARC_LINK_SFML(Demo)
