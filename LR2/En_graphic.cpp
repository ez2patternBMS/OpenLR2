#include "En_graphic.h"
#include "DxLib/DxLib.h"

int ScreenCapture(uint iGrHandle, int x, int y){
	GetDrawScreenGraph(0, 0, x, y, iGrHandle, 1);
	return 0;
}

int hBackImage;
int SetBackground(int hImage) {
	hBackImage = hImage;
	return 1;
}

int screenSizeX, screenSizeY;
int skinSizeX, skinSizeY;
int Resize(game* g, double skinX, double skinY, bool bit16) {
	int oldXpos = 320, oldYpos = 240;

#ifdef _WIN32
	GetWindowPosition(&oldXpos, &oldYpos);
#endif // _WIN32
	SetGraphMode(skinX, skinY, bit16? 16 : 32, 60);
#ifdef _WIN32
	SetWindowSizeExtendRate((double)g->config.system.windowsize_x / skinX, (double)g->config.system.windowsize_y / skinY);
#endif // _WIN32
	SetDrawScreen(DX_SCREEN_BACK);
#ifdef _WIN32
	SetWindowPosition(oldXpos, oldYpos);
#endif // _WIN32

	skinSizeX = skinX;
	skinSizeY = skinY;
	return 0;
}
