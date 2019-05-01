#include "global.h"
#include "alloc.h"
#include "battle.h"
#include "battle_gfx_sfx_util.h"
#include "bg.h"
#include "contest.h"
#include "contest_painting.h"
#include "contest_painting_effects.h"
#include "data.h"
#include "decompress.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "main.h"
#include "lilycove_lady.h"
#include "palette.h"
#include "random.h"
#include "scanline_effect.h"
#include "string_util.h"
#include "strings.h"
#include "text.h"
#include "window.h"
#include "constants/rgb.h"

// IWRAM common
u16 (*gUnknown_03006190)[][32];
struct Unk030061A0 gUnknown_030061A0;
struct ContestWinner *gUnknown_030061C0;
u16 *gContestPaintingMonPalette;

// IWRAM bss
IWRAM_DATA u8 gContestPaintingState;
IWRAM_DATA u16 gContestPaintingMosaicVal;
IWRAM_DATA u16 gContestPaintingFadeCounter;
IWRAM_DATA bool8 gUnknown_030011F6;
IWRAM_DATA u8 gContestPaintingWindowId;

static void ShowContestPainting(void);
static void HoldContestPainting(void);
static void InitContestPaintingWindow(void);
static void InitContestPaintingBg(void);
static void InitContestPaintingVars(bool8);
static void sub_8130884(u8, u8);
static void PrintContestPaintingCaption(u8, u8);
static void VBlankCB_ContestPainting(void);
static void sub_8130380(u8 *spritePixels, u16 *palette, u16 (*destColorBuffer)[64][64]);

extern const u8 gUnknown_0827EA0C[];
extern const u8 gContestCoolness[];
extern const u8 gContestBeauty[];
extern const u8 gContestCuteness[];
extern const u8 gContestSmartness[];
extern const u8 gContestToughness[];
extern const u8 gContestRankNormal[];
extern const u8 gContestRankSuper[];
extern const u8 gContestRankHyper[];
extern const u8 gContestRankMaster[];
extern const u8 gContestLink[];
extern const u8 gContestPaintingCool1[];
extern const u8 gContestPaintingCool2[];
extern const u8 gContestPaintingCool3[];
extern const u8 gContestPaintingBeauty1[];
extern const u8 gContestPaintingBeauty2[];
extern const u8 gContestPaintingBeauty3[];
extern const u8 gContestPaintingCute1[];
extern const u8 gContestPaintingCute2[];
extern const u8 gContestPaintingCute3[];
extern const u8 gContestPaintingSmart1[];
extern const u8 gContestPaintingSmart2[];
extern const u8 gContestPaintingSmart3[];
extern const u8 gContestPaintingTough1[];
extern const u8 gContestPaintingTough2[];
extern const u8 gContestPaintingTough3[];

const u16 gPictureFramePalettes[] = INCBIN_U16("graphics/picture_frame/bg.gbapal");
const u8 gPictureFrameTiles_0[] = INCBIN_U8("graphics/picture_frame/frame0.4bpp.rl");
const u8 gPictureFrameTiles_1[] = INCBIN_U8("graphics/picture_frame/frame1.4bpp.rl");
const u8 gPictureFrameTiles_2[] = INCBIN_U8("graphics/picture_frame/frame2.4bpp.rl");
const u8 gPictureFrameTiles_3[] = INCBIN_U8("graphics/picture_frame/frame3.4bpp.rl");
const u8 gPictureFrameTiles_4[] = INCBIN_U8("graphics/picture_frame/frame4.4bpp.rl");
const u8 gPictureFrameTiles_5[] = INCBIN_U8("graphics/picture_frame/frame5.4bpp.rl");
const u8 gPictureFrameTilemap_0[] = INCBIN_U8("graphics/picture_frame/frame0_map.bin.rl");
const u8 gPictureFrameTilemap_1[] = INCBIN_U8("graphics/picture_frame/frame1_map.bin.rl");
const u8 gPictureFrameTilemap_2[] = INCBIN_U8("graphics/picture_frame/frame2_map.bin.rl");
const u8 gPictureFrameTilemap_3[] = INCBIN_U8("graphics/picture_frame/frame3_map.bin.rl");
const u8 gPictureFrameTilemap_4[] = INCBIN_U8("graphics/picture_frame/frame4_map.bin.rl");
const u8 gPictureFrameTilemap_5[] = INCBIN_U8("graphics/picture_frame/frame5_map.bin.rl");

