# Target name
set(target UnitTest)

# Sources
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

add_executable(${target} ${sources})
target_link_libraries(${target}
	SmashStone
	gtest
	effolkronium_random
	sfml-graphics
	sfml-main
	sfml-system
	sfml-window
)