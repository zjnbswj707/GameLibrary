//WARNING : This header file is only applicable to Windows OS.
//GameFrame.h - the basic header file about something should be defined.

#pragma once

#include "types.h"
#include "APIDraw.h"
#include <windows.h>
#include <string>
#include <iostream>
#include <thread>
using namespace std;


HINSTANCE local_hInstance;
HINSTANCE local_hPrevInstance;
LPSTR local_lpCmdLine;
int local_nShowCmd;
HWND local_hWnd;

enum ClickState {None = 0, Left = 1, Right = 2, Both = 3};
ClickState mouseclick_state;

struct WindowInformation {
	HINSTANCE hInstance;
	HINSTANCE hPrevInstance;
	LPSTR lpCmdLine;
	int nShowCmd;
	HWND hWnd;
};
typedef struct WindowInformation wininfo;
typedef wininfo GetWindowInfoReturnValue;
GetWindowInfoReturnValue GetWindowInfo(NoArgument) {
	return {
		local_hInstance,
		local_hPrevInstance,
		local_lpCmdLine,
		local_nShowCmd,
		local_hWnd
	};
}

string Error = "[Error]";
string Warning = "[Warning]";
string Log = "[Log]";
NoReturn ConsoleLog(string content, string caller, string MessageType) {
	cout << MessageType << " " << caller << " : " << content << endl;
	return;
}

typedef int SendMessageBoxReturnValue;
SendMessageBoxReturnValue SendMessageBox(string content, string title) {
	return MessageBox(NULL, content.c_str(), title.c_str(), 0);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LONG_PTR returnValue;
	switch (uMsg) {
		case WM_CLOSE:
			DestroyWindow(hwnd);
			returnValue = 0;
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			returnValue = 0;
			break;
		case WM_LBUTTONDOWN:
			if (mouseclick_state == Right)
				mouseclick_state = Both;
			else
				mouseclick_state = Left;
			break;
		case WM_RBUTTONDOWN:
			if (mouseclick_state == Left)
				mouseclick_state = Both;
			else
				mouseclick_state = Right;
			break;
		case WM_LBUTTONUP:
			if (mouseclick_state == Left)
				mouseclick_state = None;
			else
				mouseclick_state = Right;
			break;
		case WM_RBUTTONUP:
			if (mouseclick_state == Right)
				mouseclick_state = None;
			else
				mouseclick_state = Left;
			break;
		default:
			returnValue = DefWindowProc(hwnd, uMsg, wParam, lParam);
			break;
	}
	return returnValue;
}

NoReturn InitWindow(string title, int width, int height) {
	WNDCLASS windowclass = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	windowclass.lpfnWndProc = WindowProc;
	windowclass.hInstance = local_hInstance;
	windowclass.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	windowclass.lpszClassName = "GameFrame.WindowClass";
	if (!RegisterClass(&windowclass)) {
		SendMessageBox("fx InitWindow Error : Regist window failed. Please try again.", "InitWindow Error Message");
		ConsoleLog("Window " + title + " created failed.", "fx InitWindow", Error);
		return;
	}
	local_hWnd = CreateWindow (
	                 "GameFrame.WindowClass", title.c_str(),
	                 WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
	                 CW_USEDEFAULT, CW_USEDEFAULT, width, height,
	                 NULL, NULL, local_hInstance, NULL);
	if (local_hWnd == NULL) {
		SendMessageBox("fx InitWindow Error : Create window failed. Please try again.", "InitWindow Error Message");
		ConsoleLog("Window " + title + " created failed.", "fx InitWindow", Error);
		return;
	}
	ShowWindow(local_hWnd, local_nShowCmd);
	UpdateWindow(local_hWnd);
	ConsoleLog("Window " + title + " created successfully.", "fx InitWindow", Log);
	return;
}

NoReturn Mainloop(NoArgument) {
	MSG msg = {0, 0, 0, 0, 0, 0, 0};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return;
}

NoReturn API_ConsoleVisible(NoArgument) {
	bool state = false;
	while (true) {
		if (GetAsyncKeyState(VK_RCONTROL)) {
			if (GetAsyncKeyState('S') && !state) {
				ShowWindow(GetConsoleWindow(), SW_SHOW);
				state = true;
			}
			if (GetAsyncKeyState('H') && state) {
				ShowWindow(GetConsoleWindow(), SW_HIDE);
				state = false;
			}
		}
	}
}

NoReturn API_ConsoleVisibleControl(NoArgument) {
	thread API(API_ConsoleVisible);
	API.detach();
}

typedef int MainReturnValue;
MainReturnValue Main(NoArgument);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	local_hInstance = hInstance;
	local_hPrevInstance = hPrevInstance;
	local_lpCmdLine = lpCmdLine;
	local_nShowCmd = nShowCmd;
	local_hWnd = NULL;
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	API_ConsoleVisibleControl();
	thread api(API_Draw);
	api.detach();
	Main();
	return 0;
}
