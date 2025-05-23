// license:BSD-3-Clause
// copyright-holders:Bryan McPhail,Ernesto Corvi,Andrew Prime,Zsolt Vasvari
// thanks-to:Fuzz

/***************************************************************************

    Neo-Geo hardware

    Credits:
        * This driver was made possible by the research done by
          Charles MacDonald.  For a detailed description of the Neo-Geo
          hardware, please visit his page at:
          http://cgfm2.emuviews.com/txt/mvstech.txt
        * Presented to you by the Shin Emu Keikaku team.
        * The following people have all spent probably far
          too much time on this:
          AVDB
          Bryan McPhail
          Fuzz
          Ernesto Corvi
          Andrew Prime
          Zsolt Vasvari


    Known driver issues/to-do's:
    ============================

        * Fatal Fury 3 crashes during the ending - this doesn't occur if
          the language is set to Japanese, maybe the English endings
          are incomplete / buggy?
        * Graphical Glitches caused by incorrect timing?
          - Some raster effects are imperfect (off by a couple of lines)
        * Multi-cart support not implemented - the MVS can take up to
          6 cartridges depending on the board being used
        * 68000 waitstates on ROM region access, determined by jumpers on cart
          (garou train stage 3 background bug is probably related to this)


    Confirmed non-bugs:

        * Bad zooming in the Kof2003 bootlegs - this is what happens
          if you try and use the normal bios with a pcb set, it
          looks like the bootleggers didn't care.
        * Glitches at the edges of the screen - the real hardware
          can display 320x224 but most of the games seem designed
          to work with a width of 304, some less.
        * Distorted jumping sound in Nightmare in the Dark
        * Ninja Combat sometimes glitches


*****************************************************************************

    The Neo-Geo Multi Video System (MVS), is an arcade system board, being
    the first product in the Neo-Geo family, designed by Alpha Denshi(ADK)
    and released in 1990 by SNK. It was known to the coin-op industry, and
    offered arcade operators the ability to put up to 6 different arcade
    titles into a single cabinet, a key economic consideration for operators
    with limited floorspace (games for the Neo-Geo are cartridge based and are
    easily exchangeable). It comes in many different cabinets but basically
    consists of an add on board that can be linked to a standard Jamma system.
    The system was discontinued in 2004.
    Source (modified): http://en.wikipedia.org/wiki/Neo_Geo


    MVS motherboards were produced in 1 / 2 / 4 and 6 Slot versions.

    Known motherboards:
    ===================

    1 Slot:
    NEO-MVH MV1
    NEO-MVH MV1-1
    NEO-MVH MV1A
     . NEO-MVH MV1A CHX ??
    NEO-MVH MV1B (1996.1.19)
     . NEO-MVH MV1B CHX (1996.1.19) ??
    NEO-MVH MV1B1 (1998.6.17)
    NEO-MVH MV1C (1999.4.30)
    NEO-MVH MV1F
    NEO-MVH MV1FS
    NEO-MVH MV1FT
    NEO-MVH MV1FZ
    NEO-MVH MV1FZS

    2 Slot:
    NEO-MVH MV2
    NEO-MVH MV2F
    NEO-MVH MV2F-01

    4 Slot:
    NEO-MVH MV4
    NEO-MVH MV4F
    NEO-MVH MV4FS
    NEO-MVH MV4FT
    NEO-MVH MV4FT2

    6 Slot:
    NEO-MVH MV6
    NEO-MVH MV6F


    Neo-Geo Motherboard (info - courtesy of Guru):

          NEO-MVH MV1
          |---------------------------------------------------------------------|
          |       4558                                                          |
          |                                          HC04  HC32                 |
          |                      SP-S2.SP1  NEO-E0   000-L0.L0   LS244  AS04    |
          |             YM2610                                                  |
          | 4558                                                                |
          |       4558                        5814  HC259   SFIX.SFIX           |
          |                                                             NEO-I0  |
          | HA13001 YM3016                    5814                              |
          --|                                                                   |
            |     4558                                                          |
          --|                                                 SM1.SM1   LS32    |
          |                                                                     |
          |                           LSPC-A0         PRO-C0            LS244   |
          |                                                                     |
          |J              68000                                                 |
          |A                                                                    |
          |M                                                                    |
          |M                                                      NEO-ZMC2      |
          |A                                                                    |
          |   LS273  NEO-G0                          58256  58256     Z80A      |
          |                           58256  58256   58256  58256     6116      |
          |   LS273 5864                                                        |
          --| LS05  5864  PRO-B0                                                |
            |                                                                   |
          --|             LS06   HC32           D4990A    NEO-F0   24.000MHz    |
          |                      DSW1    BATT3.6V 32.768kHz       NEO-D0        |
          |                                           2003  2003                |
          |---------------------------------------------------------------------|


*****************************************************************************

    Neo-Geo game PCB infos:
    =======================

    The Neo-Geo games for AES (home) and MVS (arcade) systems are cartridge based.

    Each cartridge consists of two PCBs: CHA and PROG.
    .CHA PCB contains gfx data ('C' - rom), text layer data ('S' - rom) and sound driver ('M' - rom).
    .PROG PCB contains sample data ('V' - rom) and program code ('P' - rom).

    On most PCBs various custom/protection chips can also be found:
    (Custom chip detail information (modified) from: http://wiki.neogeodev.org)

    CHA:
    . NEO-273  (C and S-ROM address latch)
    . NEO-CMC 90G06CF7042 (NEO-273 logic / NEO-ZMC logic / C-ROM decryption / C and S-ROM multiplexer / S-ROM bankswitching)
    . NEO-CMC 90G06CF7050 (NEO-273 logic / NEO-ZMC logic / C-ROM decryption / M-ROM decryption / C and S-ROM multiplexer / S-ROM bankswitching)
    . NEO-ZMC  (Z80 memory controller)
    . NEO-ZMC2 (Z80 memory controller / Tile serializer)
    . PRO-CT0  (C-ROM serializer and multiplexer?; used on early AES-CHA boards)
    . SNK-9201 (C-ROM serializer and multiplexer?; used on early AES-CHA boards)

    PROG:
    . 0103 (QFP144) (Only found on Metal Slug X NEO-MVS PROGEOP board; function unknown)
    . ALTERA   (EPM7128SQC100-15) (P-ROM protection chip used for KOF98 NEO-MVS PROGSF1 board and Metal Slug X NEO-MVS PROGEOP board)
    . NEO-COMA (Microcontroller; used for MULTI PLAY MODE, boards and sets see below)
    . NEO-PCM2 (SNK 1999) (PCM functionality / V-ROM decryption / P-ROM decoding and bankswitching)
    . NEO-PCM2 (PLAYMORE 2002) (PCM functionality / V-ROM decryption / P-ROM decoding and bankswitching)
    . NEO-PVC  (P-ROM decryption and bankswitching) / RAM
    . NEO-SMA  (P-ROM decryption and bankswitching / RNG / Storage of 256kb game data)
    . PCM      (ADPCM bus latches / V-ROM multiplexer)
    . PRO-CT0  (On PROG board used for P-ROM protection -> Fatal Fury 2)
    . SNK-9201 (On PROG board used for P-ROM protection -> Fatal Fury 2)



    Known PCBs:
    ============

    MVS CHA:
    -- SNK --
    . NEO-MVS CHA-32
    . NEO-MVS CHA-8M
    . NEO-MVS CHA42G
    . NEO-MVS CHA42G-1
    . NEO-MVS CHA 42G-2
    . NEO-MVS CHA 42G-3
    . NEO-MVS CHA42G-3B
    . NEO-MVS CHA256
    . NEO-MVS CHA256B
    . NEO-MVS CHA512Y
    . NEO-MVS CHAFIO (1999.6.14) - used with NEO-CMC 90G06C7042 or NEO-CMC 90G06C7050
    . MVS CHAFIO REV1.0 (KOF-2001)
    . NEO-MVS CHAFIO (SNK 2002) - MADE IN KOREA
    -- SNKPLAYMORE --
    . NEO-MVS CHAFIO (2003.7.24) - used only with NEO-CMC 90G06C7050

    -- SNK development boards --
    . NEO-MVS CHAMC2

    MVS PROG:
    -- SNK --
    . NEO-MVS PROG-NAM
    . NEO-MVS PROG-HERO
    . NEO-MVS PROG-EP
    . NEO-MVS PROG-8MB
    . NEO-MVS PROGEP8M
    . NEO-MVS PROG8M42
    . NEO-MVS PROG16
    . NEO-MVS PROG42G
    . NEO-MVS PROG42G-COM
    . NEO-MVS PROG42G-1
    . NEO-MVS PROG-G2
    . NEO-MVS PROG 4096
    . NEO-MVS PROG 4096 B
    . NEO-MVS PROGGSC
    . NEO-MVS PROGSM
    . NEO-MVS PROGSS3
    . NEO-MVS PROGTOP
    . NEO-MVS PROGSF1 (1998.6.17)
    . NEO-MVS PROGSF1E (1998.6.18)
    . NEO-MVS PROGEOP (1999.2.2)
    . NEO-MVS PROGLBA (1999.4.12) - LBA-SUB (2000.2.24)
    . NEO-MVS PROGBK1 (1994)
    . NEO-MVS PROGBK1 (2001)
    . NEO-MVS PROGBK2 (2000.3.21) - used with NEO-PCM2 (1999 SNK) or NEO-PCM2 (2002 PLAYMORE)
    . MVS PROGBK2 REV1.0 (KOF-2001)
    . NEO-MVS PROGBK2 (SNK 2002) - MADE IN KOREA
    -- SNKPLAYMORE --
    . NEO-MVS PROGBK2R (2003.8.26) - NEO-HYCS (2003.9.29)
    . NEO-MVS PROGBK3R (2003.9.2) - NEO-HYCS (2003.9.29)
    . NEO-MVS PROGBK3S (2003.10.1)
    . NEO-MVS PROGBK2S (2003.10.18)

    -- SNK development boards --
    . NEO-MVS PROGMC2


    AES CHA:
    -- SNK --
    . NEO-AEG CHA-32
    . NEO-AEG CHA-8M
    . NEO-AEG CHA42G
    . NEO-AEG CHA42G-1
    . NEO-AEG CHA42G-2B
    . NEO-AEG CHA42G-3
    . NEO-AEG CHA42G-4
    . NEO-AEG CHA256
    . NEO-AEG CHA256 B
    . NEO-AEG CHA256[B]
    . NEO-AEG CHA256BY
    . NEO-AEG CHA256RY
    . NEO-AEG CHA512Y
    . NEO-AEG CHAFIO (1999.8.10) - used with NEO-CMC 90G06C7042 or NEO-CMC 90G06C7050
    -- SNKPLAYMORE --
    . NEO-AEG CHAFIO (2003.7.24) - used only with NEO-CMC 90G06C7050

    AES PROG:
    -- SNK --
    . NEO-AEG PROG-NAM
    . NEO-AEG PROG-HERO
    . NEO-AEG PROG-4A
    . NEO-AEG PROG-4B
    . NEO-AEG PROG 8M42
    . NEO-AEG PROG B
    . NEO-AEG PROG16
    . NEO-AEG PROG42G
    . NEO-AEG PROG42G-COM
    . NEO-AEG PROG42G-1
    . NEO-AEG PROG-G2
    . NEO-AEG PROG4096 B
    . NEO-AEG PROGGS
    . NEO-AEG PROGTOP2
    . NEO-AEG PROGTOP2Y
    . NEO-AEG PROGEOP (1999.4.2)
    . NEO-AEG PROGLBA (1999.7.6)
    . NEO-AEG PROGRK
    . NEO-AEG PROGRKB
    . NEO-AEG PROGBK1Y
    . NEO-AEG PROGBK1F
    -- PLAYMORE --
    . NEO-AEG PROGBK2 (2002.4.1) - used with NEO-PCM2 (1999 SNK) or NEO-PCM2 (2002 PLAYMORE)
    -- SNKPLAYMORE --
    . NEO-AEG PROGBK3R (2003.8.29) - NEO-HYCS (2003.9.29)
    . NEO-AEG PROGBK3S (2003.10.6)
    . NEO-AEG PROGBK2S (2003.10.16)



    Cartridge colours:
    ==================

    MVS cartridges were produced in different colours.

    Known cartridge colours:
    . Black
    . Blue
    . Green
    . Grey
    . Red
    . Transparent
    . Transparent Blue
    . Transparent Green
    . White
    . Yellow

    The above listed only covers SNK / PLAYMORE / SNKPLAYMORE PCBs. There also exists a
    wide range of 'bootleg' PCBs.


    Unofficial pcb's from NG:DEV.TEAM:

    MVS CHA:
    GIGA CHAR Board 1.0 Rev. A
    GIGA CHAR Board 1.5 Rev. 0
    GIGA CHAR Board 1.5 Rev. C

    MVS PROG:
    GIGA PROG Board 1.0 Rev. B
    GIGA PROG Board 1.5 Rev. A
    GIGA PROG Board 1.5 Rev. C


    Unofficial pcb's from NEOBITZ:

    MVS CHA:
    CHARBITZ1 2013.12.01

    MVS PROG:
    PROGBITZ1 2013.12.01


    Neo-Geo game PCB infos by Johnboy



    MVS cart pinout:
    ================

    Kindly submitted by Apollo69 (apollo69@columbus.rr.com)
    =================================================================
                CTRG1                            CTRG2
    =================================================================
         GND = 01A | 01B = GND            GND = 01A | 01B = GND
         GND = 02A | 02B = GND            GND = 02A | 02B = GND
          P0 = 03A | 03B = P1             GND = 03A | 03B = GND
          P2 = 04A | 04B = P3             GND = 04A | 04B = GND
          P4 = 05A | 05B = P5              D0 = 05A | 05B = A1
          P6 = 06A | 06B = P7              D1 = 06A | 06B = A2
          P8 = 07A | 07B = P9              D2 = 07A | 07B = A3
         P10 = 08A | 08B = P11             D3 = 08A | 08B = A4
         P12 = 09A | 09B = P13             D4 = 09A | 09B = A5
         P14 = 10A | 10B = P15             D5 = 10A | 10B = A6
         P16 = 11A | 11B = P17             D6 = 11A | 11B = A7
         P18 = 12A | 12B = P19             D7 = 12A | 12B = A8
         P20 = 13A | 13B = P21             D8 = 13A | 13B = A9
         P22 = 14A | 14B = P23             D9 = 14A | 14B = A10
       PCK1B = 15A | 15B = 24M            D10 = 15A | 15B = A11
       PCK2B = 16A | 16B = 12M            D11 = 16A | 16B = A12
         2H1 = 17A | 17B = 8M             D12 = 17A | 17B = A13
         CA4 = 18A | 18B = RESET          D13 = 18A | 18B = A14
         CR0 = 19A | 19B = CR1            D14 = 19A | 19B = A15
         CR2 = 20A | 20B = CR3            D15 = 20A | 20B = A16
         CR4 = 21A | 21B = CR5            R/W = 21A | 21B = A17
         CR6 = 22A | 22B = CR7             AS = 22A | 22B = A18
         CR8 = 23A | 23B = CR9         ROMOEU = 23A | 23B = A19
        CR10 = 24A | 24B = CR11        ROMOEL = 24A | 24B = 68KCLKB
        CR12 = 25A | 25B = CR13       PORTOEU = 25A | 25B = ROMWAIT
        CR14 = 26A | 26B = CR15       PORTOEL = 26A | 26B = PWAIT0
        CR16 = 27A | 27B = CR17       PORTWEU = 27A | 27B = PWAIT1
        CR18 = 28A | 28B = CR19       PORTWEL = 28A | 28B = PDTACT
         VCC = 29A | 29B = VCC            VCC = 29A | 29B = VCC
         VCC = 30A | 30B = VCC            VCC = 30A | 30B = VCC
         VCC = 31A | 31B = VCC            VCC = 31A | 31B = VCC
         VCC = 32A | 32B = VCC            VCC = 32A | 32B = VCC
        CR20 = 33A | 33B = CR21      PORTADRS = 33A | 33B = 4MB
        CR22 = 34A | 34B = CR23            NC = 34A | 34B = ROMOE
        CR24 = 35A | 35B = CR25            NC = 35A | 35B = RESET
        CR26 = 36A | 36B = CR27            NC = 36A | 36B = NC
        CR28 = 37A | 37B = CR29            NC = 37A | 37B = NC
        CR30 = 38A | 38B = CR31            NC = 38A | 38B = NC
          NC = 39A | 39B = FIX00           NC = 39A | 39B = NC
          NC = 40A | 40B = FIX01           NC = 40A | 40B = NC
          NC = 41A | 41B = FIX02           NC = 41A | 41B = SDPAD0
     SYSTEMB = 42A | 42B = FIX03      SYSTEMB = 42A | 42B = SDPAD1
        SDA0 = 43A | 43B = FIX04        SDPA8 = 43A | 43B = SDPAD2
        SDA1 = 44A | 44B = FIX05        SDPA9 = 44A | 44B = SDPAD3
        SDA2 = 45A | 45B = FIX06       SDPA10 = 45A | 45B = SDPAD4
        SDA3 = 46A | 46B = FIX07       SDPA11 = 46A | 46B = SDPAD5
        SDA4 = 47A | 47B = SDRD0       SDPMPX = 47A | 47B = SDPAD6
        SDA5 = 48A | 48B = SDRD1        SDPOE = 48A | 48B = SDPAD7
        SDA6 = 49A | 49B = SDROM        SDRA8 = 49A | 49B = SDRA00
        SDA7 = 50A | 50B = SDMRD        SDRA9 = 50A | 50B = SDRA01
        SDA8 = 51A | 51B = SDDO        SDRA20 = 51A | 51B = SDRA02
        SDA9 = 52A | 52B = SDD1        SDRA21 = 52A | 52B = SDRA03
       SDA10 = 53A | 53B = SDD2        SDRA22 = 53A | 53B = SDRA04
       SDA11 = 54A | 54B = SDD3        SDRA23 = 54A | 54B = SDRA05
       SDA12 = 55A | 55B = SDD4        SDRMPX = 55A | 55B = SDRA06
       SDA13 = 56A | 56B = SDD5         SDROE = 56A | 56B = SDRA07
       SDA14 = 57A | 57B = SDD6           GND = 57A | 57B = GND
       SDA15 = 58A | 58B = SDD7           GND = 58A | 58B = GND
         GND = 59A | 59B = GND            GND = 59A | 59B = GND
         GND = 60A | 60B = GND            GND = 60A | 60B = GND

    CTRG1 (CHA)  = Contains gfx data ('C' - rom), text layer data ('S' - rom) and sound driver ('M' - rom)
    CTRG2 (PROG) = Contains sample data ('V' - rom) and program code ('P' - rom)

    NOTE: On CTRG2-B, The "A" lines start at "A1". If you trace this on an
    actual cart, you will see that this is actually "A0" (A0 - A18).

    These are from a very hard to read copy of the schematics, so
    I hope that I got the pin names correct.

    Apollo69 10/19/99


*****************************************************************************

    Watchdog:
    =========

    The watchdog timer will reset the system after ~0.13 seconds.
    By cgfm's research, exactly 3,244,030 cycles (based on 24MHz clock).

    Newer games force a reset using the following code (this from kof99):
        009CDA  203C 0003 0D40             MOVE.L   #0x30D40,D0
        009CE0  5380                       SUBQ.L   #1,D0
        009CE2  64FC                       BCC.S    *-0x2 [0x9CE0]
    Note however that there is a valid code path after this loop.

    The watchdog is used as a form of protection on a number of games,
    previously this was implemented as a specific hack which locked a single
    address of SRAM.

    What actually happens is if the game doesn't find valid data in the
    backup ram it will initialize it, then sit in a loop.  The watchdog
    should then reset the system while it is in this loop.  If the watchdog
    fails to reset the system the code will continue and set a value in
    backup ram to indiate that the protection check has failed.


    Mahjong Panel notes (2009-03 FP):
    =================================

    * In Service Mode menu with mahjong panel active, controls are as
      follows:

        A = select / up (for options)
        B = down (for options)
        C = go to previous menu
        E = up (for menu entries)
        F = down (for menu entries)
        G = left (for options)
        H = right (for options)

    * These only work with Japanese BIOS, but I think it's not a bug: I
      doubt other BIOS were programmed to be compatible with mahjong panels

****************************************************************************/

