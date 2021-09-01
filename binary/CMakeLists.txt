# MIT License

# Copyright (c) 2021 Vladimir Yu. Ivanov <inbox@vova-ivanov.info>

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.10.0)
project(xkcdxx LANGUAGES CXX C)

file(READ "VERSION" LIB_SEMVER)
string(REPLACE "." ";" LIB_SEMVER_LIST ${LIB_SEMVER})
list(GET LIB_SEMVER_LIST 0 LIB_SEMVER_MAJOR)
list(GET LIB_SEMVER_LIST 1 LIB_SEMVER_MINOR)
list(GET LIB_SEMVER_LIST 2 LIB_SEMVER_PATCH)

add_library(objlib OBJECT src/xkcd.cpp src/xkcdxx.cpp src/impl.cpp)
target_compile_options(objlib PRIVATE -Wall -Wextra -Ofast -std=gnu++17 -fvisibility=hidden)
target_include_directories(objlib PRIVATE inc/)

add_library(libshared SHARED $<TARGET_OBJECTS:objlib>)
set_target_properties(libshared PROPERTIES OUTPUT_NAME xkcdxx)
set_target_properties(objlib PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(libshared PROPERTIES VERSION ${LIB_SEMVER} SOVERSION ${LIB_SEMVER_MAJOR})
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")
target_link_libraries(libshared PRIVATE ssl crypto)

add_library(libstatic STATIC $<TARGET_OBJECTS:objlib>)
set_target_properties(libstatic PROPERTIES OUTPUT_NAME xkcdxx)
target_link_libraries(libstatic PRIVATE ssl.a crypto.a pthread.a dl.so)

add_executable(xkcd_test test/test.c)
target_compile_options(xkcd_test PRIVATE -Wall -Wextra)
target_include_directories(xkcd_test PRIVATE inc/)
target_link_libraries(xkcd_test PRIVATE libstatic)

add_executable(xkcd_testxx test/test.cpp)
target_compile_options(xkcd_testxx PRIVATE -Wall -Wextra -std=c++17)
target_include_directories(xkcd_testxx PRIVATE inc/)
target_link_libraries(xkcd_testxx PRIVATE libshared)

install(TARGETS libshared libstatic LIBRARY DESTINATION lib/ ARCHIVE DESTINATION lib/)
install(FILES inc/xkcd.h inc/xkcdxx.h DESTINATION include/)
