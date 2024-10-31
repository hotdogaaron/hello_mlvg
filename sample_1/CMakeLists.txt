
#--------------------------------------------------------------------
# CMake Version Configuration
#--------------------------------------------------------------------

cmake_minimum_required(VERSION 3.7...3.29)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

#--------------------------------------------------------------------
# Compiler flags
#--------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN OFF)

if(APPLE)
    # For now, explicitly disable C++17 alignment feature
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-aligned-new")
endif()

#--------------------------------------------------------------------
# Project and Global configuration
#--------------------------------------------------------------------
project(HelloMadrona VERSION 0.1.0 LANGUAGES CXX)

#--------------------------------------------------------------------
# Target configuration
#--------------------------------------------------------------------
set(target helloMadrona)
set(ext_libs "${CMAKE_SOURCE_DIR}/../ext_libs")

add_executable(${target} helloMadrona.cpp helloMadrona.h
                helloMadronaView.cpp helloMadronaView.h)

target_compile_definitions(${target} PRIVATE ML_INCLUDE_SDL=1)
target_include_directories(${target} PRIVATE "${ext_libs}/include")
target_link_directories(${target} PRIVATE "${ext_libs}/lib")

# Add SDL
if(APPLE)
    find_package(SDL2 REQUIRED COMPONENTS SDL2)
    set_target_properties(${target} PROPERTIES
 	  XCODE_ATTRIBUTE_LD_RUNPATH_SEARCH_PATHS "/Library/Frameworks")
endif()

target_include_directories(${target} PRIVATE ${SDL2_INCLUDE_DIRS})

# add madronalib

target_include_directories(${target} PRIVATE "${ext_libs}/include/madronalib")
if(APPLE)
    target_link_libraries(${target} PRIVATE "libmadrona-debug.a")
endif()

#add mlvg library
target_include_directories(${target} PRIVATE "${ext_libs}/include/mlvg")
if(APPLE)
    target_link_libraries(${target} PRIVATE "libmlvg-debug.a")
endif()

# add UI libs and frameworks- note that these appear under
# "other linker flags" in XCode and not in its file browser
if(APPLE)
    target_link_libraries(${target} PRIVATE "-framework Cocoa"
        "-framework Metal" "-framework MetalKit"
        "-framework CoreAudio" "-framework CoreServices"
        "-framework AppKit" "-framework SDL2" )
endif()