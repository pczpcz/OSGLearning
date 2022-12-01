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

osg::Camera *CreateCamera(int x, int y, int width, int height) 
{
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->windowDecoration = false;
	traits->x = x;
	traits->y = y;
	traits->width = width;
	traits->height = height;
	traits->doubleBuffer = true;
	osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());
	
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setGraphicsContext(gc.get());
	camera->setViewport(0, 0, width, height);

	return camera.release();
}

int main()
{
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("osgData/cow.osg");

	osgViewer::Viewer viewer;

	//TODO：投影矩阵平移方向，正负号没有太明白

	/*
	viewer.addSlave(CreateCamera(100, 100, 400, 300), osg::Matrixd::translate(0.5, -0.5, 0.0), osg::Matrixd());		//左上角为原点
	viewer.addSlave(CreateCamera(505, 100, 400, 300), osg::Matrixd::translate(-0.5, -0.5, 0.0), osg::Matrixd());	//左上角为原点
	viewer.addSlave(CreateCamera(100, 405, 400, 300), osg::Matrixd::translate(0.5, 0.5, 0.0), osg::Matrixd());		//左上角为原点
	viewer.addSlave(CreateCamera(505, 405, 400, 300), osg::Matrixd::translate(-0.5, 0.5, 0.0), osg::Matrixd());		//左上角为原点
	*/

	viewer.addSlave(CreateCamera(100, 100, 400, 300), osg::Matrixd::translate(1.0, -1.0, 0.0), osg::Matrixd());		//左上角为原点
	viewer.addSlave(CreateCamera(505, 100, 400, 300), osg::Matrixd::translate(-1.0, -1.0, 0.0), osg::Matrixd());	//左上角为原点
	viewer.addSlave(CreateCamera(100, 405, 400, 300), osg::Matrixd::translate(1.0, 1.0, 0.0), osg::Matrixd());		//左上角为原点
	viewer.addSlave(CreateCamera(505, 405, 400, 300), osg::Matrixd::translate(-1.0, 1.0, 0.0), osg::Matrixd());		//左上角为原点

	viewer.setSceneData(node.get());
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
