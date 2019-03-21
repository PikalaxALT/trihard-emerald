#include "global.h"
#include "gpu_regs.h"
#include "multiboot.h"
#include "alloc.h"
#include "bg.h"
#include "graphics.h"
#include "main.h"
#include "sprite.h"
#include "task.h"
#include "scanline_effect.h"
#include "window.h"
#include "text.h"
#include "menu.h"
#include "m4a.h"

// Static type declarations

typedef struct {
    u8 state;
    u8 unk1;
    u16 unk2;
    struct MultiBootParam mb;
} berryfix_t;

// Static RAM declarations

static berryfix_t *berry_fix_mb_manager;

// Static ROM declarations

static void berry_fix_main(void);
static void berry_fix_gpu_set(void);
static int berry_fix_text_update(int);
static void berry_fix_text_print(int);
static void berry_fix_bg_hide(void);

// .rodata

static const u8 sUnknown_08617E78[] = _("Berry Program Update");
static const u8 sUnknown_08617E8D[] = _("Ruby/Sapphire");
static const u8 sUnknown_08617E9B[] = _("Emerald");

static const u8 Unknown_08617EA3[] = _("The Berry Program on your POKéMON\nRuby/Sapphire Game Pak will be updated.\n{COLOR RED}{SHADOW LIGHT_RED}Press the A Button.");
static const u8 Unknown_08617F07[] = _("Please ensure the connection of your\nGame Boy Advance system matches this.\n{COLOR RED}{SHADOW LIGHT_RED}YES: Press the A Button.\nNO: Turn off the power and try again.");
static const u8 Unknown_08617F97[] = _("Please turn on the power of POKéMON\nRuby/Sapphire while holding START and\nSELECT simultaneously. Then, ensure\nthe picture above appears.");
static const u8 Unknown_08618020[] = _("Transmitting. Please wait.\n{COLOR RED}{SHADOW LIGHT_RED}Please do not turn off the power or\nunplug the Game Boy Advance Game\nLink Cable.");
static const u8 Unknown_08618092[] = _("Please follow the instructions on your\nPOKéMON Ruby/Sapphire screen.");
static const u8 Unknown_086180D7[] = _("Transmission failure.\n{COLOR RED}{SHADOW LIGHT_RED}Please try again.");

static const struct BgTemplate gUnknown_08618108[] = {
    {
        0, 0, 30, 0, 0, 0
    }, {
        1, 1, 31, 0, 0, 1
    }
};

static const struct WindowTemplate gUnknown_08618110[] = {
    {0, 2,  4, 26, 2, 15, 0x001},
    {0, 1, 11, 28, 8, 15, 0x035},
    {0, 0,  8, 30, 2, 15, 0x115},
    {0, 8,  0, 14, 2, 15, 0x151},
    {-1}
};

static const u16 sUnknown_08618138[] = {
    0x7fff, 0x7fff, 0x318c, 0x675a,
    0x043c, 0x3aff, 0x0664, 0x4bd2,
    0x6546, 0x7b14, 0x7fff, 0x318c,
    0x675a, 0, 0, 0
};

static const u8 sUnknown_08618158[] = {10, 11, 12};
static const u8 sUnknown_0861815B[] = { 0, 10, 13};

static const u8 *const gUnknown_08618160[] = {
    Unknown_08617F07,
    Unknown_08617F97,
    Unknown_08618020,
    Unknown_08618092,
    Unknown_086180D7,
    Unknown_08617EA3
};

static const void *const gUnknown_08618178[][3] = {
    {
        gBerryFixGameboy_Gfx,
        gBerryFixGameboy_Tilemap,
        gBerryFixGameboy_Pal
    }, {
        gBerryFixGameboyLogo_Gfx,
        gBerryFixGameboyLogo_Tilemap,
        gBerryFixGameboyLogo_Pal
    }, {
        gBerryFixGbaTransfer_Gfx,
        gBerryFixGbaTransfer_Tilemap,
        gBerryFixGbaTransfer_Pal
    }, {
        gBerryFixGbaTransferHighlight_Gfx,
        gBerryFixGbaTransferHighlight_Tilemap,
        gBerryFixGbaTransferHighlight_Pal
    }, {
        gBerryFixGbaTransferError_Gfx,
        gBerryFixGbaTransferError_Tilemap,
        gBerryFixGbaTransferError_Pal
    }, {
        gBerryFixWindow_Gfx,
        gBerryFixWindow_Tilemap,
        gBerryFixWindow_Pal
    },
};