#include "includes/neogeo.h"
#include "neogeo.lh"


#define LOG_VIDEO_SYSTEM         (0)
#define LOG_MAIN_CPU_BANKING     (0)
#define LOG_AUDIO_CPU_BANKING    (0)


/*************************************
 *
 *  Main CPU interrupt generation
 *
 *************************************/



// The display counter is automatically reloaded with the load register contents on scanline 224,
// 1146 mclks from the rising edge of /HSYNC.
#define NEOGEO_VBLANK_RELOAD_HTIM (attotime::from_ticks(1146, NEOGEO_MASTER_CLOCK))

#define IRQ2CTRL_ENABLE             (0x10)
#define IRQ2CTRL_LOAD_RELATIVE      (0x20)
#define IRQ2CTRL_AUTOLOAD_VBLANK    (0x40)
#define IRQ2CTRL_AUTOLOAD_REPEAT    (0x80)


void neogeo_state::adjust_display_position_interrupt_timer()
{
	attotime period = attotime::from_ticks((u64)m_display_counter + 1, NEOGEO_PIXEL_CLOCK);
	if (LOG_VIDEO_SYSTEM) logerror("adjust_display_position_interrupt_timer  current y: %02x  current x: %02x   target y: %x  target x: %x\n", m_screen->vpos(), m_screen->hpos(), (m_display_counter + 1) / NEOGEO_HTOTAL, (m_display_counter + 1) % NEOGEO_HTOTAL);

	m_display_position_interrupt_timer->adjust(period);
}


