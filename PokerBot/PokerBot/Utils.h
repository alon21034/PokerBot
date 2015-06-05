#ifndef __UTILS_H
#define __UTILS_H

#include <vector>
#include <iostream>
#include <time.h>

using namespace std;

static int SCREEN_X;
static int SCREEN_Y;

static void MouseMove(int x, int y) {
	INPUT input = {0};
	input.mi.dx = (x) * 65535/SCREEN_X;
	input.mi.dy = (y) * 65535/SCREEN_Y;
	input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_MOVE;
	input.type = INPUT_MOUSE;
	SendInput( 1, &input, sizeof INPUT );
}

static void MouseClick() {
	INPUT input[2] = {0,0};
	input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	input[0].type = INPUT_MOUSE;
	input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
	input[1].type = INPUT_MOUSE;
	SendInput( 2, input, sizeof INPUT );
}

static void MouseClick(int x, int y, long delay = 5) {
	MouseMove(x, y);
	MouseClick();
}

static std::vector<unsigned char> ToPixels(HBITMAP BitmapHandle, int &width, int &height)
{        
    BITMAP Bmp = {0};
    BITMAPINFO Info = {0};
    std::vector<unsigned char> Pixels = std::vector<unsigned char>();

    HDC DC = CreateCompatibleDC(NULL);
    std::memset(&Info, 0, sizeof(BITMAPINFO)); //not necessary really..
    HBITMAP OldBitmap = (HBITMAP)SelectObject(DC, BitmapHandle);
    GetObject(BitmapHandle, sizeof(Bmp), &Bmp);

    Info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    Info.bmiHeader.biWidth = width = Bmp.bmWidth;
    Info.bmiHeader.biHeight = height = Bmp.bmHeight;
    Info.bmiHeader.biPlanes = 1;
    Info.bmiHeader.biBitCount = Bmp.bmBitsPixel;
    Info.bmiHeader.biCompression = BI_RGB;
    Info.bmiHeader.biSizeImage = ((width * Bmp.bmBitsPixel + 31) / 32) * 4 * height;

    Pixels.resize(Info.bmiHeader.biSizeImage);
    GetDIBits(DC, BitmapHandle, 0, height, &Pixels[0], &Info, DIB_RGB_COLORS);
    SelectObject(DC, OldBitmap);

    height = std::abs(height);
    DeleteDC(DC);
    return Pixels;
}

static void PrintTime() {
	time_t timer;
	cout << time(&timer) << endl;
}

#endif