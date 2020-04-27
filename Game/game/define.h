﻿#pragma once
#define WINDOW_CLASS_NAME L"Simon"
#define MAIN_WINDOW_TITLE L"Simon"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define SCREEN_WIDTH 272
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 120

// SCENE
#define SCENE_SECTION_UNKNOWN			-1
#define SCENE_SECTION_SETTINGS			0
#define SCENE_SECTION_TEXTURES			2
#define SCENE_SECTION_SPRITES			3
#define SCENE_SECTION_ANIMATIONS		4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS			6
#define SCENE_SECTION_TILEMAP			7
#define SCENE_SECTION_GRID				8

#define MAX_SCENE_LINE					1024

//ID TEXTURES
#define ID_TEX_SIMON              0
#define ID_TEX_BRICK_OUT_CASTLE   1
#define ID_TEX_TORCH              2 
#define ID_TEX_MORNINGSTAR		  3
#define ID_TEX_BRICK_SCENE_ONE	  4
#define ID_TEX_CANDLE	          5
#define ID_TEX_ITEM_MORNINGSTAR	  200
#define ID_TEX_ITEM_HEART		  201
#define ID_TEX_COLLISION_EFFECT	  800
#define ID_TEX_DEAD_EFFECT		  801
#define ID_TEX_HP				  900
#define ID_TEX_ITEM_BOARD_HEART	  901
#define ID_TEX_MAP_OUT_CASTLE     1000

//ID SPRITES
#define ID_SPRITE_MAP_OUT_CASTLE		1000


// config game
#define DEVIATION_X						0
#define DEVIATION_Y						20

//ID OBJECTS
#define	OBJECT_TYPE_SIMON				1

#define	OBJECT_TYPE_TORCH				10
#define OBJECT_TYPE_CANDLE				11
#define OBJECT_TYPE_GATE				12
#define	OBJECT_TYPE_BOUNGDING_MAP		13
#define OBJECT_TYPE_OBJECTHIDDEN		14
#define	OBJECT_TYPE_BOTTOM_STAIR		15
#define OBJECT_TYPE_TOP_STAIR			16

#define OBJECT_TYPE_ITEM_MORNINGSTAR	100
#define	OBJECT_TYPE_ITEM_SMALL_HEART	101
#define	OBJECT_TYPE_ITEM_HEART			102
#define	OBJECT_TYPE_ITEM_KNIFE			103


//SIMON
#define SIMON_WALKING_SPEED			0.05f 
#define SIMON_JUMP_SPEED_Y			0.204f
#define SIMON_JUMP_DEFLECT_SPEED	0.2f
#define SIMON_GRAVITY				0.0007f   //0.0017f 
#define SIMON_DIE_DEFLECT_SPEED		0.5f
#define SIMON_HP					16

#define SIMON_ATTACK_TIME			150*3-10



//simon state
#define SIMON_STATE_IDLE					100

#define SIMON_STATE_WALK_RIGHT				200
#define SIMON_STATE_WALK_LEFT				300
#define SIMON_STATE_JUMP					400
#define SIMON_STATE_SIT_DOWN				500
#define SIMON_STATE_CLIMB_STAIR_UP		    600
#define SIMON_STATE_CLIMB_STAIR_DOWN		700
#define SIMON_STATE_ATTACKING				800
#define SIMON_STATE_INTRO					900
#define SIMON_STATE_HURT					900
#define SIMON_STATE_DIE						10000

//simon ani
#define SIMON_ANI_IDLE_LEFT						0
#define SIMON_ANI_IDLE_RIGHT					1
#define SIMON_ANI_WALKING_LEFT					2
#define SIMON_ANI_WALKING_RIGHT					3
#define SIMON_ANI_SIT_DOWN_LEFT					4
#define SIMON_ANI_SIT_DOWN_RIGHT				5
#define SIMON_ANI_CIMB_STAIR_UP_LEFT			6
#define SIMON_ANI_CIMB_STAIR_UP_RIGHT			7
#define SIMON_ANI_CIMB_STAIR_DOWN_LEFT			8
#define SIMON_ANI_CIMB_STAIR_DOWN_RIGHT			9
#define SIMON_ANI_HURT_LEFT						10
#define SIMON_ANI_HURT_RIGHT					11
#define SIMON_ANI_DEATH_LEFT					12
#define SIMON_ANI_DEATH_RIGHT					13
#define SIMON_ANI_ATTACKING_LEFT				14
#define SIMON_ANI_ATTACKING_RIGHT				15
#define SIMON_ANI_ATTACKING_SIT_LEFT			16
#define SIMON_ANI_ATTACKING_SIT_RIGHT			17
#define SIMON_ANI_ATTACKING_UP_STAIR_LEFT	    18
#define SIMON_ANI_ATTACKING_UP_STAIR_RIGHT		19
#define SIMON_ANI_ATTACKING_DOWN_STAIR_LEFT		20
#define SIMON_ANI_ATTACKING_DOWN_STAIR_RIGHT	21
#define SIMON_ANI_INTRO							22
#define SIMON_ANI_IDLE_STAIR_UP_LEFT			23
#define SIMON_ANI_IDLE_STAIR_UP_RIGHT			24
#define SIMON_ANI_IDLE_STAIR_DOWN_LEFT			25
#define SIMON_ANI_IDLE_STAIR_DOWN_RIGHT			26


