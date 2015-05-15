option(BUILD_APPS "Build applications" ON)

if (BUILD_APPS)
	add_subdirectory(osg)
endif (BUILD_APPS)
