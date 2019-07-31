cmake_minimum_required (VERSION 3.11)

project (shader_examples)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(ShdrShwdwn_OPENCL "" ON)
if(${ShdrShwdwn_OPENCL})
	#Using FindOpenCl usually ends at the CUDA install, which has old CL headders.
	#I'm using this instead
	set(OPENCL_DIR "${CMAKE_SOURCE_DIR}/deps/AMD-Opencl/3-0")
	set(OpenCL_LIBRARIES ${OPENCL_DIR}/lib/x86_64/OpenCL.lib)
	set(OpenCL_INCLUDE_DIRS "${OPENCL_DIR}/include")
	
	file(GLOB OPENCL_SOURCE_FILES opencl/*.cpp opencl/*.h)
	source_group(OPENCL FILES ${OPENCL_SOURCE_FILES})
	set(SOURCE_FILES ${SOURCE_FILES} ${OPENCL_SOURCE_FILES})
endif(${ShdrShwdwn_OPENCL})

file(GLOB children RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" cl/*)
SET(dirlist "")
FOREACH(child ${children})
  IF(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${child})
	get_filename_component(childName ${child} NAME BASE_DIR practicals)
    LIST(APPEND dirlist ${childName})
    file(GLOB_RECURSE SOURCE_FILES ${child}/*.cpp ${child}/*.h ${child}/*.glsl)
    file(GLOB_RECURSE NOT_RESOURCE_FILES ${child}/*.cpp ${child}/*.h)
    file(GLOB_RECURSE RESOURCE_FILES  ${child}/*.*)
    LIST(REMOVE_ITEM RESOURCE_FILES ${NOT_RESOURCE_FILES}) 
    
    add_library( ${childName} MODULE  ${SOURCE_FILES})
	target_include_directories(${childName} PUBLIC "G:/AMD-Opencl/3-0/include")
		target_include_directories(${childName} PUBLIC "../shader_showdown")
	target_link_libraries(${childName} PUBLIC "G:/AMD-Opencl/3-0/lib/x86_64/OpenCL.lib")
	if(${MSVC})
		target_compile_options(${childName} PUBLIC /MP)
	#	target_link_libraries(MAIN "rpcrt4.lib")
	endif()

  ENDIF()
ENDFOREACH()



