LittlerootTown_MaysHouse_2F_MapScripts:: @ 81F9296
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_MaysHouse_2F_MapScript1_1F92A1
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LittlerootTown_MaysHouse_2F_MapScript2_1F931D
	.byte 0

@ -----------------------------------------------------

LittlerootTown_MaysHouse_2F_MapScript1_1F92A1: @ 81F92A1
	compare VAR_LITTLEROOT_RIVAL_STATE, 2
	call_if_lt LittlerootTown_MaysHouse_2F_EventScript_1F930A
	compare VAR_LITTLEROOT_RIVAL_STATE, 3
	call_if_ge LittlerootTown_MaysHouse_2F_EventScript_1F92CD
	compare VAR_LITTLEROOT_INTRO_STATE, 4
	call_if_eq LittlerootTown_MaysHouse_2F_EventScript_2926FE
	call LittlerootTown_MaysHouse_2F_EventScript_275CE1
	@ setvar VAR_SECRET_BASE_INITIALIZED, 0
	end

LittlerootTown_MaysHouse_2F_EventScript_1F92CD:: @ 81F92CD
	goto_if_set FLAG_MET_RIVAL_LILYCOVE, LittlerootTown_MaysHouse_2F_EventScript_1F92E6
	compare VAR_BIRCH_LAB_STATE, 2
	goto_if_ge LittlerootTown_MaysHouse_2F_EventScript_1F9309
	goto LittlerootTown_MaysHouse_2F_EventScript_1F92E6

LittlerootTown_MaysHouse_2F_EventScript_1F92E6:: @ 81F92E6
	checkplayergender
	compare VAR_RESULT, 1
	goto_if_eq LittlerootTown_MaysHouse_2F_EventScript_1F9309
	compare VAR_0x40D3, 2
	goto_if_ge LittlerootTown_MaysHouse_2F_EventScript_1F9309
	setobjectxyperm 1, 8, 2
	setobjectmovementtype 1, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_BrendansHouse_2F_EventScript_1F9309:: @ 81F9309
LittlerootTown_MaysHouse_2F_EventScript_1F9309:: @ 81F9309
	return

LittlerootTown_MaysHouse_2F_EventScript_1F930A:: @ 81F930A
	checkplayergender
	compare VAR_RESULT, 0
	goto_if_eq LittlerootTown_MaysHouse_2F_EventScript_1F9317
	return

LittlerootTown_MaysHouse_2F_EventScript_1F9317:: @ 81F9317
	setvar VAR_LITTLEROOT_RIVAL_STATE, 2
	return

@ -----------------------------------------------------

LittlerootTown_MaysHouse_2F_MapScript2_1F931D: @ 81F931D
	@ map_script_2 VAR_SECRET_BASE_INITIALIZED, 0, LittlerootTown_MaysHouse_2F_EventScript_1F9327
	.2byte 0

@ LittlerootTown_MaysHouse_2F_EventScript_1F9327:: @ 81F9327
@ 	checkplayergender
@ 	compare VAR_RESULT, 1
@ 	goto_if_eq EventScript_275D0C
@ 	end

@ -----------------------------------------------------

LittlerootTown_MaysHouse_2F_EventScript_1F9334:: @ 81F9334
	lockall
	compare VAR_LITTLEROOT_RIVAL_STATE, 2
	goto_if_eq LittlerootTown_MaysHouse_2F_EventScript_1F934A
	msgbox LittlerootTown_RivalsHouse_2F_Text_1F9962, MSGBOX_DESCRIBE
	releaseall
	end

LittlerootTown_MaysHouse_2F_EventScript_1F934A:: @ 81F934A
	flagasdialog
	delay 10
	addobject 1
	applymovement 1, LittlerootTown_MaysHouse_2F_Movement_1F946F
	waitmovement 0
	playse SE_PIN
	applymovement 1, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 1, Common_Movement_Delay48
	waitmovement 0
	delay 10
	playbgm MUS_GIRL_SUP, 1
	compare VAR_FACING, 2
	call_if_eq LittlerootTown_MaysHouse_2F_EventScript_1F93BA
	compare VAR_FACING, 1
	call_if_eq LittlerootTown_MaysHouse_2F_EventScript_1F93E9
	compare VAR_FACING, 3
	call_if_eq LittlerootTown_MaysHouse_2F_EventScript_1F9418
	compare VAR_FACING, 4
	call_if_eq LittlerootTown_MaysHouse_2F_EventScript_1F9440
	setvar VAR_LITTLEROOT_RIVAL_STATE, 3
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_POKE_BALL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	setvar VAR_0x4050, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LittlerootTown_MaysHouse_2F_EventScript_1F93BA:: @ 81F93BA
	applymovement 1, LittlerootTown_MaysHouse_2F_Movement_1F9473
	waitmovement 0
	applymovement EVENT_OBJ_ID_PLAYER, Common_Movement_WalkInPlaceLeft
	waitmovement 0
	msgbox LittlerootTown_RivalHouse_1F_Text_1F8EC6, MSGBOX_DEFAULT
	closemessage
	applymovement EVENT_OBJ_ID_PLAYER, LittlerootTown_MaysHouse_2F_Movement_1F9483
	applymovement 1, LittlerootTown_MaysHouse_2F_Movement_1F9479
	waitmovement 0
	return

