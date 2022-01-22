
add_executable(
	particles
	${CMAKE_SOURCE_DIR}/examples/particles/main.cpp
	${CMAKE_SOURCE_DIR}/examples/particles/particles.cpp
)

ARC_INCLUDE_LIBRARIES(particles)
ARC_LINK_LIBRARIES(particles)
