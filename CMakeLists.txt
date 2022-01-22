cmake_minimum_required(VERSION 3.20)
project(PROJECT_ARC)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

##########################################################
#
#	DIRECTORIES
#
##########################################################

#
#	INCLUDE
#

set(ARC_SFML_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/externals/SFML-2.5.1/include)
set(ARC_ARC_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

#
#	LIBRARY
#

set(ARC_SFML_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/externals/SFML-2.5.1/lib)

##########################################################
#
#	CONFIGURATIONS
#
##########################################################

#
#	BUILDING
#

set(ARC_STATIC_BUILD_EXAMPLES TRUE CACHE BOOL "On for statically building the examples")

#
#	LIBRARY UTILS
#

set(ARC_LIB_PREFIX)
set(ARC_LIB_EXTENSION)

if (MSVC)
	set(ARC_LIB_EXTENSION lib)
elseif (MINGW)
	set(ARC_LIB_PREFIX lib)
	set(ARC_LIB_EXTENSION a)
endif ()

#
#	BUILD TYPE
#

set(ARC_SFML_BUILD_TYPE_POSTFIX)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(ARC_SFML_BUILD_TYPE_POSTFIX -d)
endif ()

#
#	SYSTEM SPECIFIC LIBRARIES
#
#	NOTE: currently there are only windows specific libraries
#

set(ARC_OPENGL_LIB_FILE)
set(ARC_WINMM_LIB_FILE)
set(ARC_GDI32_LIB_FILE)

if (WIN32)
	set(ARC_OPENGL_LIB_FILE ${ARC_LIB_PREFIX}opengl32.${ARC_LIB_EXTENSION})
	set(ARC_WINMM_LIB_FILE ${ARC_LIB_PREFIX}winmm.${ARC_LIB_EXTENSION})
	set(ARC_GDI32_LIB_FILE ${ARC_LIB_PREFIX}gdi32.${ARC_LIB_EXTENSION})
endif ()

##########################################################
#
#	UTILITY MACROS
#
##########################################################

macro(ARC_INCLUDE_LIBRARIES target_name)
	target_include_directories(${target_name} PUBLIC ${ARC_ARC_INCLUDE_DIR} ${ARC_SFML_INCLUDE_DIR})
endmacro()

macro (ARC_LINK_LIBRARIES target_name)
	if (ARC_STATIC_BUILD_EXAMPLES)
		target_compile_definitions(${target_name} PUBLIC SFML_STATIC)
		target_link_libraries(
			${target_name}
			${ARC_SFML_LIBRARY_DIR}/${ARC_LIB_PREFIX}sfml-graphics-s${ARC_SFML_BUILD_TYPE_POSTFIX}.${ARC_LIB_EXTENSION}
			${ARC_SFML_LIBRARY_DIR}/${ARC_LIB_PREFIX}sfml-window-s${ARC_SFML_BUILD_TYPE_POSTFIX}.${ARC_LIB_EXTENSION}
			${ARC_SFML_LIBRARY_DIR}/${ARC_LIB_PREFIX}sfml-audio-s${ARC_SFML_BUILD_TYPE_POSTFIX}.${ARC_LIB_EXTENSION}
			${ARC_SFML_LIBRARY_DIR}/${ARC_LIB_PREFIX}sfml-network-s${ARC_SFML_BUILD_TYPE_POSTFIX}.${ARC_LIB_EXTENSION}
			${ARC_SFML_LIBRARY_DIR}/${ARC_LIB_PREFIX}sfml-system-s${ARC_SFML_BUILD_TYPE_POSTFIX}.${ARC_LIB_EXTENSION}
			${ARC_SFML_LIBRARY_DIR}/${ARC_LIB_PREFIX}flac.${ARC_LIB_EXTENSION}
			${ARC_SFML_LIBRARY_DIR}/${ARC_LIB_PREFIX}freetype.${ARC_LIB_EXTENSION}
			${ARC_SFML_LIBRARY_DIR}/${ARC_LIB_PREFIX}ogg.${ARC_LIB_EXTENSION}
			${ARC_SFML_LIBRARY_DIR}/${ARC_LIB_PREFIX}openal32.${ARC_LIB_EXTENSION}
			${ARC_SFML_LIBRARY_DIR}/${ARC_LIB_PREFIX}vorbis.${ARC_LIB_EXTENSION}
			${ARC_SFML_LIBRARY_DIR}/${ARC_LIB_PREFIX}vorbisenc.${ARC_LIB_EXTENSION}
			${ARC_SFML_LIBRARY_DIR}/${ARC_LIB_PREFIX}vorbisfile.${ARC_LIB_EXTENSION}
			${ARC_OPENGL_LIB_FILE}
			${ARC_WINMM_LIB_FILE}
			${ARC_GDI32_LIB_FILE}
		)
	else ()
		target_link_libraries(
			${target_name}
			${ARC_SFML_LIBRARY_DIR}/${ARC_LIB_PREFIX}sfml-graphics${ARC_SFML_BUILD_TYPE_POSTFIX}.${ARC_LIB_EXTENSION}
			${ARC_SFML_LIBRARY_DIR}/${ARC_LIB_PREFIX}sfml-window${ARC_SFML_BUILD_TYPE_POSTFIX}.${ARC_LIB_EXTENSION}
			${ARC_SFML_LIBRARY_DIR}/${ARC_LIB_PREFIX}sfml-audio${ARC_SFML_BUILD_TYPE_POSTFIX}.${ARC_LIB_EXTENSION}
			${ARC_SFML_LIBRARY_DIR}/${ARC_LIB_PREFIX}sfml-network${ARC_SFML_BUILD_TYPE_POSTFIX}.${ARC_LIB_EXTENSION}
			${ARC_SFML_LIBRARY_DIR}/${ARC_LIB_PREFIX}sfml-system${ARC_SFML_BUILD_TYPE_POSTFIX}.${ARC_LIB_EXTENSION}
		)
	endif ()
endmacro ()

##########################################################
#
#	EXAMPLES
#
##########################################################

add_subdirectory(${CMAKE_SOURCE_DIR}/examples/intro ${CMAKE_SOURCE_DIR}/build/examples/intro)
add_subdirectory(${CMAKE_SOURCE_DIR}/examples/particles ${CMAKE_SOURCE_DIR}/build/examples/particles)
add_subdirectory(${CMAKE_SOURCE_DIR}/examples/random ${CMAKE_SOURCE_DIR}/build/examples/random)
add_subdirectory(${CMAKE_SOURCE_DIR}/examples/tiles ${CMAKE_SOURCE_DIR}/build/examples/tiles)
