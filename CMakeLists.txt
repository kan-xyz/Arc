cmake_minimum_required(VERSION 3.20)
project(Arc_Tests)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_STANDARD_REQUIRED TRUE)

#
# -------------------------------------------------------------------------------------------------------------------
# VARIABLES
# -------------------------------------------------------------------------------------------------------------------
#

set(ARC_SFML_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../../libraries/SFML-2.5.1/include)
set(ARC_SFML_LIB_DIR ${CMAKE_SOURCE_DIR}/../../libraries/SFML-2.5.1/lib)

set(ARC_LIB_PREFIX)
if (MINGW)
    set(ARC_LIB_PREFIX lib)
endif()

set(ARC_LIB_EXT)
if (MSVC)
    set(ARC_LIB_EXT lib)
elseif (MINGW)
    set(ARC_LIB_EXT a)
endif()

set(ARC_BUILD_EXT)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(ARC_BUILD_EXT -d)
endif ()

set(ARC_STATIC_BUILD TRUE)

#
# -------------------------------------------------------------------------------------------------------------------
# HELPER MACROS
# -------------------------------------------------------------------------------------------------------------------
#

macro(ARC_INCLUDE_SFML TargetName)
    target_include_directories(${TargetName} PUBLIC ${ARC_SFML_INCLUDE_DIR})
endmacro()

macro(ARC_LINK_SFML TargetName)
    if (ARC_STATIC_BUILD)
        target_link_libraries(
            ${TargetName}
            ${ARC_SFML_LIB_DIR}/${ARC_LIB_PREFIX}sfml-graphics-s${ARC_BUILD_EXT}.${ARC_LIB_EXT}
            ${ARC_SFML_LIB_DIR}/${ARC_LIB_PREFIX}sfml-window-s${ARC_BUILD_EXT}.${ARC_LIB_EXT}
            ${ARC_SFML_LIB_DIR}/${ARC_LIB_PREFIX}sfml-audio-s${ARC_BUILD_EXT}.${ARC_LIB_EXT}
            ${ARC_SFML_LIB_DIR}/${ARC_LIB_PREFIX}sfml-network-s${ARC_BUILD_EXT}.${ARC_LIB_EXT}
            ${ARC_SFML_LIB_DIR}/${ARC_LIB_PREFIX}sfml-system-s${ARC_BUILD_EXT}.${ARC_LIB_EXT}
            ${ARC_SFML_LIB_DIR}/${ARC_LIB_PREFIX}flac.${ARC_LIB_EXT}
            ${ARC_SFML_LIB_DIR}/${ARC_LIB_PREFIX}freetype.${ARC_LIB_EXT}
            ${ARC_SFML_LIB_DIR}/${ARC_LIB_PREFIX}ogg.${ARC_LIB_EXT}
            ${ARC_SFML_LIB_DIR}/${ARC_LIB_PREFIX}openal32.${ARC_LIB_EXT}
            ${ARC_SFML_LIB_DIR}/${ARC_LIB_PREFIX}vorbis.${ARC_LIB_EXT}
            ${ARC_SFML_LIB_DIR}/${ARC_LIB_PREFIX}vorbisenc.${ARC_LIB_EXT}
            ${ARC_SFML_LIB_DIR}/${ARC_LIB_PREFIX}vorbisfile.${ARC_LIB_EXT}
            ${ARC_LIB_PREFIX}opengl32.${ARC_LIB_EXT}
            ${ARC_LIB_PREFIX}winmm.${ARC_LIB_EXT}
            ${ARC_LIB_PREFIX}gdi32.${ARC_LIB_EXT}
        )
    else ()
        target_link_libraries(
            ${TargetName}
            ${ARC_SFML_LIB_DIR}/${ARC_LIB_PREFIX}sfml-graphics${ARC_BUILD_EXT}.${ARC_LIB_EXT}
            ${ARC_SFML_LIB_DIR}/${ARC_LIB_PREFIX}sfml-window${ARC_BUILD_EXT}.${ARC_LIB_EXT}
            ${ARC_SFML_LIB_DIR}/${ARC_LIB_PREFIX}sfml-audio${ARC_BUILD_EXT}.${ARC_LIB_EXT}
            ${ARC_SFML_LIB_DIR}/${ARC_LIB_PREFIX}sfml-network${ARC_BUILD_EXT}.${ARC_LIB_EXT}
            ${ARC_SFML_LIB_DIR}/${ARC_LIB_PREFIX}sfml-system${ARC_BUILD_EXT}.${ARC_LIB_EXT}
        )
    endif ()
endmacro()

macro(ARC_INCLUDE_ARC TargetName)
    target_include_directories(${TargetName} PUBLIC ${CMAKE_SOURCE_DIR}/include)
endmacro()

macro(ARC_ADD_EXAMPLE FolderName)
    add_subdirectory(${CMAKE_SOURCE_DIR}/tests/${FolderName} ${CMAKE_SOURCE_DIR}/build/${FolderName})
endmacro()

#
# -------------------------------------------------------------------------------------------------------------------
# SUBDIRECTORIES
# -------------------------------------------------------------------------------------------------------------------
#

ARC_ADD_EXAMPLE(basic)
ARC_ADD_EXAMPLE(demo)
ARC_ADD_EXAMPLE(particle_system)
ARC_ADD_EXAMPLE(tiles)
