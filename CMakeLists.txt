cmake_minimum_required(VERSION 3.10)

project(PROF_APPLICATION)

set(Application ./src/Application)

set(Framework 
    ./src/Framework/PROF.cpp
    ./src/Framework/GLCall.cpp
    ./src/Framework/Colors.cpp)

set(Modules
    ./src/Modules/Component.cpp
    ./src/Modules/Object.cpp
    ./src/Modules/Scene.cpp
    ./src/Modules/Shader.cpp
    ./src/Modules/Camera.cpp
    ./src/Modules/Model.cpp
    ./src/Modules/RigidBody.cpp)

set(Objects
    ./src/Objects/Sphere.cpp
    ./src/Objects/Arrow.cpp
    ./src/Objects/Line.cpp
    ./src/Objects/Field.cpp)

set(SRCS ${Application} ${Framework} ${Modules} ${Objects})

include_directories(./include ./include/Framework)
link_directories(./lib)
add_executable(Application ${SRCS})

if(UNIX)
    set(LIBS GL glfw3 GLU GLEW pthread X11 dl Xcursor Xinerama Xxf86vm Xrandr)
elseif(MSVC)
    set(LIBS opengl32 glew32s glfw3 User32 Gdi32 Shell32)
endif()

target_link_libraries(Application ${LIBS})