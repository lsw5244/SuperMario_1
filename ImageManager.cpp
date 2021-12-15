#include "ImageManager.h"
#include "Image.h"
#include "MacroCollection.h"

void ImageManager::Init()
{
	ImageManager::GetInstance()->AddImage("Image/Character/SamllRedMario.bmp", 224, 64, 14, 2, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("Image/Character/BigRedMario.bmp", 224, 64, 14, 2, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("Image/Character/BigFireMario.bmp", 224, 64, 14, 2, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("Image/Monster/Gunba.bmp", 64, 32, 4, 2, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("Image/mario_overwordTile.bmp", 176, 208, 11, 13, true, RGB(255, 0, 255));
}

void ImageManager::Release()
{
	map<string, Image*>::iterator it;
	for (it = mapImages.begin(); it != mapImages.end(); /*it++*/)
	{
		SAFE_RELEASE(it->second);
		it = mapImages.erase(it);	// ���� ������ �ּ�(iterator)�� ���ŵȴ�.
	}
	mapImages.clear();
}

//void ImageManager::AddImage()
//{
//	// �߰��Ϸ��� �̹����� �ڷᱸ������ ã�´�.
//
//	// ������ ����.
//
//	// ������ �߰��Ѵ�.
//	//new Image();
//	//img->Init
//
//}

Image* ImageManager::AddImage(const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	if (FindImage(fileName))
	{
		return nullptr;
	}

	Image* img = new Image;
	if (FAILED(img->Init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_RELEASE(img);
		return nullptr;
	}

	mapImages.insert(make_pair(fileName, img));

	return img;
}

Image* ImageManager::AddImage(const char* fileName, int width, int height, 
	int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	if (FindImage(fileName))
	{
		return nullptr;
	}

	Image* img = new Image;
	if (FAILED(img->Init(fileName, width, height, maxFrameX, 
		maxFrameY, isTrans, transColor)))
	{
		SAFE_RELEASE(img);
		return nullptr;
	}

	mapImages.insert(make_pair(fileName, img));

	return img;
}

Image* ImageManager::FindImage(const char* fileName)
{
	map<string, Image*>::iterator it = mapImages.find(fileName);
	if (it == mapImages.end())
	{
		return nullptr;
	}

	return it->second;
}

void ImageManager::DeleteImage(const char* fileName)
{
	map<string, Image*>::iterator it = mapImages.find(fileName);
	if (it == mapImages.end())
	{
		return;
	}

	SAFE_RELEASE(it->second);	// Image*	// Image �����Ҵ� ����
	mapImages.erase(it);		// �ʿ��� ��� ����
}
