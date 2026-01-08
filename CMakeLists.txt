# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.16)

# Include ESPIDF build system
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# Set the project name
project(app)