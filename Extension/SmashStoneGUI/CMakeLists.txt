# Target name
set(target SmashStoneGUI)

# Sources
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

add_executable(${target} ${sources})
target_link_libraries(${target}
	SmashStone
	sfml-graphics
	sfml-main
	sfml-system
	sfml-window
	gtest
)