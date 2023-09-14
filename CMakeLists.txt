cmake_minimum_required(VERSION 3.25)
project(untitled1 C CXX)

set(CMAKE_C_STANDARD 11)

add_library(untitled1 SHARED library.c email.c passwordOps.c GUI.c example_implementations.c biometric_auth.cpp transactions.c)

find_package(SQLite3 REQUIRED)

# Set the include directory for the target "bank_management_app"
target_include_directories(untitled1 PRIVATE ${SQLite3_INCLUDE_DIRS})

# Link the SQLite3 library to the target "bank_management_app"
target_link_libraries(untitled1 PRIVATE ${SQLite3_LIBRARIES})

#find_package(PkgConfig REQUIRED)
#pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)
#
#add_executable(untitled1 gui.c)
#target_link_libraries(untitled1 PRIVATE PkgConfig::GTK4)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})

add_executable(gui GUI.c)
add_executable(examp example_implementations.c)
target_link_libraries(gui ${GTK4_LIBRARIES})
target_link_libraries(gui ${SQLite3_LIBRARIES})
target_link_libraries(examp ${GTK4_LIBRARIES})

pkg_check_modules(opencv REQUIRED opencv4)
include_directories(${opencv4_INCLUDE_DIRS})
link_directories(${opencv4_LIBRARY_DIRS})
add_executable(bioauth biometric_auth.cpp)
target_link_libraries(bioauth ${opencv4_LIBRARIES})


#
#target_include_directories(untitled1 PRIVATE ${GTK4_LIBRARIES})
#
#target_include_directories(untitled1 PRIVATE ${GTK4_INCLUDE_DIRS})
#
## Link the SQLite3 library to the target "bank_management_app"
#target_link_libraries(untitled1 PRIVATE ${GTK4_INCLUDE_DIRS})
#
## Link the SQLite3 library to the target "bank_management_app"
#target_link_libraries(untitled1 PRIVATE ${GTK4_LIBRARIES})

#add_executable(guip GUI.cpp)
#target_link_libraries(guip gtk4)