cmake_minimum_required(VERSION 3.5.0)
project(lab1)

add_executable(lab1)

set_target_properties(lab1 PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON

  RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/debug/bin"
  RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/release/bin"
)

set(HEADERS
  include/base_menu.hpp
  include/error_menu.hpp
  include/main_menu.hpp
  include/text_menu.hpp
  include/json_menu.hpp
  include/xml_menu.hpp
  include/zip_menu.hpp
)

set(SOURCES src/main.cpp
  src/base_menu.cpp
  src/error_menu.cpp
  src/main_menu.cpp
  src/text_menu.cpp
  src/json_menu.cpp
  src/xml_menu.cpp
  src/zip_menu.cpp
)


target_include_directories(lab1 PRIVATE include)

target_sources(lab1 PRIVATE ${HEADERS} ${SOURCES})

target_link_libraries(lab1 PRIVATE filesinfo)