void neogeo_state::neogeo_set_display_position_interrupt_control( u16  data )
{
	m_display_position_interrupt_control = data;
}


void neogeo_state::neogeo_set_display_counter_msb( u16  data )
{
	m_display_counter = (m_display_counter & 0x0000ffff) | ((u32)data << 16);

	if (LOG_VIDEO_SYSTEM) logerror("PC %06x: set_display_counter %08x\n", m_maincpu->pc(), m_display_counter);
}


void neogeo_state::neogeo_set_display_counter_lsb( u16  data )
{
	m_display_counter = (m_display_counter & 0xffff0000) | data;

	if (LOG_VIDEO_SYSTEM) logerror("PC %06x: set_display_counter %08x\n", m_maincpu->pc(), m_display_counter);

	if (m_display_position_interrupt_control & IRQ2CTRL_LOAD_RELATIVE)
	{
		if (LOG_VIDEO_SYSTEM) logerror("AUTOLOAD_RELATIVE ");
		adjust_display_position_interrupt_timer();
	}
}


void neogeo_state::update_interrupts()
{
	m_maincpu->set_input_line(3, m_irq3_pending ? ASSERT_LINE : CLEAR_LINE);
	m_maincpu->set_input_line(m_raster_level, m_display_position_interrupt_pending ? ASSERT_LINE : CLEAR_LINE);
	m_maincpu->set_input_line(m_vblank_level, m_vblank_interrupt_pending ? ASSERT_LINE : CLEAR_LINE);
}


void neogeo_state::neogeo_acknowledge_interrupt( u16  data )
{
	if (data & 0x01)
		m_irq3_pending = 0;
	if (data & 0x02)
		m_display_position_interrupt_pending = 0;
	if (data & 0x04)
		m_vblank_interrupt_pending = 0;

	update_interrupts();
}


TIMER_CALLBACK_MEMBER(neogeo_state::display_position_interrupt_callback)
{
	if (LOG_VIDEO_SYSTEM) logerror("--- Scanline @ %d,%d\n", m_screen->vpos(), m_screen->hpos());

	if (m_display_position_interrupt_control & IRQ2CTRL_ENABLE)
	{
		if (LOG_VIDEO_SYSTEM) logerror("*** Scanline interrupt (IRQ2) ***  y: %02x  x: %02x\n", m_screen->vpos(), m_screen->hpos());
		m_display_position_interrupt_pending = 1;

		update_interrupts();
	}

	if (m_display_position_interrupt_control & IRQ2CTRL_AUTOLOAD_REPEAT)
	{
		if (LOG_VIDEO_SYSTEM) logerror("AUTOLOAD_REPEAT ");
		adjust_display_position_interrupt_timer();
	}
}


TIMER_CALLBACK_MEMBER(neogeo_state::display_position_vblank_callback)
{
	if (m_display_position_interrupt_control & IRQ2CTRL_AUTOLOAD_VBLANK)
	{
		if (LOG_VIDEO_SYSTEM) logerror("AUTOLOAD_VBLANK ");
		adjust_display_position_interrupt_timer();
	}

	/* set timer for next screen */
	m_display_position_vblank_timer->adjust(m_screen->time_until_pos(NEOGEO_VBSTART) + NEOGEO_VBLANK_RELOAD_HTIM);
}


TIMER_CALLBACK_MEMBER(neogeo_state::vblank_interrupt_callback)
{
	if (LOG_VIDEO_SYSTEM) logerror("+++ VBLANK @ %d,%d\n", m_screen->vpos(), m_screen->hpos());

	m_vblank_interrupt_pending = 1;
	update_interrupts();

	/* set timer for next screen */
	m_vblank_interrupt_timer->adjust(m_screen->time_until_pos(NEOGEO_VBSTART) + NEOGEO_VBLANK_IRQ_HTIM);
}


void neogeo_state::create_interrupt_timers()
{
	m_display_position_interrupt_timer = machine().scheduler().timer_alloc(timer_expired_delegate(FUNC(neogeo_state::display_position_interrupt_callback),this));
	m_display_position_vblank_timer = machine().scheduler().timer_alloc(timer_expired_delegate(FUNC(neogeo_state::display_position_vblank_callback),this));
	m_vblank_interrupt_timer = machine().scheduler().timer_alloc(timer_expired_delegate(FUNC(neogeo_state::vblank_interrupt_callback),this));
}


void neogeo_state::start_interrupt_timers()
{
	m_vblank_interrupt_timer->adjust(m_screen->time_until_pos(NEOGEO_VBSTART) + NEOGEO_VBLANK_IRQ_HTIM);
	m_display_position_vblank_timer->adjust(m_screen->time_until_pos(NEOGEO_VBSTART) + NEOGEO_VBLANK_RELOAD_HTIM);
}



/*************************************
 *
 *  Audio CPU interrupt generation
 *
 *************************************/

void neogeo_state::audio_cpu_check_nmi()
{
	m_audiocpu->set_input_line(INPUT_LINE_NMI, (m_audio_cpu_nmi_enabled && m_audio_cpu_nmi_pending) ? ASSERT_LINE : CLEAR_LINE);
}

void neogeo_state::audio_cpu_enable_nmi_w(offs_t offset, u8 data)
{
	// out ($08) enables the nmi, out ($18) disables it
	m_audio_cpu_nmi_enabled = !(offset & 0x10);
	audio_cpu_check_nmi();
}



/*************************************
 *
 *  Input ports / Controllers
 *
 *************************************/

u16 neogeo_state::in0_r()
{
	return ((m_edge->in0_r() & m_ctrl1->read_ctrl()) << 8) | m_dsw->read();
}

u16 neogeo_state::in1_r()
{
	return ((m_edge->in1_r() & m_ctrl2->read_ctrl()) << 8) | 0xff;
}

void neogeo_state::io_control_w(offs_t offset, u8 data)
{
	switch (offset)
	{
		case 0x00:
			if (m_ctrl1) m_ctrl1->write_ctrlsel(data);
			if (m_ctrl2) m_ctrl2->write_ctrlsel(data);
			if (m_edge) m_edge->write_ctrlsel(data);
			break;

		case 0x10:
			break;

		case 0x18:
			if (m_type == NEOGEO_MVS)
				set_output_latch(data);
			break;

		case 0x20:
			if (m_type == NEOGEO_MVS)
				set_output_data(data);
			break;

		case 0x28:
			if (m_type == NEOGEO_MVS)
			{
				m_upd4990a->data_in_w(data >> 0 & 1);
				m_upd4990a->clk_w(data >> 1 & 1);
				m_upd4990a->stb_w(data >> 2 & 1);
			}
			break;

//  case 0x30: break; // coin counters
//  case 0x31: break; // coin counters
//  case 0x32: break; // coin lockout
//  case 0x33: break; // coin lockout

		default:
			logerror("PC: %x  Unmapped I/O control write.  Offset: %x  Data: %x\n", machine().describe_context(), offset, data);
			break;
	}
}


/*************************************
 *
 *  Unmapped memory access
 *
 *************************************/

u16 neogeo_state::neogeo_unmapped_r(address_space &space)
{
	u16  ret;

	/* unmapped memory returns the last word on the data bus, which is almost always the opcode
	   of the next instruction due to prefetch */

	/* prevent recursion */
	if (m_recurse)
		ret = 0xffff;
	else
	{
		m_recurse = true;
		ret = space.read_word(m_maincpu->pc());
		m_recurse = false;
	}
	return ret;
}



/*************************************
 *
 *  NVRAM (Save RAM)
 *
 *************************************/

void neogeo_state::set_save_ram_unlock( u8 data )
{
	m_save_ram_unlocked = data;
}


void neogeo_state::save_ram_w(offs_t offset, u16 data, u16 mem_mask)
{
	if (m_save_ram_unlocked)
		COMBINE_DATA(&m_save_ram[offset]);
}



/*************************************
 *
 *  Memory card
 *
 *************************************/

CUSTOM_INPUT_MEMBER(neogeo_state::get_memcard_status)
{
	// D0 and D1 are memcard 1 and 2 presence indicators, D2 indicates memcard
	// write protect status (we are always write enabled)
	return (m_memcard->present() == -1) ? 0x07 : 0x00;
}


u16 neogeo_state::memcard_r(offs_t offset)
{
	m_maincpu->eat_cycles(2); // insert waitstate

	u16  ret;

	if (m_memcard->present() != -1)
		ret = m_memcard->read(offset) | 0xff00;
	else
		ret = 0xffff;

	return ret;
}


void neogeo_state::memcard_w(offs_t offset, u16 data, u16 mem_mask)
{
	m_maincpu->eat_cycles(2); // insert waitstate

	if (ACCESSING_BITS_0_7)
	{
		if (m_memcard->present() != -1)
				m_memcard->write(offset, data);
	}
}

/*************************************
 *
 *  Inter-CPU communications
 *
 *************************************/

void neogeo_state::audio_command_w(u8 data)
{
	m_soundlatch->write(data);

	m_audio_cpu_nmi_pending = true;
	audio_cpu_check_nmi();

	/* boost the interleave to let the audio CPU read the command */
	machine().scheduler().boost_interleave(attotime::zero, attotime::from_usec(50));
}


u8 neogeo_state::audio_command_r()
{
	u8 ret = m_soundlatch->read();

	m_audio_cpu_nmi_pending = false;
	audio_cpu_check_nmi();

	return ret;
}


CUSTOM_INPUT_MEMBER(neogeo_state::get_audio_result)
{
	u8 ret = m_soundlatch2->read();

	return ret;
}




void neogeo_state::neogeo_main_cpu_banking_init()
{
	m_use_cart_vectors = 0;

	if (m_type != NEOGEO_CD)
	{
		m_banked_cart->init_banks();
	}
}


/*************************************
 *
 *  Audio CPU banking
 *
 *************************************/

u8 neogeo_state::audio_cpu_bank_select_r(offs_t offset)
{
	m_bank_audio_cart[offset & 3]->set_entry(offset >> 8);

	return 0;
}


