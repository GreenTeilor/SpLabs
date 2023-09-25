#include "Sprite.h"

Sprite::Sprite(HWND hwnd, RECT workSpace)
{
	m_device = GetDC(hwnd);
	m_bufferDevice = CreateCompatibleDC(m_device);
	this->m_workSpace = workSpace;

	m_hScreen = CreateCompatibleBitmap(m_device, workSpace.right, workSpace.bottom);
	m_oldBmp = (HBITMAP)SelectObject(m_bufferDevice, m_hScreen);

	m_image = (HBITMAP)LoadImage(0, L"images/snail.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(m_image, sizeof(BITMAP), &m_bm);
	m_spriteDevice = CreateCompatibleDC(m_device);
	SelectObject(m_spriteDevice, m_image);
}

void Sprite::draw(HWND hWnd, float X, float Y)
{
	BeginPaint(hWnd, &m_PStruct);
	PatBlt(m_bufferDevice, 0, 0, m_workSpace.right, m_workSpace.bottom, WHITENESS);

	BitBlt(m_bufferDevice, (int)X, (int)Y, m_bm.bmWidth, m_bm.bmHeight, m_spriteDevice, 0, 0, SRCCOPY);

	BitBlt(m_device, 0, 0, m_workSpace.right, m_workSpace.bottom, m_bufferDevice, 0, 0, SRCCOPY);

	EndPaint(hWnd, &m_PStruct);
}

CenterPoints* Sprite::center(float width, float height)
{
	m_points.x = -width / 2;
	m_points.y = -height / 2;
	return &m_points;
}