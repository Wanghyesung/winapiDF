#pragma once

//���� ���ڷ� �� Ÿ�Կ� ���� �̱������� �����Ϳ����� �ִ� �ھ� ��ü�� �ش�
#define SINGLE(type) public:\
					static type* GetInst()\
					{\
						static type mgr;\
						return &mgr;\
					}\
					private:\
						type(); \
						~type();

#define fDT CTimeMgr::GetInst()->GetfDT()
#define DT CTimeMgr::GetInst()->GetDT()

#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)

#define SET_ANIMATION_MULTI_ZERO   GetAnimator()->GetCurAnimation()->SetFram(0); \
							 GetAnimator()->GetOtherAnimation()->SetFram(0);

#define SET_ANIMATION_ZERO GetAnimator()->GetCurAnimation()->SetFram(0);

#define FIND_ANIMATION_SETFRAME_ZERO(player, strName) player->GetAnimator()->FindAnimation(strName)->SetFram(0);

#define IS_HOLD_MOVE_KEY (KEY_HOLD(KEY::LEFT) || KEY_HOLD(KEY::RIGHT) || KEY_HOLD(KEY::UP) || KEY_HOLD(KEY::DOWN))

#define PI 3.14592

enum class SCENE_TYPE
{
	LOGO_SCENE,
	SELECT_SCENE,
	START_SCENE,
	SERIA_SCENE,
	TOOL_SCENE,
	WEST_COAST,
	FIRST_DUNGEON,
	DUNGEON_2,
	DUNGEON_3,
	DUNGEON_4,
	DUNGEON_5,
	DUNGEON_BOSS,
	EVIL_SCENE_1,
	EVIL_SCENE_2,
	EVIL_SCENE_3,
	EVIL_SCENE_4,
	EVIL_SCENE_5,
	EVIL_BOSS,
	SCENE_BACKSTREET,//�԰��
	SCENE_BAR,//����

	END = 20,
};

enum class DUNGEON_TYPE
{
	NONE,
	EVIL,
	LORD,
	END = 3
};

enum class GROUP_TYPE
{
	DEFAULT,
	TILE,
	PORTAL,
	GROUND,
	STONE_BOX,
	STONE_PILLAR,
	SPINNER,
	CRYSTAL,
	GATE,
	PLAYER,
	ITEM,
	WALL,
	MONSTER,
	PARTICLE,
	SKILL,
	DROUP,
	ROBOT,
	MONSTER_SKILL,
	BULLET,
	FIREBALL,

	UI = 31,
	END = 32,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	BLACK,
	END
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END,
};

enum class MONSTER_STATE
{
	STONE,
	IDLE,
	PATROL, //����
	TRACE,
	ATTACK,
	ATTACK_STAND,
	ULTIMATE,
	DEFENSE,
	HIT,
	UPPER_HIT,
	DEAD,
	END
};

enum class ROBOTSTATE
{
	WAIT,
	TRACE,
	ATTACK,
	JUMP,
	BOOM
};

enum class MONSTER_ATTACK_TYPE
{
	NORMAL,
	NORMAL2,
	NORMAL3,
	SKILL1,
	SKILL2,
	SKILL3,
	END = 6
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	CHANGE_AI_STATE,
	CHANGE_FSM_STATE,
	END,
};


enum class SKILL_STATE
{
	UPPER_KICK,
	MACH_KICK,
	WINDMILL,
	RANDOM_FIRE,
	WALK_FIRE,
	MULTI_HEAD,
	RX,
	DROP,
	EX8,
	FIRE,
	EXS,
	LASER,
	END = 12,
};

enum class ATTACK_TYPE
{
	UPPER,
	DOWN,
	NORMAL
};

enum class ITEM_TYPE
{
	HPITEM,
	MPITEM,

	NONE = 3,
};


enum class PLAYER_STATE
{
	IDLE,
	WALK,
	RUN,
	ATTACK,
	ATTACK_DOWN,
	ATTACK_SLIDING,
	ATTACK_AIR,
	JUMP,
	JUMP_AIR,
	JUMP_DOWN,
	SKILL,
	HIT,
	UPPER_HIT,
	DEAD,

	END = 32,
};