void neogeo_state::neogeo_audio_cpu_banking_init(int set_entry)
{
	if (m_type == NEOGEO_CD) return;

	int region;
	int bank;
	u8 *rgn;
	u32 address_mask;

	rgn = memregion("audiocpu")->base();

	/* audio bios/cartridge selection */
	m_bank_audio_main->configure_entry(1, memregion("audiocpu")->base());
	if (memregion("audiobios"))
		m_bank_audio_main->configure_entry(0, memregion("audiobios")->base());
	else /* on hardware with no SM1 ROM, the cart ROM is always enabled */
		m_bank_audio_main->configure_entry(0, memregion("audiocpu")->base());

	m_bank_audio_main->set_entry(m_use_cart_audio);

	/* audio banking */
	m_bank_audio_cart[0] = membank("audio_f000");
	m_bank_audio_cart[1] = membank("audio_e000");
	m_bank_audio_cart[2] = membank("audio_c000");
	m_bank_audio_cart[3] = membank("audio_8000");

	address_mask = (memregion("audiocpu")->bytes() - 0x10000 - 1) & 0x3ffff;


	for (region = 0; region < 4; region++)
	{
		for (bank = 0xff; bank >= 0; bank--)
		{
			u32 bank_address = 0x10000 + ((bank << (11 + region)) & address_mask);
			m_bank_audio_cart[region]->configure_entry(bank, &rgn[bank_address]);
		}
	}

	// set initial audio banks - THIS IS A HACK
	// Z80 banking is handled by the NEO-ZMC chip in the cartridge
	// (in later cartridges, by multifunction banking/protection chips that implement the same bank scheme)
	// On the real chip, initial banks are all 0.
	// However, early cartridges with less than 64KB of Z80 code and data don't have ROM banking at all.
	// These initial bank settings are required so non-banked games will work until we identify them
	// and use a different Z80 address map for them.
	m_bank_audio_cart[0]->set_entry(0x1e);
	m_bank_audio_cart[1]->set_entry(0x0e);
	m_bank_audio_cart[2]->set_entry(0x06);
	m_bank_audio_cart[3]->set_entry(0x02);
}



/*************************************
 *
 *  System control register
 *
 *************************************/

void neogeo_state::system_control_w(offs_t offset, u8 data)
{
	u8 bit = (offset >> 3) & 0x01;

	switch (offset & 0x07)
	{
		default:
		case 0x00:
			neogeo_set_screen_shadow(bit);
			break;

		case 0x01:
			if (m_type == NEOGEO_CD)
				printf("NeoCD: write to regular vector change address? %d\n", bit); // what IS going on with "neocdz doubledr" and why do games write here if it's hooked up to nothing?
			else
				m_use_cart_vectors = bit;
			break;

		case 0x05:
			if (m_type == NEOGEO_MVS)
			{
				m_use_cart_audio = bit;
				m_sprgen->neogeo_set_fixed_layer_source(bit);
				m_bank_audio_main->set_entry(m_use_cart_audio);
			}
			break;

		case 0x06:
			if (m_type == NEOGEO_MVS)
				set_save_ram_unlock(bit);
			break;

		case 0x07:
			neogeo_set_palette_bank(bit);
			break;

		case 0x02: // memory card 1: write enable/disable
		case 0x03: // memory card 2: write disable/enable
		case 0x04: // memory card: register select enable/set to normal (what does it mean?)
			logerror("PC: %x  Unmapped system control write.  Offset: %x  Data: %x\n", machine().describe_context(), offset & 0x07, bit);
			break;
	}

	if (LOG_VIDEO_SYSTEM && ((offset & 0x07) != 0x06)) logerror("PC: %x  System control write.  Offset: %x  Data: %x\n", machine().describe_context(), offset & 0x07, bit);
}



/*************************************
 *
 *  LEDs
 *
 *************************************/

void neogeo_state::set_outputs(  )
{
	static const u8 led_map[0x10] =
		{ 0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x58,0x4c,0x62,0x69,0x78,0x00 };

	/* EL */
	m_out_digit[0] = led_map[m_el_value];

	/* LED1 */
	m_out_digit[1] = led_map[m_led1_value >> 4];
	m_out_digit[2] = led_map[m_led1_value & 0x0f];

	/* LED2 */
	m_out_digit[3] = led_map[m_led2_value >> 4];
	m_out_digit[4] = led_map[m_led2_value & 0x0f];
}


void neogeo_state::set_output_latch( u8 data )
{
	/* looks like the LEDs are set on the
	   falling edge */
	u8 falling_bits = m_output_latch & ~data;

	if (falling_bits & 0x08)
		m_el_value = 16 - (m_output_data & 0x0f);

	if (falling_bits & 0x10)
		m_led1_value = ~m_output_data;

	if (falling_bits & 0x20)
		m_led2_value = ~m_output_data;

	if (falling_bits & 0xc7)
		logerror("%s  Unmaped LED write.  Data: %x\n", machine().describe_context(), falling_bits);

	m_output_latch = data;

	set_outputs();
}


void neogeo_state::set_output_data( u8 data )
{
	m_output_data = data;
}



/*************************************
 *
 *  Machine initialization
 *
 *************************************/

void neogeo_state::init_neogeo()
{
	m_banked_cart->install_banks(machine(), m_maincpu, m_region_maincpu->base(), m_region_maincpu->bytes());

	m_sprgen->m_fixed_layer_bank_type = 0;

	// install controllers
	m_maincpu->space(AS_PROGRAM).install_read_handler(0x300000, 0x300001, 0, 0x01ff7e, 0, read16smo_delegate(*this, FUNC(neogeo_state::in0_r)));
	m_maincpu->space(AS_PROGRAM).install_read_handler(0x340000, 0x340001, 0, 0x01fffe, 0, read16smo_delegate(*this, FUNC(neogeo_state::in1_r)));
    m_maincpu->space(AS_PROGRAM).install_read_port(0x300000, 0x300001, 0x01ff7e, "DSW");
	m_maincpu->space(AS_PROGRAM).install_read_port(0x340000, 0x340001, 0x01fffe, "P2");
}


void neogeo_state::neogeo_postload()
{
	m_bank_audio_main->set_entry(m_use_cart_audio);

	if (m_type == NEOGEO_MVS) set_outputs();
}


void neogeo_state::machine_start()
{
	m_out_digit.resolve();
	m_type = NEOGEO_MVS;

	/* set the initial main CPU bank */
	neogeo_main_cpu_banking_init();

	/* set the initial audio CPU ROM banks */
	neogeo_audio_cpu_banking_init(1);

	create_interrupt_timers();

	/* irq levels for MVS / AES */
	m_vblank_level = 1;
	m_raster_level = 2;

	/* start with an IRQ3 - but NOT on a reset */
	m_irq3_pending = 1;

	// enable rtc and serial mode
	m_upd4990a->cs_w(1);
	m_upd4990a->oe_w(1);
	m_upd4990a->c0_w(1);
	m_upd4990a->c1_w(1);
	m_upd4990a->c2_w(1);

	/* register state save */
	save_item(NAME(m_display_position_interrupt_control));
	save_item(NAME(m_display_counter));
	save_item(NAME(m_vblank_interrupt_pending));
	save_item(NAME(m_display_position_interrupt_pending));
	save_item(NAME(m_irq3_pending));
	save_item(NAME(m_audio_cpu_nmi_enabled));
	save_item(NAME(m_audio_cpu_nmi_pending));
	save_item(NAME(m_save_ram_unlocked));
	save_item(NAME(m_output_data));
	save_item(NAME(m_output_latch));
	save_item(NAME(m_el_value));
	save_item(NAME(m_led1_value));
	save_item(NAME(m_led2_value));

	save_item(NAME(m_use_cart_vectors));
	save_item(NAME(m_use_cart_audio));

	machine().save().register_postload(save_prepost_delegate(FUNC(neogeo_state::neogeo_postload), this));

	m_sprgen->set_screen(m_screen);
	m_sprgen->set_sprite_region(m_region_sprites->base(), m_region_sprites->bytes());
	m_sprgen->set_fixed_regions(m_region_fixed->base(), m_region_fixed->bytes(), m_region_fixedbios);
}



/*************************************
 *
 *  Machine reset
 *
 *************************************/

void neogeo_state::machine_reset()
{
	/* reset system control registers */
	for (offs_t offs = 0; offs < 8; offs++)
		system_control_w(offs, 0);

	// disable audiocpu nmi
	m_audio_cpu_nmi_enabled = false;
	m_audio_cpu_nmi_pending = false;
	audio_cpu_check_nmi();

	m_maincpu->reset();

	start_interrupt_timers();

	/* trigger the IRQ3 that was set by MACHINE_START */
	update_interrupts();

	m_recurse = false;

	u16 game = cpuregion[0x109] * 256 + cpuregion[0x108];
	printf("Game number = %04X\n", game);
}

u16 neogeo_state::banked_vectors_r(offs_t offset)
{
	if (!m_use_cart_vectors)
	{
		u16 * bios = (u16 *)memregion("mainbios")->base();
		return bios[offset];
	}
	else
	{
		u16 * game = (u16 *)m_region_maincpu->base();
		return game[offset];
	}

}

u16 neogeo_state::neogeo_slot_rom_low_r()
{
	return 0;
}

u16 neogeo_state::neogeo_slot_rom_low_vectors_r(offs_t offset)
{
	if (!m_use_cart_vectors)
	{
		u16 * bios = (u16 *)memregion("mainbios")->base();
		return bios[offset];
	}
	else
	{
		return 0;
	}

}

/*************************************
 *
 *  Main CPU memory handlers
 *
 *************************************/

void neogeo_state::neogeo_main_map(address_map &map)
{
	map(0x100000,0x10ffff).mirror(0x0f0000).ram();
	/* some games have protection devices in the 0x200000 region, it appears to map to cart space, not surprising, the ROM is read here too */
	map(0x300080,0x300081).mirror(0x01ff7e).portr("TEST");
	map(0x300000,0x300001).mirror(0x01fffe).w("watchdog",FUNC(watchdog_timer_device::reset_w)).umask16(0x00ff);
	map(0x320000,0x320001).mirror(0x01fffe).portr("AUDIO/COIN");
	map(0x320000,0x320001).mirror(0x01fffe).w(FUNC(neogeo_state::audio_command_w)).umask16(0xff00);
	map(0x360000,0x37ffff).r(FUNC(neogeo_state::neogeo_unmapped_r));
	map(0x380000,0x380001).mirror(0x01fffe).portr("SYSTEM");
	map(0x380000,0x38007f).mirror(0x01ff80).w(FUNC(neogeo_state::io_control_w)).umask16(0x00ff);
	map(0x3a0000,0x3a001f).mirror(0x01ffe0).r(FUNC(neogeo_state::neogeo_unmapped_r));
	map(0x3a0000,0x3a001f).mirror(0x01ffe0).w(FUNC(neogeo_state::system_control_w)).umask16(0x00ff);
	map(0x3c0000,0x3c0007).mirror(0x01fff8).r(FUNC(neogeo_state::neogeo_video_register_r));
	map(0x3c0000,0x3c000f).mirror(0x01fff0).w(FUNC(neogeo_state::neogeo_video_register_w));
	map(0x3e0000,0x3fffff).r(FUNC(neogeo_state::neogeo_unmapped_r));
	map(0x400000,0x401fff).mirror(0x3fe000).rw(FUNC(neogeo_state::neogeo_paletteram_r),FUNC(neogeo_state::neogeo_paletteram_w));
	map(0x800000,0x800fff).rw(FUNC(neogeo_state::memcard_r),FUNC(neogeo_state::memcard_w));
	map(0xc00000,0xc1ffff).mirror(0x0e0000).rom().region("mainbios",0);
	map(0xd00000,0xd0ffff).mirror(0x0f0000).ram().w(FUNC(neogeo_state::save_ram_w)).share("saveram");
	map(0xe00000,0xffffff).r(FUNC(neogeo_state::neogeo_unmapped_r));
}


