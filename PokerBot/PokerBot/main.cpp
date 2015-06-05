#include <iostream>
#include <stdlib.h>
#include "Solver.h"
#include <windows.h>
#include "Utils.h"

using namespace std;

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);

HWND targetWindow;

int main() {

	// Get the titles of all windows
	EnumWindows(EnumWindowsProc, NULL);
	
	//SetForegroundWindow(targetWindow);

	// initial constant
	SCREEN_X = GetSystemMetrics( SM_CXVIRTUALSCREEN );
	SCREEN_Y = GetSystemMetrics( SM_CYVIRTUALSCREEN );
	cout << "screen is: " << SCREEN_X << " x " << SCREEN_Y << endl;


	RECT rect;
	GetWindowRect(targetWindow, &rect);

	HDC hdcScreen = GetDC(NULL);
	HDC hdc = CreateCompatibleDC(hdcScreen);
	HBITMAP hbmp = CreateCompatibleBitmap(hdcScreen, rect.right - rect.left, rect.bottom - rect.top);

	int w, h;
	vector<unsigned char> bmp = ToPixels(hbmp, w, h);
	cout << "(w, h) = (" << w << ", " << h << ")" << endl;

	for (int i = 0 ; i < w*h ; i+=10) {
		cout << hex << (int)bmp[i] << "  ";
	}

	Solver solver;

	solver.setTitle("");
	solver.solve();

	system("pause");
	return 0;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
	char class_name[80];
	char title[80];
	GetClassName(hwnd,class_name, sizeof(class_name));
	GetWindowText(hwnd,title,sizeof(title));

	if (string(title) ==  "¤pºâ½L") {
	    cout <<"Window title: "<<title<<endl;
	    cout <<"Class name: "<<class_name<<endl<<endl;

		targetWindow = hwnd;
	}

	return true;
}