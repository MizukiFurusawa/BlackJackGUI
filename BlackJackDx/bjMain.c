#include "DxLib.h"
#include "bjMain.h"
#include "fps_ctrl.h"
#include "common.h"
#include <math.h>
#include<stdlib.h>
#include <stdio.h>
#include <time.h>


const char  topInfoStr[] = "CREDITS: %05d   BET: %05d   WIN: %05d";
const char  messege[] = "ベットボタンを押してゲームを開始してください.";
const char  betErrorMsg[] = "※ クレジットが不足しています ※";
const char  gameOverStr[] = "GAME  OVER!!";
const char  playerWinStr[] = "YOU  WIN!!";
const char  drawStr[] = "DRAW!!";
const int   chip_num[] = { 1, 5, 10, 25, 50, 100, 500, 1000, 5000 };
int         img_chips[9];
int         keyBuff[256];
int         mouseLeaveBuff[2];
int         mouseBuff[2];
char        strInfo[128];
int         credits = 10000;      //プレイヤーの持ち金
int         bet;                  //プレイヤーの掛け金
int         win;                  //プレイヤーの勝ち金
int         stack_y;              //山札のy座標
int         game_pattern;
int         isFinish;
int         isResult;
int         isDouble;
int         loadSize;
int         move_pattern;
int         cnt;
int         target_x;
int         target_y;
int         backImg;
int         moveImg;
int         isVisible;
int         playerBlackJackFlag;
int         dealerBlackJackFlag;
int         chip_position[9];
int         isBetError;
int         cntFirstDeal;
int         dealType;
int         timer;
list        stack;                //山札
list        player_card;          //プレイヤーの手札
list        dealer_card;          //ディーラーの手札
list        lstTmp;
card_t      tmp;



void initialize(void){
  int i;
  for (i = 0; i < 9; i++)chip_position[i] = 0;
  cntFirstDeal = 0;
  timer = 0;
  isDouble = 0;
  credits += win;
  win = 0;
  bet = 0;
  returnCard();
}



int isDealFinish(void){
  if (move_pattern == 0)return 1;
  return 0;
}



void card_render(void){
  static int x, y;
  stack_render();
  player_card_render();
  dealer_card_render();

  switch (move_pattern){
  case 10:
    x = STACK_X - (int)((sin(-PI / 2 + PI / MOVE_CARD_FRAME * cnt) + 1) / 2 * target_x);
    y = STACK_Y + (int)((sin(-PI / 2 + PI / MOVE_CARD_FRAME * cnt) + 1) / 2 * target_y);
    DrawGraph(x, y, moveImg, false);
    cnt++;
    if (cnt > MOVE_CARD_FRAME){
      cnt = 0;
      move_pattern++;
      break;
    }
    break;

  case 11:
    stack_y = (int)((sin(PI / 2 / 3 * cnt) + 1) / 2 * CARD_SPACE);
    DrawGraph(x, y, moveImg, false);
    cnt++;
    if (cnt > 3){
      tmp = get_card(stack);
      tmp.isRender = isVisible;
      set_card(stack, tmp, 0);
      player_card = transferStack(player_card);
      move_pattern = 0;
      stack_y = 0;
      break;
    }
    break;

  case 20:
    x = STACK_X - (int)((sin(-PI / 2 + PI / MOVE_CARD_FRAME * cnt) + 1) / 2 * target_x);
    y = STACK_Y + (int)((sin(-PI / 2 + PI / MOVE_CARD_FRAME * cnt) + 1) / 2 * target_y);
    DrawGraph(x, y, moveImg, false);
    cnt++;
    if (cnt > MOVE_CARD_FRAME){
      cnt = 0;
      move_pattern++;
      break;
    }
    break;

  case 21:
    stack_y = (int)((sin(PI / 2 / 3 * cnt) + 1) / 2 * CARD_SPACE);
    DrawGraph(x, y, moveImg, false);
    cnt++;
    if (cnt > 3){
      tmp = get_card(stack);
      tmp.isRender = isVisible;
      set_card(stack, tmp, 0);
      dealer_card = transferStack(dealer_card);
      move_pattern = 0;
      stack_y = 0;
      break;
    }
    break;
  }
}