void neogeo_state::main_map_slot(address_map &map)
{
	neogeo_main_map(map);
	map(0x000000,0x00007f).r(FUNC(neogeo_state::neogeo_slot_rom_low_vectors_r));
	map(0x000080,0x0fffff).r(FUNC(neogeo_state::neogeo_slot_rom_low_r));
	map(0x200000,0x2fffff).bankr("cartridge");
//  AM_RANGE(0x2ffff0, 0x2fffff) AM_WRITE(main_cpu_bank_select_w)
}

/*************************************
 *
 *  Audio CPU memory handlers
 *
 *************************************/

void neogeo_state::audio_map(address_map &map)
{
	map(0x0000,0x7fff).bankr("audio_main");
	map(0x8000,0xbfff).bankr("audio_8000");
	map(0xc000,0xdfff).bankr("audio_c000");
	map(0xe000,0xefff).bankr("audio_e000");
	map(0xf000,0xf7ff).bankr("audio_f000");
	map(0xf800,0xffff).ram();
}

/*************************************
 *
 *  Audio CPU port handlers
 *
 *************************************/

void neogeo_state::audio_io_map(address_map &map)
{
	map(0x00,0x00).mirror(0xff00).r(FUNC(neogeo_state::audio_command_r)).w("soundlatch",FUNC(generic_latch_8_device::clear_w));
	map(0x04,0x07).mirror(0xff00).rw("ymsnd",FUNC(ym2610_device::read),FUNC(ym2610_device::write));
	map(0x08,0x08).mirror(0xff00).select(0x0010).w(FUNC(neogeo_state::audio_cpu_enable_nmi_w));
	map(0x08,0x0b).mirror(0x00f0).select(0xff00).r(FUNC(neogeo_state::audio_cpu_bank_select_r));
	map(0x0c,0x0c).mirror(0xff00).w("soundlatch2",FUNC(generic_latch_8_device::write));
}

/*************************************
 *
 *  Standard Neo-Geo DIPs and
 *  input port definition
 *
 *************************************/

INPUT_PORTS_START( neogeo )
	PORT_START("DSW")
	PORT_DIPNAME( 0x01, 0x01, "Setting Mode" ) PORT_DIPLOCATION("SW:1")
	PORT_DIPSETTING(    0x01, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x02, 0x00, DEF_STR( Cabinet ) ) PORT_DIPLOCATION("SW:2")
	PORT_DIPSETTING(    0x00, DEF_STR( Normal ) )
	PORT_DIPSETTING(    0x02, "VS Mode" )
	PORT_DIPNAME( 0x04, 0x04, DEF_STR( Controller ) ) PORT_DIPLOCATION("SW:3")
	PORT_DIPSETTING(    0x04, DEF_STR( Joystick ) )
	PORT_DIPSETTING(    0x00, "Mahjong Panel" )
	PORT_DIPNAME( 0x18, 0x18, "COMM Setting (Cabinet No.)" ) PORT_DIPLOCATION("SW:4,5")
	PORT_DIPSETTING(    0x18, "1" )
	PORT_DIPSETTING(    0x10, "2" )
	PORT_DIPSETTING(    0x08, "3" )
	PORT_DIPSETTING(    0x00, "4" )
	PORT_DIPNAME( 0x20, 0x20, "COMM Setting (Link Enable)" ) PORT_DIPLOCATION("SW:6")
	PORT_DIPSETTING(    0x20, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x40, 0x00, DEF_STR( Free_Play ) ) PORT_DIPLOCATION("SW:7")
	PORT_DIPSETTING(    0x00, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x40, DEF_STR( On ) )
	PORT_DIPNAME( 0x80, 0x80, "Freeze" ) PORT_DIPLOCATION("SW:8")
	PORT_DIPSETTING(    0x80, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_CONDITION("DSW", 0xF000, NOTEQUALS, 0x0100)
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_CONDITION("DSW", 0xF000, NOTEQUALS, 0x0200)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_CONDITION("DSW", 0xF000, NOTEQUALS, 0x0400)
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_CONDITION("DSW", 0xF000, NOTEQUALS, 0x0800)
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_NAME("@P1 Attack @Button1") PORT_CONDITION("DSW", 0xF000, NOTEQUALS, 0x1000)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_NAME("@P1 Jump @Button2") PORT_CONDITION("DSW", 0xF000, NOTEQUALS, 0x2000)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_NAME("@P1 Bomb @Button3") PORT_CONDITION("DSW", 0xF000, NOTEQUALS, 0x4000)
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_BUTTON4 ) PORT_NAME("@P1 It Has No Use @Button4") PORT_CONDITION("DSW", 0xF000, NOTEQUALS, 0x8000)

	PORT_START("P2")
	PORT_BIT( 0x00ff, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_PLAYER(2) PORT_CONDITION("P2", 0xF000, NOTEQUALS, 0x0100)
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_PLAYER(2) PORT_CONDITION("P2", 0xF000, NOTEQUALS, 0x0200)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_PLAYER(2) PORT_CONDITION("P2", 0xF000, NOTEQUALS, 0x0400)
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_PLAYER(2) PORT_CONDITION("P2", 0xF000, NOTEQUALS, 0x0800)
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(2) PORT_NAME("@P2 Attack @Button1") PORT_CONDITION("P2", 0xF000, NOTEQUALS, 0x1000)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(2) PORT_NAME("@P2 Jump @Button2") PORT_CONDITION("P2", 0xF000, NOTEQUALS, 0x2000)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(2) PORT_NAME("@P2 Bomb @Button3") PORT_CONDITION("P2", 0xF000, NOTEQUALS, 0x4000)
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_BUTTON4 ) PORT_PLAYER(2) PORT_NAME("@P2 It Has No Use @Button4") PORT_CONDITION("P2", 0xF000, NOTEQUALS, 0x8000)

	PORT_START("SYSTEM")
	PORT_BIT( 0x00ff, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_START1 )
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("Next Game") PORT_CODE(KEYCODE_3)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_START2 )
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("Previous Game") PORT_CODE(KEYCODE_4)
	PORT_BIT( 0x7000, IP_ACTIVE_HIGH, IPT_CUSTOM ) PORT_CUSTOM_MEMBER(neogeo_state, get_memcard_status)
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_CUSTOM ) /* Hardware type (AES=0, MVS=1). Some games check this and show a piracy warning screen if the hardware and BIOS don't match */

	PORT_START("AUDIO/COIN")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_COIN1 )
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_COIN2 )
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_SERVICE1 )
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_COIN3 ) /* What is this? "us-e" BIOS uses it as a coin input; Universe BIOS uses it to detect MVS or AES hardware */
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_COIN4 ) /* What is this? "us-e" BIOS uses it as a coin input; Universe BIOS uses it to detect MVS or AES hardware */
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_CUSTOM ) /* what is this? When ACTIVE_HIGH + IN4 bit 6 ACTIVE_LOW MVS-4 slot is detected */
	PORT_BIT( 0x0040, IP_ACTIVE_HIGH, IPT_CUSTOM ) PORT_READ_LINE_DEVICE_MEMBER("upd4990a", upd1990a_device, tp_r)
	PORT_BIT( 0x0080, IP_ACTIVE_HIGH, IPT_CUSTOM ) PORT_READ_LINE_DEVICE_MEMBER("upd4990a", upd1990a_device, data_out_r)
	PORT_BIT( 0xff00, IP_ACTIVE_HIGH, IPT_CUSTOM ) PORT_CUSTOM_MEMBER(neogeo_state,get_audio_result)

	PORT_START("TEST")
	PORT_BIT( 0x003f, IP_ACTIVE_HIGH, IPT_UNUSED )
	PORT_BIT( 0x0040, IP_ACTIVE_HIGH, IPT_CUSTOM ) /* what is this? If ACTIVE_LOW, MVS-6 slot detected, when ACTIVE_HIGH MVS-1 slot (AES) detected */
	PORT_SERVICE_NO_TOGGLE( 0x0080, IP_ACTIVE_LOW )
	PORT_BIT( 0xff00, IP_ACTIVE_LOW, IPT_UNUSED )
INPUT_PORTS_END

static INPUT_PORTS_START( neogeo_6slot )
	PORT_INCLUDE( neogeo )

	PORT_MODIFY("TEST")
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_CUSTOM )
INPUT_PORTS_END


// Fixed
const gfx_layout charlayout =
{
	8,8,			/* 8 x 8 chars */
	RGN_FRAC(1,1),
	4,				/* 4 bits per pixel */
	{ 0, 1, 2, 3 },    /* planes are packed in a nibble */
	{ 33*4, 32*4, 49*4, 48*4, 1*4, 0*4, 17*4, 16*4 },
	{ 0*8, 1*8, 2*8, 3*8, 4*8, 5*8, 6*8, 7*8 },
	32*8	/* 32 bytes per char */
};

// Sprites
const gfx_layout tilelayout =
{
	16,16,	 /* 16*16 sprites */
	RGN_FRAC(1,1),
	4,
	{ GFX_RAW },
	{ 0 },		/* org displacement */
	{ 8*8 },	/* line modulo */
	128*8		/* char modulo */
};

GFXDECODE_START( gfx_neogeo )
	GFXDECODE_ENTRY( "fixed",     0x0000, charlayout, 0, 0x1fff )
	GFXDECODE_ENTRY( "fixedbios", 0x0000, charlayout, 0, 0x1fff )
	//GFXDECODE_ENTRY( "sprites",   0x0000, tilelayout, 0, 0x1fff )  // not working
GFXDECODE_END


