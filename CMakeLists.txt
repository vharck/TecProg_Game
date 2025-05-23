cmake_minimum_required(VERSION 3.11)

project(SimpleGame LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

# Add this for NixOS - tells CMake where to find SFML
if(DEFINED ENV{SFML_DIR})
    set(SFML_DIR "$ENV{SFML_DIR}")
    message(STATUS "Using SFML from: ${SFML_DIR}")
endif()

add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
)

# Find SFML - keep your professor's version
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

# For NixOS - skip the download attempt and fail fast
if(NOT SFML_FOUND AND NOT DEFINED ENV{SFML_DIR})
    message(FATAL_ERROR "SFML not found. In NixOS, use: nix-shell --packages sfml")
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC 
    sfml-graphics 
    sfml-audio
)

file(GLOB_RECURSE cpp_source_files 
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

# Create SourceDir.h with fallback
if(EXISTS "${PROJECT_SOURCE_DIR}/include/SourceDir.h.in")
    set(SourceDir "${PROJECT_SOURCE_DIR}")
    configure_file(
        "${PROJECT_SOURCE_DIR}/include/SourceDir.h.in"
        "${PROJECT_SOURCE_DIR}/include/SourceDir.h"
    )
else()
    file(WRITE "${PROJECT_SOURCE_DIR}/include/SourceDir.h"
        "const std::string SourceDir = \"${PROJECT_SOURCE_DIR}\";\n")
endif()

target_sources(${PROJECT_NAME} PRIVATE ${cpp_source_files})

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    message("Build type set to Debug, fsanitize activated")
    target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address)
    target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address)
endif()