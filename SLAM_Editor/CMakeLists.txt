project( SLAM_Editor )
cmake_minimum_required( VERSION 3.1 )
set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_AUTOMOC ON )
set( CMAKE_BUILD_TYPE Release )
add_definitions ( -Wall )
find_package ( Qt5Widgets REQUIRED )
find_package ( Qt5Core REQUIRED )
find_package ( Qt5Gui REQUIRED )
set ( SLAM_Editor_HDRS
	canvasscene.h
	)

set ( SLAM_Editor_SRCS
	main.cpp
	mainwindow.cpp
	canvasscene.cpp
	)

set ( SLAM_Editor_UIS
	mainwindow.ui
	)
QT5_WRAP_UI(UIS ${SLAM_Editor_UIS})

set ( SLAM_Editor_MOCS
	#mainwindow.h
	)
QT5_WRAP_CPP(MOCS ${SLAM_Editor_MOCS})

add_executable ( SLAM_Editor ${SLAM_Editor_SRCS} ${UIS} ${RSCS} ${TRS} ${MOCS} )
target_link_libraries ( SLAM_Editor  Qt5::Core Qt5::Gui Qt5::Widgets )
