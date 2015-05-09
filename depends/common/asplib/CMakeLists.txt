project(asplib)

cmake_minimum_required(VERSION 2.8)

set(asplib_NAME asplib)
set(asplib_DESCRIPTION "asplib (Achim's Signal Processing LIBrary), is a small and lightweight C++ library for digital signal processing.")

set(SOURCES Biquads/apslib_BiquadFactory.cpp
			Biquads/Biquad_Native/asplib_Biquad_Native.cpp)

if(WIN32)
  add_definitions(-DWIN32 -D_LIB)
endif()

add_library(asplib STATIC ${SOURCES})

include_directories(${PROJECT_SOURCE_DIR}
					${PROJECT_SOURCE_DIR}/Biquads)

#set(HEADERS ${PROJECT_SOURCE_DIR}/Biquads/apslib_BiquadFactory.h
#           ${PROJECT_SOURCE_DIR}/Biquads/Biquad_Native/asplib_Biquad_Native.h
#			${PROJECT_SOURCE_DIR}/constants_typedefs/asplib_constants.h
#			${PROJECT_SOURCE_DIR}/constants_typedefs/asplib_typedefs.h
#			${PROJECT_SOURCE_DIR}/interfaces/asplib_IBaseBiquad.h)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/Biquads/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include/asplib/Biquads
		FILES_MATCHING PATTERN "*.h")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/interfaces/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include/asplib/interfaces
		FILES_MATCHING PATTERN "*.h")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/constants_typedefs/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include/asplib/constants_typedefs
		FILES_MATCHING PATTERN "*.h")

install(TARGETS asplib DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
