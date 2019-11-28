#include"DxLib.h"
#include<stdio.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevIntance, LPSTR lPCmdLine, int nCmdShow) {
	ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ɐݒ�
	if (DxLib_Init() == -1) {
		return -1;
	}


	char keyState[256];
	SetGraphMode(500, 500, 16);
	SetDrawScreen(DX_SCREEN_BACK); //�`���𗠉�ʂɐݒ�
	int x = 56,y=450,w,h,r,g,b,a;
	int color[1000][1000];
	int acceleration = 0, mode = 0;
	int Handle;     // �摜�i�[�p�n���h��
	Handle = LoadGraph("user.png"); // �摜�̃��[�h
	GetSoftImageSize(Handle, &w, &h);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			// �P�h�b�g�̐F���擾!
			GetPixelSoftImage(Handle, j, i, &r, &g, &b, &a);
			if (r == 255) {
				color[j][i] = 1;
			}
		}
	}

	while (1) {
		if (ProcessMessage() != 0) { // ���b�Z�[�W����
			break;//�E�B���h�E�́~�{�^���������ꂽ�烋�[�v�𔲂���
		}
		ClearDrawScreen(); // ��ʂ�����
		LoadGraphScreen(0, 0, "���H.png", TRUE);
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
				x = x + 1; // x��2���₷
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

				x = x - 1; // x��2���₷
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
		DrawRotaGraph(x,y,0.4,0.0, Handle, TRUE); //�摜�̕`��
		ScreenFlip(); //����ʂ�\��ʂɔ��f
		WaitTimer(10);
		if (x>450&&y>70&&y<120) {
			break;
		}
	}
	DeleteSoftImage(Handle);



	DxLib_End(); // DX���C�u�����I������
	return 0;
}