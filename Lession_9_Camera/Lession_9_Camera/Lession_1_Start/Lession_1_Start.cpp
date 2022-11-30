// Lession_1_Start.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include <osg/Node>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/PositionAttitudeTransform>
#include <osg/Texture2D>
#include <osg/TextureCubeMap>
#include <osgUtil/SmoothingVisitor>
#include <osg/LineWidth>
#include <osg/DrawPixels>
#include <osgText/Text>
#include <osg/ShapeDrawable>
#include <osg/TexGen>
#include <osg/Camera>

osg::Camera* CreateCamera(const osg::BoundingSphere& bound) 
{
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	
	float distance = 2  * bound.radius();
	float near = bound.center().z() - bound.radius();
	float far = bound.center().z() + bound.radius();
	float left = -bound.radius();
	float right = bound.radius();
	float top = bound.radius();
	float bottom = -bound.radius();
	camera->setProjectionMatrixAsOrtho(left, right, bottom, top, near, far);

	osg::Vec3 lookatPos = bound.center();
	osg::Vec3 upDirection = osg::Vec3(0.0, 1.0, 0.0);
	osg::Vec3 cameraPos = lookatPos + osg::Vec3(0.0, 0.0, distance);
	camera->setViewMatrixAsLookAt(cameraPos, lookatPos, upDirection);

	return camera.release();
}

int main()
{
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("osgData/cow.osg");
	osg::ref_ptr<osg::Camera> camera = CreateCamera(node->getBound());

	camera->addChild(node.get());

	osgViewer::Viewer viewer;
	viewer.setSceneData(camera.get());
	return viewer.run();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
