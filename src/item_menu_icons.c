#include "global.h"
#include "berry.h"
#include "decompress.h"
#include "graphics.h"
#include "item.h"
#include "item_menu.h"
#include "item_icon.h"
#include "item_menu_icons.h"
#include "menu_helpers.h"
#include "sprite.h"
#include "window.h"
#include "constants/items.h"

struct CompressedTilesPal
{
    const u32 *tiles;
    const u32 *pal;
};

// this file's functions
static void SpriteCB_BagVisualSwitchingPockets(struct Sprite *sprite);
static void SpriteCB_ShakeBagVisual(struct Sprite *sprite);
static void SpriteCB_SwitchPocketRotatingBallInit(struct Sprite *sprite);
static void SpriteCB_SwitchPocketRotatingBallContinue(struct Sprite *sprite);

// static const rom data
static const u16 gUnknown_0857F564[] = INCBIN_U16("graphics/interface/bag_spinner.gbapal");
static const u8 gUnknown_0857F584[] = INCBIN_U8("graphics/interface/bag_spinner.4bpp");
static const u8 gUnknown_0857F604[] = INCBIN_U8("graphics/unused/cherry.4bpp");
static const u16 gUnknown_0857FA84[] = INCBIN_U16("graphics/unused/cherry.gbapal");

static const struct OamData sOamData_857FAA4 =
{
    .y = 0,
    .affineMode = 1,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0
};

