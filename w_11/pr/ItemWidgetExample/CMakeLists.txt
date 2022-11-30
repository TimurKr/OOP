#Tu nastavit verziu Qt6
set(Qt6_Version 6.4.1)

cmake_minimum_required(VERSION 3.16.0)

PROJECT(ItemWidgetExample VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
	add_definitions( "/D_CRT_SECURE_NO_WARNINGS /MP /openmp" )
endif(MSVC)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(Qt6_DIR "C:/Qt/${Qt6_Version}/msvc2019_64/lib/cmake/Qt6")
set(Qt6WidgetsTools_DIR "C:/Qt/${Qt6_Version}/msvc2019_64/lib/cmake/Qt6WidgetsTools")
set(Qt6CoreTools_DIR "C:/Qt/${Qt6_Version}/msvc2019_64/lib/cmake/Qt6CoreTools")
set(Qt6GuiTools_DIR "C:/Qt/${Qt6_Version}/msvc2019_64/lib/cmake/Qt6GuiTools")

find_package(Qt6 COMPONENTS Widgets Core Gui REQUIRED)

file(GLOB UI_FILES src/*.ui)
file(GLOB H_FILES src/*.h)
file(GLOB CPP_FILES src/*.cpp)
file(GLOB QRC_FILES src/*.qrc)

set(SOURCE_LIST ${CPP_FILES} ${UI_FILES} ${H_FILES} ${QRC_FILES})

add_executable(${PROJECT_NAME} ${SOURCE_LIST})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_LIST})

add_custom_command(TARGET ${PROJECT_NAME}
 				POST_BUILD COMMAND "C:/Qt/${Qt6_Version}/msvc2019_64/bin/windeployqt.exe" "$(OutDir)$(TargetName)$(TargetExt)" 
 				COMMENT "Win deploy qt")
