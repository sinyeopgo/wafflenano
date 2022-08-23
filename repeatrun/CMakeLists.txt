cmake_minimum_required(VERSION 3.0.2)
project(repeatrun)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
  move_base_msgs
)

set( sources
  src/repeatrun.cpp
)

set( headers
  src/repeatrun.h
)

catkin_package(
  LIBRARIES repeatrun
  CATKIN_DEPENDS roscpp geometry_msgs move_base_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_node ${headers} ${sources})
add_executable(remote_wafflenano src/remote_wafflenano.cpp)

target_link_libraries(${PROJECT_NAME}_node
   ${catkin_LIBRARIES}
)
target_link_libraries(remote_wafflenano
   ${catkin_LIBRARIES}
)