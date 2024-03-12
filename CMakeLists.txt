cmake_minimum_required(VERSION 3.20)

project(misis2023f-23-03-fediunin-e-a)


set(CMAKE_CXX_STANDARD 20)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")


option(BUILD_WITH_CODEFORCES "Build prj.codeforces targets" off)

if (BUILD_WITH_CODEFORCES)
    add_subdirectory(prj.codeforces)
endif()

add_subdirectory(prj.lab)
add_subdirectory(prj.test)