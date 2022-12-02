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
#include <osgViewer/CompositeViewer>
#include <osgGA/GUIEventHandler>

class UserGUIEventHandler : public osgGA::GUIEventHandler 
{
public:
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa, osg::Object* obj, osg::NodeVisitor* nv) 
	{
		osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer *>(&aa);
		if (!viewer) 
		{
			return false;
		}
	
		switch (ea.getEventType())
		{
		case osgGA::GUIEventAdapter::KEYDOWN: 
			{
				if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Space) 
				{
					std::cout << "hahh" << std::endl;
					int width = ea.getWindowWidth();
					int height = ea.getWindowHeight();
					viewer->requestWarpPointer(0.5 * width, 0.5 * height);
				}
				else 
				{
					osg::Switch* root = dynamic_cast<osg::Switch*>(viewer->getSceneData());
					if (!root)
					{
						return false;
					}

					if (ea.getKey() == osgGA::GUIEventAdapter::KEY_1)
					{
						root->setValue(0, true);
						root->setValue(1, false);
					}
					else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_2)
					{
						root->setValue(0, false);
						root->setValue(1, true);
					}
				}
				return true;
			}
			break;
		default:
			break;
		}
		return false;
	}
};

int main()
{
	osg::ref_ptr<osg::Switch> root = new osg::Switch;
	osg::ref_ptr<osg::Node> node0 = osgDB::readNodeFile("osgData/cessna.osg");
	osg::ref_ptr<osg::Node> node1 = osgDB::readNodeFile("osgData/cessnafire.osg");

	root->addChild(node0.get(), true);
	root->addChild(node1.get(), true);

	osg::ref_ptr<UserGUIEventHandler> handler = new UserGUIEventHandler;

	osgViewer::Viewer viewer;
	viewer.setSceneData(root.get());
	viewer.addEventHandler(handler.get());
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
