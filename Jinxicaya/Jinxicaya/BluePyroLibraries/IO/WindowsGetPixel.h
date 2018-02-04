FARPROC pGetPixel;
HINSTANCE hGDI;

struct BPVec3 {
	float x, y, z;
};
struct BPVec3INT {
	int x, y, z;
};

void BPGetPixelInit() {
	hGDI = LoadLibrary("gdi32.dll");
	pGetPixel = GetProcAddress(hGDI, "GetPixel");
}

void BPGetPixelRelease() {
	FreeLibrary(hGDI);
}

struct BPVec3INT BPGetPixel(int _x, int _y) {
	struct BPVec3INT vec;
	if (hGDI) {
		HDC hdc = GetDC(NULL);
		if (hdc)
		{
			/*POINT _cursor;
			GetCursorPos(&_cursor);
			COLORREF _color = (*pGetPixel) (_hdc, _cursor.x, _cursor.y);
			int _red = GetRValue(_color);
			int _green = GetGValue(_color);
			int _blue = GetBValue(_color);

			printf("Red: 0x%02x\n", _red);
			printf("Green: 0x%02x\n", _green);
			printf("Blue: 0x%02x\n", _blue);*/
			COLORREF color = (*pGetPixel) (hdc, _x, _y);
			vec.x = GetRValue(color);
			vec.y = GetGValue(color);
			vec.z = GetBValue(color);
			return vec;
		}
	}
	return vec;
}

struct BPVec3INT BPGetPixelAtMouse() {
	POINT cursor;
	GetCursorPos(&cursor);
	struct BPVec3INT vec = BPGetPixel(cursor.x, cursor.y);
	return vec;
}