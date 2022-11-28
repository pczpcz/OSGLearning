// Lession_1_Start.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include <osg/Node>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/PositionAttitudeTransform>
#include <osg/Texture2D>
#include <osgUtil/SmoothingVisitor>
#include <osg/LineWidth>

class UserUpdateCallback : public osg::Drawable::UpdateCallback 
{
public:
    UserUpdateCallback() 
        : angle(0.0)
    {
    }

    void update(osg::NodeVisitor *visitor, osg::Drawable *drawable) 
    {
        osg::Geometry *geo = dynamic_cast<osg::Geometry *>(drawable);
        if (!geo) 
        {
            return;
        }

        osg::Vec3Array *vertices = dynamic_cast<osg::Vec3Array *>(geo->getVertexArray());
        if (!vertices || vertices->empty()) 
        {
            return;
        }

        for (auto ittr = vertices->begin(); ittr != vertices->end() - 1; ++ittr) 
        {
            //ittr->set(*(ittr+1));
            ittr->set(ittr->x(), ittr->y(), (ittr + 1)->z());
        }
        
        angle += 1.0 / 10.0;
        osg::Vec3& vertice = vertices->back();
        //vertice.set(10.0 * cos(angle), 0.0, 10.0 * sin(angle));
        vertice.set(vertice.x(), 0.0, 10.0 * sin(angle));

        vertices->dirty();
    }
private:
    double angle;
};

int main()
{
    osg::ref_ptr<osg::Geometry> geo = new osg::Geometry;
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    for (int i = 0; i < 10; ++i) 
    {
        vertices->push_back(osg::Vec3(i*1.0, 0.0, 0.0));
    }
    geo->setVertexArray(vertices.get());
    osg::ref_ptr<UserUpdateCallback> userCallback = new UserUpdateCallback;
    geo->setUpdateCallback(userCallback);
    geo->addPrimitiveSet(new osg::DrawArrays(osg::DrawArrays::LINE_STRIP, 0, 10));
    geo->setUseDisplayList(false);
    geo->setUseVertexBufferObjects(true);
    geo->setInitialBound(osg::BoundingBox(osg::Vec3(-10.0, -10.0, -10.0), osg::Vec3(10.0, 10.0, 10.0)));

    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(geo.get());
    geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    geode->getOrCreateStateSet()->setAttribute(new osg::LineWidth(2.0));

    osgViewer::Viewer viewer;
    viewer.setSceneData(geode.get());
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
