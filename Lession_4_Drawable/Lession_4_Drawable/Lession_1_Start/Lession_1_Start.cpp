// Lession_1_Start.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include <osg/Node>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/PositionAttitudeTransform>
#include <osg/Texture2D>
#include <osgUtil/SmoothingVisitor>

osg::Drawable *CreateHouseWall()
{
    osg::ref_ptr<osg::Vec3Array> vertex = new osg::Vec3Array;
    vertex->push_back(osg::Vec3(0.0, 0.0, 4.0));
    vertex->push_back(osg::Vec3(0.0, 0.0, 0.0));
    vertex->push_back(osg::Vec3(6.0, 0.0, 4.0));
    vertex->push_back(osg::Vec3(6.0, 0.0, 0.0));
    vertex->push_back(osg::Vec3(6.0, 4.0, 4.0));
    vertex->push_back(osg::Vec3(6.0, 4.0, 0.0));
    vertex->push_back(osg::Vec3(0.0, 4.0, 4.0));
    vertex->push_back(osg::Vec3(0.0, 4.0, 0.0));
    vertex->push_back(osg::Vec3(0.0, 0.0, 4.0));
    vertex->push_back(osg::Vec3(0.0, 0.0, 0.0));

    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
    normals->push_back(osg::Vec3(-0.707, -0.707, 0.0));
    normals->push_back(osg::Vec3(-0.707, -0.707, 0.0));
    normals->push_back(osg::Vec3(0.707, -0.707, 0.0));
    normals->push_back(osg::Vec3(0.707, -0.707, 0.0));
    normals->push_back(osg::Vec3(0.707, 0.707, 0.0));
    normals->push_back(osg::Vec3(0.707, 0.707, 0.0));
    normals->push_back(osg::Vec3(-0.707, 0.707, 0.0));
    normals->push_back(osg::Vec3(-0.707, 0.707, 0.0));
    normals->push_back(osg::Vec3(-0.707, -0.707, 0.0));
    normals->push_back(osg::Vec3(-0.707, -0.707, 0.0));

    osg::ref_ptr<osg::Vec2Array> textcoordinates = new osg::Vec2Array;
    textcoordinates->push_back(osg::Vec2(0.0, 1.0));
    textcoordinates->push_back(osg::Vec2(0.0, 0.0));
    textcoordinates->push_back(osg::Vec2(0.3, 1.0));
    textcoordinates->push_back(osg::Vec2(0.3, 0.0));
    textcoordinates->push_back(osg::Vec2(0.5, 1.0));
    textcoordinates->push_back(osg::Vec2(0.5, 0.0));
    textcoordinates->push_back(osg::Vec2(0.8, 1.0));
    textcoordinates->push_back(osg::Vec2(0.8, 0.0));
    textcoordinates->push_back(osg::Vec2(1.0, 1.0));
    textcoordinates->push_back(osg::Vec2(1.0, 0.0));

    osg::ref_ptr<osg::Geometry> geo = new osg::Geometry;
    geo->setVertexArray(vertex.get());
    geo->setNormalArray(normals.get());
    geo->setTexCoordArray(0, textcoordinates.get());
    geo->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
    geo->addPrimitiveSet(new osg::DrawArrays(osg::DrawArrays::QUAD_STRIP, 0, 10));
    geo->getOrCreateStateSet()->setTextureAttributeAndModes(0, new osg::Texture2D(osgDB::readImageFile("wall.png")));
    return geo.release();
}

osg::Drawable* CreateHouseRoof()
{
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    vertices->push_back(osg::Vec3(-0.2, -0.5, 3.5));
    vertices->push_back(osg::Vec3(6.2, -0.5, 3.5));
    vertices->push_back(osg::Vec3(0.8, 2.0, 6.0));
    vertices->push_back(osg::Vec3(5.0, 2.0, 6.0));
    vertices->push_back(osg::Vec3(-0.2, 4.5, 3.5));
    vertices->push_back(osg::Vec3(6.2, 4.5, 3.5));

    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
    colors->push_back(osg::Vec4(0.25, 0.0, 0.0, 1.0));

    osg::ref_ptr<osg::Geometry> houseRoof = new osg::Geometry;

    //设置图元组
    osg::ref_ptr<osg::DrawArrays> roof = new osg::DrawArrays(osg::DrawArrays::QUAD_STRIP, 0, 6);
    osg::ref_ptr<osg::DrawElementsUInt> roofSides = new osg::DrawElementsUInt(osg::DrawElementsUInt::TRIANGLES, 6);
    roofSides->push_back(0);
    roofSides->push_back(2);
    roofSides->push_back(4);
    roofSides->push_back(5);
    roofSides->push_back(3);
    roofSides->push_back(1);

    houseRoof->setVertexArray(vertices.get());
    houseRoof->setColorArray(colors.get());
    houseRoof->setColorBinding(osg::Geometry::BIND_OVERALL);
    houseRoof->addPrimitiveSet(roof.get());
    houseRoof->addPrimitiveSet(roofSides.get());

    osgUtil::SmoothingVisitor smv;
    smv.smooth(*houseRoof);
    return houseRoof.release();

}

int main()
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(CreateHouseWall());
    geode->addDrawable(CreateHouseRoof());

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