static const union AnimCmd sSpriteAnim_857FAAC[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_857FAB4[] =
{
    ANIMCMD_FRAME(64, 4),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_857FABC[] =
{
    ANIMCMD_FRAME(128, 4),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_857FAC4[] =
{
    ANIMCMD_FRAME(192, 4),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_857FACC[] =
{
    ANIMCMD_FRAME(256, 4),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_857FAD4[] =
{
    ANIMCMD_FRAME(320, 4),
    ANIMCMD_END
};

static const union AnimCmd *const sSpriteAnimTable_857FADC[] =
{
    sSpriteAnim_857FAAC,
    sSpriteAnim_857FAB4,
    sSpriteAnim_857FAC4,
    sSpriteAnim_857FACC,
    sSpriteAnim_857FAD4,
    sSpriteAnim_857FABC
};

static const union AffineAnimCmd sSpriteAffineAnim_857FAF4[] =
{
    AFFINEANIMCMD_FRAME(256, 256, 0, 0),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd sSpriteAffineAnim_857FB04[] =
{
    AFFINEANIMCMD_FRAME(0, 0, 254, 2),
    AFFINEANIMCMD_FRAME(0, 0, 2, 4),
    AFFINEANIMCMD_FRAME(0, 0, 254, 4),
    AFFINEANIMCMD_FRAME(0, 0, 2, 2),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd *const sSpriteAffineAnimTable_857FB2C[] =
{
    sSpriteAffineAnim_857FAF4,
    sSpriteAffineAnim_857FB04
};

const struct CompressedSpriteSheet gUnknown_0857FB34 =
{
    gBagMaleTiles, 0x3000, 100
};

const struct CompressedSpriteSheet gUnknown_0857FB3C =
{
    gBagFemaleTiles, 0x3000, 100
};

const struct CompressedSpritePalette gUnknown_0857FB44 =
{
    gBagPalette, 100
};

static const struct SpriteTemplate gUnknown_0857FB4C =
{
    .tileTag = 100,
    .paletteTag = 100,
    .oam = &sOamData_857FAA4,
    .anims = sSpriteAnimTable_857FADC,
    .images = NULL,
    .affineAnims = sSpriteAffineAnimTable_857FB2C,
    .callback = SpriteCallbackDummy,
};

static const struct OamData sOamData_857FB64 =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = SPRITE_SHAPE(16x16),
    .x = 0,
    .matrixNum = 4,
    .size = SPRITE_SIZE(16x16),
    .tileNum = 0,
    .priority = 2,
    .paletteNum = 0,
    .affineParam = 0
};

static const union AnimCmd sSpriteAnim_857FB6C[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END
};

static const union AnimCmd *const sSpriteAnimTable_857FB74[] =
{
    sSpriteAnim_857FB6C
};

static const union AffineAnimCmd sSpriteAffineAnim_857FB78[] =
{
    AFFINEANIMCMD_FRAME(0, 0, 8, 16),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd sSpriteAffineAnim_857FB88[] =
{
    AFFINEANIMCMD_FRAME(0, 0, 248, 16),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd *const sSpriteAffineAnimTable_857FB98[] =
{
    sSpriteAffineAnim_857FB78,
};

static const union AffineAnimCmd *const sSpriteAffineAnimTable_857FB9C[] =
{
    sSpriteAffineAnim_857FB88,
};

static const struct SpriteSheet gUnknown_0857FBA0 =
{
    gUnknown_0857F584, 0x80, 101
};

static const struct SpritePalette gUnknown_0857FBA8 =
{
    gUnknown_0857F564, 101
};

static const struct SpriteTemplate gSpriteTemplate_RotatingBall =
{
    .tileTag = 101,
    .paletteTag = 101,
    .oam = &sOamData_857FB64,
    .anims = sSpriteAnimTable_857FB74,
    .images = NULL,
    .affineAnims = sSpriteAffineAnimTable_857FB98,
    .callback = SpriteCB_SwitchPocketRotatingBallInit,
};

static const struct OamData sOamData_857FBC8 =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 7,
    .affineParam = 0
};

static const struct OamData sOamData_857FBD0 =
{
    .y = 0,
    .affineMode = 3,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 7,
    .affineParam = 0
};

static const union AnimCmd sSpriteAnim_857FBD8[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END
};

static const union AnimCmd *const sSpriteAnimTable_857FBE0[] =
{
    sSpriteAnim_857FBD8
};

static const struct SpriteFrameImage sSpriteImageTable_857FBE4[] =
{
    {&gDecompressionBuffer[0], 0x800},
};

static const struct SpriteTemplate gUnknown_0857FBEC =
{
    .tileTag = 65535,
    .paletteTag = 30020,
    .oam = &sOamData_857FBC8,
    .anims = sSpriteAnimTable_857FBE0,
    .images = sSpriteImageTable_857FBE4,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const union AffineAnimCmd sSpriteAffineAnim_857FC04[] =
{
    AFFINEANIMCMD_FRAME(-1, -1, 253, 96),
    AFFINEANIMCMD_FRAME(0, 0, 0, 16),
    AFFINEANIMCMD_FRAME(-2, -2, 255, 64),
    AFFINEANIMCMD_FRAME(-8, 0, 0, 16),
    AFFINEANIMCMD_FRAME(0, -8, 0, 16),
    AFFINEANIMCMD_FRAME(256, 256, 0, 0),
    AFFINEANIMCMD_JUMP(0)
};

static const union AffineAnimCmd sSpriteAffineAnim_857FC3C[] =
{
    AFFINEANIMCMD_FRAME(-1, -1, 3, 96),
    AFFINEANIMCMD_FRAME(0, 0, 0, 16),
    AFFINEANIMCMD_FRAME(-2, -2, 1, 64),
    AFFINEANIMCMD_FRAME(-8, 0, 0, 16),
    AFFINEANIMCMD_FRAME(0, -8, 0, 16),
    AFFINEANIMCMD_FRAME(256, 256, 0, 0),
    AFFINEANIMCMD_JUMP(0)
};

static const union AffineAnimCmd *const sSpriteAffineAnimTable_857FC74[] =
{
    sSpriteAffineAnim_857FC04,
    sSpriteAffineAnim_857FC3C
};

static const struct SpriteTemplate gUnknown_0857FC7C =
{
    .tileTag = 0xFFFF,
    .paletteTag = 0x7544,
    .oam = &sOamData_857FBD0,
    .anims = sSpriteAnimTable_857FBE0,
    .images = sSpriteImageTable_857FBE4,
    .affineAnims = sSpriteAffineAnimTable_857FC74,
    .callback = SpriteCallbackDummy,
};

static const struct CompressedTilesPal gBerryPicTable[] =
{
    {gBerryPic_Cheri,  gBerryPalette_Cheri},
    {gBerryPic_Chesto, gBerryPalette_Chesto},
    {gBerryPic_Pecha,  gBerryPalette_Pecha},
    {gBerryPic_Rawst,  gBerryPalette_Rawst},
    {gBerryPic_Aspear, gBerryPalette_Aspear},
    {gBerryPic_Leppa,  gBerryPalette_Leppa},
    {gBerryPic_Oran,   gBerryPalette_Oran},
    {gBerryPic_Persim, gBerryPalette_Persim},
    {gBerryPic_Lum,    gBerryPalette_Lum},
    {gBerryPic_Sitrus, gBerryPalette_Sitrus},
    {gBerryPic_Figy,   gBerryPalette_Figy},
    {gBerryPic_Wiki,   gBerryPalette_Wiki},
    {gBerryPic_Mago,   gBerryPalette_Mago},
    {gBerryPic_Aguav,  gBerryPalette_Aguav},
    {gBerryPic_Iapapa, gBerryPalette_Iapapa},
    {gBerryPic_Razz,   gBerryPalette_Razz},
    {gBerryPic_Bluk,   gBerryPalette_Bluk},
    {gBerryPic_Nanab,  gBerryPalette_Nanab},
    {gBerryPic_Wepear, gBerryPalette_Wepear},
    {gBerryPic_Pinap,  gBerryPalette_Pinap},
    {gBerryPic_Pomeg,  gBerryPalette_Pomeg},
    {gBerryPic_Kelpsy, gBerryPalette_Kelpsy},
    {gBerryPic_Qualot, gBerryPalette_Qualot},
    {gBerryPic_Hondew, gBerryPalette_Hondew},
    {gBerryPic_Grepa,  gBerryPalette_Grepa},
    {gBerryPic_Tamato, gBerryPalette_Tamato},
    {gBerryPic_Cornn,  gBerryPalette_Cornn},
    {gBerryPic_Magost, gBerryPalette_Magost},
    {gBerryPic_Rabuta, gBerryPalette_Rabuta},
    {gBerryPic_Nomel,  gBerryPalette_Nomel},
    {gBerryPic_Spelon, gBerryPalette_Spelon},
    {gBerryPic_Pamtre, gBerryPalette_Pamtre},
    {gBerryPic_Watmel, gBerryPalette_Watmel},
    {gBerryPic_Durin,  gBerryPalette_Durin},
    {gBerryPic_Belue,  gBerryPalette_Belue},
    {gBerryPic_Liechi, gBerryPalette_Liechi},
    {gBerryPic_Ganlon, gBerryPalette_Ganlon},
    {gBerryPic_Salac,  gBerryPalette_Salac},
    {gBerryPic_Petaya, gBerryPalette_Petaya},
    {gBerryPic_Apicot, gBerryPalette_Apicot},
    {gBerryPic_Lansat, gBerryPalette_Lansat},
    {gBerryPic_Starf,  gBerryPalette_Starf},
    {gBerryPic_Enigma, gBerryPalette_Enigma},
};

const struct CompressedSpriteSheet gUnknown_0857FDEC =
{
    gBerryCheckCircle_Gfx, 0x800, 10000
};

const struct CompressedSpritePalette gUnknown_0857FDF4 =
{
    gUnknown_08D9BEF0, 10000
};

static const struct OamData sOamData_857FDFC =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0
};

static const union AnimCmd sSpriteAnim_857FE04[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END
};

static const union AnimCmd *const sSpriteAnimTable_857FE0C[] =
{
    sSpriteAnim_857FE04
};

static const struct SpriteTemplate gUnknown_0857FE10 =
{
    .tileTag = 10000,
    .paletteTag = 10000,
    .oam = &sOamData_857FDFC,
    .anims = sSpriteAnimTable_857FE0C,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

// code
void RemoveBagSprite(u8 id)
{
    u8 *spriteId = &gUnknown_0203CE54->spriteId[id];
    if (*spriteId != 0xFF)
    {
        FreeSpriteTilesByTag(id + 100);
        FreeSpritePaletteByTag(id + 100);
        FreeSpriteOamMatrix(&gSprites[*spriteId]);
        DestroySprite(&gSprites[*spriteId]);
        *spriteId = 0xFF;
    }
}

void AddBagVisualSprite(u8 bagPocketId)
{
    u8 *spriteId = &gUnknown_0203CE54->spriteId[0];
    *spriteId = CreateSprite(&gUnknown_0857FB4C, 68, 66, 0);
    SetBagVisualPocketId(bagPocketId, FALSE);
}

void SetBagVisualPocketId(u8 bagPocketId, bool8 isSwitchingPockets)
{
    struct Sprite *sprite = &gSprites[gUnknown_0203CE54->spriteId[0]];
    if (isSwitchingPockets)
    {
        sprite->pos2.y = -5;
        sprite->callback = SpriteCB_BagVisualSwitchingPockets;
        sprite->data[0] = bagPocketId + 1;
        StartSpriteAnim(sprite, 0);
    }
    else
    {
        StartSpriteAnim(sprite, bagPocketId + 1);
    }
}

static void SpriteCB_BagVisualSwitchingPockets(struct Sprite *sprite)
{
    if (sprite->pos2.y != 0)
    {
        sprite->pos2.y++;
    }
    else
    {
        StartSpriteAnim(sprite, sprite->data[0]);
        sprite->callback = SpriteCallbackDummy;
    }
}

void ShakeBagVisual(void)
{
    struct Sprite *sprite = &gSprites[gUnknown_0203CE54->spriteId[0]];
    if (sprite->affineAnimEnded)
    {
        StartSpriteAffineAnim(sprite, 1);
        sprite->callback = SpriteCB_ShakeBagVisual;
    }
}

static void SpriteCB_ShakeBagVisual(struct Sprite *sprite)
{
    if (sprite->affineAnimEnded)
    {
        StartSpriteAffineAnim(sprite, 0);
        sprite->callback = SpriteCallbackDummy;
    }
}

void AddSwitchPocketRotatingBallSprite(s16 rotationDirection)
{
    u8 *spriteId = &gUnknown_0203CE54->spriteId[1];
    LoadSpriteSheet(&gUnknown_0857FBA0);
    LoadSpritePalette(&gUnknown_0857FBA8);
    *spriteId = CreateSprite(&gSpriteTemplate_RotatingBall, 16, 16, 0);
    gSprites[*spriteId].data[0] = rotationDirection;
}

static void update_switch_pocket_rotating_ball_coords(struct Sprite *sprite)
{
    sprite->centerToCornerVecX = sprite->data[1] - ((sprite->data[3] + 1) & 1);
    sprite->centerToCornerVecY = sprite->data[1] - ((sprite->data[3] + 1) & 1);
}

static void SpriteCB_SwitchPocketRotatingBallInit(struct Sprite *sprite)
{
    sprite->oam.affineMode = 1;
    if (sprite->data[0] == -1)
        sprite->affineAnims = sSpriteAffineAnimTable_857FB98;
    else
        sprite->affineAnims = sSpriteAffineAnimTable_857FB9C;

    InitSpriteAffineAnim(sprite);
    sprite->data[1] = sprite->centerToCornerVecX;
    sprite->data[1] = sprite->centerToCornerVecY;
    update_switch_pocket_rotating_ball_coords(sprite);
    sprite->callback = SpriteCB_SwitchPocketRotatingBallContinue;
}

static void SpriteCB_SwitchPocketRotatingBallContinue(struct Sprite *sprite)
{
    sprite->data[3]++;
    update_switch_pocket_rotating_ball_coords(sprite);
    if (sprite->data[3] == 16)
        RemoveBagSprite(1);
}

void AddBagItemIconSprite(u16 itemId, u8 id)
{
    u8 *spriteId = &gUnknown_0203CE54->spriteId[id + 2];
    if (*spriteId == 0xFF)
    {
        u8 iconSpriteId;

        FreeSpriteTilesByTag(id + 102);
        FreeSpritePaletteByTag(id + 102);
        iconSpriteId = AddItemIconSprite(id + 102, id + 102, itemId);
        if (iconSpriteId != MAX_SPRITES)
        {
            *spriteId = iconSpriteId;
            gSprites[iconSpriteId].pos2.x = 24;
            gSprites[iconSpriteId].pos2.y = 88;
        }
    }
}

void RemoveBagItemIconSprite(u8 id)
{
    RemoveBagSprite(id + 2);
}

void sub_80D4FAC(void)
{
    sub_8122344(&gUnknown_0203CE54->spriteId[4], 8);
}

void sub_80D4FC8(u8 arg0)
{
    sub_81223FC(&gUnknown_0203CE54->spriteId[4], 8, arg0);
}

void sub_80D4FEC(u8 arg0)
{
    sub_8122448(&gUnknown_0203CE54->spriteId[4], 136, 120, (arg0 + 1) * 16);
}

static void sub_80D5018(void *mem0, void *mem1)
{
    u8 i, j;

    memset(mem1, 0, 0x800);
    mem1 += 0x100;
    for (i = 0; i < 6; i++)
    {
        mem1 += 0x20;
        for (j = 0; j < 6; j++)
        {
            memcpy(mem1, mem0, 0x20);
            mem1 += 0x20;
            mem0 += 0x20;
        }
        if (i != 5)
            mem1 += 0x20;
    }
}

static void sub_80D5070(u8 berryId)
{
    struct CompressedSpritePalette pal;

    if (berryId == ITEM_TO_BERRY(ITEM_ENIGMA_BERRY) - 1 && IsEnigmaBerryValid())
    {
        // unknown empty if statement
    }

    pal.data = gBerryPicTable[berryId].pal;
    pal.tag = 0x7544;
    LoadCompressedSpritePalette(&pal);
    LZDecompressWram(gBerryPicTable[berryId].tiles, &gDecompressionBuffer[0x1000]);
    sub_80D5018(&gDecompressionBuffer[0x1000], &gDecompressionBuffer[0]);
}

u8 CreateBerryTagSprite(u8 id, s16 x, s16 y)
{
    sub_80D5070(id);
    return CreateSprite(&gUnknown_0857FBEC, x, y, 0);
}

void FreeBerryTagSpritePalette(void)
{
    FreeSpritePaletteByTag(0x7544);
}

u8 sub_80D511C(u8 berryId, u8 x, u8 y, bool8 startAffine)
{
    u8 spriteId;

    FreeSpritePaletteByTag(0x7544);
    sub_80D5070(berryId);
    spriteId = CreateSprite(&gUnknown_0857FC7C, x, y, 0);
    if (startAffine == TRUE)
        StartSpriteAffineAnim(&gSprites[spriteId], 1);

    return spriteId;
}

u8 CreateBerryFlavorCircleSprite(s16 x)
{
    return CreateSprite(&gUnknown_0857FE10, x, 116, 0);
}
