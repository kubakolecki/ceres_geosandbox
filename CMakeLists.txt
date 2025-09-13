cmake_minimum_required(VERSION 3.30)
project(ceres_geosandbox VERSION 1.0.0)

add_executable(ceres_geosandbox
ceres_geosandbox.cpp
input_output.cpp
OptimizationProblem.cpp
Evaluator.cpp
)

set_property(TARGET ceres_geosandbox PROPERTY CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Ceres 2.1 REQUIRED)
find_package(Eigen3 3.4 REQUIRED)


target_link_libraries(ceres_geosandbox PRIVATE Ceres::ceres)
target_link_libraries(ceres_geosandbox PRIVATE Eigen3::Eigen)

target_include_directories(ceres_geosandbox PRIVATE include)