LittlerootTown_MaysHouse_2F_EventScript_1F93E9:: @ 81F93E9
	applymovement 1, LittlerootTown_MaysHouse_2F_Movement_1F948B
	waitmovement 0
	applymovement EVENT_OBJ_ID_PLAYER, Common_Movement_WalkInPlaceLeft
	waitmovement 0
	msgbox LittlerootTown_RivalHouse_1F_Text_1F8EC6, MSGBOX_DEFAULT
	closemessage
	applymovement EVENT_OBJ_ID_PLAYER, LittlerootTown_MaysHouse_2F_Movement_1F9497
	applymovement 1, LittlerootTown_MaysHouse_2F_Movement_1F948F
	waitmovement 0
	return

LittlerootTown_MaysHouse_2F_EventScript_1F9418:: @ 81F9418
	applymovement 1, LittlerootTown_MaysHouse_2F_Movement_1F949D
	waitmovement 0
	applymovement EVENT_OBJ_ID_PLAYER, Common_Movement_WalkInPlaceUp
	waitmovement 0
	msgbox LittlerootTown_RivalHouse_1F_Text_1F8EC6, MSGBOX_DEFAULT
	closemessage
	applymovement 1, LittlerootTown_MaysHouse_2F_Movement_1F94A4
	waitmovement 0
	return

LittlerootTown_MaysHouse_2F_EventScript_1F9440:: @ 81F9440
	applymovement 1, LittlerootTown_MaysHouse_2F_Movement_1F94AD
	waitmovement 0
	applymovement EVENT_OBJ_ID_PLAYER, Common_Movement_WalkInPlaceLeft
	waitmovement 0
	msgbox LittlerootTown_RivalHouse_1F_Text_1F8EC6, MSGBOX_DEFAULT
	closemessage
	applymovement EVENT_OBJ_ID_PLAYER, LittlerootTown_MaysHouse_2F_Movement_1F94BB
	applymovement 1, LittlerootTown_MaysHouse_2F_Movement_1F94B2
	waitmovement 0
	return

LittlerootTown_MaysHouse_2F_Movement_1F946F: @ 81F946F
	walk_down
	walk_down
	walk_in_place_fastest_right
	step_end

LittlerootTown_MaysHouse_2F_Movement_1F9473: @ 81F9473
	walk_right
	walk_right
	walk_down
	walk_down
	walk_right
	step_end

LittlerootTown_MaysHouse_2F_Movement_1F9479: @ 81F9479
	walk_up
	walk_up
	walk_up
	walk_in_place_fastest_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

LittlerootTown_MaysHouse_2F_Movement_1F9483: @ 81F9483
	delay_16
	walk_in_place_fastest_up
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_fastest_right
	step_end

LittlerootTown_MaysHouse_2F_Movement_1F948B: @ 81F948B
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_MaysHouse_2F_Movement_1F948F: @ 81F948F
	walk_up
	walk_in_place_fastest_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

LittlerootTown_MaysHouse_2F_Movement_1F9497: @ 81F9497
	delay_16
	walk_in_place_fastest_up
	delay_16
	delay_16
	walk_in_place_fastest_right
	step_end

LittlerootTown_MaysHouse_2F_Movement_1F949D: @ 81F949D
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_down
	step_end

LittlerootTown_MaysHouse_2F_Movement_1F94A4: @ 81F94A4
	walk_up
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

LittlerootTown_MaysHouse_2F_Movement_1F94A9: @ 81F94A9
	delay_16
	delay_16
	walk_in_place_fastest_right
	step_end

LittlerootTown_MaysHouse_2F_Movement_1F94AD: @ 81F94AD
	walk_right
	walk_right
	walk_down
	walk_in_place_fastest_right
	step_end

LittlerootTown_MaysHouse_2F_Movement_1F94B2: @ 81F94B2
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

LittlerootTown_MaysHouse_2F_Movement_1F94BB: @ 81F94BB
	delay_16
	walk_in_place_fastest_up
	delay_16
	delay_16
	walk_in_place_fastest_right
	step_end

