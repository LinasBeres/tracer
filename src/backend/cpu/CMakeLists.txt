file(GLOB BACKEND_CPU_HEADERS
	bsdf/*.h
	camera/*.h
	geometry/*.h
	integrator/*.h
	render/*.h
	scene/*.h
	spindulysCPUBackend.h
)

file(GLOB BACKEND_CPU_SOURCES
	bsdf/*.cpp
	camera/*.cpp
	geometry/*.cpp
	integrator/*.cpp
	render/*.cpp
	scene/*.cpp
)

add_library(
	spindulysCPUBackend
	${BACKEND_CPU_SOURCES}
	${BACKEND_CPU_HEADERS}
	${PROJECT_SHADERS}
	${PROJECT_SCENES}
	${PROJECT_CONFIGS}
)

target_include_directories(
	spindulysCPUBackend PUBLIC
	./
)

target_link_libraries(
	spindulysCPUBackend
	spindulysFrontend
	embree_common
	${Boost_LIBRARIES}
	${EMBREE_LIBRARY}
	${TBB_LIBRARIES}
	${USD_LIBRARIES}
	spindulysShare
)