/*************************************
 *
 *  Machine driver
 *
 *************************************/

void neogeo_state::neogeo_base(machine_config &config)
{
	/* basic machine hardware */
	M68000(config, m_maincpu, NEOGEO_MAIN_CPU_CLOCK);
	m_maincpu->set_addrmap(AS_PROGRAM, &neogeo_state::neogeo_main_map);

	Z80(config, m_audiocpu, NEOGEO_AUDIO_CPU_CLOCK);
	m_audiocpu->set_addrmap(AS_PROGRAM, &neogeo_state::audio_map);
	m_audiocpu->set_addrmap(AS_IO, &neogeo_state::audio_io_map);

	/* video hardware */
	config.set_default_layout(layout_neogeo);

	SCREEN(config, m_screen, SCREEN_TYPE_RASTER);
	m_screen->set_raw(NEOGEO_PIXEL_CLOCK, NEOGEO_HTOTAL, NEOGEO_HBEND, NEOGEO_HBSTART, NEOGEO_VTOTAL, NEOGEO_VBEND, NEOGEO_VBSTART);
	m_screen->set_screen_update(FUNC(neogeo_state::screen_update_neogeo));

	GFXDECODE(config, "gfxdecode", m_palette, gfx_neogeo);
	/* 4096 colors * two banks * normal and shadow */
	PALETTE(config, m_palette, palette_device::BLACK, 4096*2*2);

	NEOGEO_SPRITE(config, m_sprgen, 0).set_screen(m_screen);

	/* audio hardware */
	SPEAKER(config, "lspeaker").front_left();
	SPEAKER(config, "rspeaker").front_right();

	GENERIC_LATCH_8(config, m_soundlatch);
	GENERIC_LATCH_8(config, m_soundlatch2);

	YM2610(config, m_ym, NEOGEO_YM2610_CLOCK);
	m_ym->irq_handler().set_inputline(m_audiocpu, 0);
	m_ym->add_route(0, "lspeaker", 0.28);
	m_ym->add_route(0, "rspeaker", 0.28);
	m_ym->add_route(1, "lspeaker", 0.98);
	m_ym->add_route(2, "rspeaker", 0.98);
	NEOGEO_BANKED_CART(config, "banked_cart");
}

void neogeo_state::neogeo_arcade(machine_config &config)
{
	neogeo_base(config);
	WATCHDOG_TIMER(config, "watchdog").set_time(attotime::from_ticks(3244030, NEOGEO_MASTER_CLOCK));
	UPD4990A(config, m_upd4990a);
	NVRAM(config, "saveram", nvram_device::DEFAULT_ALL_0);
	NG_MEMCARD(config, "memcard");
}

void neogeo_state::mvs(machine_config &config)
{
	neogeo_arcade(config);
	m_maincpu->set_addrmap(AS_PROGRAM, &neogeo_state::main_map_slot);

	NEOGEO_CTRL_EDGE_CONNECTOR(config, m_edge, neogeo_arc_edge, "joy", false);

	NEOGEO_CONTROL_PORT(config, "ctrl1", neogeo_arc_pin15, nullptr, false);
	NEOGEO_CONTROL_PORT(config, "ctrl2", neogeo_arc_pin15, nullptr, false);
}

void neogeo_state::main_map_noslot(address_map &map)
{
	neogeo_main_map(map);
	map(0x000000,0x00007f).r(FUNC(neogeo_state::banked_vectors_r));
	map(0x000080,0x0fffff).rom();
}

void neogeo_state::neogeo_noslot(machine_config &config)
{
	neogeo_arcade(config); // no slot config (legacy mame)
	m_maincpu->set_addrmap(AS_PROGRAM, &neogeo_state::main_map_noslot);

	//joystick controller
	NEOGEO_CTRL_EDGE_CONNECTOR(config, m_edge, neogeo_arc_edge, "joy", true);

	//no mahjong controller
	NEOGEO_CONTROL_PORT(config, "ctrl1", neogeo_arc_pin15, nullptr, true);
	NEOGEO_CONTROL_PORT(config, "ctrl2", neogeo_arc_pin15, nullptr, true);

	MSLUGX_PROT(config, "mslugx_prot");
	SMA_PROT(config, "sma_prot");
	CMC_PROT(config, "cmc_prot");
	PCM2_PROT(config, "pcm2_prot");
	PVC_PROT(config, "pvc_prot");
	NGBOOTLEG_PROT(config, "bootleg_prot");
	KOF2002_PROT(config, "kof2002_prot");
	FATFURY2_PROT(config, "fatfury2_prot");
	KOF98_PROT(config, "kof98_prot");
	SBP_PROT(config, "sbp_prot");
}

/*********************************************** non-carts */

void neogeo_state::install_banked_bios()
{
	m_maincpu->space(AS_PROGRAM).install_read_bank(0xc00000, 0xc1ffff, 0x0e0000, "bankedbios");
	membank("bankedbios")->configure_entries(0, 2, memregion("mainbios")->base(), 0x20000);
	membank("bankedbios")->set_entry(1);
}

INPUT_CHANGED_MEMBER(neogeo_state::select_bios)
{
	membank("bankedbios")->set_entry(newval ? 0 : 1);
}

/* dummy entry for the dummy bios driver */
ROM_START( neogeo )
	NEOGEO_BIOS

	ROM_REGION( 0x100000, "maincpu", ROMREGION_ERASEFF )

	ROM_REGION( 0x20000, "audiobios", 0 )
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) )

	ROM_REGION( 0x50000, "audiocpu", 0 )
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) )

	ROM_Y_ZOOM

	ROM_REGION( 0x20000, "fixed", ROMREGION_ERASEFF )

	ROM_REGION( 0x20000, "fixedbios", 0 )
	ROM_LOAD( "sfix.sfix", 0x000000, 0x20000, CRC(c2ea0cfd) SHA1(fd4a618cdcdbf849374f0a50dd8efe9dbab706c3) )

	ROM_REGION( 0x100000, "sprites", ROMREGION_ERASEFF )
ROM_END


/*    YEAR  NAME        PARENT    MACHINE   INPUT            CLASS         INIT    */
GAME( 1990, neogeo,     0,        mvs,      neogeo_6slot,   neogeo_state, init_neogeo,  ROT0, "SNK", "Neo-Geo", MACHINE_IS_BIOS_ROOT | MACHINE_SUPPORTS_SAVE )

