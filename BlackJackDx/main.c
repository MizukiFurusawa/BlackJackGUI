#include "DxLib.h"
#include "common.h"
#include "bjMain.h"

//�ȉ����������[�N���o�p�@��������
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//�����܂�

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

  //�ȉ����������[�N���o�p�@��������
  _CrtDumpMemoryLeaks();
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
  //�����܂�

  SetMainWindowText("initializing...");
  ChangeWindowMode(TRUE);
  SetWindowSizeChangeEnableFlag(TRUE);
  SetWindowSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
  SetBackgroundColor(25, 53, 41);
  if (DxLib_Init() == -1)return -1;
  SetGraphMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, 32);
  SetMainWindowText("black jack");
  loadRc();
  exec();
  deleteRc();
  DxLib_End();
  return 0;
} 
