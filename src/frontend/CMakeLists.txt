file(GLOB FRONTEND_HEADERS
	camera/*.h
)

file(GLOB FRONTEND_SOURCES
	camera/*.cpp
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
