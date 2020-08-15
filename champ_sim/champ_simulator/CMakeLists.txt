
cmake_minimum_required(VERSION 3.0.2)
project(champ_simulator)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
)

catkin_package()

include_directories(
#include
 ${catkin_INCLUDE_DIRS}
)

#install(DIRECTORY meshes launch urdf
#    DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
#)