const u8 *const gUnknown_085B07C0[] =
{
    gContestCoolness,
    gContestBeauty,
    gContestCuteness,
    gContestSmartness,
    gContestToughness,
};

const u8 *const gContestRankTextPointers[] =
{
    gContestRankNormal,
    gContestRankSuper,
    gContestRankHyper,
    gContestRankMaster,
    gContestLink,
};

const struct BgTemplate gUnknown_085B07E8[] =
{
    {
        .bg = 1,
        .charBaseIndex = 1,
        .mapBaseIndex = 10,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0,
    },
};

const struct WindowTemplate gUnknown_085B07EC =
{
    .bg = 1,
    .tilemapLeft = 2,
    .tilemapTop = 14,
    .width = 26,
    .height = 4,
    .paletteNum = 15,
    .baseBlock = 1,
};

const u8 *const gContestPaintingDescriptionPointers[] =
{
    gContestPaintingCool1,
    gContestPaintingCool2,
    gContestPaintingCool3,
    gContestPaintingBeauty1,
    gContestPaintingBeauty2,
    gContestPaintingBeauty3,
    gContestPaintingCute1,
    gContestPaintingCute2,
    gContestPaintingCute3,
    gContestPaintingSmart1,
    gContestPaintingSmart2,
    gContestPaintingSmart3,
    gContestPaintingTough1,
    gContestPaintingTough2,
    gContestPaintingTough3,
};

const struct OamData gUnknown_085B0830 =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = TRUE,
    .bpp = ST_OAM_8BPP,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
};

const u16 gUnknown_085B0838[] = {RGB(0, 0, 0), RGB(0, 0, 0)};

void sub_812FDA8(int contestWinner)
{
    // probably fakematching
    u8 *ptr1 = &gUnknown_02039F5D;
    u8 *ptr2 = &gUnknown_02039F5C;
	gUnknown_02039F3C = gSaveBlock1Ptr->contestWinners[contestWinner - 1];
	*ptr1 = contestWinner - 1;
	*ptr2 = 0;
}

void CB2_ContestPainting(void)
{
    ShowContestPainting();
}

static void CB2_HoldContestPainting(void)
{
    HoldContestPainting();
    RunTextPrinters();
    UpdatePaletteFade();
}

static void CB2_QuitContestPainting(void)
{
    SetMainCallback2(gMain.savedCallback);
    FREE_AND_SET_NULL(gContestPaintingMonPalette);
    FREE_AND_SET_NULL(gUnknown_03006190);
    RemoveWindow(gContestPaintingWindowId);
    Free(GetBgTilemapBuffer(1));
    FreeMonSpritesGfx();
}

static void ShowContestPainting(void)
{
    switch (gMain.state)
    {
    case 0:
        ScanlineEffect_Stop();
        SetVBlankCallback(NULL);
        AllocateMonSpritesGfx();
        gUnknown_030061C0 = &gUnknown_02039F3C;
        InitContestPaintingVars(1);
        InitContestPaintingBg();
        gMain.state++;
        break;
    case 1:
        ResetPaletteFade();
        DmaFillLarge32(3, 0, (void *)BG_VRAM, 0x18000, 0x1000);
        ResetSpriteData();
        gMain.state++;
        break;
    case 2:
        SeedRng(gMain.vblankCounter1);
        InitKeys();
        InitContestPaintingWindow();
        gMain.state++;
        break;
    case 3:
        sub_8130884(gUnknown_02039F5D, gUnknown_02039F5C);
        gMain.state++;
        break;
    case 4:
        PrintContestPaintingCaption(gUnknown_02039F5D, gUnknown_02039F5C);
        LoadPalette(gUnknown_085B0838, 0, 1 * 2);
        DmaClear32(3, PLTT, PLTT_SIZE);
        BeginFastPaletteFade(2);
        SetVBlankCallback(VBlankCB_ContestPainting);
        gContestPaintingState = 0;
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_BG0_ON | DISPCNT_BG1_ON | DISPCNT_OBJ_ON);
        SetMainCallback2(CB2_HoldContestPainting);
        break;
    }
}

