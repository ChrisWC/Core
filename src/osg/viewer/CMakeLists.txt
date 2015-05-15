find_package(OSG REQUIRED)

include_directories(${OSG_INCLUDE_DIR})
link_directories(${OSG_LIBRARY})
add_executable(model_viewer main.cpp ${OSG_LIBRARY})

target_link_libraries(model_viewer ${OSG_LIBRARY} ${OSGVIEWER_LIBRARY})
