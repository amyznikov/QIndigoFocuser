cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(QIndigoFocuser C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE OFF)
set(CMAKE_LINK_WHAT_YOU_USE OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_compile_options(-march=native)
if( ENABLE_CALL_GRAPH_INSTRUMENTATION )
	add_definitions(-DENABLE_CALL_GRAPH_INSTRUMENTATION=1)
endif()


set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_PREFIX_PATH "/usr/local") # need for some stupid ubuntus


# Set the QT version
if ( NOT QT_VERSION )
	find_package(Qt6 COMPONENTS Core QUIET)
	if (NOT Qt6_FOUND)
	    set(QT_VERSION 5 CACHE STRING "Qt version")
	else()
	    set(QT_VERSION 6 CACHE STRING "Qt version")
	endif()
endif()

find_package(Qt${QT_VERSION} REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Network
)

set(CMAKE_POSITION_INDEPENDENT_CODE OFF)
set(CMAKE_LINK_WHAT_YOU_USE OFF)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CORE ${CMAKE_CURRENT_SOURCE_DIR}/core)
set(GUI ${CMAKE_CURRENT_SOURCE_DIR}/gui)

set(APP_INCLUDES 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${SRC}
  Qt${QT_VERSION}::Core
  Qt${QT_VERSION}::Gui
  Qt${QT_VERSION}::Widgets)

include_directories(${APP_INCLUDES})
add_definitions(-DINDIGO_LINUX=1)

set(APP_LIBRARIES 
  Qt${QT_VERSION}::Core
  Qt${QT_VERSION}::Gui
  Qt${QT_VERSION}::Widgets
  indigo)


file(GLOB_RECURSE SOURCE_FILES
	${SRC}/*.c
	${SRC}/*.cc
	${SRC}/*.cpp
	${CORE}/*.c
	${CORE}/*.cc
	${CORE}/*.cpp
	${GUI}/*.c
	${GUI}/*.cc
	${GUI}/*.cpp)

file(GLOB_RECURSE HEADER_FILES
	${SRC}/*.h
	${SRC}/*.hpp
	${CORE}/*.h
	${CORE}/*.hpp
	${GUI}/*.h
	${GUI}/*.hpp)


if( EXISTS ${SRC}/app-resources.qrc )
	if ( ${QT_VERSION} STREQUAL 6 )
		qt6_add_resources(RESOURCE_FILES
			${SRC}/app-resources.qrc)
	else()
		qt5_add_resources(RESOURCE_FILES
			${SRC}/app-resources.qrc)
	endif()
endif()

if( EXISTS ${GUI}/gui-resources.qrc )
	if ( ${QT_VERSION} STREQUAL 6 )
		qt6_add_resources(RESOURCE_FILES
			${GUI}/gui-resources.qrc)
	else()
		qt5_add_resources(RESOURCE_FILES
			${GUI}/gui-resources.qrc)
	endif()
endif()

if( EXISTS ${GUI}/qindigo/qindigo-resources.qrc )
	if ( ${QT_VERSION} STREQUAL 6 )
		qt6_add_resources(RESOURCE_FILES
			${GUI}/qindigo/qindigo-resources.qrc)
	else()
		qt5_add_resources(RESOURCE_FILES
			${GUI}/qindigo/qindigo-resources.qrc)
	endif()
endif()

if( EXISTS ${GUI}/qdarkstyle/style.qrc )
	if ( ${QT_VERSION} STREQUAL 6 )
	  qt6_add_big_resources(SOURCE_FILES ${GUI}/qdarkstyle/style.qrc)
	else()
	  qt5_add_big_resources(SOURCE_FILES ${GUI}/qdarkstyle/style.qrc)
	endif()
endif()


add_executable(${PROJECT_NAME}
	${SOURCE_FILES}
	${HEADER_FILES}
	${RESOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
	${APP_LIBRARIES})


# Install

set(MY_RUNTIME_PATH bin)
set(MY_DESKTOP_ENTRY_PATH ${CMAKE_INSTALL_PREFIX}/share/applications)
set(MY_DESKTOP_ENTRY_COMMENT "${PROJECT_NAME}")
set(MY_APP_ICONS_PATH ${CMAKE_INSTALL_PREFIX}/share/app-install/icons)

if( EXISTS ${SRC}/app.desktop.in)
	configure_file(${SRC}/app.desktop.in
		${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.desktop
		@ONLY)
endif()

if(EXISTS ${SRC}/app-icon.png)
	configure_file(${SRC}/app-icon.png
		${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.png
		COPYONLY)
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME
	DESTINATION ${MY_RUNTIME_PATH})

if( EXISTS ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.desktop )
	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.desktop
		DESTINATION ${MY_DESKTOP_ENTRY_PATH})
endif()

if( EXISTS ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.png )
	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.png
		DESTINATION ${MY_APP_ICONS_PATH})
endif()

add_custom_target(uninstall
	xargs rm -vf < ${CMAKE_CURRENT_BINARY_DIR}/install_manifest.txt
)
