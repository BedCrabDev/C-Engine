#pragma once

#include <Windows.h>
#include "linearMath.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window {
public:
	HBITMAP hBitmap;
	Window(int height, int width);
	Window(const Window&) = delete;
	Window& operator =(const Window&) = delete;
	~Window();

	bool ProcessMessages();

	void writeBitmap();

	void DrawLine(Point A, Point B, COLORREF color);
private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	SIZE sWind;

};