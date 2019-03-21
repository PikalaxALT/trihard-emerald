#ifndef GUARD_POKEMON_ICON_H
#define GUARD_POKEMON_ICON_H

extern const u8 gMonIconPaletteIndices[];

const u8 *GetMonIconTiles(u16 species, bool32);
void sub_80D304C(u16 offset);
u8 GetValidMonIconPalIndex(u16 species);
const u8 *GetMonIconPtr(u16 speciesId, u32 personality, u32 frameNo);
const u16 *GetValidMonIconPalettePtr(u16 speciesId);
u16 GetIconSpecies(u16 species, u32 personality);
u16 GetUnownLetterByPersonality(u32 personality);
u16 sub_80D2E84(u16 speciesId);
void LoadMonIconPalettes(void);
void LoadMonIconPalette(u16 species);
void FreeMonIconPalettes(void);
u8 sub_80D2D78(u16 species, void (*callback)(struct Sprite *), s16 x, s16 y, u8 subpriority, bool32 extra);
void FreeMonIconPalette(u16 species);
void sub_80D2EF8(struct Sprite *sprite);
u8 CreateMonIcon(u16 species, void (*callback)(struct Sprite *), s16 x, s16 y, u8 subpriority, u32 personality, bool32 extra);
u8 UpdateMonIconFrame(struct Sprite *sprite);
void LoadMonIconPalette(u16 species);
void sub_80D328C(struct Sprite *sprite);
void sub_80D3014(struct Sprite *sprite);
void SetPokemonIconAnimationNum(struct Sprite *sprite, u8 animNum);
u8 sub_80D30A0(u16 species);

#endif // GUARD_POKEMON_ICON_H
