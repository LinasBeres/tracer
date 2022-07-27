file(GLOB FRONTEND_HEADERS
	bsdf/*.h
	camera/*.h
	integrator/*.h
	material/*.h
	render/*.h
	sampling/*.h
	scene/*.h
	shapes/*.h
	utils/*.h
)

file(GLOB FRONTEND_SOURCES
	bsdf/*.cpp
	camera/*.cpp
	integrator/*.cpp
	material/*.cpp
	render/*.cpp
	sampling/*.cpp
	scene/*.cpp
	shapes/*.cpp
	utils/*.cpp
)

add_library(
	spindulysFrontend
	${FRONTEND_SOURCES}
	${FRONTEND_HEADERS}
	${PROJECT_SHADERS}
	${PROJECT_SCENES}
	${PROJECT_CONFIGS}
)

target_include_directories(
	spindulysFrontend PUBLIC
	./
)

target_link_libraries(
	spindulysFrontend
	embree_common
	${Boost_LIBRARIES}
	${EMBREE_LIBRARY}
	${TBB_LIBRARIES}
	${USD_LIBRARIES}
	spindulysShare
)
