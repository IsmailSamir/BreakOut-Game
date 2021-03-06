cmake_minimum_required(VERSION 3.9)

# list the header files
set(HEADER_FILES
	include/game/game.h
	include/game/utilities.h
	include/game/collision.h
	include/component/level.h
	include/component/sprite.h
	include/component/background.h
	include/component/brick.h
	include/component/player_paddle.h
	include/component/ball.h
)

# list the source files
set(SOURCE_FILES
	src/game/game.cpp
	src/component/level.cpp
	src/component/background.cpp
	src/component/brick.cpp
	src/component/player_paddle.cpp
	src/component/ball.cpp
)


# add library target
add_library(game
	${HEADER_FILES}
	${SOURCE_FILES}
)

target_link_libraries(game
	PRIVATE
	resource_manager
	glew
	glfw
	glm
	program
	texture
	renderer
)

# make it reflect the same structure as the one on disk
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})

# Windows specfic flags to enable W variations of winapi
if(WIN32)
	target_compile_definitions(game
		PRIVATE
			OS_WINDOWS=1
			_CRT_SECURE_NO_WARNINGS
	)
elseif(UNIX)
	target_compile_definitions(game
		PRIVATE
			OS_LINUX=1
	)
endif()


# enable C++17
# disable any compiler specifc extensions
# add d suffix in debug mode
target_compile_features(game PUBLIC cxx_std_17)
set_target_properties(game PROPERTIES
	CXX_EXTENSIONS OFF
	DEBUG_POSTFIX d
)

# define debug macro
target_compile_definitions(game PRIVATE "$<$<CONFIG:DEBUG>:DEBUG>")

# generate exports header file
include(GenerateExportHeader)
generate_export_header(game
	EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/include/game/Exports.h
)

# list include directories
target_include_directories(game
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(game
	PRIVATE
		SHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../resources"
		IMAGE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../resources"
		LEVEL_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../resources"
)
