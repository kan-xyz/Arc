
add_compile_definitions(SFML_STATIC)
add_executable(
    ParticleSystem
    ${CMAKE_SOURCE_DIR}/tests/particle_system/ParticleSystem.cpp
    ${CMAKE_SOURCE_DIR}/tests/particle_system/main.cpp
)
ARC_INCLUDE_ARC(ParticleSystem)
ARC_INCLUDE_SFML(ParticleSystem)
ARC_LINK_SFML(ParticleSystem)
