cmake_minimum_required(VERSION 3.5.0)
project(lab2)

if (POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()

add_executable(lab2)

set_target_properties(lab2 PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON

  RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/debug/bin"
  RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/release/bin"
)

set(HEADERS
  include/range_number.hpp
  include/ns26.hpp
  include/brute_force_task.hpp
  include/threadpool.hpp
)

set(SOURCES src/main.cpp
  src/ns26.cpp
  src/brute_force_task.cpp
  src/threadpool.cpp
)


find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)


target_include_directories(lab2 PRIVATE include)

target_sources(lab2 PRIVATE ${HEADERS} ${SOURCES})

target_link_libraries(lab2 PRIVATE Qt6::Core ${Boost_LIBRARIES})
