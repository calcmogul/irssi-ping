cmake_minimum_required(VERSION 3.28)

# Set default build type to release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(irssi-local)

include(FetchContent)

file(GLOB_RECURSE cpp_src src/*.cpp)
add_executable(irssi-local ${cpp_src})

if(NOT MSVC)
    target_compile_options(irssi-local PRIVATE -Wall -Wextra -pedantic)
else()
    # Suppress the following warnings:
    #   * C4244: lossy conversion
    target_compile_options(irssi-local PRIVATE /wd4244)
endif()
set_property(TARGET irssi-local PROPERTY COMPILE_WARNING_AS_ERROR ON)

target_compile_features(irssi-local PUBLIC cxx_std_23)
target_include_directories(irssi-local PRIVATE src)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(SFML)
target_link_libraries(irssi-local PUBLIC SFML::Audio SFML::Network)

install(TARGETS irssi-local DESTINATION bin)
