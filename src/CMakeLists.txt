cmake_minimum_required(VERSION 3.5)

project(sheikahWM)

set(CMAKE_CXX_STANDARD 23)

include(FindPkgConfig)
pkg_check_modules(MIRAL miral REQUIRED)
pkg_check_modules(XKBCOMMON xkbcommon REQUIRED)

add_executable(sheikahWM SheikahWM.cpp
        WindowManager.h WindowManager.cpp
)

target_include_directories(sheikahWM PUBLIC SYSTEM ${MIRAL_INCLUDE_DIRS})
target_link_libraries(sheikahWM ${MIRAL_LDFLAGS})
target_link_libraries(sheikahWM ${XKBCOMMON_LIBRARIES})