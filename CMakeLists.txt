cmake_minimum_required(VERSION 3.12)

project(tracer
    VERSION 1.0
    DESCRIPTION "Renderer using C++, Embree and USD to achieve Path Tracing techniques on the CPU."
    HOMEPAGE_URL "https://github.com/JoshuaSenouf/tracer"
    LANGUAGES C CXX
)

# Adding CMake modules
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_SOURCE_DIR}/cmake/dependencies/external
    ${CMAKE_SOURCE_DIR}/cmake/dependencies/internal
    ${CMAKE_SOURCE_DIR}/cmake/modules
    ${CMAKE_SOURCE_DIR}/cmake/setup
)

# Project CMake setup
include(Options)
include(CXX)

include(SetupBoost)
include(SetupEmbree)
include(SetupTBB)
include(SetupUSD)

add_subdirectory(thirdparty)

# OLD !!!!!!!!!!!!!!!

file(GLOB PROJECT_HEADERS
    src/bsdf/*.h
    src/camera/*.h
    src/gui/*.h
    src/integrator/*.h
    src/material/*.h
    src/math/*.h
    src/object/*.h
    src/opengl/*.h
    src/render/*.h
    src/sampling/*.h
    src/scene/*.h
    src/utility/*.h
    src/*.h)

file(GLOB PROJECT_SOURCES
    src/bsdf/*.cpp
    src/camera/*.cpp
    src/gui/*.cpp
    src/integrator/*.cpp
    src/material/*.cpp
    src/math/*.cpp
    src/object/*.cpp
    src/opengl/*.cpp
    src/render/*.cpp
    src/sampling/*.cpp
    src/scene/*.cpp
    src/utility/*.cpp
    src/*.cpp)

file(GLOB PROJECT_SHADERS
    res/shaders/*.frag
    res/shaders/*.glsl
    res/shaders/*.vert)

file(GLOB PROJECT_SCENES
    res/scenes/*.usd
    res/scenes/*.usda
    res/scenes/*.usdc
    res/scenes/*.usdz)

file(GLOB PROJECT_CONFIGS
    CMakeLists.txt
    README.md
    .gitattributes
    .gitignore
    .gitmodules)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Scenes" FILES ${PROJECT_SCENES})

add_definitions(-DGLFW_INCLUDE_NONE)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
    ${PROJECT_SHADERS}
    ${PROJECT_SCENES}
    ${PROJECT_CONFIGS})

target_include_directories(${PROJECT_NAME} PRIVATE
    src/bsdf/
    src/camera/
    src/gui/
    src/integrator/
    src/material/
    src/math/
    src/object/
    src/opengl/
    src/render/
    src/sampling/
    src/scene/
    src/utility/
)

target_link_libraries(${PROJECT_NAME}
    embree_common
    glfw
    ${GLFW_LIBRARIES}
    glad
    imgui
    tinyexr
    ${Boost_LIBRARIES}
    ${EMBREE_LIBRARY}
    ${TBB_LIBRARIES}
    ${USD_LIBRARIES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
)
