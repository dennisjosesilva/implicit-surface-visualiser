project(ImplicitSurface)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE PROJECT_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

qt5_wrap_cpp(PROJECT_SOURCE
  include/GraphicsViewWidget.hpp
  include/MainWindow.hpp)

qt5_add_resources(PROJECT_SOURCE resources.qrc)

add_executable(ImplicitSurface ${PROJECT_SOURCE})
target_link_libraries(ImplicitSurface PUBLIC
  Qt5::Core 
  Qt5::Gui 
  Qt5::Widgets
  OpenGL::OpenGL
  ${CONAN_LIBS})