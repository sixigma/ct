#include "stdafx.h"
#include "imageManager.h"
#include <algorithm>

imageManager::imageManager()
{
}


imageManager::~imageManager()
{
}

HRESULT imageManager::init()
{
	return S_OK;
}

void imageManager::release()
{
	delAll();
}

image* imageManager::add(string strKey, int width, int height)
{
	image* img = find(strKey);
	if (img) return img;

	img = new image;

	if (FAILED(img->init(width, height)))
	{
		SAFE_DEL(img);
		return nullptr;
	}

	_imageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::add(string strKey, const char * fileName, int width, int height, BOOL hasTransparentColor, COLORREF transparentColor)
{
	image* img = find(strKey);
	if (img) return img;

	img = new image;

	if (FAILED(img->init(fileName, width, height, hasTransparentColor, transparentColor)))
	{
		SAFE_DEL(img);
		return nullptr;
	}

	_imageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addF(string strKey, const char * fileName, int width, int height, int frameX, int frameY, BOOL hasTransparentColor, COLORREF transparentColor)
{
	image* img = find(strKey);
	if (img) return img;

	img = new image;

	if (FAILED(img->init(fileName, width, height, frameX, frameY, hasTransparentColor, transparentColor)))
	{
		SAFE_DEL(img);
		return nullptr;
	}

	_imageList.insert(make_pair(strKey, img));

	return img;
}


image* imageManager::addF(string strKey, const char* fileName, int x, int y, int width, int height, int frameX, int frameY, BOOL hasTransparentColor, COLORREF transparentColor)
{
	image* img = find(strKey);
	if (img) return img;

	img = new image;

	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, hasTransparentColor, transparentColor)))
	{
		SAFE_DEL(img);
		return nullptr;
	}

	_imageList.insert(make_pair(strKey, img));

	return img;
}


image* imageManager::find(string strKey)
{
	imageListIter key = _imageList.find(strKey);

	if (key != _imageList.end())
	{
		return key->second;
	}

	return nullptr;
}

BOOL imageManager::del(string strKey)
{
	imageListIter key = _imageList.find(strKey);

	if (key != _imageList.end())
	{
		key->second->release();
		SAFE_DEL(key->second);
		_imageList.erase(key);
		return TRUE;
	}

	return FALSE;
}

BOOL imageManager::delAll()
{
	imageListIter iter = _imageList.begin();

	for (; iter != _imageList.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DEL(iter->second);
			iter = _imageList.erase(iter);
		}
		else ++iter;
	}
	_imageList.clear();
	return TRUE;
}

void imageManager::render(string strKey, HDC hDC)
{
	image* img = find(strKey);
	if (img) img->render(hDC);
}

void imageManager::render(string strKey, HDC hDC, int destX, int destY)
{
	image* img = find(strKey);
	if (img) img->render(hDC, destX, destY);
}

void imageManager::render(string strKey, HDC hDC, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight)
{
	image* img = find(strKey);
	if (img) img->render(hDC, destX, destY, srcX, srcY, srcWidth, srcHeight);
}

void imageManager::renderH(string strKey, HDC hDC, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight)
{
	image* img = find(strKey);
	if (img) img->renderH(hDC, destX, destY, srcX, srcY, srcWidth, srcHeight);
}

void imageManager::renderV(string strKey, HDC hDC, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight)
{
	image* img = find(strKey);
	if (img) img->renderV(hDC, destX, destY, srcX, srcY, srcWidth, srcHeight);
}

void imageManager::renderHV(string strKey, HDC hDC, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight)
{
	image* img = find(strKey);
	if (img) img->renderHV(hDC, destX, destY, srcX, srcY, srcWidth, srcHeight);
}

void imageManager::frameRender(string strKey, HDC hDC, int destX, int destY)
{
	image* img = find(strKey);
	if (img) img->frameRender(hDC, destX, destY);
}

void imageManager::frameRender(string strKey, HDC hDC, int destX, int destY, int currentFrameX, int currentFrameY)
{
	image* img = find(strKey);
	if (img) img->frameRender(hDC, destX, destY, currentFrameX, currentFrameY);
}

void imageManager::frameRenderH(string strKey, HDC hDC, int destX, int destY, int currentFrameX, int currentFrameY)
{
	image* img = find(strKey);
	if (img) img->frameRenderH(hDC, destX, destY, currentFrameX, currentFrameY);
}

void imageManager::frameRenderV(string strKey, HDC hDC, int destX, int destY, int currentFrameX, int currentFrameY)
{
	image* img = find(strKey);
	if (img) img->frameRenderV(hDC, destX, destY, currentFrameX, currentFrameY);
}

void imageManager::frameRenderHV(string strKey, HDC hDC, int destX, int destY, int currentFrameX, int currentFrameY)
{
	image* img = find(strKey);
	if (img) img->frameRenderHV(hDC, destX, destY, currentFrameX, currentFrameY);
}

void imageManager::adjFrameRender(string strKey, HDC hDC, int destX, int destY, int currentFrameX, int currentFrameY, int adjWidth, int adjHeight)
{
	image* img = find(strKey);
	if (img) img->adjFrameRender(hDC, destX, destY, currentFrameX, currentFrameY, adjWidth, adjHeight);
}

void imageManager::alphaRender(string strKey, HDC hDC, BYTE alpha)
{
	image* img = find(strKey);
	if (img) img->alphaRender(hDC, alpha);
}

void imageManager::alphaRender(string strKey, HDC hDC, int destX, int destY, BYTE alpha)
{
	image* img = find(strKey);
	if (img) img->alphaRender(hDC, destX, destY, alpha);
}

void imageManager::alphaRender(string strKey, HDC hDC, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight, BYTE alpha)
{
	image* img = find(strKey);
	if (img) img->alphaRender(hDC, destX, destY, srcX, srcY, srcWidth, srcHeight, alpha);
}

void imageManager::animRender(string strKey, HDC hDC, int destX, int destY, animation* anim)
{
	image* img = find(strKey);
	if (img) img->animRender(hDC, destX, destY, anim);
}

void imageManager::loopRender(string strKey, HDC hDC, const LPRECT drawArea, int offSetX, int offSetY)
{
	image* img = find(strKey);
	if (img) img->loopRender(hDC, drawArea, offSetX, offSetY);
}

void imageManager::setRctClipRgn(HDC hDC, int x, int y, int width, int height)
{
	_hClipRgn = CreateRectRgn(x, y, x + width, y + height);
	SelectClipRgn(hDC, _hClipRgn);
}

void imageManager::setEllipticClipRgn(HDC hDC, int x, int y, int width, int height)
{
	_hClipRgn = CreateEllipticRgn(x, y, x + width, y + height);
	SelectClipRgn(hDC, _hClipRgn);
}

void imageManager::resetClipRgn(HDC hDC)
{
	SelectClipRgn(hDC, nullptr);
}

void imageManager::execZ()
{
	if (!_funcListKeys.empty()) _funcListKeys.clear();
	if (_funcsToCall.empty()) return;
	_funcListKeys.reserve(_funcsToCall.size());

	for (auto& iter : _funcsToCall)
	{
		_funcListKeys.push_back(iter.first);
	}

	sort(_funcListKeys.begin(), _funcListKeys.end());

	for (LONG& key : _funcListKeys)
	{
		auto iterRange = _funcsToCall.equal_range(key);
		for (auto& it = iterRange.first; it != iterRange.second; ++it)
		{
			it->second();
		}
	}
	_funcsToCall.clear();
}

