#include <windows.h>

char BPKeyState[191];

void setupKeyboardListener() {
	FOR(int i = 0, i < 191, i++)
		BPKeyState[i] = 0;
	FOR_END
}

void printKeyboard() {
	FOR(char i = 8, i < 191, i++)
		if (GetAsyncKeyState(i) & 1 == 1) {
			//printf('%d', i);
			printf(&i);
		}
	FOR_END
}

void getKeyboard() {
	FOR(int i = 8, i < 191, i++)
		if (GetAsyncKeyState(i) & 1 == 1) {
			BPKeyState[i] = 1;
		}else{
			BPKeyState[i] = 0;
		}
	FOR_END
}
