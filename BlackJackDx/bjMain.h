#include "my_list.h"

#define MOUSE_INPUT_L     0
#define MOUSE_INPUT_R     1
#define CARD_SPACE        40
#define STACK_X           (WINDOW_SIZE_X - 150)
#define STACK_Y           50
#define PLAYER_CARD_Y     70
#define DEALER_CARD_Y     300
#define PLAYER_CARD       0
#define DEALER_CARD       1
#define DEALER_CARD       1
#define EVENT_NOTHING     0
#define EVENT_HIT         1
#define EVENT_STAND       2
#define EVENT_DOUBLE      3
#define EVENT_BOX_SIZE_X  (WINDOW_SIZE_X - 80 * 2)
#define EVENT_BOX_SIZE_Y  300
#define MOVE_CARD_FRAME   20
#define SCENE_LOADING     0
#define SCENE_BET         10
#define SCENE_HANDOUT     20
#define SCENE_ACTION      30
#define SCENE_HIT         40
#define SCENE_STAND       50
#define SCENE_GAMEOVER    60
#define SCENE_PLAYERWIN   70
#define SCENE_DRAW        80
#define SCENE_RESULT      90
#define SCENE_INIT        100
const char hitStr[]     = "   HIT    ";
const char standStr[]   = "  STAND   ";
const char doubleStr[]  = "  DOUBLE  ";


//画像ファイルを読み込む
void loadRc(void);


//読み込んだ画像ファイルを削除する
void deleteRc(void);


//カードを画面に描画する
void card_render(void);


//プレイヤーの手札、もしくは、ディーラの手札に対して、
//山札から1枚を引いたカードを追加する
// type : PLAYER_CARD or DEALER_CARD
// showFlag : TRUE - 表 , FALSE - 裏
int add_card(int type,int showFlag);


//listを配列とみて、lstの0から数えてn番目のカード情報を、
//画面上に(x,y)に描画する
void show_list_card(list lst, int n, int x, int y);


//山札を描画する
void stack_render();


//プレイヤーの手札を描画する
void player_card_render(void);


//ディーラーの手札を描画する
void dealer_card_render(void);


//リストの生成、および使用する変数の初期化
void initialize(void);


//キーボードの押下状態を取得し、bufferを更新する
void Keyboard_update(void);


//マウスの押下状態を取得し、bufferを更新する
void mouse_update(void);


//ゲーム実行関数本体
void exec(void);


//描画処理本体
void draw(void);


// hit , double , stand のアクションを取得する
int get_event(void);


//カードを山札から配り終えているか
//すなわち、山札からプレイヤー、もしくはディーラー
//の手札まで、カードが移動し終わっているか
int isDealFinish(void);


//listを山札、もしくは手札とみて、
//ブラックジャックのルールに基づいて、
//スコアを整数値として返す
//firstCardOnlyがTRUEとは、手札の最初のカードのみ評価する
//firstCardOnlyがFALSEとは、手札のすべてのカードを評価する
int get_score(list lst, int firstCardOnly);
