#pragma once

//핸재 인자로 준 타입에 따라 싱글톤으로 데이터영역에 있는 코어 객체를 준다
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

struct tAttackFrame
{
	UINT first = 3;
	UINT second = 5;
	UINT third = 14;
};

enum class SCENE_TYPE
{
	START_SCENE,
	SERIA_SCENE,
	TOOL_SCENE,
	SCENE_BACKSTREET,//둣골목
	SCENE_BAR,//주점
	SCENE_PORT,

	END = 4,
};


enum class GROUP_TYPE
{
	DEFAULT,
	TILE,
	WALL,
	PORTAL,
	GROUND,
	SKILL,
	MONSTER_SKILL,
	PLAYER,
	MONSTER,
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
	IDLE,
	PATROL, //순찰
	TRACE,
	ATTACK,
	HIT,
	UPPER_HIT,
	DEAD,
	END
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
	RANDOM_FIRE,
	UPPER_KICK,
	MACH_KICK,
	WINDMILL,
	WALK_FIRE,
	BUFF,
	END = 10
};

enum class ATTACK_TYPE
{
	UPPER,
	DOWN,
	NORMAL
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


