include(cmake/addon-template-helpers.cmake)

project(adsp.biquad.filters)

cmake_minimum_required(VERSION 2.6)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

enable_language(CXX)

find_package(Kodi REQUIRED)
find_package(kodiplatform REQUIRED)
find_package(p8-platform REQUIRED)
find_package(TinyXML REQUIRED)
find_package(asplib REQUIRED)

if (NOT WIN32)
  add_definitions(-fPIC -g -O2)
endif()

include_directories(${kodiplatform_INCLUDE_DIRS}
                    ${p8-platform_INCLUDE_DIRS}
                    ${TINYXML_INCLUDE_DIRS}
                    ${KODI_INCLUDE_DIR}
                    ${ASPLIB_INCLUDE_DIRS}
                    ${PROJECT_SOURCE_DIR}/src
                    ${PROJECT_SOURCE_DIR}/src/template)

set(TEMPLATE_SOURCES  src/DSPProcessor.cpp
                      src/BiquadFiltersSettings.cpp
                      src/ADDONOptional.cpp
                      src/Dialogs/GUIDialogPostProcess.cpp
                      src/template/AddonHelpers.cpp
                      src/template/ADSPAddonHandler.cpp
                      src/template/ADSPHelpers.cpp
                      src/template/ADSPProcessorHandle.cpp
                      src/template/client.cpp
                      src/template/GUIDialogBase.cpp
                      src/template/IADDONOptional.cpp
                      src/template/IADSPProcessor.cpp
                      src/template/Settings/SettingsManager.cpp
                      src/template/Settings/SettingsHelpers.cpp
                      src/template/Messages/ADSPModeMessage.cpp
                      src/template/configuration/templateConfiguration.cpp
                      
                      src/DSPProcessor.h
                      src/BiquadFiltersSettings.h
                      src/ADDONOptional.h
                      src/Dialogs/GUIDialogPostProcess.h
                      src/Messages/BiquadMessage_types.h
                      src/utils/stdStringUtils.h
                      src/template/AddonExceptions/IAddonException.h
                      src/template/AddonExceptions/TAddonException.h
                      src/template/configuration/templateConfiguration.h
                      src/template/include/ADSPAddonHandler.h
                      src/template/include/ADSPModeMessage.h
                      src/template/include/ADSPProcessorHandle.h
                      src/template/include/checkTemplateConfig.h
                      src/template/include/client.h
                      src/template/include/GUIDialogBase.h
                      src/template/include/IADDONOptional.h
                      src/template/include/IADSPProcessor.h
                      src/template/include/MACROHelper.h
                      src/template/include/typedefs.h
                      src/template/AddonHelpers.h
                      src/template/ADSPHelpers.h
                      src/template/doxygenDocu.h)

set(DEPLIBS ${p8-platform_LIBRARIES}
            ${ASPLIB_LIBRARIES}
            ${TINYXML_LIBRARIES})

addon_source_group("${TEMPLATE_SOURCES}")
            
build_addon(adsp.biquad.filters TEMPLATE DEPLIBS)

# For generating the doxy
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
  add_custom_target(doc   ${DOXYGEN_EXECUTABLE} ${PROJECT_SOURCE_DIR}/doxygen_resources/Doxyfile
                          WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
                          COMMENT "Generating API documentation" VERBATIM)
endif()

include(CPack)
