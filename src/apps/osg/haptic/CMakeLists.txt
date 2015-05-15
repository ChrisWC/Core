#add openscenegraph dependency

#add inter-project dependencies


FIND_PACKAGE(OSG)
#if (NOT OPENSCENEGRAPH_FOUND)
#	message(ERROR " OpenSceneGraph not found! ")
#else (OPENSCENEGRAPH_FOUND)
	#include_directories(${OSG_INCLUDE_DIR})
	#link_directories(${OSG_LIBRARY})

#	message(FOUND " OpenSceneGraph")
#endif (NOT OPENSCENEGRAPH_FOUND)

include_directories( "${PROJECT_DIRECTORY}/include/apps/osg/haptic" )
add_executable( osghaptic main.cpp )