int add_card(int type,int showFlag){
  if (move_pattern == 0){
    if (type == PLAYER_CARD){
      tmp = get_card(stack);
      switch (tmp.isRender){
      default:
      case 0:moveImg = backImg; break;
      case 1:moveImg = get_card(stack).gHandle; break;
      }
      tmp.isRender = 2;
      set_card(stack, tmp, 0);
      target_x = STACK_X - (get_list_size(player_card) + 1) * CARD_SPACE;
      target_y = PLAYER_CARD_Y - STACK_Y;
      cnt = 0;
      move_pattern = 10;
    }
    if (type == DEALER_CARD){
      tmp = get_card(stack);
      switch (tmp.isRender){
      default:
      case 0:moveImg = backImg; break;
      case 1:moveImg = get_card(stack).gHandle; break;
      }
      tmp.isRender = 2;
      set_card(stack, tmp, 0);
      target_x = STACK_X - (get_list_size(dealer_card) + 1) * CARD_SPACE;
      target_y = DEALER_CARD_Y - STACK_Y;
      cnt = 0;
      move_pattern = 20;
    }
    isVisible = showFlag;
    return 1;
  }
  return 0;
}



void show_list_card(list lst, int n, int x, int y){
  tmp = get_card(get_list(lst, n));
  switch (tmp.isRender){
  case 0:DrawGraph(x, y, backImg, false); break;
  case 1:DrawGraph(x, y, tmp.gHandle, false); break;
  default:break;
  }
}



void stack_render(){
  int k = get_list_size(stack);
  for (int i = k - 1; i >= 0; i--){
    if (STACK_Y + i * CARD_SPACE < WINDOW_SIZE_X)show_list_card(stack, i, STACK_X, STACK_Y + i * CARD_SPACE - stack_y);
  }
}


void player_card_render(){
  int k = get_list_size(player_card);
  for (int i = k - 1; i >= 0; i--){ 
    show_list_card(player_card, i, (k - i) * CARD_SPACE, PLAYER_CARD_Y);
  }
  DrawFormatString(CARD_SPACE, PLAYER_CARD_Y - 25, GetColor(255, 255, 255), "YOUR SCORE :%d", get_score(player_card, FALSE));
}



void dealer_card_render(){
  int k = get_list_size(dealer_card);
  for (int i = k - 1; i >= 0; i--){
    show_list_card(dealer_card, i, (k - i) * CARD_SPACE, DEALER_CARD_Y);
  }
}



void deleteRc(void){
  stack = deleteList(stack);
  player_card = deleteList(player_card);
  dealer_card = deleteList(dealer_card);
  DeleteGraph(img_chips[0]);
  DeleteGraph(backImg);
}



void loadRc(void){
  stack = deleteList(stack);
  player_card = deleteList(player_card);
  dealer_card = deleteList(dealer_card);
  SetUseASyncLoadFlag(TRUE);
  player_card = emptyList();
  dealer_card = emptyList();
  shuffle_list(stack = init_card());
  flipRandCard(stack);
  LoadDivGraph("img/chips.png", 9, 1, 9, 100, 100, img_chips);
  backImg = LoadGraph("img/cardBack.jpg");
  SetUseASyncLoadFlag(FALSE);
}



void Keyboard_update(void){
  char tmpKey[256];
  GetHitKeyStateAll(tmpKey);
  for (int i = 0; i < 256; i++){
    if (tmpKey[i] != 0)keyBuff[i]++;
    else keyBuff[i] = 0;
  }
}



void mouse_update(void){
  if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)mouseBuff[MOUSE_INPUT_L]++;
  else if (mouseBuff[MOUSE_INPUT_L] >= 1){
    mouseLeaveBuff[MOUSE_INPUT_L] = 1;
    mouseBuff[MOUSE_INPUT_L] = 0;
  }
  else mouseLeaveBuff[MOUSE_INPUT_L] = 0;

  if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)mouseBuff[MOUSE_INPUT_R]++;
  else if (mouseBuff[MOUSE_INPUT_R] >= 1){
    mouseLeaveBuff[MOUSE_INPUT_R] = 1;
    mouseBuff[MOUSE_INPUT_R] = 0;
  }
  else mouseLeaveBuff[MOUSE_INPUT_R] = 0;
}



