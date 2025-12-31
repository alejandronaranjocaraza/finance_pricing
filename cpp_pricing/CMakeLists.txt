cmake_minimum_required(VERSION 3.16)
project(example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Core C++ library (TARGET: core)
add_library(core
    bindings/buildVanillaOption.cpp
    bindings/buildStock.cpp
    bindings/buildBSM.cpp
    src/instruments/option.cpp
    src/instruments/vanillaOption.cpp
    src/instruments/dividend.cpp
    src/instruments/stock.cpp
    src/exercise/americanExercise.cpp
    src/exercise/europeanExercise.cpp
    src/payoffs/callPayoff.cpp
    src/payoffs/putPayoff.cpp
    src/models/bsm.cpp
)

set_target_properties(core PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(core
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# Python bindings (TARGET: pyext)
set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 REQUIRED)

pybind11_add_module(pyext
    bindings/module.cpp
)

target_link_libraries(pyext
    PRIVATE core
)
