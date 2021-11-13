# to fix include errors, make sur c_cpp_properties.json has the include paths, cmake has includes, ctrl+shift+p >Cmake: Configure, make, and it should refresh

cmake_minimum_required(VERSION 3.0.0)
project(MouseCore VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(GLEW REQUIRED)

cmake_policy(SET CMP0072 NEW)
find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} /usr/local/include /usr/local/include/spine-c /usr/include /home/mouse/cdev)
link_directories(/usr/local/lib /usr/lib /lib32)

add_library(MouseCore SHARED
Camera/Camera.c
Camera/CameraBuffer.c
DataStructures/LinkedList.c
DataStructures/Queue.c
MouseCore.c
PersistentMappedBuffer.c
Quad/Quad.c
Quad/QuadBatch.c
Quad/QuadBatchable.c
Quad/QuadBufferHelpers.c
Quad/QuadBuffers.c
Quad/QuadBuffersMapped.c
Quad/QuadDrawable.c
Spine/SpineBuffers.c
Spine/SpineMesh.c
Shader.c
stb_image.c
Transform.c
Utility.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(MouseCore ${OPENGL_LIBRARY} GLEW::GLEW spine-c m)