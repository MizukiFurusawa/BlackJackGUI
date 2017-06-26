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


//�摜�t�@�C����ǂݍ���
void loadRc(void);


//�ǂݍ��񂾉摜�t�@�C�����폜����
void deleteRc(void);


//�J�[�h����ʂɕ`�悷��
void card_render(void);


//�v���C���[�̎�D�A�������́A�f�B�[���̎�D�ɑ΂��āA
//�R�D����1�����������J�[�h��ǉ�����
// type : PLAYER_CARD or DEALER_CARD
// showFlag : TRUE - �\ , FALSE - ��
int add_card(int type,int showFlag);


//list��z��Ƃ݂āAlst��0���琔����n�Ԗڂ̃J�[�h�����A
//��ʏ��(x,y)�ɕ`�悷��
void show_list_card(list lst, int n, int x, int y);


//�R�D��`�悷��
void stack_render();


//�v���C���[�̎�D��`�悷��
void player_card_render(void);


//�f�B�[���[�̎�D��`�悷��
void dealer_card_render(void);


//���X�g�̐����A����юg�p����ϐ��̏�����
void initialize(void);


//�L�[�{�[�h�̉�����Ԃ��擾���Abuffer���X�V����
void Keyboard_update(void);


//�}�E�X�̉�����Ԃ��擾���Abuffer���X�V����
void mouse_update(void);


//�Q�[�����s�֐��{��
void exec(void);


//�`�揈���{��
void draw(void);


// hit , double , stand �̃A�N�V�������擾����
int get_event(void);


//�J�[�h���R�D����z��I���Ă��邩
//���Ȃ킿�A�R�D����v���C���[�A�������̓f�B�[���[
//�̎�D�܂ŁA�J�[�h���ړ����I����Ă��邩
int isDealFinish(void);


//list���R�D�A�������͎�D�Ƃ݂āA
//�u���b�N�W���b�N�̃��[���Ɋ�Â��āA
//�X�R�A�𐮐��l�Ƃ��ĕԂ�
//firstCardOnly��TRUE�Ƃ́A��D�̍ŏ��̃J�[�h�̂ݕ]������
//firstCardOnly��FALSE�Ƃ́A��D�̂��ׂẴJ�[�h��]������
int get_score(list lst, int firstCardOnly);
