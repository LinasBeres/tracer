file(GLOB FRONTEND_HEADERS
	spindulysFrontend.h
	camera/*.h
	geometry/*.h
	render/*.h
	scene/*.h
	utils/*.h
)

file(GLOB FRONTEND_SOURCES
	camera/*.cpp
	geometry/*.cpp
	render/*.cpp
	scene/*.cpp
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
	${TBB_LIBRARIES}
	${USD_LIBRARIES}
	spindulysShare
)
