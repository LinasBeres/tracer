file(GLOB GUI_HEADERS
	window.h
	opengl/*.h
)

file(GLOB GUI_SOURCES
	main.cpp
	window.cpp
	opengl/*.cpp
)

add_executable(
	${PROJECT_NAME}
	${GUI_SOURCES}
	${GUI_HEADERS}
	${GUI_SHADERS}
	${GUI_SCENES}
	${GUI_CONFIGS}
)

add_definitions(-DGLFW_INCLUDE_NONE)

target_link_libraries(
	${PROJECT_NAME}
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
	spindulysShare
	spindulysFrontend
)

set_target_properties(${PROJECT_NAME} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
)
