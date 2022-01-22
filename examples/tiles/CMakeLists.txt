
add_executable(
	tiles
	${CMAKE_SOURCE_DIR}/examples/tiles/main.cpp
	${CMAKE_SOURCE_DIR}/examples/tiles/TileMap.cpp
)

ARC_INCLUDE_LIBRARIES(tiles)
ARC_LINK_LIBRARIES(tiles)
