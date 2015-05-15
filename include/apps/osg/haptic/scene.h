#pragma once

#include <iostream>
#include <vector>
#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <osgViewer/Viewer>
#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgText/Text>
#include <osgUtil/SmoothingVisitor>
#include <osg/Light>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgGA/SphericalManipulator>
#include <osgGA/FirstPersonManipulator>


class Scene
{
public:

	Scene();

	~Scene();

	void init(osgViewer::CompositeViewer& viewer) {}

	void load(osgViewer::CompositeViewer& viewer)
	{
		osg::GraphicsContext::WindowingSystemInterface* wsi = osg::GraphicsContext::getWindowingSystemInterface();
		if (!wsi)
		{
			osg::notify(osg::NOTICE) << "Error, no WindowSystemInterface available, cannot create windows." << std::endl;
			return;
		}

		unsigned int width, height;
		wsi->getScreenResolution(osg::GraphicsContext::ScreenIdentifier(0), width, height);

		osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
		traits->x = 100;
		traits->y = 100;
		traits->width = 1000;
		traits->height = 800;
		traits->windowDecoration = true;
		traits->doubleBuffer = true;
		traits->sharedContext = 0;

		osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());
		osgViewer::View* view = new osgViewer::View;
		view->setName("Scene View");
		viewer.addView(view);
		view->setUpViewOnSingleScreen(0);
		view->setSceneData(scene.get());
		view->getCamera()->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));		
		view->getCamera()->setGraphicsContext(gc.get());
		view->setCameraManipulator(new osgGA::TrackballManipulator());

		viewer.realize();
	}

	bool isInitialized()
	{
		return true;
	}
};
