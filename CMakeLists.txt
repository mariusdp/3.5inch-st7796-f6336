# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(sample_project)

# # Comment out following statements to build project without eez flow support.
# # Also, build lvgl-demo-no-flow.eez-project with EEZ Studio.
# add_definitions(-DHAS_FLOW_SUPPORT=1)
# set (HAS_FLOW_SUPPORT 1)

# # EEZ Framework
# add_definitions(-DEEZ_FOR_LVGL)

# include_directories(
#     ./eez-framework/src
#     ./eez-framework/src/eez/libs/agg
#     ./eez-framework/src/eez/platform/simulator
# )

# file(GLOB_RECURSE src_eez
#     ./eez-framework/src/eez/*.cpp
#     ./eez-framework/src/eez/*.c
# )

# list(APPEND SOURCES ${src_eez})
