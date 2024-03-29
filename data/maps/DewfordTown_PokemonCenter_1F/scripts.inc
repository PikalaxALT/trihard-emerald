DewfordTown_PokemonCenter_1F_MapScripts:: @ 81FC523
	map_script MAP_SCRIPT_ON_TRANSITION, DewfordTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, DewfordTown_PokemonCenter_1F_MapScript1_277C30
	.byte 0

DewfordTown_PokemonCenter_1F_OnTransition: @ 81FC52E
	setrespawn HEAL_LOCATION_DEWFORD_TOWN
	call PokemonCenter_1F_SetMrBrineyLocation
	end

@ -----------------------------------------------------

DewfordTown_PokemonCenter_1F_NurseScript:: @ 81FC537
	setvar VAR_0x800B, 1
	goto PokemonCenter_1F_NurseHealScript
	end

@ -----------------------------------------------------

DewfordTown_PokemonCenter_1F_PC::
	lockall
	msgbox DewfordTown_PokemonCenter_1F_PC_Text, MSGBOX_DEFAULT
	releaseall
	end
DewfordTown_PokemonCenter_1F_PC_Text:
	.string "{PLAYER} tries to turn on the PC, but it\n"
	.string "seems to be unplugged.$"


DewfordTown_PokemonCenter_1F_EventScript_1FC545:: @ 81FC545
	msgbox DewfordTown_PokemonCenter_1F_Text_1FC557, MSGBOX_NPC
	end
DewfordTown_PokemonCenter_1F_Text_1FC557: @ 81FC557
	.string "There's a stone cavern at the edge\n"
	.string "of town.\p"
	.string "I've heard you can find rare stones\n"
	.string "there.$"


DewfordTown_PokemonCenter_1F_EventScript_1FC54E:: @ 81FC54E
	msgbox DewfordTown_PokemonCenter_1F_Text_1FC5AE, MSGBOX_NPC
	end
DewfordTown_PokemonCenter_1F_Text_1FC5AE: @ 81FC5AE
	.string "Even if a Pokémon faints and can't\n"
	.string "battle, it can still use a move learned\l"
	.string "from a Hidden Machine (HM).$"

