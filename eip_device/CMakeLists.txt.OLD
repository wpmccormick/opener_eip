cmake_minimum_required(VERSION 2.8.3)
project(eip_device)

add_definitions(-std=c++11)

add_definitions(-DRESTRICT=)

find_package(catkin REQUIRED COMPONENTS opener_ros roscpp message_generation)

add_message_files(
  FILES
  EipDataFmPLC.msg
  EipDataToPLC.msg
  EipConfig.msg
  EipDeviceStatus.msg
)

generate_messages()

catkin_package(
  INCLUDE_DIRS
    include
    ${catkin_INCLUDE_DIRS}
    ${opener_ros_INSTALL_PREFIX}/include/opener_ros
    ${opener_ros_INSTALL_PREFIX}/include/opener_ros/cip
    ${opener_ros_INSTALL_PREFIX}/include/opener_ros/enet_encap
    ${opener_ros_INSTALL_PREFIX}/include/opener_ros/ports
    ${opener_ros_INSTALL_PREFIX}/include/opener_ros/ports/POSIX
    ${opener_ros_INSTALL_PREFIX}/include/opener_ros/utils
  CATKIN_DEPENDS opener_ros roscpp message_runtime
  LIBRARIES eip_device
  )

include_directories(
  include 
  include/eip_device
  ${catkin_INCLUDE_DIRS}
  ${opener_ros_INSTALL_PREFIX}/include/opener_ros/
  ${opener_ros_INSTALL_PREFIX}/include/opener_ros/cip
  ${opener_ros_INSTALL_PREFIX}/include/opener_ros/enet_encap
  ${opener_ros_INSTALL_PREFIX}/include/opener_ros/ports
  ${opener_ros_INSTALL_PREFIX}/include/opener_ros/ports/POSIX
  ${opener_ros_INSTALL_PREFIX}/include/opener_ros/utils
  )

add_library(eip_device src/eip_device.cpp)
target_link_libraries(eip_device
  ${catkin_LIBRARIES}
)
add_dependencies(
    eip_device
    ${${PROJECT_NAME}_EXPORTED_TARGETS}
    ${catkin_EXPORTED_TARGETS}
)


add_executable(eip_device_node src/eip_device_node.cpp src/eip_device_application.cpp)
target_link_libraries(eip_device_node
  eip_device
  ${catkin_LIBRARIES}
  rt cap pthread
  )

add_dependencies(
    eip_device_node
    ${${PROJECT_NAME}_EXPORTED_TARGETS}
    ${catkin_EXPORTED_TARGETS}
)

## Mark executables and libraries for installation
install(TARGETS eip_device eip_device_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})

