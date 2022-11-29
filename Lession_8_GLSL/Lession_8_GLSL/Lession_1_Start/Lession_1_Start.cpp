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


static const char* verticeShader = {
	"void main()\n"
	"{\n"
	"	gl_Position = ftransform();\n"
	"}\n"
};

static const char* fragShader = {
	"uniform vec4 mainColor;\n"
	"void main()\n"
	"{\n"
	"	gl_FragColor = mainColor;\n"
	"}\n"
};

class UserUniformCallback : public osg::Uniform::Callback 
{
public:
	UserUniformCallback(){}

	virtual void operator()(osg::Uniform *uniform, osg::NodeVisitor* visitor)
	{
		if (!uniform) return;

		osg::Vec4 mainColor;
		uniform->get(mainColor);
		float red = mainColor.x();
		if (red > 1.0) 
		{
			red = 0.0;
		} 
		else 
		{
			red += 0.01;
		}
		mainColor.x() = red;

		uniform->set(mainColor);
	}
};

void CreateShader(osg::StateSet &ss) 
{
	osg::ref_ptr<osg::Program> program = new osg::Program;

	osg::ref_ptr<osg::Shader> vertexShader = new osg::Shader(osg::Shader::VERTEX, verticeShader);
	osg::ref_ptr<osg::Shader> fragmentShader = new osg::Shader(osg::Shader::FRAGMENT, fragShader);

	program->addShader(vertexShader.get());
	program->addShader(fragmentShader.get());

	osg::ref_ptr<osg::Uniform> uniform = new osg::Uniform("mainColor", osg::Vec4(1.0, 0.0, 1.0, 1.0));
	uniform->setUpdateCallback(new UserUniformCallback);
	ss.addUniform(uniform.get());

	ss.setAttributeAndModes(program.get());
	return;
}

int main()
{
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("osgData/cow.osg");
	CreateShader(*(node->getOrCreateStateSet()));

	/*
	osg::ref_ptr<osg::Geode> geo = new osg::Geode;
	osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0, 0.0, 0.0), 1.0));
	geo->addDrawable(shape.get());
	CreateShader(*(geo->getOrCreateStateSet()));
	*/

	osgViewer::Viewer viewer;
	//viewer.setSceneData(geo.get());
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
