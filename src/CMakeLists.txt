# Add our custom cmake modules directory to the search path
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})
# Add the thirdparty directory to the search path for all find_ commands
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${PROJECT_SOURCE_DIR}/thirdparty)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

set(SOURCE_FILES
	CelShader.cpp
	main.cpp
	MiscGL.cpp
	RawMeshLoader.cpp
	VectorN.cpp)
set(HEADER_FILES
	../include/CelShader.h
	../include/MiscGL.h
	../include/RawMeshLoader.h
	../include/VectorN.h)
add_executable(CelShader ${SOURCE_FILES} ${HEADER_FILES})
include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})
target_link_libraries(CelShader ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES})

install(TARGETS CelShader RUNTIME DESTINATION .)
