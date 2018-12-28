cmake_minimum_required(VERSION 2.8.3)
project(beginner_tutorials)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)
## Generate messages in the 'msg' folder
 add_message_files(
   FILES
   Num.msg
 )

## Generate services in the 'srv' folder
 add_service_files(
   FILES
   AddTwoInts.srv
 )
## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   std_msgs
 )
## catkin specific configuration ##
catkin_package(
 ## INCLUDE_DIRS include
  LIBRARIES beginner_tutorials
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
  DEPENDS system_lib
)

##build talker and listener
include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)

add_executable(talker src/talker.cpp)
target_link_libraries(talker ${catkin_LIBRARIES})
add_dependencies(talker beginner_tutorials_generate_messages_cpp)

add_executable(listener src/listener.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})
add_dependencies(listener beginner_tutorials_generate_messages_cpp)

add_executable(add_two_ints_server src/add_two_ints_server.cpp)
target_link_libraries(add_two_ints_server ${catkin_LIBRARIES})
add_dependencies(add_two_ints_server beginner_tutorials_gencpp)

add_executable(add_two_ints_client src/add_two_ints_client.cpp)
target_link_libraries(add_two_ints_client ${catkin_LIBRARIES})
add_dependencies(add_two_ints_client beginner_tutorials_gencpp)


add_executable(add_two_ints_client_xx src/add_two_ints_client_xx.cpp)
target_link_libraries(add_two_ints_client_xx ${catkin_LIBRARIES})


add_executable(add_two_ints_server_xx src/add_two_ints_server_xx.cpp)
target_link_libraries(add_two_ints_server_xx ${catkin_LIBRARIES})