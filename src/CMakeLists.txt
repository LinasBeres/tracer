file(GLOB PROJECT_HEADERS
	bsdf/*.h
	frontend/camera/*.h
	gui/*.h
	integrator/*.h
	material/*.h
	math/*.h
	object/*.h
	opengl/*.h
	render/*.h
	sampling/*.h
	scene/*.h
	utility/*.h
	share/config.h
)

file(GLOB PROJECT_SOURCES
	bsdf/*.cpp
	frontend/camera/*.cpp
	gui/*.cpp
	integrator/*.cpp
	material/*.cpp
	math/*.cpp
	object/*.cpp
	opengl/*.cpp
	render/*.cpp
	sampling/*.cpp
	scene/*.cpp
	utility/*.cpp
	main.cpp
)

add_executable(
	${PROJECT_NAME}
	${PROJECT_SOURCES}
	${PROJECT_HEADERS}
	${PROJECT_SHADERS}
	${PROJECT_SCENES}
	${PROJECT_CONFIGS}
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
)

set_target_properties(${PROJECT_NAME} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
)
