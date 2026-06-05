cmake_minimum_required(VERSION 3.10)
project(Chumbimuni_Andre_pc3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(include)

# ejecutable demo
add_executable(demos_module 
    demos/demos_Range_Module.cpp 
    src/RangeModule.cpp
)
# Tests
add_executable(test_module 
    tests/test_range_module.cpp 
    src/RangeModule.cpp
)

# Benchmark
add_executable(benchmark_module 
    benchmark/benchmark_range_module.cpp 
    src/RangeModule.cpp
)