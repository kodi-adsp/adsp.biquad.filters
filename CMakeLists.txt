project(adsp.biquad.filters)

cmake_minimum_required(VERSION 2.6)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

enable_language(CXX)

find_package(kodi REQUIRED)
find_package(kodiplatform REQUIRED)
find_package(TinyXML REQUIRED)
find_package(asplib REQUIRED)

include_directories(${kodiplatform_INCLUDE_DIRS}
					${TINYXML_INCLUDE_DIRS}
					${KODI_INCLUDE_DIR}
					${asplib_INCLUDE_DIRS}
                    ${PROJECT_SOURCE_DIR}/src
                    ${PROJECT_SOURCE_DIR}/src/template)

set(TEMPLATE_SOURCES 	src/DSPProcessor.cpp
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
						src/template/configuration/templateConfiguration.cpp)

set(DEPLIBS ${kodiplatform_LIBRARIES}
			${ASPLIB_LIBRARIES}
			${TINYXML_LIBRARIES})

build_addon(adsp.biquad.filters TEMPLATE DEPLIBS)

# For generating the doxy
find_package(Doxygen)
if(DOXYGEN_FOUND)
	add_custom_target(doc 	${DOXYGEN_EXECUTABLE} ${PROJECT_SOURCE_DIR}/doxygen_resources/Doxyfile
							WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
							COMMENT "Generating API documentation" VERBATIM)
endif()

include(CPack)