// size bbox simon
#define SIMON_BBOX_WIDTH  16
#define SIMON_BBOX_HEIGHT 32

#define SIMON_SIT_BBOX_WIDTH  32
#define SIMON_SIT_BBOX_HEIGHT 46


#define SIMON_UNTOUCHABLE_TIME					2000
#define SIMON_HURTABLE_TIME						600

#define SIMON_MAX_HP 8

//MORNINGSTAR	
#define MORNINGSTAR_LEVEL_1	1
#define MORNINGSTAR_LEVEL_2	2
#define MORNINGSTAR_LEVEL_3	3

#define MORNINGSTAR_LEVEL_1_ANI_PREPARE_LEFT		0
#define MORNINGSTAR_LEVEL_1_ANI_LEFT				1
#define MORNINGSTAR_LEVEL_1_ANI_PREPARE_RIGHT		2
#define MORNINGSTAR_LEVEL_1_ANI_RIGHT				3
#define MORNINGSTAR_LEVEL_2_ANI_PREPARE_LEFT		4
#define MORNINGSTAR_LEVEL_2_ANI_LEFT				5
#define MORNINGSTAR_LEVEL_2_ANI_PREPARE_RIGHT		6
#define MORNINGSTAR_LEVEL_2_ANI_RIGHT				7
#define MORNINGSTAR_LEVEL_3_ANI_PREPARE_LEFT		8
#define MORNINGSTAR_LEVEL_3_ANI_LEFT				9
#define MORNINGSTAR_LEVEL_3_ANI_PREPARE_RIGHT		10
#define MORNINGSTAR_LEVEL_3_ANI_RIGHT				11

#define MORNINGSTAR_STATE_PREPARE					0
#define MORNINGSTAR_STATE_HIT						1

#define MORNINGSTAR_DELTA_POSITION_Y				8

#define MORNINGSTAR_DELTA_POSITION_BOX_HEIGHT		9
#define MORNINGSTAR_DELTA_X_LEFT					6
#define MORNINGSTAR_DELTA_X_RIGHT					5

#define MORNINGSTAR_LEVEL_1_BBOX_WIDTH				24
#define MORNINGSTAR_LEVEL_1_BBOX_HEIGHT				8
#define MORNINGSTAR_LEVEL_2_BBOX_WIDTH				26
#define MORNINGSTAR_LEVEL_2_BBOX_HEIGHT				6
#define MORNINGSTAR_LEVEL_3_BBOX_WIDTH				40
#define MORNINGSTAR_LEVEL_3_BBOX_HEIGHT				6

//item
#define ITEM_MORNINGSTAR	0
#define ITEM_SMALL_HEART	1
#define ITEM_HEART			2
#define ITEM_BALL			3
#define ITEM_MONEY			3
#define ITEM_ROAST			5
#define ITEM_AXE			6
#define ITEM_BOOMERANG		7
#define ITEM_HOLY_WATER		8
#define ITEM_DAGGER			9
#define ITEM_STOP_WATCH		10
#define ITEM_INVISIBLE		11
#define ITEM_UPGRADE_1		12
#define ITEM_UPGRADE_2		13
#define ITEM_CROSS			14
#define ITEM_MONEY_WHITE	15
#define ITEM_MONEY_RED		16
#define ITEM_MONEY_PURPLE	17


#define ITEM_STATE_UP				9000
#define ITEM_STATE_IDLE				9001

// Time Display Item

#define ITEM_TIMEDISPLAYMAX			5000


//item board
#define ITEM_BOARD_HEART			40001

