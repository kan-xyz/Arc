
add_executable(
	random
	${CMAKE_SOURCE_DIR}/examples/random/main.cpp
	${CMAKE_SOURCE_DIR}/examples/random/random.cpp
)

ARC_INCLUDE_LIBRARIES(random)
ARC_LINK_LIBRARIES(random)
