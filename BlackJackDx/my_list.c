#pragma once
#include<stdlib.h>
#include <stdio.h>
#include <time.h>
#include "DxLib.h"
#include "my_list.h"

extern list stack;
extern list player_card;
extern list dealer_card;
const char *mark[4] = { "h", "s", "c", "d" };
const char *value[13] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "j", "q", "k" };


list cons(card_t v, list lst) {
  list nlst;
  nlst = (list)malloc(sizeof(node_t));
  nlst->card = v;
  nlst->next = lst;
  return nlst;
}


int isEmpty(list lst) {
  return (lst == NULL);
}


list emptyList(void) {
  return NULL;
}


list get_list(list lst, int n){
  return __get_list(lst, n, 0);
}


list __get_list(list lst, int n, int k){
  if (isEmpty(lst))return NULL;
  if (n != k){
    k++;
    return __get_list(lst->next, n, k);
  }
  else{
    return lst;
  }
}


void show_card_info(list lst){
  if (isEmpty(lst))return;
  printf("[ %s ] %-2s", mark[lst->card.pic], value[lst->card.val]);
}


int get_list_size(list lst){
  return __get_list_size(lst, 0);
}


int __get_list_size(list lst, int n){
  if (isEmpty(lst))return n;
  n++;
  return __get_list_size(lst->next, n);
}


void  set_card(list lst, card_t v, int n){
  __set_card(lst, v, n, 0);
}


void  __set_card(list lst, card_t v, int n, int k){
  if (isEmpty(lst))return;
  if (n != k){
    k++;
    __set_card(lst->next, v, n, k);
  }
  else{
    lst->card = v;
    return;
  }
}


list init_card(void){
  int i, j;
  list ret = emptyList();
  card_t tmp;
  char path[128];
  for (i = 0; i < 4; i++){
    for (j = 0; j < 13; j++){
      tmp.pic = i;
      tmp.val = j;
      tmp.isRender = 0;
      sprintf_s(path, sizeof(path), "img/trump/%s%s.jpg", mark[tmp.pic], value[tmp.val]);
      tmp.gHandle = LoadGraph(path);
      ret = cons(tmp, ret);
    }
  }
  return ret;
}


void shuffle_list(list lst){
  int i, j, size;
  card_t tmp;
  srand((unsigned)time(NULL));
  size = get_list_size(lst);
  for ( i = 0; i < size; i++){
    j = rand() % size;
    tmp = get_card(get_list(lst, i));
    set_card(lst, get_card(get_list(lst, j)), i);
    set_card(lst, tmp, j);
  }
}


card_t  get_card(list lst){
  return lst->card;
}


int  get_card_graph(list lst){
  return lst->card.gHandle;
}


list exceptHeadList(list lst){
  list ret = emptyList();
  if (isEmpty(lst))return NULL;
  if (isEmpty(lst->next)){
    free(lst);
    lst = NULL;
    return emptyList();
  }
  ret = lst->next;
  free(lst);
  lst = NULL;
  return ret;
}


list deleteList(list lst){
  while (get_list_size(lst) > 0){
    DeleteGraph(lst->card.gHandle);
    lst = exceptHeadList(lst);
  }
  return lst;
}


list transferStack(list lst){
  list ret = lst;
  ret = cons(get_card(stack),ret);
  stack = exceptHeadList(stack);
  return ret;
}


list getLastList(list lst){
  list ret = lst;
  if (isEmpty(lst))return emptyList();
  while (!isEmpty(ret->next))ret = ret->next;
  return ret;
}


void returnCard(void){
  list stackLastList;
  flipRandCard(player_card);
  flipRandCard(dealer_card);
  stackLastList = getLastList(stack);
  stackLastList->next = player_card;
  stackLastList = getLastList(stack);
  stackLastList->next = dealer_card;
  player_card = emptyList();
  dealer_card = emptyList();
}



void flipRandCard(list lst){
  srand((unsigned)time(NULL));
  while (!isEmpty(lst)){
    if ((double)rand() / RAND_MAX < FLIP_PERCENTAGE)lst->card.isRender = 1;
    else lst->card.isRender = 0;
    lst = lst->next;
  }
}

void flipAllCard(list lst){
  while (!isEmpty(lst)){
    lst->card.isRender = 1;
    lst = lst->next;
  }
}