LittlerootTown_BrendansHouse_2F_EventScript_1F94C1:: @ 81F94C1
LittlerootTown_MaysHouse_2F_EventScript_1F94C1:: @ 81F94C1
	lockall
	goto_if_set FLAG_MET_RIVAL_LILYCOVE, LittlerootTown_BrendansHouse_2F_EventScript_1F94F7
	selectpointer_ongender LittlerootTown_MaysHouse_2F_Text_1F978A, LittlerootTown_BrendansHouse_2F_Text_1F9962
	msgbox_selected MSGBOX_DIALOG
	releaseall
	end

LittlerootTown_BrendansHouse_2F_EventScript_1F94F7:: @ 81F94F7
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	goto_if_set FLAG_MET_RIVAL_IN_HOUSE_AFTER_LILYCOVE, LittlerootTown_BrendansHouse_2F_EventScript_1F9541
	selectpointer_ongender LittlerootTown_MaysHouse_2F_Text_1F99C9, LittlerootTown_BrendansHouse_2F_Text_1F9B0D
	msgbox_selected MSGBOX_DIALOG
	setflag FLAG_MET_RIVAL_IN_HOUSE_AFTER_LILYCOVE
	releaseall
	end

LittlerootTown_BrendansHouse_2F_EventScript_1F9541:: @ 81F9541
	selectpointer_ongender LittlerootTown_MaysHouse_2F_Text_1F9A9E, LittlerootTown_BrendansHouse_2F_Text_1F9BE7
	msgbox_selected MSGBOX_DIALOG
	releaseall
	end

EventScript_PlayerPCFemale:: @ 81F9553
	lockall
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq LittlerootTown_MaysHouse_2F_EventScript_1F956C
	compare VAR_RESULT, FEMALE
	goto_if_eq LittlerootTown_MaysHouse_2F_EventScript_1F9576
	end

LittlerootTown_MaysHouse_2F_EventScript_1F956C:: @ 81F956C
	msgbox gUnknown_08272CD5, MSGBOX_DEFAULT
	releaseall
	end

LittlerootTown_MaysHouse_2F_EventScript_1F9576:: @ 81F9576
	msgbox Text_PCLivestreamEvent, MSGBOX_DESCRIBE
	releaseall
	end

LittlerootTown_MaysHouse_2F_EventScript_1F958F:: @ 81F958F
	setvar VAR_0x8004, 2
	playse SE_PC_OFF
	special DoPCTurnOffEffect
	releaseall
	end

LittlerootTown_MaysHouse_2F_Text_1F978A: @ 81F978A
	.string "Pokémon fully restored!\n"
	.string "Items ready, and…$"

LittlerootTown_BrendansHouse_2F_Text_1F9962: @ 81F9962
	.string "Pokémon fully restored…\n"
	.string "Items all packed, and…$"

LittlerootTown_RivalsHouse_2F_Text_1F9962: @ 81F9991
	.string "It's {RIVAL}'s Poké Ball!\p"
	.string "If you try to take it,\n"
	.string "{RIVAL_they} might see.$"

LittlerootTown_MaysHouse_2F_Text_1F99C9: @ 81F99C9
	.string "May: {PLAYER}!\p"
	.string "I was just checking my Pokédex.\p"
	.string "There's still a lot of Pokémon that\n"
	.string "I've seen but haven't caught.\p"
	.string "And there are many others that\n"
	.string "I think will evolve.\p"
	.string "I wonder where I should go catch\n"
	.string "some Pokémon next?$"

LittlerootTown_MaysHouse_2F_Text_1F9A9E: @ 81F9A9E
	.string "May: I wonder where I should go catch\n"
	.string "some Pokémon next?\p"
	.string "Wouldn't it be funny if we ran into each\n"
	.string "other, {PLAYER}?$"

LittlerootTown_BrendansHouse_2F_Text_1F9B0D: @ 81F9B0D
	.string "Brendan: Hey, it's {PLAYER}.\p"
	.string "I was just checking out my Pokédex.\p"
	.string "There are still many Pokémon that\n"
	.string "I need to catch, I know, but this\l"
	.string "is looking pretty good.\p"
	.string "Checking this Pokédex out gives me\n"
	.string "the urge to hit the road again.$"

LittlerootTown_BrendansHouse_2F_Text_1F9BE7: @ 81F9BE7
	.string "Brendan: I'm having a hard time deciding\n"
	.string "where I should catch Pokémon next.\p"
	.string "Hey, {PLAYER}, if I see you while I'm out\n"
	.string "catching Pokémon, I can pitch you a\l"
	.string "battle if you'd like.$"

@ -----------------------------------------------------
@ Trigger: Sleeping in bed

LittlerootTown_MaysHouse_2F_TriggerScript_SleepInBed::
	checkplayergender
	compare VAR_RESULT, FEMALE
	call_if_eq LittlerootTown_PlayersHouse_2F_TriggerScript_SleepInBed
	release
	end

