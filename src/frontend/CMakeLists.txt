file(GLOB FRONTEND_HEADERS
	camera/*.h
	render/*.h
	scene/*.h
	shapes/*.h
	spindulysFrontend.h
	utils/*.h
)

file(GLOB FRONTEND_SOURCES
	camera/*.cpp
	render/*.cpp
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
	${Boost_LIBRARIES}
	${EMBREE_LIBRARY}
	${TBB_LIBRARIES}
	${USD_LIBRARIES}
	spindulysShare
)
