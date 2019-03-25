cmake_minimum_required (VERSION 3.0)
project(fpcpp)

include(CheckCXXCompilerFlag)
enable_language(CXX)

set(
    ENABLE_CXXFLAGS_TO_CHECK
    -std=gnu1y
    -std=c++1y
    -std=gnu++11
    -std=c++11
    -std=gnu++0x
    -std=c++0x
)

include(CTest)

include_directories(.)

