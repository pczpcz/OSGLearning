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
#include <osg/DrawPixels>
#include <osgText/Text>

int main()
{
    osg::ref_ptr<osg::DrawPixels> imageDrawable1 = new osg::DrawPixels;
    imageDrawable1->setPosition(osg::Vec3(0.0, 0.0, 0.0));
    imageDrawable1->setImage(osgDB::readImageFile("osgData/images/osg64.png"));

    osg::ref_ptr<osg::DrawPixels> imageDrawable2 = new osg::DrawPixels;
    imageDrawable2->setPosition(osg::Vec3(80.0, 0.0, 0.0));
    imageDrawable2->setImage(osgDB::readImageFile("osgData/images/osg128.png"));

    osg::ref_ptr<osg::DrawPixels> imageDrawable3 = new osg::DrawPixels;
    imageDrawable3->setPosition(osg::Vec3(200.0, 0.0, 0.0));
    imageDrawable3->setImage(osgDB::readImageFile("osgData/images/osg256.png"));

    osg::ref_ptr<osgText::Text> text = new osgText::Text;
    text->setFont("osgData/fonts/arial.ttf");
    text->setText("Hello World!");
    text->setPosition(osg::Vec3(0.0, 0.0, 0.0));
    text->setColor(osg::Vec4(1.0, 0.0, 0.0, 1.0));
    text->setAxisAlignment(osgText::Text::XZ_PLANE);

    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    //geode->addDrawable(imageDrawable1.get());
    //geode->addDrawable(imageDrawable2.get());
    //geode->addDrawable(imageDrawable3.get());
    geode->addDrawable(text);

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
