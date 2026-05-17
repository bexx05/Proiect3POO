cmake_minimum_required(VERSION 3.28)
project(untitled LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(gol main.cpp
        Cell.h
        Cell.cpp
        Conwaycell.h
        Grid.h
        Grid.cpp
        Conwaycell.cpp
        Highlifecell.h
        Highlifecell.cpp
        Daynightcell.h
        Daynight.cpp
        Exceptions.h
        Exceptions.cpp
        CellFactory.h
        GenerationLog.h
        SimulationConfig.h
        ISimulationObserver.h
        ConsoleStatsObserver.h
)
target_compile_features(gol PRIVATE cxx_std_17)
target_link_libraries(gol PRIVATE SFML::Graphics)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT gol)