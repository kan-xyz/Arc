
add_compile_definitions(SFML_STATIC)
add_executable(
    BasicProgram
    ${CMAKE_SOURCE_DIR}/tests/basic/BasicProgram.cpp
    ${CMAKE_SOURCE_DIR}/tests/basic/main.cpp
)
ARC_INCLUDE_ARC(BasicProgram)
ARC_INCLUDE_SFML(BasicProgram)
ARC_LINK_SFML(BasicProgram)
