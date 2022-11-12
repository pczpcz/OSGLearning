// Lession_1_Start.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main()
{
    //1. 向量
    std::cout << "----------------向量-------------" << std::endl;
    osg::Vec3f v1(3.0, 4.0, 5.0);
    osg::Vec3f v2(1.0, 2.0, 3.0);
    auto printVec3 = [](const osg::Vec3f& value) { std::cout << value.x() << "," << value.y() << "," << value.z() << std::endl; };
    printVec3(v2);
    std::cout << v1 * v2 << std::endl;                  //点乘
    printVec3(v1 ^ v2);                                 //叉乘
    std::cout << v1.length2() << std::endl;             //模长的平方值
    v1.normalize();
    printVec3(v1);
    std::cout << "----------------向量end-------------" << std::endl;

    //2. 四元数
    std::cout << "----------------四元数-------------" << std::endl;
    osg::Quat quat1(osg::PI_2, osg::Vec3f(1.0, 1.0, 1.0));
    auto printQuat = [](const osg::Quat& quat) { std::cout << quat.x() << "," << quat.y() << "," << quat.z() << "," << quat.w() << std::endl; };
    printQuat(quat1);
    osg::Quat quat2(osg::DegreesToRadians(90.0), osg::Vec3f(1.0, 1.0, 1.0));
    printQuat(quat2);
    auto printRotateInfo = [](const osg::Quat& quat)
    {
        double angle;
        osg::Vec3f vec;
        quat.getRotate(angle, vec);
        std::cout << "angle = " << angle << ", (" << vec.x() << " " << vec.y() << " " << vec.z() << ")" << std::endl;
    };
    printRotateInfo(quat2);
    std::cout << "----------------四元数end-------------" << std::endl;

    //3. 矩阵（行主序）
    std::cout << "----------------矩阵-------------" << std::endl;
    auto printMatrixd = [](const osg::Matrixd& matrix) 
    {
        //默认好像是列主序
        for (int iCol = 0; iCol < 4; ++iCol)
        {
            for (int iRow = 0; iRow < 4; ++iRow)
            {
                std::cout << matrix(iRow, iCol) << " ";
            }
            std::cout << std::endl;
        }
    };
    osg::Matrixd matrix;
    printMatrixd(matrix);
    matrix.preMultRotate(osg::Quat(osg::DegreesToRadians(45.0), osg::Vec3f(1.0, 0.0, 0.0)));
    matrix.preMultTranslate(osg::Vec3f(1.0, 2.0, 3.0));
    printMatrixd(matrix);
    matrix.makeRotate(osg::Quat(osg::DegreesToRadians(45.0), osg::Vec3f(1.0, 0.0, 0.0)));
    printMatrixd(matrix);
    matrix.preMultScale(osg::Vec3f(2.0, 2.0, 2.0));
    printMatrixd(matrix);
    std::cout << "----------------矩阵end-------------" << std::endl;

    //4. 数组对象
    osg::Vec3Array* pArray = new osg::Vec3Array;
    for (int i = 0; i < 10; ++i) 
    {
        pArray->push_back(osg::Vec3f(i, i, i));
    }
    printVec3(pArray->at(3));
    for (auto ittr = pArray->begin(); ittr != pArray->end(); ++ittr) 
    {
        printVec3(*ittr);
    }

    //5. 内存管理 & 智能指针
    //略。。。。。（看懂了，不练了）
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
