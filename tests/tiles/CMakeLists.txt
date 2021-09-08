
add_compile_definitions(SFML_STATIC)
add_executable(
    Tiles
    ${CMAKE_SOURCE_DIR}/tests/tiles/TileMap.cpp
    ${CMAKE_SOURCE_DIR}/tests/tiles/main.cpp
)
ARC_INCLUDE_ARC(Tiles)
ARC_INCLUDE_SFML(Tiles)
ARC_LINK_SFML(Tiles)
