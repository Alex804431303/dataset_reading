cmake_minimum_required(VERSION 2.8.3)
project(dataset_image_read)

add_compile_options(-std=c++11)
SET(CMAKE_BUILE_TYPE RELEASE)
set(OpenCV_DIR /usr/share/OpenCV)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  std_msgs
  cv_bridge
  message_generation
)

add_message_files(
  FILES
  Dataset.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
  sensor_msgs
)

catkin_package(
  CATKIN_DEPENDS message_runtime
)


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${dataset_image_read_SOURCE_DIR}/include/dataset_image_read
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_node src/datasetRead_node.cpp src/datasetRead.cpp)

target_link_libraries(${PROJECT_NAME}_node
   ${catkin_LIBRARIES}
   ${OpenCV_LIBS}
)