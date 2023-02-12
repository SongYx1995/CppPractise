cmake_minimum_required(VERSION 3.10)
project(CppPractise)

include(FetchContent)

# specify the C++ standard 
set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED True) 

# for folly compile
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -DFOLLY_NO_CONFIG")
#message("cmake_cxx_flags ${CMAKE_CXX_FLAGS}")
add_definitions(-DFOLLY_HAVE_RECVMMSG=1)
add_definitions(-DFOLLY_HAVE_CLOCK_GETTIME=1)
add_definitions(-DFOLLY_HAVE_PTHREAD=1)

FetchContent_Declare(folly
        GIT_REPOSITORY https://github.com/facebook/folly.git
        GIT_TAG 9aa90e1b3f5c1a6be93fe29b732e219ac5dfa75e # master branch
) 
FetchContent_MakeAvailable(folly)
include_directories(${folly_SOURCE_DIR})
# message("add include ${folly_SOURCE_DIR}")


add_executable(ConditionVariable conditional_variable.cpp)
target_link_libraries(ConditionVariable pthread)

add_executable(Pid pid.cpp)
target_link_libraries(Pid pthread)

# add_executable(DagEngine dag_engine/main.cpp)
# target_link_libraries(DagEngine pthread)

add_executable(StdFuture future/future.cpp)
target_link_libraries(StdFuture pthread)

add_executable(Folly_future folly_future/folly_future_main.cpp)
target_link_libraries(Folly_future pthread)
target_link_libraries(Folly_future folly)