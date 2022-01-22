
add_executable(
	intro
	${CMAKE_SOURCE_DIR}/examples/intro/main.cpp
	${CMAKE_SOURCE_DIR}/examples/intro/intro.cpp
)

ARC_INCLUDE_LIBRARIES(intro)
ARC_LINK_LIBRARIES(intro)
