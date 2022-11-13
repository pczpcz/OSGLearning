// Lession_1_Start.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include <osg/Node>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/PositionAttitudeTransform>

//节点访问器
class InfoVisitor : public osg::NodeVisitor
{
public:
    void apply(osg::Node& node)
    {
        std::cout << node.className() << std::endl;
        traverse(node);
    }

    void apply(osg::Geode& node)
    {
        std::cout << "node: " << node.className() << std::endl;
        for (unsigned int n = 0; n < node.getNumDrawables(); ++n) 
        {
            osg::Drawable *drawable = node.getDrawable(n);
            if (drawable) 
            {
                std::cout << "drawable: " << drawable->className() << std::endl;
            }
        }

        traverse(node);
    }
};

//回调（分为 更新回调 和 人机交互事件回调）
class RotateCallback : public osg::NodeCallback 
{
public:
    RotateCallback():rotate(){}

    void operator()(osg::Node *node, osg::NodeVisitor *nv)
    {
        osg::PositionAttitudeTransform* pat = dynamic_cast<osg::PositionAttitudeTransform *>(node);
        if (pat) 
        {
            ++rotate;
            pat->setAttitude(osg::Quat(osg::DegreesToRadians(rotate), osg::Z_AXIS));
        }
        traverse(node, nv);
    }
private:
    double rotate;
};

//空间变换节点   略
//开关节点    略
//LOD节点  略

int main()
{
    /*
    InfoVisitor visitor;
    osg::Node* root = osgDB::readNodeFile("osgData/cow.osg");
    root->accept(visitor);
    */

    osg::Node* node = osgDB::readNodeFile("osgData/cow.osg");
    osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform;
    pat->addChild(node);
    pat->setUpdateCallback(new RotateCallback);

    osgViewer::Viewer viewer;
    viewer.setSceneData(pat.get());
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
