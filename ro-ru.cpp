#include"DxLib.h"
#include<stdio.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevIntance, LPSTR lPCmdLine, int nCmdShow) {
	ChangeWindowMode(TRUE); // ウィンドウモードに設定
	if (DxLib_Init() == -1) {
		return -1;
	}


	char keyState[256];
	SetGraphMode(500, 500, 16);
	SetDrawScreen(DX_SCREEN_BACK); //描画先を裏画面に設定
	int x = 56,y=450,w,h,r,g,b,a;
	int color[1000][1000];
	int acceleration = 0, mode = 0;
	int Handle;     // 画像格納用ハンドル
	Handle = LoadGraph("user.png"); // 画像のロード
	GetSoftImageSize(Handle, &w, &h);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			// １ドットの色を取得!
			GetPixelSoftImage(Handle, j, i, &r, &g, &b, &a);
			if (r == 255) {
				color[j][i] = 1;
			}
		}
	}

	while (1) {
		if (ProcessMessage() != 0) { // メッセージ処理
			break;//ウィンドウの×ボタンが押されたらループを抜ける
		}
		ClearDrawScreen(); // 画面を消す
		LoadGraphScreen(0, 0, "迷路.png", TRUE);
		GetHitKeyStateAll(keyState);
	
		if (color[x][y] == 1) {
			break;
		}
		if(keyState[KEY_INPUT_RIGHT]){
			if (mode == 1) {
				x = x + acceleration;
				acceleration++;
			}
			else {
				x = x + 1; // xを2増やす
				mode = 1;
				acceleration = 0;
			}
		}
		if (keyState[KEY_INPUT_LEFT]) {
			if (mode = 2) {
				x = x - acceleration;
				acceleration++;
			}
			else {

				x = x - 1; // xを2増やす
				mode = 2;
				acceleration = 0;
			}
		}
		if (keyState[KEY_INPUT_UP]) {
			y = y - 1;
		}
		if (keyState[KEY_INPUT_DOWN]) {
			y = y + 1;
		}
		DrawRotaGraph(x,y,0.4,0.0, Handle, TRUE); //画像の描画
		ScreenFlip(); //裏画面を表画面に反映
		WaitTimer(10);
		if (x>450&&y>70&&y<120) {
			break;
		}
	}
	DeleteSoftImage(Handle);



	DxLib_End(); // DXライブラリ終了処理
	return 0;
}