extern const u8 gMultiBootProgram_BerryGlitchFix_Start[0x3BF4];
extern const u8 gMultiBootProgram_BerryGlitchFix_End[];

// .text

void CB2_InitBerryFixProgram(void)
{
    DisableInterrupts(0xFFFF);
    EnableInterrupts(0x0001);
    m4aSoundVSyncOff();
    SetVBlankCallback(NULL);
    ResetSpriteData();
    ResetTasks();
    ScanlineEffect_Stop();
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    berry_fix_mb_manager = AllocZeroed(0x50);
    berry_fix_mb_manager->state = 0;
    berry_fix_mb_manager->unk1 = 6;
    SetMainCallback2(berry_fix_main);
}

static void berry_fix_main(void)
{
    switch (berry_fix_mb_manager->state)
    {
        case 0:
            berry_fix_gpu_set();
            berry_fix_mb_manager->state = 1;
            break;
        case 1:
            if (berry_fix_text_update(5) == 5 && (gMain.newKeys & A_BUTTON))
            {
                berry_fix_mb_manager->state = 2;
            }
            break;
        case 2:
            if (berry_fix_text_update(0) == 0 && (gMain.newKeys & A_BUTTON))
            {
                berry_fix_mb_manager->state = 3;
            }
            break;
        case 3:
            if (berry_fix_text_update(1) == 1)
            {
                berry_fix_mb_manager->mb.masterp = gMultiBootProgram_BerryGlitchFix_Start;
                berry_fix_mb_manager->mb.server_type = 0;
                MultiBootInit(&berry_fix_mb_manager->mb);
                berry_fix_mb_manager->unk2 = 0;
                berry_fix_mb_manager->state = 4;
            }
            break;
        case 4:
            MultiBootMain(&berry_fix_mb_manager->mb);
            if (berry_fix_mb_manager->mb.probe_count != 0 || (!(berry_fix_mb_manager->mb.response_bit & 2) || !(berry_fix_mb_manager->mb.client_bit & 2)))
            {
                berry_fix_mb_manager->unk2 = 0;
            }
            else if (++ berry_fix_mb_manager->unk2 > 180)
            {
                MultiBootStartMaster(&berry_fix_mb_manager->mb, gMultiBootProgram_BerryGlitchFix_Start + ROM_HEADER_SIZE, (u32)(gMultiBootProgram_BerryGlitchFix_End - (gMultiBootProgram_BerryGlitchFix_Start + ROM_HEADER_SIZE)), 4, 1);
                berry_fix_mb_manager->state = 5;
            }
            break;
        case 5:
            if (berry_fix_text_update(2) == 2) {
                MultiBootMain(&berry_fix_mb_manager->mb);
                if (MultiBootCheckComplete(&berry_fix_mb_manager->mb)) {
                    berry_fix_mb_manager->state = 6;
                }
                else if (!(berry_fix_mb_manager->mb.client_bit & 2)) {
                    berry_fix_mb_manager->state = 7;
                }
            }
            break;
        case 6:
            if (berry_fix_text_update(3) == 3 && gMain.newKeys & A_BUTTON)
            {
                DoSoftReset();
            }
            break;
        case 7:
            if (berry_fix_text_update(4) == 4 && gMain.newKeys & A_BUTTON)
            {
                berry_fix_mb_manager->state = 1;
            }
            break;
    }
}