static void HoldContestPainting(void)
{
    switch (gContestPaintingState)
    {
    case 0:
        if (!gPaletteFade.active)
            gContestPaintingState = 1;
        if (gUnknown_030011F6 && gContestPaintingFadeCounter)
            gContestPaintingFadeCounter--;
        break;
    case 1:
        if ((gMain.newKeys & A_BUTTON) || (gMain.newKeys & B_BUTTON))
        {
            u8 two = 2;  //needed to make the asm match
            gContestPaintingState = two;
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB(0, 0, 0));
        }

        if (gUnknown_030011F6)
            gContestPaintingFadeCounter = 0;
        break;
    case 2:
        if (!gPaletteFade.active)
            SetMainCallback2(CB2_QuitContestPainting);
        if (gUnknown_030011F6 && gContestPaintingFadeCounter < 30)
            gContestPaintingFadeCounter++;
        break;
    }
}

static void InitContestPaintingWindow(void)
{
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, gUnknown_085B07E8, ARRAY_COUNT(gUnknown_085B07E8));
    ChangeBgX(1, 0, 0);
    ChangeBgY(1, 0, 0);
    SetBgTilemapBuffer(1, AllocZeroed(BG_SCREEN_SIZE));
    gContestPaintingWindowId = AddWindow(&gUnknown_085B07EC);
    DeactivateAllTextPrinters();
    FillWindowPixelBuffer(gContestPaintingWindowId, PIXEL_FILL(0));
    PutWindowTilemap(gContestPaintingWindowId);
    CopyWindowToVram(gContestPaintingWindowId, 3);
    ShowBg(1);
}

static void PrintContestPaintingCaption(u8 contestType, u8 arg1)
{
    int x;
    u8 category;

    if (arg1 == TRUE)
        return;

    category = gUnknown_030061C0->contestCategory;
    if (contestType < 8)
    {
        sub_818E868(gStringVar1, category);
        StringAppend(gStringVar1, gText_Space);
        StringAppend(gStringVar1, gContestRankTextPointers[gUnknown_030061C0->contestRank]);
        StringCopy(gStringVar2, gUnknown_030061C0->trainerName);
        sub_81DB5AC(gStringVar2);
        StringCopy(gStringVar3, gUnknown_030061C0->monName);
        StringExpandPlaceholders(gStringVar4, gUnknown_0827EA0C);
    }
    else
    {
        StringCopy(gStringVar1, gUnknown_030061C0->monName);
        StringExpandPlaceholders(gStringVar4, gContestPaintingDescriptionPointers[category]);
    }

    x = GetStringCenterAlignXOffset(1, gStringVar4, 208);
    AddTextPrinterParameterized(gContestPaintingWindowId, 1, gStringVar4, x, 1, 0, 0);
    CopyBgTilemapBufferToVram(1);
}

static void InitContestPaintingBg(void)
{
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    REG_IE |= INTR_FLAG_VBLANK;
    SetGpuReg(REG_OFFSET_BG0CNT, BGCNT_PRIORITY(2) | BGCNT_CHARBASE(0) | BGCNT_SCREENBASE(12) | BGCNT_MOSAIC | BGCNT_16COLOR | BGCNT_TXT256x256);
    SetGpuReg(REG_OFFSET_BG1CNT, BGCNT_PRIORITY(1) | BGCNT_CHARBASE(1) | BGCNT_SCREENBASE(10) | BGCNT_MOSAIC | BGCNT_16COLOR | BGCNT_TXT256x256);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    SetGpuReg(REG_OFFSET_BLDY, 0);
}

static void InitContestPaintingVars(bool8 arg0)
{
    if (arg0 == FALSE)
    {
        gUnknown_030011F6 = FALSE;
        gContestPaintingMosaicVal = 0;
        gContestPaintingFadeCounter = 0;
    }
    else
    {
        gUnknown_030011F6 = TRUE;
        gContestPaintingMosaicVal = 15;
        gContestPaintingFadeCounter = 30;
    }
}

static void UpdateContestPaintingMosaicEffect(void)
{
    if (!gUnknown_030011F6)
    {
        SetGpuReg(REG_OFFSET_MOSAIC, 0);
    }
    else
    {
        SetGpuReg(REG_OFFSET_BG1CNT, BGCNT_PRIORITY(1) | BGCNT_CHARBASE(1) | BGCNT_SCREENBASE(10) | BGCNT_MOSAIC | BGCNT_16COLOR | BGCNT_TXT256x256);
        gContestPaintingMosaicVal = gContestPaintingFadeCounter / 2;
        SetGpuReg(REG_OFFSET_MOSAIC, (gContestPaintingMosaicVal << 12) | (gContestPaintingMosaicVal << 8) | (gContestPaintingMosaicVal << 4) | (gContestPaintingMosaicVal << 0));
    }
}

