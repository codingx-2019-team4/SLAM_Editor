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

find_package(catkin REQUIRED COMPONENTS image_transport roscpp std_msgs std_srvs sensor_msgs camera_info_manager)
include_directories( "/opt/ros/kinetic/include" )

set ( SLAM_Editor_HDRS
	canvasView.h
	)

set ( SLAM_Editor_SRCS
	main.cpp
	mainwindow.cpp
	canvasscene.cpp
	door.cpp
	sensor.cpp
	qnode.cpp
	
	)

set ( SLAM_Editor_UIS
	mainwindow.ui
	)
QT5_WRAP_UI(UIS ${SLAM_Editor_UIS})

set ( SLAM_Editor_MOCS
	#mainwindow.h
	#canvasScene.h
	#qnode.h
	)
QT5_WRAP_CPP(MOCS ${SLAM_Editor_MOCS})

add_executable ( SLAM_Editor ${SLAM_Editor_SRCS} ${UIS} ${RSCS} ${TRS} ${MOCS} ${catkin_LIBRARIES})
target_link_libraries ( SLAM_Editor  Qt5::Core Qt5::Gui Qt5::Widgets ${catkin_LIBRARIES})
