cmake_minimum_required(VERSION 2.8.3)
project(towr_simulator)

find_package(catkin_simple REQUIRED)
catkin_simple()

cs_add_executable( joint_state_converter_node
    src/joint_state_converter.cpp
)

cs_install()
cs_export()