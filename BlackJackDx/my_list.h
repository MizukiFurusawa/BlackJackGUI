#pragma once


//山札を作るときに、カードが表になる確率
#define FLIP_PERCENTAGE   0.02


struct card{
  int val;      // 1 - 13までの値
  int pic;      // 0 - 3 までの値をトランプの絵柄に対応させる
  int gHandle;  // 読み込んだトランプの画像のグラフィックハンドル
  int isRender; // 裏、表どちらを描画するのか
};
typedef struct card card_t;


struct node {
  card_t card;
  struct node *next;
};


typedef struct node node_t;
typedef node_t *list; 


//lstのカード情報を表示する
//最初のリストのみ
void  draw_card_info(int x,int y,list lst);


//lstのカード情報を取得する
//最初のリストのみ
card_t  get_card(list lst);


//カード情報vをlstに追加したリストを返す
list  cons(card_t v, list lst);


//空リストかどうか返す
int   isEmpty(list lst);


//リストの個数を1から数えて返す
//空リストの場合は0
int   get_list_size(list lst);
int   __get_list_size(list lst, int n);


//空リストを返す
list  emptyList(void);


//リストを配列とみて、lstのn番目のリストを返す
list  get_list(list lst, int n);
list  __get_list(list lst, int n, int k);


//リストを配列とみて、lstのn番目のリストに
//カード情報vを設定する
void  set_card(list lst, card_t v,int n);
void  __set_card(list lst, card_t v, int n, int k);


//52枚のカードを生成する。
list init_card(void);


//lstをシャッフルする。
void shuffle_list(list lst);


//先頭リストを除いたリストを返す
list exceptHeadList(list lst);


//リストを全部消す(freeする)
list deleteList(list lst);


//stackから1枚カードを取り出し、
//引いたカードはstackから取り除き、
//lstの先頭に加えたリストを返す。
list transferStack(list lst);


//PlayerCardとdealerCardを山札の最後尾に移動する
//メモリの確保解放は行われない
void returnCard(void);


//一定確率でlstのカードを表にする
void flipRandCard(list lst);


//すべてのカードを表にする
void flipAllCard(list lst);


//lstの最後尾のリストを返す
list getLastList(list lst);


//最初のリストにある、
//画像描画に必要なグラフィックハンドルを返す
int  get_card_graph(list lst);
