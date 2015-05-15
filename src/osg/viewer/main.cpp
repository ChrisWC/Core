#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <osg/CoordinateSystemNode>

#include <osgViewer/Viewer>
#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>

#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/Device>

#include <iostream>
#include <stdint.h>

#include <osg/GLExtensions>

#ifndef GL_ARB_sync
#define GL_MAX_SERVER_WAIT_TIMEOUT        0x9111
#define GL_OBJECT_TYPE                    0x9112
#define GL_SYNC_CONDITION                 0x9113
#define GL_SYNC_STATUS                    0x9114
#define GL_SYNC_FLAGS                     0x9115
#define GL_SYNC_FENCE                     0x9116
#define GL_SYNC_GPU_COMMANDS_COMPLETE     0x9117
#define GL_UNSIGNALED                     0x9118
#define GL_SIGNALED                       0x9119
#define GL_ALREADY_SIGNALED               0x911A
#define GL_TIMEOUT_EXPIRED                0x911B
#define GL_CONDITION_SATISFIED            0x911C
#define GL_WAIT_FAILED                    0x911D
#define GL_SYNC_FLUSH_COMMANDS_BIT        0x00000001
#define GL_TIMEOUT_IGNORED                0xFFFFFFFFFFFFFFFFull
#endif


class MySwapBuffersCallback : public osg::GraphicsContext::SwapCallback
{
public:
	MySwapBuffersCallback() :
		_extensionInitialized(false),
		_glFenceSync(0),
		_glIsSync(0),
		_glDeleteSync(0),
		_glClientWaitSync(0),
		_glWaitSync(0),
		_glGetInteger64v(0),
		_glGetSynciv(0),
		_previousSync(0)

	{
		OSG_NOTICE << "Created Swap callback." << std::endl;
	}



	void setUpExtensions()
	{
		_extensionInitialized = true;
		osg::setGLExtensionFuncPtr(_glFenceSync, "glFenceSync");
		osg::setGLExtensionFuncPtr(_glIsSync, "glIsSync");
		osg::setGLExtensionFuncPtr(_glDeleteSync, "glDeleteSync");
		osg::setGLExtensionFuncPtr(_glClientWaitSync, "glClientWaitSync");
		osg::setGLExtensionFuncPtr(_glWaitSync, "glWaitSync");
		osg::setGLExtensionFuncPtr(_glGetInteger64v, "glGetInteger64v");
		osg::setGLExtensionFuncPtr(_glGetSynciv, "glGetSynciv");
	}



	virtual void swapBuffersImplementation(osg::GraphicsContext* gc)
	{

		// OSG_NOTICE<<"Before swap - place to do swap ready sync"<<std::endl;

		gc->swapBuffersImplementation();

		//glFinish();

		if (!_extensionInitialized) setUpExtensions();

		if (_glClientWaitSync)
		{

			if (_previousSync)
			{
				unsigned int num_seconds = 1;
				GLuint64 timeout = num_seconds * ((GLuint64)1000 * 1000 * 1000);
				_glClientWaitSync(_previousSync, 0, timeout);

				_glDeleteSync(_previousSync);
			}

			_previousSync = _glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);

		}

		//gc->getState()->checkGLErrors("after glWaitSync");
		//OSG_NOTICE<<"After swap"<<std::endl;
	}



#ifdef _WIN32
	typedef __int64 GLint64;
	typedef unsigned __int64 GLuint64;
#else
	typedef int64_t GLint64;
	typedef uint64_t GLuint64;
#endif
	typedef struct __GLsync *GLsync;

	typedef GLsync(GL_APIENTRY * PFNGLFENCESYNCPROC) (GLenum condition, GLbitfield flags);
	typedef GLboolean(GL_APIENTRY * PFNGLISSYNCPROC) (GLsync sync);
	typedef void (GL_APIENTRY * PFNGLDELETESYNCPROC) (GLsync sync);
	typedef GLenum(GL_APIENTRY * PFNGLCLIENTWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
	typedef void (GL_APIENTRY * PFNGLWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
	typedef void (GL_APIENTRY * PFNGLGETINTEGER64VPROC) (GLenum pname, GLint64 *params);
	typedef void (GL_APIENTRY * PFNGLGETSYNCIVPROC) (GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values);

	bool                        _extensionInitialized;

	PFNGLFENCESYNCPROC          _glFenceSync;
	PFNGLISSYNCPROC             _glIsSync;
	PFNGLDELETESYNCPROC         _glDeleteSync;
	PFNGLCLIENTWAITSYNCPROC     _glClientWaitSync;
	PFNGLWAITSYNCPROC           _glWaitSync;
	PFNGLGETINTEGER64VPROC      _glGetInteger64v;
	PFNGLGETSYNCIVPROC          _glGetSynciv;



	GLsync _previousSync;

};

int main(int argc, char** argv)
{
	osg::ArgumentParser arguments(&argc, argv);

	arguments.getApplicationUsage()->setApplicationName(arguments.getApplicationName());

	osgViewer::CompositeViewer viewer(arguments);

	bool doArbSync = arguments.read("--sync");

	return viewer.run();
}
