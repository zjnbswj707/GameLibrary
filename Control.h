#pragma once

#include <windows.h>
#include <vector>
#include "GameFrame.h"
using namespace std;

vector<char> Checkers;

NoReturn SetCheckers(vector<char> newCheckers) {
	Checkers = newCheckers;
	return;
}

NoReturn AddChecker(char newChecker) {
	Checkers.push_back(newChecker);
	return;
}

typedef bool DeleteCheckerReturnValue;
DeleteCheckerReturnValue DeleteChecker(char targetChecker) {
	bool deleted = false;
	for (vector<char>::iterator iter = Checkers.begin(); iter != Checkers.end(); iter++) {
		if (*iter == targetChecker) {
			Checkers.erase(iter);
			deleted = true;
		}
	}
	return deleted;
}

typedef bool PressingReturnValue;
PressingReturnValue Pressing(NoArgument) {
	for (int i = 0; i < int(Checkers.size()); i++) {
		if (GetAsyncKeyState(Checkers[i])) {
			return true;
		}
	}
	return false;
}

typedef vector<char> PresserReturnValue;
PresserReturnValue Presser(NoArgument) {
	vector<char> pressing;
	for (int i = 0; i < int(Checkers.size()); i++) {
		if (GetAsyncKeyState(Checkers[i])) {
			pressing.push_back(Checkers[i]);
		}
	}
	return pressing;
}

typedef bool OnPressReturnValue;
OnPressReturnValue OnPress(char c) {
	return GetAsyncKeyState(c);
}

typedef bool ClickingReturnValue;
ClickingReturnValue Clicking(NoArgument) {
	return mouseclick_state != 0;
}


typedef ClickState ClickerReturnValue;
ClickerReturnValue Clicker(NoArgument) {
	return mouseclick_state;
}

typedef string ConsoleInputReturnValue;
ConsoleInputReturnValue ConsoleInput(NoArgument) {
	string s;
	cin >> s;
	return s;
}
