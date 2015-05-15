option(BUILD_SAMPLES "Build Sample Applications?" OFF)

if (BUILD_SAMPLES)
	add_subdirectory( cuda )
endif (BUILD_SAMPLES)
