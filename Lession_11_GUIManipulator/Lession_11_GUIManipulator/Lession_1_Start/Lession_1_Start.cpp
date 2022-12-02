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
#include <osgManipulator/TranslateAxisDragger>
#include <osgManipulator/CommandManager>
#include <osgUtil/LineSegmentIntersector>

class UserGUIEventHandler : public osgGA::GUIEventHandler 
{
public:
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa, osg::Object* obj, osg::NodeVisitor* nv) 
	{
		osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
		if (!viewer)
		{
			return false;
		}
	
		switch (ea.getEventType())
		{
		case osgGA::GUIEventAdapter::PUSH: 
			{
				_pointer.reset();
				osgUtil::LineSegmentIntersector::Intersections hits;
				if (viewer->computeIntersections(ea.getX(), ea.getY(), hits))
				{
					_pointer.setCamera(viewer->getCamera());
					_pointer.setMousePosition(ea.getX(), ea.getY());

					//获取所有有交集的对象
					for (auto ittr = hits.begin(); ittr != hits.end(); ++ittr) 
					{
						_pointer.addIntersection(ittr->nodePath, ittr->getLocalIntersectPoint());
					}

					//选取第一个交集对象，其他对象不选取???, 用front没太看明白，drager一定是第一个吗？？？
					for (auto ittr = _pointer._hitList.front().first.begin(); ittr != _pointer._hitList.front().first.end(); ++ittr) 
					{
						osgManipulator::Dragger* dragger = dynamic_cast<osgManipulator::Dragger*>(*ittr);
						if (dragger)
						{
							dragger->handle(_pointer, ea, aa);
							_activeDragger = dragger;
							break;
						}
					}
				}
			}
			break;
		case osgGA::GUIEventAdapter::DRAG:
		case osgGA::GUIEventAdapter::RELEASE: 
			{
				if (_activeDragger) 
				{
					_pointer._hitIter = _pointer._hitList.begin();
					_pointer.setCamera(viewer->getCamera());
					_pointer.setMousePosition(ea.getX(), ea.getY());	//传递拖动过程中坐标位置变化
					_activeDragger->handle(_pointer, ea,aa);
				}
				
				//osgGA::GUIEventAdapter::DRAG也会进来，固由此判断
				if (ea.getEventType() == osgGA::GUIEventAdapter::RELEASE)
				{
					_activeDragger = NULL;
					_pointer.reset();
				}
			}
			break;
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
protected:
	osgManipulator::Dragger* _activeDragger;
	osgManipulator::PointerInfo _pointer;
};

int main()
{
	osg::ref_ptr<osg::Switch> root = new osg::Switch;
	osg::ref_ptr<osg::Node> node0 = osgDB::readNodeFile("osgData/cessna.osg");
	osg::ref_ptr<osg::Node> node1 = osgDB::readNodeFile("osgData/cessnafire.osg");
	//root->addChild(node0.get(), true);
	//root->addChild(node1.get(), true);

	//拖拽功能
	osg::ref_ptr<osg::Node> axis = osgDB::readNodeFile("osgData/axes.osgt");
	osg::ref_ptr<osgManipulator::Selection> selection = new osgManipulator::Selection;
	selection->addChild(node0.get());

	//操控的几何原理还不太懂？？？
	float scale = node0->getBound().radius() * 1.6;
	osg::ref_ptr<osgManipulator::TranslateAxisDragger> dragger = new osgManipulator::TranslateAxisDragger;
	dragger->setupDefaultGeometry();
	dragger->setMatrix(osg::Matrix::scale(scale, scale, scale) * osg::Matrix::translate(node0->getBound().center()));

	root->addChild(selection.get());
	root->addChild(dragger.get());
	root->addChild(axis.get());

	osg::ref_ptr<osgManipulator::CommandManager> cmdManager = new osgManipulator::CommandManager;
	cmdManager->connect(*dragger, *selection);

	osgViewer::Viewer viewer;
	viewer.setSceneData(root.get());
	viewer.addEventHandler(new UserGUIEventHandler);
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
