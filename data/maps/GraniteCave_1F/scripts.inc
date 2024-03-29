GraniteCave_1F_MapScripts:: @ 822DA5D
	.byte 0

GraniteCave_1F_EventScript_22DA5E:: @ 822DA5E
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM55, GraniteCave_1F_EventScript_22DA8A
	msgbox GraniteCave_1F_Text_22DA94, MSGBOX_DEFAULT
	giveitem_std ITEM_TM55
	setflag FLAG_RECEIVED_TM55
	msgbox GraniteCave_1F_Text_22DBB7, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_EventScript_22DA8A:: @ 822DA8A
	msgbox GraniteCave_1F_Text_22DBB7, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_Text_22DA94: @ 822DA94
	.string "Hey, you.\n"
	.string "It gets awfully dark ahead.\l"
	.string "It'll be tough trying to explore.\p"
	.string "That guy who came by earlier…\n"
	.string "Steven, I think it was.\p"
	.string "He knew how to use Flash, so he ought\n"
	.string "to be all right, but…\p"
	.string "Well, for us hikers, helping out those\n"
	.string "that we meet is our motto.\p"
	.string "Here you go, I'll pass this on to you.$"

GraniteCave_1F_Text_22DBB7: @ 822DBB7
	.string "Teach that hidden move Flash to\n"
	.string "a Pokémon and use it.\p"
	.string "It lights up even the inky darkness\n"
	.string "of caves.\p"
	.string "But, to use it, you need the Gym Badge\n"
	.string "from Dewford's Pokémon Gym.$"

