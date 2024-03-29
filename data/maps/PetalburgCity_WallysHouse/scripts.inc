PetalburgCity_WallysHouse_MapScripts:: @ 8204229
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PetalburgCity_WallysHouse_MapScript2_204247
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PetalburgCity_WallysHouse_MapScript2_204234
	.byte 0

PetalburgCity_WallysHouse_MapScript2_204234: @ 8204234
	map_script_2 VAR_PETALBURG_STATE, 4, PetalburgCity_WallysHouse_EventScript_20423E
	.2byte 0

PetalburgCity_WallysHouse_EventScript_20423E:: @ 820423E
	turnobject EVENT_OBJ_ID_PLAYER, 4
	turnobject 1, 3
	end

PetalburgCity_WallysHouse_MapScript2_204247: @ 8204247
	map_script_2 VAR_PETALBURG_STATE, 4, PetalburgCity_WallysHouse_EventScript_204251
	.2byte 0

PetalburgCity_WallysHouse_EventScript_204251:: @ 8204251
	lockall
	msgbox PetalburgCity_WallysHouse_Text_20446E, MSGBOX_DEFAULT
	giveitem_std ITEM_TM53
	setflag FLAG_RECEIVED_TM53
	msgbox PetalburgCity_WallysHouse_Text_20461A, MSGBOX_DEFAULT
	setvar VAR_PETALBURG_STATE, 5
	releaseall
	end

PetalburgCity_WallysHouse_EventScript_204278:: @ 8204278
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, PetalburgCity_WallysHouse_EventScript_2042AC
	goto_if_set FLAG_RECEIVED_TM53, PetalburgCity_WallysHouse_EventScript_2042A2
	goto_if_set FLAG_THANKED_FOR_PLAYING_WITH_WALLY, PetalburgCity_WallysHouse_EventScript_2042B6
	msgbox PetalburgCity_WallysHouse_Text_2042DF, MSGBOX_DEFAULT
	setflag FLAG_THANKED_FOR_PLAYING_WITH_WALLY
	release
	end

PetalburgCity_WallysHouse_EventScript_2042A2:: @ 82042A2
	msgbox PetalburgCity_WallysHouse_Text_204661, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_2042AC:: @ 82042AC
	msgbox PetalburgCity_WallysHouse_Text_204698, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_2042B6:: @ 82042B6
	msgbox PetalburgCity_WallysHouse_Text_20444D, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_2042C0:: @ 82042C0
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM53, PetalburgCity_WallysHouse_EventScript_2042D5
	msgbox PetalburgCity_WallysHouse_Text_204732, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_2042D5:: @ 82042D5
	msgbox PetalburgCity_WallysHouse_Text_2047A7, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_Text_2042DF: @ 82042DF
	.string "You're…\n"
	.string "Ah, you must be {PLAYER}, right?\p"
	.string "Thank you for playing with WALLY a\n"
	.string "little while ago.\p"
	.string "He's been frail and sickly ever\n"
	.string "since he was a baby.\p"
	.string "We've sent him to stay with my relatives\n"
	.string "in Verdanturf Town for a while.\p"
	.string "The air is a lot cleaner there\n"
	.string "than it is here.\p"
	.string "What's that? Where's WALLY?\n"
	.string "He's already left, our WALLY.\p"
	.string "I wonder where he could have\n"
	.string "gotten by now?$"

PetalburgCity_WallysHouse_Text_20444D: @ 820444D
	.string "I wonder how our WALLY is doing?$"

PetalburgCity_WallysHouse_Text_20446E: @ 820446E
	.string "{PLAYER}! Please excuse us for\n"
	.string "dragging you here this way.\p"
	.string "But our WALLY's become very healthy\n"
	.string "since he went to Verdanturf Town.\p"
	.string "We owe it all to you!\p"
	.string "When WALLY left town, you helped\n"
	.string "him catch a Pokémon, right?\p"
	.string "I think that made WALLY really\n"
	.string "happy.\p"
	.string "Actually, not just WALLY.\n"
	.string "It made me, his father, happy too.\p"
	.string "Happy that he's gained such a great\n"
	.string "friend as you.\p"
	.string "This isn't a bribe or anything, but\n"
	.string "I'd really like you to have this.$"

PetalburgCity_WallysHouse_Text_20461A: @ 820461A
	.string "If your Pokémon can SURF, you'll be\n"
	.string "able to go to all sorts of places.$"

PetalburgCity_WallysHouse_Text_204661: @ 8204661
	.string "WALLY's coming home soon.\n"
	.string "I'm looking forward to that.$"

PetalburgCity_WallysHouse_Text_204698: @ 8204698
	.string "Oh? You met WALLY in\n"
	.string "Ever Grande City?\p"
	.string "Oh, {PLAYER}, don't be silly.\p"
	.string "He may have gotten healthy, but he\n"
	.string "can't go somewhere far away like\l"
	.string "that all by himself.$"

PetalburgCity_WallysHouse_Text_204732: @ 8204732
	.string "WALLY was really happy when he told\n"
	.string "us that he caught a Pokémon.\p"
	.string "It's been ages since I've seen him\n"
	.string "smile like that.$"

PetalburgCity_WallysHouse_Text_2047A7: @ 82047A7
	.string "I want you to keep this a secret\n"
	.string "from my husband…\p"
	.string "But our WALLY left Verdanturf Town\n"
	.string "without telling anyone.\p"
	.string "You know, WALLY is frail, but\n"
	.string "he's surprisingly strong-willed.\p"
	.string "I'm sure that he'll come back safe\n"
	.string "and sound one day!$"

