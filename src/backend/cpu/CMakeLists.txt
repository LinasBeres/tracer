file(GLOB BACKEND_CPU_HEADERS
	camera/*.h
	integrator/*.h
	spindulysCPUBackend.h
)

file(GLOB BACKEND_CPU_SOURCES
	camera/*.cpp
	integrator/*.cpp
)

add_library(
	spindulysCPUBackend
	${FRONTEND_SOURCES}
	${FRONTEND_HEADERS}
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
