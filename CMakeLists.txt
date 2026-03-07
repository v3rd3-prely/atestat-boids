cmake_minimum_required(VERSION 3.2)
project( Boids )
# add_compile_options("-pg")
# add_link_options("-pg")

include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories(${PROJECT_SOURCE_DIR}/src/)
include_directories(${PROJECT_SOURCE_DIR}/)
include_directories(${PROJECT_SOURCE_DIR}/ext/SFML/include/)
link_directories(${PROJECT_SOURCE_DIR}/ext/SFML/lib/)
link_directories(${PROJECT_SOURCE_DIR}/ext/SFML/bin/)

add_executable(${PROJECT_NAME} src/main.cpp src/boid.cpp src/fps.cpp src/ray.cpp src/rest.cpp src/slider.cpp src/wall.cpp src/info.cpp src/showable.cpp src/segment.cpp)

target_link_libraries(${PROJECT_NAME} sfml-graphics-2.dll sfml-system-2.dll sfml-window-2.dll)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
target_link_libraries(${PROJECT_NAME} "-Wl,--stack,10000000")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
