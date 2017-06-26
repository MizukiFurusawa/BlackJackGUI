#include "DxLib.h"
#include "fps_ctrl.h"

int mStartTime;
int mCount;
double mFps;

void fps_update(void){
  if (mCount == 0)mStartTime = GetNowCount(FALSE);
  if (mCount == SAMPLE_N){
    int t = GetNowCount(FALSE);
    mFps = 1000.f / ((t - mStartTime) / (float)SAMPLE_N);
    mCount = 0;
    mStartTime = t;
  }
  mCount++;
}

void fps_wait(void){
  int tookTime = GetNowCount(FALSE) - mStartTime;
  int waitTime = mCount * 1000 / SET_FPS - tookTime;
  if (waitTime > 0)Sleep(waitTime);
}

void fps_draw(void){
  DrawFormatString(10, 10, GetColor(255, 255, 255), "%.1fFPS", mFps);
}