static void VBlankCB_ContestPainting(void)
{
    UpdateContestPaintingMosaicEffect();
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void sub_81302E8(u16 species, u8 arg1)
{
    const void *pal = GetFrontSpritePalFromSpeciesAndPersonality(species, gUnknown_030061C0->trainerId, gUnknown_030061C0->personality);
    LZDecompressVram(pal, gContestPaintingMonPalette);
    if (!arg1)
    {
        HandleLoadSpecialPokePic_DontHandleDeoxys(
            &gMonFrontPicTable[species],
            gMonSpritesGfxPtr->sprites[1],
            species,
            gUnknown_030061C0->personality);
        sub_8130380(gMonSpritesGfxPtr->sprites[1], gContestPaintingMonPalette, (void *)gUnknown_03006190);
    }
    else
    {
        HandleLoadSpecialPokePic_DontHandleDeoxys(
            &gMonBackPicTable[species],
            gMonSpritesGfxPtr->sprites[0],
            species,
            gUnknown_030061C0->personality);
        sub_8130380(gMonSpritesGfxPtr->sprites[0], gContestPaintingMonPalette, (void *)gUnknown_03006190);
    }
}

#ifdef NONMATCHING
// functionally equivalent.
static void sub_8130380(u8 *spritePixels, u16 *palette, u16 (*destColorBuffer)[64][64])
{
    u16 tileY, tileX, pixelY, pixelX;
    u8 colorIndex;

    for (tileY = 0; tileY < 8; tileY++)
    {
        for (tileX = 0; tileX < 8; tileX++)
        {
            for (pixelY = 0; pixelY < 8; pixelY++)
            {
                for (pixelX = 0; pixelX < 8; pixelX++)
                {
                    int offset = 32 * (8 * tileY + tileX) + (pixelY * 4 + pixelX / 2);
                    colorIndex = spritePixels[offset];
                    if (pixelX & 1)
                        colorIndex >>= 4;
                    else
                        colorIndex &= 0xF;

                    if (colorIndex == 0) // transparent pixel
                        (*destColorBuffer)[8 * tileY + pixelY][tileX * 8 + pixelX] = 0x8000;
                    else
                        (*destColorBuffer)[8 * tileY + pixelY][tileX * 8 + pixelX] = palette[colorIndex];
                }
            }
        }
    }
}
#else
NAKED
static void sub_8130380(u8 *spritePixels, u16 *palette, u16 (*destColorBuffer)[64][64])
{
    asm_unified("\n\
    push {r4-r7,lr}\n\
    mov r7, r10\n\
    mov r6, r9\n\
    mov r5, r8\n\
    push {r5-r7}\n\
    sub sp, 0xC\n\
    mov r10, r0\n\
    mov r9, r1\n\
    str r2, [sp]\n\
    movs r0, 0\n\
_08130394:\n\
    movs r3, 0\n\
    adds r1, r0, 0x1\n\
    str r1, [sp, 0x4]\n\
    lsls r0, 3\n\
    str r0, [sp, 0x8]\n\
_0813039E:\n\
    movs r1, 0\n\
    adds r2, r3, 0x1\n\
    mov r8, r2\n\
    ldr r7, [sp, 0x8]\n\
    adds r0, r7, r3\n\
    lsls r0, 5\n\
    mov r12, r0\n\
    lsls r4, r3, 3\n\
_081303AE:\n\
    movs r3, 0\n\
    lsls r0, r1, 2\n\
    adds r6, r1, 0x1\n\
    mov r2, r12\n\
    adds r5, r2, r0\n\
    ldr r7, [sp, 0x8]\n\
    adds r0, r7, r1\n\
    lsls r0, 7\n\
    ldr r1, [sp]\n\
    adds r2, r0, r1\n\
_081303C2:\n\
    lsrs r0, r3, 1\n\
    adds r0, r5, r0\n\
    add r0, r10\n\
    ldrb r1, [r0]\n\
    movs r0, 0x1\n\
    ands r0, r3\n\
    cmp r0, 0\n\
    beq _081303D6\n\
    lsrs r1, 4\n\
    b _081303DA\n\
_081303D6:\n\
    movs r0, 0xF\n\
    ands r1, r0\n\
_081303DA:\n\
    cmp r1, 0\n\
    bne _081303EC\n\
    adds r0, r4, r3\n\
    lsls r0, 1\n\
    adds r0, r2\n\
    movs r7, 0x80\n\
    lsls r7, 8\n\
    adds r1, r7, 0\n\
    b _081303F8\n\
_081303EC:\n\
    adds r0, r4, r3\n\
    lsls r0, 1\n\
    adds r0, r2\n\
    lsls r1, 1\n\
    add r1, r9\n\
    ldrh r1, [r1]\n\
_081303F8:\n\
    strh r1, [r0]\n\
    adds r0, r3, 0x1\n\
    lsls r0, 16\n\
    lsrs r3, r0, 16\n\
    cmp r3, 0x7\n\
    bls _081303C2\n\
    lsls r0, r6, 16\n\
    lsrs r1, r0, 16\n\
    cmp r1, 0x7\n\
    bls _081303AE\n\
    mov r1, r8\n\
    lsls r0, r1, 16\n\
    lsrs r3, r0, 16\n\
    cmp r3, 0x7\n\
    bls _0813039E\n\
    ldr r2, [sp, 0x4]\n\
    lsls r0, r2, 16\n\
    lsrs r0, 16\n\
    cmp r0, 0x7\n\
    bls _08130394\n\
    add sp, 0xC\n\
    pop {r3-r5}\n\
    mov r8, r3\n\
    mov r9, r4\n\
    mov r10, r5\n\
    pop {r4-r7}\n\
    pop {r0}\n\
    bx r0");
}
#endif

static void sub_8130430(u8 arg0, u8 arg1)
{
    u8 x, y;

    LoadPalette(gPictureFramePalettes, 0, 0x100);
    if (arg1 == 1)
    {
        switch (gUnknown_030061C0->contestCategory / 3)
        {
        case CONTEST_CATEGORY_COOL:
            RLUnCompVram(gPictureFrameTiles_0, (void *)VRAM);
            RLUnCompWram(gPictureFrameTilemap_0, gUnknown_03006190);
            break;
        case CONTEST_CATEGORY_BEAUTY:
            RLUnCompVram(gPictureFrameTiles_1, (void *)VRAM);
            RLUnCompWram(gPictureFrameTilemap_1, gUnknown_03006190);
            break;
        case CONTEST_CATEGORY_CUTE:
            RLUnCompVram(gPictureFrameTiles_2, (void *)VRAM);
            RLUnCompWram(gPictureFrameTilemap_2, gUnknown_03006190);
            break;
        case CONTEST_CATEGORY_SMART:
            RLUnCompVram(gPictureFrameTiles_3, (void *)VRAM);
            RLUnCompWram(gPictureFrameTilemap_3, gUnknown_03006190);
            break;
        case CONTEST_CATEGORY_TOUGH:
            RLUnCompVram(gPictureFrameTiles_4, (void *)VRAM);
            RLUnCompWram(gPictureFrameTilemap_4, gUnknown_03006190);
            break;
        }

#define VRAM_PICTURE_DATA(x, y) (((u16 *)(BG_SCREEN_ADDR(12)))[(y) * 32 + (x)])

        // Set the background
        for (y = 0; y < 20; y++)
        {
            for (x = 0; x < 32; x++)
                VRAM_PICTURE_DATA(x, y) = 0x1015;
        }

        // Copy the image frame
        for (y = 0; y < 10; y++)
        {
            for (x = 0; x < 18; x++)
                VRAM_PICTURE_DATA(x + 6, y + 2) = (*gUnknown_03006190)[y + 2][x + 6];
        }

        // Re-set the entire top row to the first top frame part
        for (x = 0; x < 16; x++)
            VRAM_PICTURE_DATA(x + 7, 2) = (*gUnknown_03006190)[2][7];

#undef VRAM_PICTURE_DATA
    }
    else if (arg0 < 8)
    {
        RLUnCompVram(gPictureFrameTiles_5, (void *)VRAM);
        RLUnCompVram(gPictureFrameTilemap_5, (void *)(BG_SCREEN_ADDR(12)));
    }
    else
    {
        switch (gUnknown_030061C0->contestCategory / 3)
        {
        case CONTEST_CATEGORY_COOL:
            RLUnCompVram(gPictureFrameTiles_0, (void *)VRAM);
            RLUnCompVram(gPictureFrameTilemap_0, (void *)(BG_SCREEN_ADDR(12)));
            break;
        case CONTEST_CATEGORY_BEAUTY:
            RLUnCompVram(gPictureFrameTiles_1, (void *)VRAM);
            RLUnCompVram(gPictureFrameTilemap_1, (void *)(BG_SCREEN_ADDR(12)));
            break;
        case CONTEST_CATEGORY_CUTE:
            RLUnCompVram(gPictureFrameTiles_2, (void *)VRAM);
            RLUnCompVram(gPictureFrameTilemap_2, (void *)(BG_SCREEN_ADDR(12)));
            break;
        case CONTEST_CATEGORY_SMART:
            RLUnCompVram(gPictureFrameTiles_3, (void *)VRAM);
            RLUnCompVram(gPictureFrameTilemap_3, (void *)(BG_SCREEN_ADDR(12)));
            break;
        case CONTEST_CATEGORY_TOUGH:
            RLUnCompVram(gPictureFrameTiles_4, (void *)VRAM);
            RLUnCompVram(gPictureFrameTilemap_4, (void *)(BG_SCREEN_ADDR(12)));
            break;
        }
    }
}

static void sub_8130688(u8 arg0)
{
    //Some hacks just to get the asm to match
#ifndef NONMATCHING
    asm(""::"r"(arg0));
#endif

    gMain.oamBuffer[0] = gUnknown_085B0830;
    gMain.oamBuffer[0].tileNum = 0;

#ifndef NONMATCHING
    if (arg0) arg0 = gMain.oamBuffer[0].tileNum;
#endif

    gMain.oamBuffer[0].x = 88;
    gMain.oamBuffer[0].y = 24;
}

static u8 sub_81306CC(u8 arg0)
{
    u8 contestCategory;

    if (arg0 < 8)
        contestCategory = gUnknown_030061C0->contestCategory;
    else
        contestCategory = gUnknown_030061C0->contestCategory / 3;

    switch (contestCategory)
    {
    case CONTEST_CATEGORY_COOL:
        return CONTESTRESULT_COOL;
    case CONTEST_CATEGORY_BEAUTY:
        return CONTESTRESULT_BEAUTY;
    case CONTEST_CATEGORY_CUTE:
        return CONTESTRESULT_CUTE;
    case CONTEST_CATEGORY_SMART:
        return CONTESTRESULT_SMART;
    case CONTEST_CATEGORY_TOUGH:
        return CONTESTRESULT_TOUGH;
    }

    return contestCategory;
}

static void sub_8130738(void)
{
    gContestPaintingMonPalette = AllocZeroed(0x200);
    gUnknown_03006190 = AllocZeroed(0x2000);
}

static void sub_8130760(u8 contestResult)
{
    gUnknown_030061A0.var_4 = gUnknown_03006190;
    gUnknown_030061A0.var_8 = gContestPaintingMonPalette;
    gUnknown_030061A0.var_18 = 0;
    gUnknown_030061A0.var_1F = gUnknown_030061C0->personality % 256;
    gUnknown_030061A0.var_19 = 0;
    gUnknown_030061A0.var_1A = 0;
    gUnknown_030061A0.var_1B = 64;
    gUnknown_030061A0.var_1C = 64;
    gUnknown_030061A0.var_1D = 64;
    gUnknown_030061A0.var_1E = 64;

    switch (contestResult)
    {
    case CONTESTRESULT_SMART:
    case CONTESTRESULT_TOUGH:
        gUnknown_030061A0.var_14 = 3;
        break;
    case CONTESTRESULT_COOL:
    case CONTESTRESULT_BEAUTY:
    case CONTESTRESULT_CUTE:
    default:
        gUnknown_030061A0.var_14 = 1;
        break;
    }

    gUnknown_030061A0.var_16 = 2;
    gUnknown_030061A0.var_0 = contestResult;
    gUnknown_030061A0.var_10 = 0x6010000;

    sub_8124F2C(&gUnknown_030061A0);
    sub_81261A4(&gUnknown_030061A0);
    sub_8126058(&gUnknown_030061A0);

    LoadPalette(gContestPaintingMonPalette, 0x100, 0x200);
}

static void sub_8130884(u8 arg0, u8 arg1)
{
    sub_8130738();
    sub_81302E8(gUnknown_030061C0->species, 0);
    sub_8130760(sub_81306CC(arg0));
    sub_8130688(arg0);
    sub_8130430(arg0, arg1);
}

