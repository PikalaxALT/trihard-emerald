Route111_WinstrateFamilysHouse_MapScripts:: @ 822A48C
	.byte 0

Route111_WinstrateFamilysHouse_EventScript_22A48D:: @ 822A48D
	lock
	faceplayer
	setvar VAR_0x8008, 2
	msgbox Route111_WinstrateFamilysHouse_Text_22A539, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_22A52C
	end

Route111_WinstrateFamilysHouse_EventScript_22A4A2:: @ 822A4A2
	lock
	faceplayer
	setvar VAR_0x8008, 3
	goto_if_set FLAG_RECEIVED_MACHO_BRACE, Route111_WinstrateFamilysHouse_EventScript_22A4DA
	msgbox Route111_WinstrateFamilysHouse_Text_22A5F4, MSGBOX_DEFAULT
	giveitem_std ITEM_MACHO_BRACE
	compare VAR_RESULT, 0
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_MACHO_BRACE
	goto Route111_WinstrateFamilysHouse_EventScript_22A52C
	end

Route111_WinstrateFamilysHouse_EventScript_22A4DA:: @ 822A4DA
	msgbox Route111_WinstrateFamilysHouse_Text_22A6B4, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_22A52C
	end

Route111_WinstrateFamilysHouse_EventScript_22A4E8:: @ 822A4E8
	lock
	faceplayer
	setvar VAR_0x8008, 1
	msgbox Route111_WinstrateFamilysHouse_Text_22A6F7, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_22A52C
	end

Route111_WinstrateFamilysHouse_EventScript_22A4FD:: @ 822A4FD
	lock
	faceplayer
	setvar VAR_0x8008, 4
	goto_if_set FLAG_TEMP_4, Route111_WinstrateFamilysHouse_EventScript_22A51E
	msgbox Route111_WinstrateFamilysHouse_Text_22A780, MSGBOX_DEFAULT
	setflag FLAG_TEMP_4
	goto Route111_WinstrateFamilysHouse_EventScript_22A52C
	end

Route111_WinstrateFamilysHouse_EventScript_22A51E:: @ 822A51E
	msgbox Route111_WinstrateFamilysHouse_Text_22A89B, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_22A52C
	end

Route111_WinstrateFamilysHouse_EventScript_22A52C:: @ 822A52C
	closemessage
	applymovement VAR_0x8008, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route111_WinstrateFamilysHouse_Text_22A539: @ 822A539
	.string "You're the first TRAINER I've seen who\n"
	.string "deploys Pokémon so masterfully.\p"
	.string "But, I should tell you--my son is\n"
	.string "stronger than you.\p"
	.string "He even took the Pokémon League\n"
	.string "challenge, I'll have you know.$"

Route111_WinstrateFamilysHouse_Text_22A5F4: @ 822A5F4
	.string "We use this MACHO BRACE to more\n"
	.string "effectively strengthen our Pokémon\l"
	.string "in training.\p"
	.string "Since you've beaten all of us here,\n"
	.string "I don't know if you need it, but we\l"
	.string "would like you to have our MACHO BRACE.$"

Route111_WinstrateFamilysHouse_Text_22A6B4: @ 822A6B4
	.string "When it comes to Pokémon battles,\n"
	.string "we tend to be pretty passionate.$"

Route111_WinstrateFamilysHouse_Text_22A6F7: @ 822A6F7
	.string "Mommy is stronger than Daddy.\p"
	.string "I'm stronger than Mommy.\p"
	.string "And Grandma's stronger than me!\p"
	.string "But my big brother is even stronger\n"
	.string "than Grandma.$"

Route111_WinstrateFamilysHouse_Text_22A780: @ 822A780
	.string "There's no question that you're strong.\p"
	.string "But if you were to battle my grandson,\n"
	.string "you'd end up crying in frustration.\p"
	.string "He's much stronger than any TRAINER\n"
	.string "our family knows.\p"
	.string "He must be challenging the Pokémon\n"
	.string "LEAGUE CHAMPION by now.\p"
	.string "Knowing my grandson, he could be the\n"
	.string "CHAMPION already!$"

Route111_WinstrateFamilysHouse_Text_22A89B: @ 822A89B
	.string "My grandson must be challenging the\n"
	.string "Pokémon League CHAMPION by now.\p"
	.string "Knowing my grandson, he could be the\n"
	.string "CHAMPION already!$"

