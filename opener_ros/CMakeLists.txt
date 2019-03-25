cmake_minimum_required( VERSION 2.8.12 )
project( opener_ros )

find_package( catkin REQUIRED COMPONENTS )

catkin_package(
  INCLUDE_DIRS
    OpENer/source
  LIBRARIES
    ENET_ENCAP
    Utils
    CIP
    PLATFORM_GENERIC
    POSIXPLATFORM
  )

set( OpENer_Device_Config_Device_Name "ROS [OpENer PC]" CACHE STRING "Device Name" )
set( OpENer_PLATFORM "POSIX" CACHE STRING "Set Platform" )
set( BUILD_SHARED_LIBS ON CACHE BOOL "Use Sharedd Libs" )
set( CMAKE_INSTALL_INCLUDEDIR ${CATKIN_PACKAGE_INCLUDE_DESTINATION})
set( CMAKE_INSTALL_LIBDIR ${CATKIN_PACKAGE_LIB_DESTINATION} )

add_subdirectory(OpENer/source)

configure_file(
  "${PROJECT_BINARY_DIR}/OpENer/source/src/ports/devicedata.h"
  "${CMAKE_INSTALL_PREFIX}/${CATKIN_PACKAGE_INCLUDE_DESTINATION}/ports/devicedata.h"
  COPYONLY )


# TODO add headers/libs to INSTALL_DIR
install(FILES package.xml DESTINATION share/opener_ros)

