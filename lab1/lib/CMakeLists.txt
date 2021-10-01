cmake_minimum_required(VERSION 3.5.0)
project(lab1)

add_library(filesinfo STATIC)

set_target_properties(filesinfo PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON

  ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/debug/lib"
  ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/release/lib"

  LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/debug/lib"
  LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/release/lib"
)


set(HEADERS
  include/logicdisk.hpp
  include/filemanager.hpp
)

set(SOURCES
  src/logicdisk.cpp
  src/filemanager.cpp
)

find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Boost COMPONENTS filesystem REQUIRED)


target_include_directories(filesinfo PUBLIC include ${Boost_INCLUDE_DIR} ${Qt6Core_INCLUDE_DIRS})

target_sources(filesinfo PRIVATE ${HEADERS} ${SOURCES})

target_link_libraries(filesinfo PRIVATE Qt6::Core ${Boost_LIBRARIES})