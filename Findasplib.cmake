# - Try to find libsamplerate
# Once done this will define
#
# ASPLIB_FOUND - system has asplib
# ASPLIB_INCLUDE_DIRS - the asplib include directory
# ASPLIB_LIBRARIES - The asplib libraries

if(PKG_CONFIG_FOUND)
pkg_check_modules (ASPLIB asplib)
list(APPEND ASPLIB_INCLUDE_DIRS ${ASPLIB_INCLUDEDIR})
endif()

if(NOT ASPLIB_FOUND)
  find_path(ASPLIB_INCLUDE_DIRS "apslib_BiquadFactory.h"
            ASPLIB_INCLUDE_DIRS "Biquads/Biquad_Native/asplib_Biquad_Native.h"
            ASPLIB_INCLUDE_DIRS "constants_typedefs/asplib_constants.h"
            ASPLIB_INCLUDE_DIRS "constants_typedefs/asplib_typedefs.h"
            ASPLIB_INCLUDE_DIRS "interfaces/asplib_IBaseBiquad.h"
            PATH_SUFFIXES "asplib" )

  find_library(ASPLIB_LIBRARIES
               NAMES "asplib"
               PATH_SUFFIXES "asplib" )
endif()

# handle the QUIETLY and REQUIRED arguments and set SAMPLERATE_FOUND to TRUE if
# all listed variables are TRUE
include( "FindPackageHandleStandardArgs" )
find_package_handle_standard_args(asplib DEFAULT_MSG ASPLIB_INCLUDE_DIRS ASPLIB_LIBRARIES)

mark_as_advanced(ASPLIB_INCLUDE_DIRS ASPLIB_LIBRARIES)