Route101_MapScripts:: @ 81EBCBA
	map_script MAP_SCRIPT_ON_TRANSITION, Route101_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route101_MapScript2_1EBCCB
	.byte 0

Route101_OnTransition: @ 81EBCC5
	call Route101_EventScript_2720AD
	end

Route101_MapScript2_1EBCCB: @ 81EBCCB
	map_script_2 VAR_ROUTE101_STATE, 0, Route101_EventScript_1EBCD5
	.2byte 0

Route101_EventScript_1EBCD5:: @ 81EBCD5
	setflag FLAG_HIDE_MAP_NAME_POPUP
	setvar VAR_ROUTE101_STATE, 1
	end

@ -----------------------------------------------------

Route101_EventScript_1EBCDE:: @ 81EBCDE
	lockall
	playbgm MUS_EVENT0, 1
	msgbox Route101_Text_1EBE8F, MSGBOX_DIALOG
	closemessage
	setobjectxy 2, 0, 15
	setobjectxy 4, 0, 16
	applymovement EVENT_OBJ_ID_PLAYER, Route101_Movement_StarterChoose_PlayerRunUp
	applymovement 2, Route101_Movement_StarterChoose_Birch1
	applymovement 4, Route101_Movement_StarterChoose_Ziggy1
	waitmovement 0
	applymovement 4, Route101_Movement_StarterChoose_Ziggy2
	applymovement 2, Route101_Movement_StarterChoose_Birch2
	waitmovement 0
	applymovement 2, Common_Movement_WalkInPlaceRight
	waitmovement 0
	applymovement 4, Route101_Movement_StarterChoose_Ziggy3
	applymovement 2, Route101_Movement_StarterChoose_Birch3
	waitmovement 0
	msgbox Route101_Text_1EBE9A, MSGBOX_DIALOG
	closemessage
	setvar VAR_ROUTE101_STATE, 2
	releaseall
	end
Route101_Text_1EBE8F: @ 81EBE8F
	.string "H-help me!$"
Route101_Text_1EBE9A: @ 81EBE9A
	.string "Hello! You over there!\n"
	.string "Please! Help!\p"
	.string "In my bag! There's a Poké Ball!\n"
	.string "Grab it! Quick please!!$"
Route101_Movement_StarterChoose_PlayerRunUp: @ 81EBDC2
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_in_place_fastest_left
	step_end
Route101_Movement_StarterChoose_Birch1: @ 81EBDE7
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	step_end
Route101_Movement_StarterChoose_Ziggy1: @ 81EBDB5
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	step_end
Route101_Movement_StarterChoose_Ziggy2: @ 81EBD96
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	step_end
Route101_Movement_StarterChoose_Birch2: @ 81EBDC8
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end
Route101_Movement_StarterChoose_Ziggy3: @ 81EBDBD
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_fast_left
	step_end
Route101_Movement_StarterChoose_Birch3: @ 81EBDEF
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_in_place_fast_right
	step_end



Route101_EventScript_1EBD4E:: @ 81EBD4E
	lockall
	msgbox Route101_Text_1EBEDF, MSGBOX_DIALOG
	closemessage
	applymovement EVENT_OBJ_ID_PLAYER, Common_Movement_WalkUp1
	waitmovement 0
	releaseall
	end
Route101_EventScript_1EBD64:: @ 81EBD64
	lockall
	msgbox Route101_Text_1EBEDF, MSGBOX_DIALOG
	closemessage
	applymovement EVENT_OBJ_ID_PLAYER, Common_Movement_WalkRight1
	waitmovement 0
	releaseall
	end
Route101_EventScript_1EBD7A:: @ 81EBD7A
	lockall
	msgbox Route101_Text_1EBEDF, MSGBOX_DIALOG
	closemessage
	applymovement EVENT_OBJ_ID_PLAYER, Common_Movement_WalkDown1
	waitmovement 0
	releaseall
	end
Route101_Text_1EBEDF: @ 81EBEDF
	.string "Oi! Wh-Where are you going?!\n"
	.string "Don't leave me like this!$"


@ -----------------------------------------------------

Route101_EventScript_1EBDFB:: @ 81EBDFB
	msgbox Route101_Text_1EBFDD, MSGBOX_NPC
	end
Route101_Text_1EBFDD: @ 81EBFDD
	.string "If Pokémon get tired, take them to\n"
	.string "a Pokémon Center.\p"
	.string "There's a Pokémon Center in Oldale\n"
	.string "Town just north of here.$"


Route101_EventScript_1EBE04:: @ 81EBE04
	msgbox Route101_Text_1EC04A, MSGBOX_NPC
	end
Route101_Text_1EC04A: @ 81EC04A
	.string "Wild Pokémon will jump out at you in\n"
	.string "tall grass.\p"
	.string "If you want to catch Pokémon, you have\n"
	.string "to go into the tall grass and search.$"


Route101_EventScript_1EBE0D:: @ 81EBE0D
	msgbox Route101_Text_1EC0C8, MSGBOX_SIGN
	end
Route101_Text_1EC0C8: @ 81EC0C8
	.string "Route 101\n"
	.string "{UP_ARROW} Oldale Town$"

Route101_EventScript_1EBE16:: @ 81EBE16
	lock
	faceplayer
	flagasdialog
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_RESCUED_BIRCH
	fadescreen 1
	removeobject 4
	setobjectxy EVENT_OBJ_ID_PLAYER, 6, 13
	applymovement EVENT_OBJ_ID_PLAYER, Common_Movement_WalkInPlaceLeft
	waitmovement 0
	special ChooseStarter
	waitstate
	applymovement 2, Common_Movement_WalkRight1
	waitmovement 0
	msgbox Route101_Text_1EBF12, MSGBOX_DEFAULT
	special HealPlayerParty
	setflag FLAG_HIDE_ROUTE_101_BIRCH_ZIGZAGOON_BATTLE
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	setflag FLAG_HIDE_ROUTE_101_BIRCH_STARTERS_BAG
	setvar VAR_BIRCH_LAB_STATE, 2
	setvar VAR_ROUTE101_STATE, 3
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	call_on_gender Route101_EventScript_1EBE85, Route101_EventScript_1EBE89
	warp MAP_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB, 255, 6, 5
	waitstate
	release
	end
Route101_Text_1EBF12: @ 81EBF12
	.string "Prof. Birch: Whew…\p"
	.string "I was in the tall grass studying wild\n"
	.string "Pokémon when I was jumped.\p"
	.string "You saved me.\n"
	.string "Thanks a lot!\p"
	.string "This is not the place to chat.\n"
	.string "Come back to my Lab with me, okay?$"
Route101_EventScript_1EBE85:: @ 81EBE85
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	return
Route101_EventScript_1EBE89:: @ 81EBE89
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	return

