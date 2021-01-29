#include "stdafx.h"
#include "imageManager.h"

void imageManager::setWindowSkin(string tilesetStrKey, string skinStrKey, int width, int height, int destX, int destY)
{
	if (width < 96 || height < 96 || height % 16 > 0) return;
	image* img = find(tilesetStrKey);
	image* img2 = find(skinStrKey);
	if (!img || !img2) return;
	HDC hTempDC = CreateCompatibleDC(img->getMemDC());
	BITMAPINFO bI = { 0 };
	DWORD* bitmapData = nullptr;
	bI.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bI.bmiHeader.biBitCount = 32;
	bI.bmiHeader.biWidth = width;
	bI.bmiHeader.biHeight = height;
	bI.bmiHeader.biCompression = BI_RGB;
	bI.bmiHeader.biPlanes = 1;
	HBITMAP hTempBitmap = CreateDIBSection(hTempDC, &bI, DIB_RGB_COLORS, reinterpret_cast<void**>(&bitmapData), 0, 0);
	if (hTempBitmap == nullptr)
	{
		DeleteDC(hTempDC);
		return;
	}
	HBITMAP hTempOBitmap = (HBITMAP)SelectObject(hTempDC, hTempBitmap);

	// 명암을 주기 전에 임시 DC 비트맵에 글 출력 창 스킨을 그린다.
	img->loopRenderP(hTempDC, &RECT({32, 32, width, height}), &RECT({128, _textWindowSkin * 128, 256, _textWindowSkin * 128 + 128}), 0, 0); // 바탕
	img->loopRenderP(hTempDC, &RECT({32, 0, width, 32}), &RECT({32, _textWindowSkin * 128, 96, _textWindowSkin * 128 + 32}), 0, 0); // 상단
	img->loopRenderP(hTempDC, &RECT({32, height - 32, width, height}), &RECT({32, _textWindowSkin * 128 + 96, 96, _textWindowSkin * 128 + 128}), 0, 0); // 하단
	img->loopRenderP(hTempDC, &RECT({0, 32, 32, height}), &RECT({0, _textWindowSkin * 128 + 32, 32, _textWindowSkin * 128 + 96}), 0, 0); // 좌단
	img->loopRenderP(hTempDC, &RECT({width - 32, 32, width, height }), &RECT({96, _textWindowSkin * 128 + 32, 128, _textWindowSkin * 128 + 96}), 0, 0); // 우단
	img->render(hTempDC, 0, 0, 0, _textWindowSkin * 128, 32, 32);  // 좌상단 모서리
	img->render(hTempDC, width - 32, 0, 96, _textWindowSkin * 128, 32, 32); // 우상단 모서리
	img->render(hTempDC, 0, height - 32, 0, _textWindowSkin * 128 + 96, 32, 32); // 좌하단 모서리
	img->render(hTempDC, width - 32, height - 32, 96, _textWindowSkin * 128 + 96, 32, 32); // 우하단 모서리

	size_t sectionHeight = static_cast<size_t>(height / 16);
	size_t sectionArea = static_cast<size_t>(width) * sectionHeight;
	for (size_t sectionNum = 0; sectionNum < 16; ++sectionNum)
	{
		if (sectionNum == 7) continue;
		signed char valueChange = static_cast<signed char>(8 * (static_cast<int>(sectionNum) - 7));
		for (size_t i = sectionNum * sectionArea; i < (sectionNum + 1) * sectionArea; ++i)
		{
			BYTE* currPixelData = reinterpret_cast<BYTE*>(&bitmapData[i]);
			currPixelData[0] = min(max(currPixelData[0] + valueChange, 0x00), 0xFF);
			currPixelData[1] = min(max(currPixelData[1] + valueChange, 0x00), 0xFF);
			currPixelData[2] = min(max(currPixelData[2] + valueChange, 0x00), 0xFF);
		}
	}

	BitBlt(img2->getMemDC(), 0, 0, width, height, hTempDC, 0, 0, SRCCOPY);
	DeleteObject(SelectObject(hTempDC, hTempOBitmap));
	DeleteDC(hTempDC);
}

void imageManager::setAllWindowSkins()
{
	IMG->setWindowSkin("글 출력 창 스킨 타일셋", "대사 출력 창 스킨", 1024, 320);
	IMG->setWindowSkin("글 출력 창 스킨 타일셋", "전투 메시지 창 스킨", 1024, 96);
	IMG->setWindowSkin("글 출력 창 스킨 타일셋", "설정 메시지 창 스킨", 898, 128);

	// 리마인더: 추가 필요

}