void exec(void){
  while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
    Keyboard_update();
    mouse_update();
    fps_update();
    draw();
    fps_draw();
    ScreenFlip();
    fps_wait();
  }
}



int get_score(list lst, int firstCardOnly){
  int ret = 0;
  list check_lst = lst;
  while (!isEmpty(check_lst)){
    tmp = get_card(check_lst);
    if (tmp.val == 0)ret++;
    if (10 <= tmp.val && tmp.val < 13)ret += 10;
    if (1 <= tmp.val && tmp.val < 10)ret += tmp.val + 1;
    if (firstCardOnly == TRUE)break;
    check_lst = check_lst->next;
  }
  check_lst = lst;
  while (!isEmpty(check_lst)){
    tmp = get_card(check_lst);
    if (tmp.val == 0 && ret + 10 <= 21)ret += 10;
    if (firstCardOnly == TRUE)break;
    check_lst = check_lst->next;
  }
  return ret;
}



int get_event(void){
  int x1 = (WINDOW_SIZE_X - EVENT_BOX_SIZE_X) / 2;
  int y1 = (WINDOW_SIZE_Y - EVENT_BOX_SIZE_Y) / 2 + 100;
  const int side = 10;
  int mx, my,width;
  SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
  DrawBox(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, GetColor(0, 0, 0), true);
  DrawBox(x1 + side, y1 + EVENT_BOX_SIZE_Y * 0 / 3 + side, x1 + EVENT_BOX_SIZE_X - side, y1 + EVENT_BOX_SIZE_Y * 1 / 3 - side, GetColor(255, 0, 0), true);
  if (!isDouble)DrawBox(x1 + side, y1 + EVENT_BOX_SIZE_Y * 1 / 3 + side, x1 + EVENT_BOX_SIZE_X - side, y1 + EVENT_BOX_SIZE_Y * 2 / 3 - side, GetColor(0, 255, 0), true);
  DrawBox(x1 + side, y1 + EVENT_BOX_SIZE_Y * 2 / 3 + side, x1 + EVENT_BOX_SIZE_X - side, y1 + EVENT_BOX_SIZE_Y * 3 / 3 - side, GetColor(0, 0, 255), true);
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
  width = (WINDOW_SIZE_X - GetDrawStringWidth(hitStr, strlen(hitStr))) / 2;
  DrawString(width, y1 + 50, hitStr, GetColor(255, 255, 255));
  if (!isDouble)DrawString(width, y1 + 150, doubleStr, GetColor(255, 255, 255));
  DrawString(width, y1 + 250, standStr, GetColor(255, 255, 255));
  if (mouseLeaveBuff[MOUSE_INPUT_L]  == 1){
    GetMousePoint(&mx, &my);
    if (x1 + side < mx && mx < x1 + EVENT_BOX_SIZE_X - side &&
      y1 + EVENT_BOX_SIZE_Y * 0 / 3 + side < my  && my < y1 + EVENT_BOX_SIZE_Y * 1 / 3 - side)return EVENT_HIT;
    if (x1 + side < mx && mx < x1 + EVENT_BOX_SIZE_X - side &&
      y1 + EVENT_BOX_SIZE_Y * 1 / 3 + side < my  && my < y1 + EVENT_BOX_SIZE_Y * 2 / 3 - side)return EVENT_DOUBLE;
    if (x1 + side < mx && mx < x1 + EVENT_BOX_SIZE_X - side &&
      y1 + EVENT_BOX_SIZE_Y * 2 / 3 + side < my  && my < y1 + EVENT_BOX_SIZE_Y * 3 / 3 - side)return EVENT_STAND;
  }
  return EVENT_NOTHING;
}



