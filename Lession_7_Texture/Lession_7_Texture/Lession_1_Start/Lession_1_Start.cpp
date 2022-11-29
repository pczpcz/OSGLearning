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

osg::Image* CreateMipmap(unsigned int resolution)
{
	osg::ref_ptr<osg::Image> image = osgDB::readImageFile("osgData/images/clockface.jpg");
	unsigned int totalSize = 0;
	osg::Image::MipmapDataType mipmapData;

	int width = image->s();
	int height = image->t();
	int res = std::min(width, height);

	for (; res > 0; res >>= 1)
	{
		mipmapData.push_back(totalSize);
	}

	image->setMipmapLevels(mipmapData);

	return image.release();
}

void CreateTexture2D(osg::StateSet& ss) 
{
	osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
	
	//texture->setImage(osgDB::readImageFile("osgData/images/clockface.jpg"));
	texture->setImage(CreateMipmap(32));
	texture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
	texture->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);
	texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
	texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);

	ss.setTextureAttributeAndModes(0, texture.get());
	return;
}

//立方体贴图
void CreateTextureCubeMap(osg::StateSet &ss) 
{
	osg::ref_ptr<osg::TextureCubeMap> textureCubeMap = new osg::TextureCubeMap;
	textureCubeMap->setImage(osg::TextureCubeMap::NEGATIVE_X, osgDB::readImageFile("osgData/Cubemap_snow/negx.jpg"));
	textureCubeMap->setImage(osg::TextureCubeMap::POSITIVE_X, osgDB::readImageFile("osgData/Cubemap_snow/posx.jpg"));
	textureCubeMap->setImage(osg::TextureCubeMap::NEGATIVE_Y, osgDB::readImageFile("osgData/Cubemap_snow/negy.jpg"));
	textureCubeMap->setImage(osg::TextureCubeMap::POSITIVE_Y, osgDB::readImageFile("osgData/Cubemap_snow/posy.jpg"));
	textureCubeMap->setImage(osg::TextureCubeMap::NEGATIVE_Z, osgDB::readImageFile("osgData/Cubemap_snow/negz.jpg"));
	textureCubeMap->setImage(osg::TextureCubeMap::POSITIVE_Z, osgDB::readImageFile("osgData/Cubemap_snow/posz.jpg"));

	textureCubeMap->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
	textureCubeMap->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);
	textureCubeMap->setWrap(osg::Texture::WRAP_R, osg::Texture::CLAMP_TO_EDGE);
	textureCubeMap->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
	textureCubeMap->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);

	ss.setTextureAttributeAndModes(0, textureCubeMap.get());
	ss.setTextureAttributeAndModes(0, new osg::TexGen);			//???
	return;
}

int main()
{
	osg::ref_ptr<osg::Geode> geo1 = new osg::Geode;
	geo1->addDrawable(osg::createTexturedQuadGeometry(osg::Vec3(0.0, 0.0, 0.0), osg::Vec3(1.0, 0.0, 0.0), osg::Vec3(0.0, 0.0, 1.0), 0.0, 0.0, 1.0, 1.0));
	CreateTexture2D(*(geo1->getOrCreateStateSet()));

	osg::ref_ptr<osg::Geode> geo2 = new osg::Geode;
	geo2->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(3.0, 0.0, 0.0), 1.5)));
	CreateTextureCubeMap(*(geo2->getOrCreateStateSet()));

	osg::ref_ptr<osg::Group> group = new osg::Group;
	group->addChild(geo1);
	group->addChild(geo2);

	osgViewer::Viewer viewer;
	viewer.setSceneData(group.get());
	viewer.run();
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
