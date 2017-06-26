#include "DxLib.h"
#include "common.h"
#include "bjMain.h"

//以下メモリリーク検出用　ここから
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//ここまで

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

  //以下メモリリーク検出用　ここから
  _CrtDumpMemoryLeaks();
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
  //ここまで

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