void draw(void){
  int i, mx, my, y, width, load;


  switch (game_pattern){


    //ローディング画面
  case SCENE_LOADING:
    loadSize = GetASyncLoadNum();
    game_pattern++;
    break;

  case SCENE_LOADING + 1:
    load = (loadSize - GetASyncLoadNum()) * 100 / loadSize;
    DrawFormatString(10, 10, GetColor(255, 255, 255), "now loading... %d%%", load);
    if (GetASyncLoadNum() <= 0){
      game_pattern = SCENE_BET;
    }
    break;


    //ベット画面
  case SCENE_BET:
    for (i = 0; i < 9; i++){
      GetMousePoint(&mx, &my);
      y = (int)((sin(-PI / 2 + PI / 5 * chip_position[i]) + 1) / 2 * 30);
      if (i * 70 - 10 < mx  && mx < i * 70 - 10 + 70 && WINDOW_SIZE_Y - 80 < my  && my < WINDOW_SIZE_Y){
        if (y < 30)chip_position[i]++;
        if (mouseBuff[MOUSE_INPUT_L] == 1){
          if (credits - chip_num[i] >= 0){
            isBetError = 0;
            game_pattern = SCENE_HANDOUT;
            srand((unsigned)time(NULL));
            dealType = rand() % 3;
            credits -= chip_num[i];
            bet += chip_num[i];
          }
          else isBetError = 1;
        }
      }
      else if (y > 0)chip_position[i]--;
      DrawGraph(i * 70 - 10, WINDOW_SIZE_Y - 90 - y, img_chips[i], true);
    }

    width = GetDrawStringWidth(messege, strlen(messege));
    DrawString((WINDOW_SIZE_X - width) / 2, WINDOW_SIZE_Y / 2, messege, GetColor(255, 255, 255));
    width = GetDrawStringWidth(betErrorMsg, strlen(betErrorMsg));
    if (isBetError)DrawString((WINDOW_SIZE_X - width) / 2, WINDOW_SIZE_Y / 2 - 30, betErrorMsg, GetColor(255, 255, 255));
    break;


    //ゲーム画面
  case SCENE_HANDOUT:
    switch (dealType){
    case 0:
      switch (cntFirstDeal){
      case 0:if (add_card(PLAYER_CARD, 1))cntFirstDeal++; break;
      case 1:if (add_card(DEALER_CARD, 1))cntFirstDeal++; break;
      case 2:if (add_card(PLAYER_CARD, 1))cntFirstDeal++; break;
      case 3:if (add_card(DEALER_CARD, 0))cntFirstDeal++; break;
      case 4:if (isDealFinish())game_pattern = SCENE_ACTION; break;
      }
      break;
    case 1:
      switch (cntFirstDeal){
      case 0:if (add_card(PLAYER_CARD, 1))cntFirstDeal++; break;
      case 1:if (add_card(PLAYER_CARD, 1))cntFirstDeal++; break;
      case 2:if (add_card(DEALER_CARD, 1))cntFirstDeal++; break;
      case 3:if (add_card(DEALER_CARD, 0))cntFirstDeal++; break;
      case 4:if (isDealFinish())game_pattern = SCENE_ACTION; break;
      }
      break;
    case 2:
      switch (cntFirstDeal){
      case 0:if (add_card(DEALER_CARD, 1))cntFirstDeal++; break;
      case 1:if (add_card(DEALER_CARD, 0))cntFirstDeal++; break;
      case 2:if (add_card(PLAYER_CARD, 1))cntFirstDeal++; break;
      case 3:if (add_card(PLAYER_CARD, 1))cntFirstDeal++; break;
      case 4:if (isDealFinish())game_pattern = SCENE_ACTION; break;
      }
      break;
    }
    card_render();
    break;


    //行動選択
  case SCENE_ACTION:
    card_render();
    switch (get_event()){
    case EVENT_HIT:add_card(PLAYER_CARD, 1); game_pattern = SCENE_HIT; break;
    case EVENT_DOUBLE:
      if (isDouble || credits - bet < 0)break;
      credits -= bet;
      bet += bet;
      isDouble = 1;
      add_card(PLAYER_CARD, 1);
      game_pattern = SCENE_HIT;
      break;
    case EVENT_STAND:
      flipAllCard(dealer_card);
      game_pattern = SCENE_STAND;
      break;
    }
    break;


  case SCENE_HIT:
    if (isDealFinish()){
      if (get_score(player_card, FALSE) > 21){
        game_pattern = SCENE_RESULT;
        timer = GetNowCount();
        break;
      }
      game_pattern = SCENE_ACTION;
    }
    card_render();
    break;


  case SCENE_STAND:
    card_render();
    if (get_score(dealer_card, FALSE) <= 16){
      add_card(DEALER_CARD, 1);
      game_pattern++;
      break;
    }
    else game_pattern = SCENE_RESULT;
    break;


  case SCENE_STAND + 1:
    if (isDealFinish())game_pattern = SCENE_STAND;
    card_render();
    break;


  case SCENE_GAMEOVER:
    card_render();
    flipAllCard(dealer_card);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
    DrawBox(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, GetColor(0, 0, 0), true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
    width = GetDrawStringWidth(gameOverStr, strlen(gameOverStr));
    DrawString((WINDOW_SIZE_X - width) / 2, WINDOW_SIZE_Y / 2, gameOverStr, GetColor(255, 255, 255));
    if (mouseLeaveBuff[MOUSE_INPUT_L] == 1){
      game_pattern = SCENE_INIT;
    }
    break;
    

  case SCENE_PLAYERWIN:
    if (playerBlackJackFlag == TRUE)win = (int)(bet * 3.5);
    else win = bet * 2;
    card_render();
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
    DrawBox(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, GetColor(0, 150, 0), true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
    width = GetDrawStringWidth(playerWinStr, strlen(playerWinStr));
    DrawString((WINDOW_SIZE_X - width) / 2, WINDOW_SIZE_Y / 2, playerWinStr, GetColor(255, 255, 255));
    if (mouseLeaveBuff[MOUSE_INPUT_L] == 1){
      game_pattern = SCENE_INIT;
    }
    break;


  case SCENE_DRAW:
    card_render();
    win = bet;
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
    DrawBox(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, GetColor(0, 0, 255), true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
    width = GetDrawStringWidth(drawStr, strlen(drawStr));
    DrawString((WINDOW_SIZE_X - width) / 2, WINDOW_SIZE_Y / 2, drawStr, GetColor(255, 255, 255));
    if (mouseLeaveBuff[MOUSE_INPUT_L] == 1){
      game_pattern = SCENE_INIT;
    }
    break;
     

  case SCENE_RESULT:

    card_render();
    tmp = get_card(get_list(stack, 0));
    tmp.isRender = 1;
    set_card(stack, tmp, 0);

    //ブラックジャック
    if (get_list_size(player_card) == 2 && get_score(player_card, FALSE) == 21)playerBlackJackFlag = TRUE;
    else playerBlackJackFlag = FALSE;

    if (get_list_size(dealer_card) == 2 && get_score(dealer_card, FALSE) == 21)dealerBlackJackFlag = TRUE;
    else dealerBlackJackFlag = FALSE;


    //dealerのバースト
    if (get_score(dealer_card, FALSE) > 21){
      game_pattern = SCENE_PLAYERWIN;
      timer = GetNowCount();
      break;
    }

    //playerのバースト
    else if (get_score(player_card, FALSE) > 21){
      game_pattern = SCENE_GAMEOVER;
      timer = GetNowCount();
      break;
    }

    //dealerの得点のほうが多い
    else if (get_score(dealer_card, FALSE) > get_score(player_card, FALSE)){
      game_pattern = SCENE_GAMEOVER;
      timer = GetNowCount();
      break;
    }

    //プレイヤーの得点のほうが多い
    else if (get_score(dealer_card, FALSE) < get_score(player_card, FALSE)){
      game_pattern = SCENE_PLAYERWIN;
      timer = GetNowCount();
      break;
    }

    //得点は同じ
    else{

      //playerがブラックジャック
      if (playerBlackJackFlag == TRUE && dealerBlackJackFlag == FALSE){
        game_pattern = SCENE_PLAYERWIN;
        timer = GetNowCount();
        break;
      }

      //dealerがブラックジャック
      if (playerBlackJackFlag == FALSE && dealerBlackJackFlag == TRUE){
        game_pattern = SCENE_GAMEOVER;
        timer = GetNowCount();
        break;
      }

      //それ以外はDrawで処理
      game_pattern = SCENE_DRAW;
      timer = GetNowCount();
      break;
    }
    break;


  case SCENE_INIT:
    card_render();
    tmp = get_card(get_list(stack, 0));
    tmp.isRender = 0;
    set_card(stack, tmp, 0);
    initialize();
    game_pattern = SCENE_BET;
    break;
  }
  //上部に表示する部分
  width = GetDrawFormatStringWidth(topInfoStr, credits, bet, win);
  DrawFormatString(WINDOW_SIZE_X - width - 10, 10, GetColor(255, 255, 255), topInfoStr, credits, bet, win);
}
