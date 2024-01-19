#include "Window.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Window::Window(int width, int height) : m_hInstance(GetModuleHandle(nullptr)) {
	const wchar_t* CLASS_NAME = L"Window Class";

	hBitmap = CreateCompatibleBitmap(GetDC(NULL), width, height);
	sWind = { width, height };
	WNDCLASS wndClass = {};
	wndClass.lpszClassName = CLASS_NAME;
	wndClass.hInstance = m_hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.lpfnWndProc = WindowProc;

	RegisterClass(&wndClass);

	DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	RECT rect;
	rect.left = 250;
	rect.top = 250;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	AdjustWindowRect(&rect, style, false);

	m_hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"EA SPORTS IS IN THE GAME",
		style,
		rect.left,
		rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		m_hInstance,
		NULL
	);

	ShowWindow(m_hWnd, SW_SHOW);
}

Window::~Window() {
	const wchar_t* CLASS_NAME = L"Window Class";

	UnregisterClass(CLASS_NAME, m_hInstance);
}

bool Window::ProcessMessages() {
	MSG msg = {};


	while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE)) {
		if (msg.message == WM_QUIT) return false;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}

void Window::writeBitmap() {
	HDC hdc = GetDC(m_hWnd);
	SIZE sBmp = sWind;
	BITMAPINFO bmi; // This will hold the bitmap information
	LPVOID pvBits; // the raw bitmap bits

	if (hBitmap != NULL) {
		BITMAP bmp;
		GetObject(hBitmap, sizeof(BITMAP), &bmp);

		// Initialize the BITMAPINFO structure
		memset(&bmi, 0, sizeof(BITMAPINFO));
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = bmp.bmWidth;
		bmi.bmiHeader.biHeight = bmp.bmHeight;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = bmp.bmBitsPixel;
		bmi.bmiHeader.biCompression = BI_RGB; // Assuming uncompressed RGB

		// Allocate memory for bitmap bits
		pvBits = malloc(bmp.bmWidthBytes * bmp.bmHeight);

		if (pvBits != NULL) {
			// Retrieve bitmap bits
			GetBitmapBits(hBitmap, bmp.bmWidthBytes * bmp.bmHeight, pvBits);

			// Use StretchDIBits to draw the bitmap
			StretchDIBits(hdc, 0, 0, sBmp.cx, sBmp.cy,
				0, 0, bmp.bmWidth, bmp.bmHeight,
				pvBits, &bmi,
				DIB_RGB_COLORS,
				SRCCOPY);
		}
	}
}

void Window::DrawLine(Point A, Point B, COLORREF color) {
	HDC hdcMem = CreateCompatibleDC(NULL);
	HGDIOBJ oldBitmap = SelectObject(hdcMem, hBitmap);

	// Calculate differences and direction
	int dx = abs(B.x - A.x);
	int dy = abs(B.y - A.y);
	int sx = (A.x < B.x) ? 1 : -1;
	int sy = (A.y < B.y) ? 1 : -1;
	int err = dx - dy;

	while (true) {
		SetPixel(hdcMem, A.x, A.y, color);
		if (A.x == B.x && A.y == B.y) break;
		int e2 = 2 * err;
		if (e2 > -dy) { err -= dy; A.x += sx; }
		if (e2 < dx) { err += dx; A.y += sy; }
	}
	SetPixel(hdcMem, B.x, B.y, color);
	SelectObject(hdcMem, oldBitmap);
	DeleteDC(hdcMem);
}