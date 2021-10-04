cmake_minimum_required(VERSION 3.5.0)
project(lab1)

add_executable(lab1)

set_target_properties(lab1 PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON

  RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/debug/bin"
  RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/release/bin"
)

target_compile_options(lab1 PRIVATE -fPIC)

set(HEADERS
  include/menu/base_menu.hpp
  include/menu/error_menu.hpp
  include/menu/main_menu.hpp
  include/menu/text_menu.hpp
  include/menu/json_menu.hpp
  include/menu/xml_menu.hpp
  include/menu/zip_menu.hpp

  include/pod/some_pod.hpp
)

set(SOURCES src/main.cpp
  src/menu/base_menu.cpp
  src/menu/error_menu.cpp
  src/menu/main_menu.cpp
  src/menu/text_menu.cpp
  src/menu/json_menu.cpp
  src/menu/xml_menu.cpp
  src/menu/zip_menu.cpp

  src/pod/some_pod.cpp
)


target_include_directories(lab1 PRIVATE include)

target_sources(lab1 PRIVATE ${HEADERS} ${SOURCES})

target_link_libraries(lab1 PRIVATE filesinfo)