static void berry_fix_gpu_set(void)
{
    s32 width, left;

    SetGpuReg(REG_OFFSET_BG0CNT, 0);
    SetGpuReg(REG_OFFSET_BG1CNT, 0);
    SetGpuReg(REG_OFFSET_BG0HOFS, 0);
    SetGpuReg(REG_OFFSET_BG0VOFS, 0);
    SetGpuReg(REG_OFFSET_BG1HOFS, 0);
    SetGpuReg(REG_OFFSET_BG1VOFS, 0);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);

    DmaFill32(3, 0, VRAM, VRAM_SIZE);
    DmaFill32(3, 0, OAM, OAM_SIZE);
    DmaFill32(3, 0, PLTT, PLTT_SIZE);
    ResetBgsAndClearDma3BusyFlags(0);

    InitBgsFromTemplates(0, gUnknown_08618108, ARRAY_COUNT(gUnknown_08618108));
    ChangeBgX(0, 0, 0);
    ChangeBgY(0, 0, 0);
    ChangeBgX(1, 0, 0);
    ChangeBgY(1, 0, 0);
    InitWindows(gUnknown_08618110);
    DeactivateAllTextPrinters();

    DmaCopy32(3, sUnknown_08618138, BG_PLTT + 0x1E0, 0x20);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP);
    FillWindowPixelBuffer(2, PIXEL_FILL(0));
    FillWindowPixelBuffer(3, PIXEL_FILL(0));
    FillWindowPixelBuffer(0, PIXEL_FILL(0xA));

    width = GetStringWidth(0, sUnknown_08617E9B, 0);
    left = (0x78 - width) / 2;
    AddTextPrinterParameterized3(2, 0, left, 3, sUnknown_0861815B, TEXT_SPEED_FF, sUnknown_08617E9B);

    width = GetStringWidth(0, sUnknown_08617E8D, 0);
    left = (0x78 - width) / 2 + 0x78;
    AddTextPrinterParameterized3(2, 0, left, 3, sUnknown_0861815B, TEXT_SPEED_FF, sUnknown_08617E8D);

    width = GetStringWidth(0, sUnknown_08617E8D, 0);
    left = (0x70 - width) / 2;
    AddTextPrinterParameterized3(3, 0, left, 0, sUnknown_0861815B, TEXT_SPEED_FF, sUnknown_08617E8D);

    width = GetStringWidth(1, sUnknown_08617E78, 0);
    left = (0xD0 - width) / 2;
    AddTextPrinterParameterized3(0, 1, left, 2, sUnknown_08618158, TEXT_SPEED_FF, sUnknown_08617E78);

    CopyWindowToVram(2, 2);
    CopyWindowToVram(3, 2);
    CopyWindowToVram(0, 2);
}

static int berry_fix_text_update(int checkval)
{
    if (berry_fix_mb_manager->unk1 == checkval)
    {
        return checkval;
    }
    if (berry_fix_mb_manager->unk1 == 6)
    {
        berry_fix_text_print(checkval);
        berry_fix_mb_manager->unk1 = checkval;
    }
    else
    {
        berry_fix_bg_hide();
        berry_fix_mb_manager->unk1 = 6;
    }
    return berry_fix_mb_manager->unk1;
}

static void berry_fix_text_print(int scene)
{
    FillBgTilemapBufferRect_Palette0(0, 0, 0, 0, 32, 32);
    FillWindowPixelBuffer(1, PIXEL_FILL(0xA));
    AddTextPrinterParameterized3(1, 1, 0, 0, sUnknown_08618158, -1, gUnknown_08618160[scene]);
    PutWindowTilemap(1);
    CopyWindowToVram(1, 2);
    switch (scene)
    {
        case 0:
        case 2:
        case 3:
        case 4:
            PutWindowTilemap(2);
            break;
        case 1:
            PutWindowTilemap(3);
            break;
        case 5:
            PutWindowTilemap(0);
            break;
    }
    CopyBgTilemapBufferToVram(0);
    LZ77UnCompVram(gUnknown_08618178[scene][0], (void *)BG_CHAR_ADDR(1));
    LZ77UnCompVram(gUnknown_08618178[scene][1], (void *)BG_SCREEN_ADDR(31));
    CpuCopy32(gUnknown_08618178[scene][2], (void *)BG_PLTT, 0x100);
    ShowBg(0);
    ShowBg(1);
}

static void berry_fix_bg_hide(void)
{
    HideBg(0);
    HideBg(1);
}