/***********************************************************************************************************************************
 Old Documentation PSMAME PLUS (Metal Slug Forever Special Edition Final):
 
 Metal Slug 2:
  A definitive solution has been found in the hacks of roms called Version Hybrid Bullets, 
  which has been included in HBMAME around 8 years ago, this rom hacks have a very serious problem 
  that generates a crash in mission 2 / phase 2 and phase 3 , its way of manifesting is to make the 
  torso disappear from the body that if the button is pressed shooting, the game crashes immediately 
  and will restart the game from scratch and will not allow you to continue playing at level 2, 
  now you can skip level 2 playing Normally, the mission will be finished at the beginning of level 2 
  of phase 2 and phase 3, the rest of the levels work normally, it will no longer be an impediment to 
  continue playing until the end of the game.
  
 Metal Slug 3:
  I have been working very hard to optimize it and to adapt it with the emulator 
  the Ghost Wu Zuoma version, which the original version is 100% incompatible with this 
  emulator, because it causes the emulator to freeze completely when the players have Contact 
  with any enemy and one by quickly pressing the command A + B generates random items and in 
  this way the game crashes. I have managed to disable this command so that you do not cause 
  this case of fatal accident or the discomfort of one when one is playing through the game.
  Command disabled in file 256.p1:
  00025DA0 // 00 00 9C 00 [B9 4E 0F 00 30 B0] EE 08 03 00 9B 00
  00026370 // [B9 4E 0F 00 B6 AF] 2E 08 07 00 5B 00 00 66 08 00
  00026380 // [B9 4E 0F 00 86 B0] 00 60 AC 00 00 70 2E 10 58 00
  000271C0 // AE 08 07 00 15 00 [B9 4E 0F 00 60 AF] 2E 08 07 00

  The Random Enemies Resetting Version has also been optimized 
  and adapted correctly to the emulator, which the original version is 50% incompatible 
  with this emulator, which caused the crash of level 3, of the stages of the confrontation with 
  the boss of the level called Jupiter King, which one of the boss's action is to attack you with 
  a rocket and hit it on the ground at the moment two or more lobster-shaped enemies [The Huge Logust]
  appear at that same moment the game crashes and restarts from scratch. I have managed to disable 
  this command like this to be able to prevent the enemy lobster [The Huge Logust] from appearing 
  at level 3 of the boss stage, so this way it will no longer cause this fatal accident or discomfort
  when one is playing through the match.
  Command disabled in file 256.p1:
  000481C0 //02 00 A2 C8 3C 00 01 00 [B9 4E 0F 00 90 DA] 6E 4A
  
  Another bug in the roms has been fixed, which is generated by this emulator when playing, since it 
  is incompatible with a certain action or command that the character is going to take. The problem 
  that caused suddenly when one pressed the command START + D, quickly causes a crash in the game is 
  forced to restart all or one of the worst case that the screen freezes.
  Command disabled in file 256.p1: 
  00003C20 //CF 51 FC FF 75 4E [B9 4E 0F 00 10 A2] 00 46 00 02
  
  At last a bugs that caused it with the HBMAME / PSMAMEPLUS emulator has been corrected, it is that 
  it prevented you from being able to play the most random scenarios it has, which this problem does 
  not cause in the FB Alpha emulator.
  How is this?
  It is established by three random scenarios, interspersing the scenarios of each level that one will be playing.
  The problem that this causes is that the rom starts with two random scenarios instead of three, 
  apart from when the game starts, 99% will start one of the random scenarios, 1% the second of the random scenarios 
  and 0% for the third random scenarios.
  For this, the roms have been corrected, now either by separating by each random scenario it is converted into an individual roms:
  Random Enemies Resetting Version # 1
  Random Enemies Resetting Version # 2
  Random Enemies Resetting Version # 3 
  
  030F360//[CC 04 2F 01 00 00 00 00 00 00 01 00]14 08 00 0C [Level 4-2]
  030F360// 74 03 5C 00 84 03 00 00 00 00 01 00 14 08 00 0C [Replace To Correct]

  Crashes for killing a cursed small crab has settled with new command without replacing ID.
  0311BB0// 30 00 C4 02 00 00 01 00 78 00 01 00 00 00 0E 09 [Level 4-9]
  0311BB0// 30 00 C4 02 00 00 00 00 00 00 00 00 00 00 0E 09 [Replace To Correct]
  
  0343A40// A0 8D 10 08 0B 01 E0 FF 38 00 A4 02 00 00 78 00 68 00
  0343A40// A0 8D 10 08 0B 01 E0 FF 38 00 A4 02 00 00 00 00 00 00 [Replace To Correct]
  
  Enemy spawns that are floating in the air ship when destroyed crashes immediately, fixed replaced with piranha ID.
  03894A0// 2C 01 14 08 02 07 40 01 [60 00 A0 00 40 00 2C 00
  03894B0// FA 00 18 01 00 00] 14 08 02 07 40 01 30 00 EC 01

  03894A0// 2C 01 14 08 02 07 40 01 [30 00 EC 01 01 FF FF 00 [Replace To Correct]
  03894B0// 40 00 4A 00 2C 01] 14 08 02 07 40 01 30 00 EC 01 
  
  2021-09-17 "Random Enemies Resetting Version"
  It seems that this roms is very troublesome for this emulator, the problems do not stop.
  It was discovered at the last minute that the neutral path of the three random scenarios, from level 4-8 the random 
  spawning cycle appears a yellowish green crab to the left "does not always appear" if it kills them it crashes 
  the game of Instantaneously, because of this event it has been decided to put the red label that the machine 
  that does not work correctly to all the roms that are related. 

  2021-09-24 "Random Enemies Resetting Version 2018-03-01"
  Fixed crash at level 5-3 
  0007FD30 //5D 00 [B9 4E 0F 00 90 C3] 3C 3A 08 00 BA 4E 0A 17
  Fixed crash at level 5-F 
  0009FE50//54 EE 00 61 B0 EE 7C 3D 00 20 6A 00 [B9 4E 0F 00
  0009FE60//90 DB] 00 61 3A 00 2D 30 46 6D 40 04 0C 00 00 64
  0009FE80//10 00 6E 42 6A 00 00 61 A4 FD [B9 4E 0F 00 B0 FA]

  2023-09-01 "Random Enemies Resetting Version"
  Crash occurs in level 3-2 at the end of the level.
  30A820//04 02 00 00 00 00 00 00 00 00 01 00

  Metal Slug 3 Store Version 2017-12-16
  Another bug in the roms has been fixed, which is generated by this emulator when playing, since it 
  is incompatible with a certain action or command that the character is going to take. The problem 
  that caused suddenly when one pressed the command START + D, quickly causes a crash in the game is 
  forced to restart all or one of the worst case that the screen freezes.
  Command disabled in file 256.p1: 
  00003C20 //CF 51 FC FF 75 4E [B9 4E 0F 00 10 A2] 00 46 00 02

  Metal Slug 3 Enemy Soldiers Reset 2019-01-02
  CRC(64ae37fc) SHA1(9a82b407f29986138a109d4620fc0a113049047a)
  Fixed a crash in level 3-3, the "Ball Shooting Tank" ID was misplaced in the command memory.
  03D2450//90 01 [01 00 01 00 78 00 00 00] // Error
  03D2450//90 01 00 00 00 00 F0 00 04 01 // Fix
  
  Metal Slug 3 Onimusha Samanosuke 2018-05-29
  The roms hack has conflict causes a bug in which the player does not die causes a cycle of infinite fall, 
  in space travel when changing weapons with the D key.
  
 Metal Slug 4
  I have been working very hard to optimize and adapt it with the emulator the Mslug 4 
  roms version Last Bullet 2017-07-27, which caused the emulator to freeze completely when 
  players quickly press the START + D command. I have managed to disable it this command so 
  that it does not cause this fatal accident case or one's discomfort when playing the game.
  Command disabled in file 256.p1:
  0000FBF0 //[B9 4E 0E 00 E0 0A] 00 46 00 02 0F 00 2D 12 50 E4

  I have been working very hard to optimize and adapt it with the emulator the Mslug 4 
  roms version Last Bullet Removal Of Body Armor 2020-09-16, which caused the emulator to freeze completely when 
  players quickly press the START + D command. I have managed to disable it this command so 
  that it does not cause this fatal accident case or one's discomfort when playing the game.
  Command disabled in file 256.p1:
  00001E50 //92 80 7C 3B 00 00 D2 DB B9 4E 00 00 [F0 FB] B9 4E

  This version of the Metal Slug 4 20th Anniversary Edition And Metal Slug 4 Longest Fight, is optimized to work correctly 
  with the emulator by disabling a command that caused immortality to all the enemies 
  that are inside the screens, thus making the game unusable. The modification is 
  generated in the .P1 file: 
  00007DD0 //[B9 4E 21 00 C8 BF] 00 62 18 00 EA 08 07 00 5B 00 
 ************************************************************************************************************************************/

