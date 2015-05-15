#pragma once

#ifdef DEBUG 1
	#include <iostream>
	#include <assert>
#endif

#include <osg/Group>
#include <osg/Geode>
#include <osg/Point>
#include <osg/ShapeDrawable>
#include <osgUtil/IntersectionVisitor>

class Voxelizer
{
private:
	osg::Vec3d stride;
public:
	Voxelizer();
	~Voxelizer();

	osg::ref_ptr<osg::Node> create_voxel(osg::Vec3d point, osg::Vec3d scale, bool immediate)
	{
		//if immediate then add to scene...
	}
	osg::ref_ptr<osg::Group> voxelize_ray(osg::ref_ptr<osg::Group> group, osg::Vec3d pos, osg::Vec3d up, osg::Vec3d lookAt, bool immediate)
	{
		//get boundingbox

		//calculate h steps, w steps needed

		//shoot lines from each location

		//for each intersection
			//create voxel
			
			//if hasIntersectionNext and count is odd
				//step between isect pair
					//add voxel
	}
	osg::ref_ptr<osg::Group> voxelize_plane(osg::ref_ptr<osg::Group> group, osg::Vec3d pos, osg::Vec3d up, osg::Vec3d lookAt, bool immediate)
	{
		//get boundingbox

		//calculate width
		//calculate h steps

		//create planes and calculate intersections
	}
}
