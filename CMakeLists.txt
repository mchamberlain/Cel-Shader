cmake_minimum_required(VERSION 2.8)
project(CelShader)

include_directories("include")
add_subdirectory("src")

install(DIRECTORY shaders DESTINATION .)
install(DIRECTORY models DESTINATION . FILES_MATCHING PATTERN *.raw)
if(WIN32)
	install(DIRECTORY thirdparty/lib/ DESTINATION . FILES_MATCHING PATTERN *.dll)
else(WIN32)
	install(DIRECTORY thirdparty/lib/ DESTINATION . FILES_MATCHING PATTERN *.so)
endif(WIN32)