/************************************************************************************************************************************
  !!Game specific Olds Rom_Fill definitions!!

#define MSLUG_AUTOFIRE_MVS_FILL \
	ROM_FILL(0x25081,1,0x03)

#define MSLUG_FLAMESHOT_MVS_FILL \
	ROM_FILL(0x32FC1,1,0x02) \
	ROM_FILL(0x33E07,1,0x02) \
	ROM_FILL(0x33E0C,1,0x03) \
	ROM_FILL(0x33E0D,1,0xE7)

#define MSLUG_HEAVYMACHINEGUN_MVS_FILL \
	ROM_FILL(0x32FC1,1,0x04) \
	ROM_FILL(0x33E07,1,0x04) \
	ROM_FILL(0x33E0C,1,0x03) \
	ROM_FILL(0x33E0D,1,0xE7)

#define MSLUG_ROCKETLAUNCHER_MVS_FILL \
	ROM_FILL(0x32FC1,1,0x03) \
	ROM_FILL(0x33E07,1,0x03) \
	ROM_FILL(0x33E0C,1,0x03) \
	ROM_FILL(0x33E0D,1,0xE7)

#define MSLUG_SHOTGUN_MVS_FILL \
	ROM_FILL(0x32FC1,1,0x01) \
	ROM_FILL(0x33E07,1,0x01) \
	ROM_FILL(0x33E0C,1,0x03) \
	ROM_FILL(0x33E0D,1,0xE7)

#define MSLUG2_HELICOPTERSHOTELECTRICSHOT_MVS_FILL 
    ROM_FILL(0xC6C90,1,0x01)\
	ROM_FILL(0xC6C91,1,0x69)\
	ROM_FILL(0xC6C9F,1,0x0A)\
	ROM_FILL(0xC6CA0,1,0x74)\
	ROM_FILL(0xC6CA1,1,0x22)\
	ROM_FILL(0xC6CE7,1,0x0A)\
	ROM_FILL(0xC6CE8,1,0x47)\
	ROM_FILL(0xC6CE9,1,0xD0)

#define MSLUG2_FLAMESHOT_MVS_FILL \
	ROM_FILL(0x92940,1,0x4E) \
	ROM_FILL(0x92941,1,0x71) \
	ROM_FILL(0x92942,1,0x4E) \
	ROM_FILL(0x92943,1,0x71) \
	ROM_FILL(0x929B7,1,0x02) \
	ROM_FILL(0x92A3B,1,0x02) \
	ROM_FILL(0x92B5C,1,0x4E) \
	ROM_FILL(0x92B5D,1,0x71) \
	ROM_FILL(0x92B5E,1,0x4E) \
	ROM_FILL(0x92B5F,1,0x71) \
	ROM_FILL(0x94A28,1,0x01) \
	ROM_FILL(0x94AFF,1,0x02)

#define MSLUG2_HEAVYMACHINEGUN_MVS_FILL \
	ROM_FILL(0x92940,1,0x4E) \
	ROM_FILL(0x92941,1,0x71) \
	ROM_FILL(0x92942,1,0x4E) \
	ROM_FILL(0x92943,1,0x71) \
	ROM_FILL(0x929B7,1,0x02) \
	ROM_FILL(0x92A3B,1,0x03) \
	ROM_FILL(0x92B5C,1,0x4E) \
	ROM_FILL(0x92B5D,1,0x71) \
	ROM_FILL(0x92B5E,1,0x4E) \
	ROM_FILL(0x92B5F,1,0x71) \
	ROM_FILL(0x94A28,1,0x01) \
	ROM_FILL(0x94AFF,1,0x03)

#define MSLUG2_LASER_MVS_FILL \
	ROM_FILL(0x92940,1,0x4E) \
	ROM_FILL(0x92941,1,0x71) \
	ROM_FILL(0x92942,1,0x4E) \
	ROM_FILL(0x92943,1,0x71) \
	ROM_FILL(0x929B7,1,0x02) \
	ROM_FILL(0x92A3B,1,0x04) \
	ROM_FILL(0x92B5C,1,0x4E) \
	ROM_FILL(0x92B5D,1,0x71) \
	ROM_FILL(0x92B5E,1,0x4E) \
	ROM_FILL(0x92B5F,1,0x71) \
	ROM_FILL(0x94A28,1,0x01) \
	ROM_FILL(0x94AFF,1,0x04)

#define MSLUG2_ROCKETLAUNCHER_MVS_FILL \
	ROM_FILL(0x92940,1,0x4E) \
	ROM_FILL(0x92941,1,0x71) \
	ROM_FILL(0x92942,1,0x4E) \
	ROM_FILL(0x92943,1,0x71) \
	ROM_FILL(0x929B7,1,0x02) \
	ROM_FILL(0x92A3B,1,0x01) \
	ROM_FILL(0x92B5C,1,0x4E) \
	ROM_FILL(0x92B5D,1,0x71) \
	ROM_FILL(0x92B5E,1,0x4E) \
	ROM_FILL(0x92B5F,1,0x71) \
	ROM_FILL(0x94A28,1,0x01) \
	ROM_FILL(0x94AFF,1,0x01)

#define MSLUG2_SHOTGUN_MVS_FILL \
	ROM_FILL(0x92940,1,0x4E) \
	ROM_FILL(0x92941,1,0x71) \
	ROM_FILL(0x92942,1,0x4E) \
	ROM_FILL(0x92943,1,0x71) \
	ROM_FILL(0x929B7,1,0x02) \
	ROM_FILL(0x92A3B,1,0x00) \
	ROM_FILL(0x92B5C,1,0x4E) \
	ROM_FILL(0x92B5D,1,0x71) \
	ROM_FILL(0x92B5E,1,0x4E) \
	ROM_FILL(0x92B5F,1,0x71) \
	ROM_FILL(0x94A28,1,0x01) \
	ROM_FILL(0x94AFF,1,0x00)

#define MSLUG3_DELETESCENEGOTOSPACES_MVS_FILL \
    ROM_FILL(0xDF1FB,1,0x06)

#define MSLUG3_AUTOFIRE_MVS_FILL \
	ROM_FILL(0x3D03,1,0x00)

#define MSLUG3H_MUMMYMOVEMENT_MODS_FILL \
    ROM_FILL(0x27EB2,1,0x42)\
	ROM_FILL(0x27EB3,1,0x2E)\
	ROM_FILL(0x27EB4,1,0x00)\
	ROM_FILL(0x27EB5,1,0x72)

#define MSLUG3_BSTONE_MVS_FILL \
	ROM_FILL(0x2170D,1,0x03)

#define MSLUG3_BFLAMESHOT_MVS_FILL \
	ROM_FILL(0x21719,1,0x09) \
	ROM_FILL(0x21C2A,1,0x09)

#define MSLUG3_BHEAVYMACHINEGUN_MVS_FILL \
	ROM_FILL(0x21719,1,0x0A) \
	ROM_FILL(0x21C2A,1,0x0A)

#define MSLUG3_BLASER_MVS_FILL \
	ROM_FILL(0x21719,1,0x0B) \
	ROM_FILL(0x21C2A,1,0x0B)

#define MSLUG3_BROCKETLAUNCHER_MVS_FILL \
	ROM_FILL(0x21719,1,0x08) \
	ROM_FILL(0x21C2A,1,0x08)

#define MSLUG3_BSHOTGUN_MVS_FILL \
	ROM_FILL(0x21719,1,0x07) \
	ROM_FILL(0x21C2A,1,0x07)

#define MSLUG3_CANNON_MVS_FILL \
	ROM_FILL(0x21719,1,0x01) \
	ROM_FILL(0x21C2A,1,0x01)

#define MSLUG3_SATELLITE_MVS_FILL \
	ROM_FILL(0x21719,1,0x10) \
	ROM_FILL(0x21C2A,1,0x10)

#define MSLUG3_SUPERGRENADE_MVS_FILL \
	ROM_FILL(0x21719,1,0x0F) \
	ROM_FILL(0x21C2A,1,0x0F)

#define MSLUG3_ENEMYCHASER_MVS_FILL \
	ROM_FILL(0x21719,1,0x0C) \
	ROM_FILL(0x21C2A,1,0x0C)

#define MSLUG4_AUTOFIRE_MVS_FILL \
	ROM_FILL(0xFCCD,1,0x00)

#define MSLUG4_SKIPLEVEL6_1_MVS_FILL \
	ROM_FILL(0xEABCB,1,0x03)

#define MSLUG4_BSTONE_MVS_FILL \
	ROM_FILL(0xC4625,1,0x03)

#define MSLUG4_BFLAMESHOT_MVS_FILL \
	ROM_FILL(0xC4631,1,0x09) \
	ROM_FILL(0xC4C7C,1,0x09)

#define MSLUG4_BHEAVYMACHINEGUN_MVS_FILL \
	ROM_FILL(0xC4631,1,0x0A) \
	ROM_FILL(0xC4C7C,1,0x0A)

#define MSLUG4_BLASER_MVS_FILL \
	ROM_FILL(0xC4631,1,0x0B) \
	ROM_FILL(0xC4C7C,1,0x0B)

#define MSLUG4_BROCKETLAUNCHER_MVS_FILL \
	ROM_FILL(0xC4631,1,0x08) \
	ROM_FILL(0xC4C7C,1,0x08)

#define MSLUG4_BSHOTGUN_MVS_FILL \
	ROM_FILL(0xC4631,1,0x07) \
	ROM_FILL(0xC4C7C,1,0x07)

#define MSLUG4_CANNON_MVS_FILL \
	ROM_FILL(0xC4631,1,0x01) \
	ROM_FILL(0xC4C7C,1,0x01)

#define MSLUG4_SATELLITE_MVS_FILL \
	ROM_FILL(0xC4631,1,0x10) \
	ROM_FILL(0xC4C7C,1,0x10)

#define MSLUG4_SUPERGRENADE_MVS_FILL \
	ROM_FILL(0xC4631,1,0x0F) \
	ROM_FILL(0xC4C7C,1,0x0F)

#define MSLUG4_DUALMACHINEGUN_MVS_FILL \
	ROM_FILL(0xC4631,1,0x12) \
	ROM_FILL(0xC4C7C,1,0x12)

#define MSLUG4_ENEMYCHASER_MVS_FILL \
	ROM_FILL(0xC4631,1,0x0C) \
	ROM_FILL(0xC4C7C,1,0x0C)

#define MSLUG5H_BSTONE_MVS_FILL \
	ROM_FILL(0x1BD67,1,0x03)

#define MSLUG5H_BFLAMESHOT_MVS_FILL \
	ROM_FILL(0x1BD73,1,0x09) \
	ROM_FILL(0x1C298,1,0x09)

#define MSLUG5H_BHEAVYMACHINEGUN_MVS_FILL \
	ROM_FILL(0x1BD73,1,0x0A) \
	ROM_FILL(0x1C298,1,0x0A)

#define MSLUG5H_BLASER_MVS_FILL \
	ROM_FILL(0x1BD73,1,0x0B) \
	ROM_FILL(0x1C298,1,0x0B)

#define MSLUG5H_BROCKETLAUNCHER_MVS_FILL \
	ROM_FILL(0x1BD73,1,0x08) \
	ROM_FILL(0x1C298,1,0x08)

#define MSLUG5H_BSHOTGUN_MVS_FILL \
	ROM_FILL(0x1BD73,1,0x07) \
	ROM_FILL(0x1C298,1,0x07)

#define MSLUG5H_SUPERGRENADE_MVS_FILL \
	ROM_FILL(0x1BD73,1,0x0F) \
	ROM_FILL(0x1C298,1,0x0F)

#define MSLUG5H_ENEMYCHASER_MVS_FILL \
	ROM_FILL(0x1BD73,1,0x0C) \
	ROM_FILL(0x1C298,1,0x0C)

#define MSLUGX_AUTOFIRE_MVS_FILL \
	ROM_FILL(0x3CC17,1,0x00)

#define MSLUGX_ELECTRICBOMB_MVS_FILL \
    ROM_FILL(0x3BC2A,1,0x01)\
	ROM_FILL(0x3BC2B,1,0x20)\
    ROM_FILL(0x3BC38,1,0x01)\
	ROM_FILL(0x3BC39,1,0x1E)\
    ROM_FILL(0x3BC46,1,0x01)\
	ROM_FILL(0x3BC47,1,0x1F)\
    ROM_FILL(0x3BC67,1,0x2A)\
	ROM_FILL(0x3BC68,1,0x38)\
    ROM_FILL(0x3BC69,1,0x16)\
	ROM_FILL(0x3BD6E,1,0xBF)\
    ROM_FILL(0x3BD6F,1,0x1C)

#define MSLUGX_?_MVS_FILL \
    ROM_FILL(0x3BD85,1,0x04)\
	ROM_FILL(0x3BD86,1,0x30)\
    ROM_FILL(0x3BD87,1,0x54)

#define MSLUGX_CHANGEWEAPONEFFECTBOSS3_MVS_FILL \
    ROM_FILL(0x4B6D6,1,0x50)\
	ROM_FILL(0x4E144,1,0xC1)\
    ROM_FILL(0x4E145,1,0x94)\
	ROM_FILL(0x4E158,1,0xCA)\
    ROM_FILL(0x4E159,1,0xBA)

#define MSLUG2_HELICOPTERSHOTELECTRICSHOT_MVS_FILL 
    ROM_FILL(0xDD64E,1,0x00)\
	ROM_FILL(0xDD64F,1,0xD3)\
	ROM_FILL(0xDD65D,1,0x24)\
	ROM_FILL(0xDD65E,1,0x23)\
	ROM_FILL(0xDD65F,1,0x86)\
	ROM_FILL(0xDD6BB,1,0x04)\
	ROM_FILL(0xDD6BC,1,0x2F)\
	ROM_FILL(0xDD6BD,1,0x5C)\
	ROM_FILL(0xDD6BD,1,0x08)

#define MSLUGX_ALLENO'NEILBLACK_MVS_FILL \
    ROM_FILL(0x3EC01,1,0x05)\
    ROM_FILL(0x3EC02,1,0x35)\
	ROM_FILL(0x3EC03,1,0xAE)

#define MSLUGX_BFIRE_MVS_FILL \
	ROM_FILL(0xC0EA5,1,0x02)

#define MSLUGX_BSTONE_MVS_FILL \
	ROM_FILL(0xC0EA5,1,0x03)

#define MSLUGX_BFLAMESHOT_MVS_FILL \
	ROM_FILL(0xC0E75,1,0x01) \
	ROM_FILL(0xC0EF2,1,0x01) \
	ROM_FILL(0xC0EF3,1,0x09) \
	ROM_FILL(0xC33AB,1,0x01)

#define MSLUGX_BHEAVYMACHINEGUN_MVS_FILL \
	ROM_FILL(0xC0E75,1,0x01) \
	ROM_FILL(0xC0EF2,1,0x10) \
	ROM_FILL(0xC0EF3,1,0x0A) \
	ROM_FILL(0xC33AB,1,0x01)

#define MSLUGX_BLASER_MVS_FILL \
	ROM_FILL(0xC0E75,1,0x01) \
	ROM_FILL(0xC0EF2,1,0x07) \
	ROM_FILL(0xC0EF3,1,0x0B) \
	ROM_FILL(0xC33AB,1,0x01)

#define MSLUGX_BROCKETLAUNCHER_MVS_FILL \
	ROM_FILL(0xC0E75,1,0x01) \
	ROM_FILL(0xC0EF2,1,0x00) \
	ROM_FILL(0xC0EF3,1,0x08) \
	ROM_FILL(0xC33AB,1,0x01)

#define MSLUGX_BSHOTGUN_MVS_FILL \
	ROM_FILL(0xC0E75,1,0x01) \
	ROM_FILL(0xC0EF2,1,0x00) \
	ROM_FILL(0xC0EF3,1,0x07) \
	ROM_FILL(0xC33AB,1,0x01)

#define MSLUGX_CANNON_MVS_FILL \
	ROM_FILL(0xC0E75,1,0x01) \
	ROM_FILL(0xC0EF2,1,0x00) \
	ROM_FILL(0xC0EF3,1,0x01) \
	ROM_FILL(0xC33AB,1,0x01)

#define MSLUGX_SUPERGRENADE_MVS_FILL \
	ROM_FILL(0xC0E75,1,0x01) \
	ROM_FILL(0xC0EF2,1,0x04) \
	ROM_FILL(0xC0EF3,1,0x0F) \
	ROM_FILL(0xC33AB,1,0x01)

#define MSLUGX_ENEMYCHASER_MVS_FILL \
	ROM_FILL(0xC0E75,1,0x01) \
	ROM_FILL(0xC0EF2,1,0x04) \
	ROM_FILL(0xC0EF3,1,0x0C) \
	ROM_FILL(0xC33AB,1,0x01)

 ************************************************************************************************************************************/

