// Proyecto Shadows Metal Slug Forever
// Copyright-Holders:Gaston90
// Thanks To The Collaborators Who Have Made A Great Contribution To The Project: Remikare And Robbert.

#include "includes/neogeo.h"
#include "neogeo.lh"

/************************************************************************************************************************************
    In 2010, SNK Playmore, the successor of SNK, released a title catalogue which lists the released
    games (MVS/AES/CD) including their release dates in Japan. It is not 100% complete.
    The included title catalogue is the english one.

    Game Title                                                  Genre           Publisher       Date Released (in Japan)
    =================================================================================================================================
    METAL SLUG                                                  Action          Nazca           MVS Cartridge:1996/04/19
                                                                                                NEOGEO ROM-cart:1996/05/24
                                                                                                NEOGEO CD:1996/07/05
    METAL SLUG 2                                                Action          SNK             MVS Cartridge:1998/02/23
                                                                                                NEOGEO ROM-cart:1998/04/02
                                                                                                NEOGEO CD:1998/06/25
    METAL SLUG X                                                Action          SNK             MVS Cartridge:1999/03/19
                                                                                                NEOGEO ROM-cart:1999/05/27
    METAL SLUG 3                                                Action Shooter  SNK             MVS Cartridge:2000/03/23
                                                                                                NEOGEO ROM-cart:2000/06/01
    METAL SLUG 4                                                Action Shooter  SNK Playmore    MVS Cartridge:2002/03/27
                                                                                                NEOGEO ROM-cart:2002/06/13
    METAL SLUG 5                                                Action Shooter  SNK Playmore    MV-0:2003/11/14
                                                                                                NEOGEO ROM-cart:2004/02/19
************************************************************************************************************************************/

/*************************************
 *
 *  Neo-Geo bios
 *
 *************************************

    These are the known Bios Roms, Set options.bios to the one you want.

    The Universe bios roms are supported because they're now used on enough PCBs
    to be considered 'in active arcade use' rather than just homebrew hacks.
    Some may be missing, there have been multiple CRCs reported for the same
    revision in some cases (the Universe bios has an option for entering / displaying
    a serial number; these should be noted as such if they're added).
    Universe bios prior to version 1.3 was incompatible with AES.

    The 'japan-hotel' BIOS is a dump of an MVS which could be found in some japanese
    hotels. it is a custom MVS mobo which uses MVS carts but it hasn't jamma
    connector and it's similar to a console with a coin mechanism, so it's a sort
    of little coin op console installed in hotels.

    The sp-45.sp1 bios is the latest 'ASIA' revision. Japan-j3.bin is the latest 'JAPAN'
    revision. Both of them are also used in the sp-4x.sp1 bios of the Jamma PCB boards.

    The current Neo-Geo MVS system set (SFIX/SM1/000-LO) used is from a NEO-MVH MV1FS board.
    Other boards (MV1xx / MV2x / MV4x /MV6x) other system sets?

    Zoom ROM (LO)    128K   TC531000CP      1x 128Kx8   Zoom look-up table ROM
    Fix ROM (SFIX)   128K   27C1000         1x 128Kx8   Text layer graphics ROM
    Sound ROM (SM1)  128K   27C1000/23C1000 1x 128Kx8   Z80 program ROM

*/

#define ROM_LOAD16_WORD_SWAP_BIOS(bios,name,offset,length,hash) \
		ROMX_LOAD(name, offset, length, hash, ROM_GROUPWORD | ROM_REVERSE | ROM_BIOS(bios))

#define NEOGEO_BIOS \
	ROM_REGION16_BE( 0x80000, "mainbios", 0 ) \
	ROM_SYSTEM_BIOS( 0, "arcade_mode", "Arcade Mode MVS" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 0, "arcade mode.rom",  0x00000, 0x020000, CRC(0de70ac8) SHA1(d41ab190a2c9f91c52649f7e0faf85a9cfa8ed24) ) \
	ROM_SYSTEM_BIOS( 1, "console_mode", "Consola Mode AES" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 1, "console mode.rom",  0x00000, 0x020000, CRC(a371d430) SHA1(9519a43eaed7a5753a9fdffaca8167b7214c4d93) ) \
	ROM_DEFAULT_BIOS("arcade_mode")

#define NEO_BIOS_AUDIO_64K(name, hash) \
	NEOGEO_BIOS \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( 0x20000, "audiocpu", 0 ) \
	ROM_LOAD( name, 0x00000, 0x10000, hash ) \
	ROM_RELOAD(     0x10000, 0x10000 )

#define NEO_BIOS_AUDIO_128K(name, hash) \
	NEOGEO_BIOS \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( 0x30000, "audiocpu", 0 ) \
	ROM_LOAD( name, 0x00000, 0x20000, hash ) \
	ROM_RELOAD(     0x10000, 0x20000 )

#define NEO_BIOS_AUDIO_256K(name, hash) \
	NEOGEO_BIOS \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( 0x50000, "audiocpu", 0 ) \
	ROM_LOAD( name, 0x00000, 0x40000, hash ) \
	ROM_RELOAD(     0x10000, 0x40000 )

#define NEO_BIOS_AUDIO_512K(name, hash) \
	NEOGEO_BIOS \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( 0x90000, "audiocpu", 0 ) \
	ROM_LOAD( name, 0x00000, 0x80000, hash ) \
	ROM_RELOAD(     0x10000, 0x80000 )

#define NEO_BIOS_AUDIO_ENCRYPTED_64K(name, hash) \
	NEOGEO_BIOS \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( 0x90000, "audiocpu", ROMREGION_ERASEFF ) \
	ROM_REGION( 0x80000, "audiocrypt", 0 ) \
	ROM_LOAD( name, 0x00000, 0x10000, hash )

#define NEO_BIOS_AUDIO_ENCRYPTED_128K(name, hash) \
	NEOGEO_BIOS \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( 0x90000, "audiocpu", ROMREGION_ERASEFF ) \
	ROM_REGION( 0x80000, "audiocrypt", 0 ) \
	ROM_LOAD( name, 0x00000, 0x20000, hash )

#define NEO_BIOS_AUDIO_ENCRYPTED_256K(name, hash) \
	NEOGEO_BIOS \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( 0x90000, "audiocpu", ROMREGION_ERASEFF ) \
	ROM_REGION( 0x80000, "audiocrypt", 0 ) \
	ROM_LOAD( name, 0x00000, 0x40000, hash )

#define NEO_BIOS_AUDIO_ENCRYPTED_512K(name, hash) \
	NEOGEO_BIOS \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( 0x90000, "audiocpu", ROMREGION_ERASEFF ) \
	ROM_REGION( 0x80000, "audiocrypt", 0 ) \
	ROM_LOAD( name,      0x00000, 0x80000, hash )

#define ROM_Y_ZOOM \
	ROM_REGION( 0x20000, "zoomy", 0 ) \
	ROM_LOAD( "000-lo.lo", 0x00000, 0x20000, CRC(5a86cff2) SHA1(5992277debadeb64d1c1c64b0a92d9293eaf7e4a) )

#define NEO_SFIX_MT(bytes) \
	ROM_Y_ZOOM \
	ROM_REGION( 0x20000, "fixedbios", 0 ) \
	ROM_LOAD( "sfix.sfix",  0, 0x20000, CRC(c2ea0cfd) SHA1(fd4a618cdcdbf849374f0a50dd8efe9dbab706c3) ) \
	ROM_REGION( bytes, "fixed", ROMREGION_ERASE00 )

#define NEO_SFIX_MT_128K \
	NEO_SFIX_MT( 0x20000 )

#define NEO_SFIX_MT_512K \
	NEO_SFIX_MT( 0x80000 )

#define NEO_SFIX(bytes, name, hash) \
	NEO_SFIX_MT( bytes ) \
	ROM_LOAD( name, 0x00000, bytes, hash )

#define NEO_SFIX_64K(name, hash) \
	NEO_SFIX( 0x10000, name, hash )

#define NEO_SFIX_128K(name, hash) \
	NEO_SFIX( 0x20000, name, hash )

#define NEO_SFIX_512K(name, hash) \
	NEO_SFIX( 0x80000, name, hash )

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
	attotime period = attotime::from_ticks((uint64_t)m_display_counter + 1, NEOGEO_PIXEL_CLOCK);
	if (LOG_VIDEO_SYSTEM) logerror("adjust_display_position_interrupt_timer  current y: %02x  current x: %02x   target y: %x  target x: %x\n", m_screen->vpos(), m_screen->hpos(), (m_display_counter + 1) / NEOGEO_HTOTAL, (m_display_counter + 1) % NEOGEO_HTOTAL);

	m_display_position_interrupt_timer->adjust(period);
}


void neogeo_state::neogeo_set_display_position_interrupt_control( uint16_t data )
{
	m_display_position_interrupt_control = data;
}


void neogeo_state::neogeo_set_display_counter_msb( uint16_t data )
{
	m_display_counter = (m_display_counter & 0x0000ffff) | ((uint32_t)data << 16);

	if (LOG_VIDEO_SYSTEM) logerror("PC %06x: set_display_counter %08x\n", m_maincpu->pc(), m_display_counter);
}


void neogeo_state::neogeo_set_display_counter_lsb( uint16_t data )
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


void neogeo_state::neogeo_acknowledge_interrupt( uint16_t data )
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

WRITE8_MEMBER(neogeo_state::audio_cpu_enable_nmi_w)
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

READ16_MEMBER(neogeo_state::in0_r)
{
	return ((m_edge->in0_r(space, offset) & m_ctrl1->ctrl_r(space, offset)) << 8) | m_dsw->read();
}

READ16_MEMBER(neogeo_state::in1_r)
{
	return ((m_edge->in1_r(space, offset) & m_ctrl2->ctrl_r(space, offset)) << 8) | 0xff;
}

WRITE8_MEMBER(neogeo_state::io_control_w)
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

READ16_MEMBER(neogeo_state::neogeo_unmapped_r)
{
	uint16_t ret;

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

void neogeo_state::set_save_ram_unlock( uint8_t data )
{
	m_save_ram_unlocked = data;
}


WRITE16_MEMBER(neogeo_state::save_ram_w)
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


READ16_MEMBER(neogeo_state::memcard_r)
{
	m_maincpu->eat_cycles(2); // insert waitstate

	uint16_t ret;

	if (m_memcard->present() != -1)
		ret = m_memcard->read(space, offset) | 0xff00;
	else
		ret = 0xffff;

	return ret;
}


WRITE16_MEMBER(neogeo_state::memcard_w)
{
	m_maincpu->eat_cycles(2); // insert waitstate

	if (ACCESSING_BITS_0_7)
	{
		if (m_memcard->present() != -1)
				m_memcard->write(space, offset, data);
	}
}

/*************************************
 *
 *  Inter-CPU communications
 *
 *************************************/

WRITE8_MEMBER(neogeo_state::audio_command_w)
{
	m_soundlatch->write(data);

	m_audio_cpu_nmi_pending = true;
	audio_cpu_check_nmi();

	/* boost the interleave to let the audio CPU read the command */
	machine().scheduler().boost_interleave(attotime::zero, attotime::from_usec(50));
}

READ8_MEMBER(neogeo_state::audio_command_r)
{
	uint8_t ret = m_soundlatch->read();

	m_audio_cpu_nmi_pending = false;
	audio_cpu_check_nmi();

	return ret;
}

CUSTOM_INPUT_MEMBER(neogeo_state::get_audio_result)
{
	uint8_t ret = m_soundlatch2->read();

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

READ8_MEMBER(neogeo_state::audio_cpu_bank_select_r)
{
	m_bank_audio_cart[offset & 3]->set_entry(offset >> 8);

	return 0;
}


void neogeo_state::neogeo_audio_cpu_banking_init(int set_entry)
{
	if (m_type == NEOGEO_CD) return;

	int region;
	int bank;
	uint8_t *rgn;
	uint32_t address_mask;

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
			uint32_t bank_address = 0x10000 + ((bank << (11 + region)) & address_mask);
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

WRITE8_MEMBER(neogeo_state::system_control_w)
{
	uint8_t bit = (offset >> 3) & 0x01;

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
	static const uint8_t led_map[0x10] =
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


void neogeo_state::set_output_latch( uint8_t data )
{
	/* looks like the LEDs are set on the
	   falling edge */
	uint8_t falling_bits = m_output_latch & ~data;

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


void neogeo_state::set_output_data( uint8_t data )
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
	m_maincpu->space(AS_PROGRAM).install_read_handler(0x300000, 0x300001, 0, 0x01ff7e, 0, read16_delegate(FUNC(neogeo_state::in0_r), this));
	m_maincpu->space(AS_PROGRAM).install_read_handler(0x340000, 0x340001, 0, 0x01fffe, 0, read16_delegate(FUNC(neogeo_state::in1_r), this));

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
	offs_t offs;
	address_space &space = m_maincpu->space(AS_PROGRAM);

	/* reset system control registers */
	for (offs = 0; offs < 8; offs++)
		system_control_w(space, offs, 0);

	// disable audiocpu nmi
	m_audio_cpu_nmi_enabled = false;
	m_audio_cpu_nmi_pending = false;
	audio_cpu_check_nmi();

	m_maincpu->reset();

	start_interrupt_timers();

	/* trigger the IRQ3 that was set by MACHINE_START */
	update_interrupts();

	m_recurse = false;
}

READ16_MEMBER(neogeo_state::banked_vectors_r)
{
	if (!m_use_cart_vectors)
	{
		uint16_t* bios = (uint16_t*)memregion("mainbios")->base();
		return bios[offset];
	}
	else
	{
		uint16_t* game = (uint16_t*)m_region_maincpu->base();
		return game[offset];
	}

}

READ16_MEMBER(neogeo_state::neogeo_slot_rom_low_r)
{
	return 0;
}

READ16_MEMBER(neogeo_state::neogeo_slot_rom_low_vectors_r)
{
	if (!m_use_cart_vectors)
	{
		uint16_t* bios = (uint16_t*)memregion("mainbios")->base();
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
	map(0x300000,0x300001).mirror(0x01ff7e).portr("DSW");
	map(0x300080,0x300081).mirror(0x01ff7e).portr("TEST");
	map(0x300000,0x300001).mirror(0x01fffe).w("watchdog",FUNC(watchdog_timer_device::reset_w)).umask16(0x00ff);
	map(0x320000,0x320001).mirror(0x01fffe).portr("AUDIO/COIN");
	map(0x320000,0x320001).mirror(0x01fffe).w(FUNC(neogeo_state::audio_command_w)).umask16(0xff00);
	map(0x340000,0x340001).mirror(0x01fffe).portr("P2");
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
	PORT_DIPNAME( 0x02, 0x02, DEF_STR( Cabinet ) ) PORT_DIPLOCATION("SW:2")
	PORT_DIPSETTING(    0x02, DEF_STR( Normal ) )
	PORT_DIPSETTING(    0x00, "VS Mode" )
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
	PORT_DIPNAME( 0x40, 0x40, DEF_STR( Free_Play ) ) PORT_DIPLOCATION("SW:7")
	PORT_DIPSETTING(    0x40, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x80, 0x80, "Freeze" ) PORT_DIPLOCATION("SW:8")
	PORT_DIPSETTING(    0x80, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_UP )
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN )
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT )
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT )
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 )
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 )
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON3 )
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_BUTTON4 )

	PORT_START("P2")
	PORT_BIT( 0x00ff, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_PLAYER(2)
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_PLAYER(2)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_PLAYER(2)
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_PLAYER(2)
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(2)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(2)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(2)
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_BUTTON4 ) PORT_PLAYER(2)

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

	NEOGEO_CONTROL_PORT(config, "ctrl1", neogeo_arc_pin15, "", false);
	NEOGEO_CONTROL_PORT(config, "ctrl2", neogeo_arc_pin15, "", false);
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
	NEOGEO_CONTROL_PORT(config, "ctrl1", neogeo_arc_pin15, "", true);
	NEOGEO_CONTROL_PORT(config, "ctrl2", neogeo_arc_pin15, "", true);

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

/*************************************
 *
 *  Game-specific inits
 *
 *************************************/

/* Fixed by remikare */
void neogeo_state::init_darksoft()
{
	init_neogeo();
	m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
}

void neogeo_state::init_ms5plushb()
{
	init_neogeo();
	m_sprgen->m_fixed_layer_bank_type = 1; // for those sets with 512k of s1

	// decrypt p roms if needed
	u8 *ram = memregion("maincpu")->base();
	if (ram[0x100] != 0x25)
	{
		//printf("Maincpu=%X\n",ram[0x100]);fflush(stdout);
		m_bootleg_prot->install_ms5plus_protection(m_maincpu,m_banked_cart);
	}

	// decrypt m1 if needed
	if (memregion("audiocrypt"))
		m_cmc_prot->neogeo_cmc50_m1_decrypt(audiocrypt_region, audiocrypt_region_size, audiocpu_region, audio_region_size);

	// decrypt v roms if needed
	ram = memregion("ymsnd")->base();
	if (ram[0x60] != 0x82)
	{
		//printf("ym=%X\n",ram[0x60]);
		m_pcm2_prot->neo_pcm2_swap(ym_region, ym_region_size, 2);
	}

	// decrypt c roms if needed
	ram = memregion("sprites")->base();
	if (ram[0] != 0)
	{
		//printf("Sprites=%X\n",ram[0]);
		m_cmc_prot->cmc50_neogeo_gfx_decrypt(spr_region, spr_region_size, MSLUG5_GFX_KEY);
	    m_bootleg_prot->neogeo_bootleg_sx_decrypt(fix_region, fix_region_size,1);
	}

	// if no s rom, copy info from end of c roms
	ram = memregion("fixed")->base();
	if (ram[0x100] == 0)
	{
		//printf("Fixed1=%X\n",ram[0x100]);
		m_cmc_prot->neogeo_sfix_decrypt(spr_region, spr_region_size, fix_region, fix_region_size);
	}
}

void neogeo_state::init_ms5pcbhb()
{
	init_neogeo();
	m_sprgen->m_fixed_layer_bank_type = 2; // for those sets with 512k of s1

	// decrypt p roms if needed
	u8 *ram = memregion("maincpu")->base();
	if (ram[0x100] != 0x45)
	{
		//printf("Maincpu=%X\n",ram[0x100]);fflush(stdout);
		m_pvc_prot->mslug5_decrypt_68k(cpuregion, cpuregion_size);
		m_pvc_prot->install_pvc_protection(m_maincpu, m_banked_cart);
	}

	// decrypt m1 if needed
	if (memregion("audiocrypt"))
		m_cmc_prot->neogeo_cmc50_m1_decrypt(audiocrypt_region, audiocrypt_region_size, audiocpu_region, audio_region_size);

	// decrypt v roms if needed
	ram = memregion("ymsnd")->base();
	if (ram[0x60] != 0x82)
	{
		//printf("ym=%X\n",ram[0x60]);
		m_pcm2_prot->neo_pcm2_swap(ym_region, ym_region_size, 2);
	}

	// decrypt c roms if needed
	ram = memregion("sprites")->base();
	if (ram[0] != 0)
	{
		//printf("Sprites=%X\n",ram[0]);
        m_sma_prot->svcpcb_gfx_decrypt(spr_region, spr_region_size);
		m_cmc_prot->cmc50_neogeo_gfx_decrypt(spr_region, spr_region_size, MSLUG5_GFX_KEY);
	}

	// if no s rom, copy info from end of c roms
	ram = memregion("fixed")->base();
	if (ram[0x100] == 0)
	{
		//printf("Fixed1=%X\n",ram[0x100]);
		m_cmc_prot->neogeo_sfix_decrypt(spr_region, spr_region_size, fix_region, fix_region_size);
	}

	// decrypt s1 if needed
	if (ram[0x100] != 0xBB)
	{
		//printf("Fixed2=%X\n",ram[0]);
		m_sma_prot->svcpcb_s1data_decrypt(fix_region, fix_region_size);
	    install_banked_bios();
	}
}

void neogeo_state::init_mslug3a()
{
	init_neogeo();
	m_sma_prot->mslug3a_decrypt_68k(cpuregion);
	m_sprgen->m_fixed_layer_bank_type = 1;
	m_cmc_prot->cmc42_neogeo_gfx_decrypt(spr_region, spr_region_size, MSLUG3_GFX_KEY);
	m_cmc_prot->neogeo_sfix_decrypt(spr_region, spr_region_size, fix_region, fix_region_size);
	m_sma_prot->mslug3a_install_protection(m_maincpu,m_banked_cart);
}

void neogeo_state::init_mslug3hb()
{
	init_neogeo();
	m_sprgen->m_fixed_layer_bank_type = 1;

	// decrypt p roms if needed
	u8 *ram = memregion("maincpu")->base();
	if (ram[0x100] != 0x45)
	{
		//printf("Maincpu=%X\n",ram[0x100]);fflush(stdout);
		m_sma_prot->mslug3_decrypt_68k(cpuregion);
	    m_sma_prot->mslug3_install_protection(m_maincpu,m_banked_cart);
	}

	// decrypt c roms if needed
	ram = memregion("sprites")->base();
	if (ram[0] != 0)
	{
		//printf("Sprites=%X\n",ram[0]);
		m_cmc_prot->cmc42_neogeo_gfx_decrypt(spr_region, spr_region_size, MSLUG3_GFX_KEY);
	}

	// if no s rom, copy info from end of c roms
	ram = memregion("fixed")->base();
	if (ram[0x100] == 0)
	{
		//printf("Fixed1=%X\n",ram[0x100]);
		m_cmc_prot->neogeo_sfix_decrypt(spr_region, spr_region_size, fix_region, fix_region_size);
	}
}

void neogeo_state::init_mslug3de()
{
	init_mslug3hb();
	m_sma_prot->mslug3_install_protection(m_maincpu,m_banked_cart);
}

/* Fixed by remikare */
void neogeo_state::init_mslug3dd()
{
	init_neogeo();
	m_sprgen->m_fixed_layer_bank_type = 1;
	m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
	m_sma_prot->mslug3_install_protection(m_maincpu,m_banked_cart);
}

void neogeo_state::init_mslug3b6hb()
{
	init_mslug3hb();
	m_bootleg_prot->neogeo_bootleg_sx_decrypt(fix_region, fix_region_size,2);
}

/* Fixed by remikare */
void neogeo_state::init_mslug4dd()
{
	init_neogeo();

	m_sprgen->m_fixed_layer_bank_type = 1;
	m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
}

void neogeo_state::init_mslug4hb()
{
	init_neogeo();
	m_sprgen->m_fixed_layer_bank_type = 1;

	// decrypt m1 if needed
	if (memregion("audiocrypt"))
		m_cmc_prot->neogeo_cmc50_m1_decrypt(audiocrypt_region, audiocrypt_region_size, audiocpu_region, audio_region_size);

	// decrypt v roms if needed
	u8 *ram = memregion("ymsnd")->base();
	if (ram[0x20] != 0x99)
	{
		//printf("ym=%X\n",ram[0x20]);
		m_pcm2_prot->neo_pcm2_snk_1999(ym_region, ym_region_size, 8);
	}

	// decrypt c roms if needed
	ram = memregion("sprites")->base();
	if (ram[0] != 0)
	{
		//printf("Sprites=%X\n",ram[0]);
		m_cmc_prot->cmc50_neogeo_gfx_decrypt(spr_region, spr_region_size, MSLUG4_GFX_KEY);
	}

	// if no s rom, copy info from end of c roms
	ram = memregion("fixed")->base();
	if (ram[0x100] == 0)
	{
		//printf("Fixed1=%X\n",ram[0x100]);
		m_cmc_prot->neogeo_sfix_decrypt(spr_region, spr_region_size, fix_region, fix_region_size);
	}
}

void neogeo_state::init_mslug4p()
{
	init_mslug4hb();
	m_cmc_prot->cmc50_neogeo_gfx_decrypt(spr_region, spr_region_size, MSLUG4_GFX_KEY);
}

void neogeo_state::init_mslug5b()
{
	init_neogeo();
	m_bootleg_prot->mslug5b_vx_decrypt(ym_region, ym_region_size);
	m_bootleg_prot->neogeo_bootleg_sx_decrypt(fix_region, fix_region_size, 2);
	m_bootleg_prot->mslug5b_cx_decrypt(spr_region, spr_region_size);
}

/* Fixed by remikare */
void neogeo_state::init_mslug5dd()
{
	init_neogeo();
	m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
	m_pvc_prot->install_pvc_protection(m_maincpu,m_banked_cart);
}

void neogeo_state::init_mslug5b1()
{
	init_mslug5hb();
	m_pvc_prot->install_pvc_protection(m_maincpu, m_banked_cart);
}

void neogeo_state::init_mslug5hb()
{
	init_neogeo();
	m_sprgen->m_fixed_layer_bank_type = 2; // for those sets with 512k of s1

	// decrypt p roms if needed
	u8 *ram = memregion("maincpu")->base();
	if (ram[0x100] != 0x45)
	{
		//printf("Maincpu=%X\n",ram[0x100]);fflush(stdout);
		m_pvc_prot->mslug5_decrypt_68k(cpuregion, cpuregion_size);
		m_pvc_prot->install_pvc_protection(m_maincpu, m_banked_cart);
	}

	// decrypt m1 if needed
	if (memregion("audiocrypt"))
		m_cmc_prot->neogeo_cmc50_m1_decrypt(audiocrypt_region, audiocrypt_region_size, audiocpu_region, audio_region_size);

	// decrypt v roms if needed
	ram = memregion("ymsnd")->base();
	if (ram[0x60] != 0x82)
	{
		//printf("ym=%X\n",ram[0x60]);
		m_pcm2_prot->neo_pcm2_swap(ym_region, ym_region_size, 2);
	}

	// decrypt c roms if needed
	ram = memregion("sprites")->base();
	if (ram[0] != 0)
	{
		//printf("Sprites=%X\n",ram[0]);
		m_cmc_prot->cmc50_neogeo_gfx_decrypt(spr_region, spr_region_size, MSLUG5_GFX_KEY);
	}

	// if no s rom, copy info from end of c roms
	ram = memregion("fixed")->base();
	if (ram[0x100] == 0)
	{
		//printf("Fixed1=%X\n",ram[0x100]);
		m_cmc_prot->neogeo_sfix_decrypt(spr_region, spr_region_size, fix_region, fix_region_size);
	}
}

void neogeo_state::init_mslugx()
{
	init_neogeo();
	m_mslugx_prot->mslugx_install_protection(m_maincpu);
}

/* Fixed by remikare */
void neogeo_state::init_mslugxdd()
{
	init_neogeo();
	m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
	m_mslugx_prot->mslugx_install_protection(m_maincpu);
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

#define MSLUG_FLASHOFF_MVS_FILL \
    ROM_FILL(0x13830,1,0x4E)\
	ROM_FILL(0x13831,1,0x71)\
	ROM_FILL(0x13832,1,0x4E)\
	ROM_FILL(0x13833,1,0x71)

#define MSLUG_POWNEVERLOSE_MVS_FILL \
    ROM_FILL(0x25A44,1,0x4E)\
	ROM_FILL(0x25A45,1,0x71)\
	ROM_FILL(0x25DEA,1,0x4E)\
	ROM_FILL(0x25DEB,1,0x71)

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

#define MSLUG2T_ESSENTIALPATCH_MODS_FILL \
	ROM_FILL(0x108,1,0x09)\
    ROM_FILL(0x11F7,1,0xCF)\
	ROM_FILL(0x11F8,1,0xF9)\
	ROM_FILL(0x11F9,1,0xDD)\
	ROM_FILL(0x11FA,1,0xF7)\
	ROM_FILL(0x1450,1,0x70)\
    ROM_FILL(0x1451,1,0x02)\
	ROM_FILL(0x1452,1,0x4E)\
	ROM_FILL(0x1453,1,0x71)\
	ROM_FILL(0x1454,1,0x4E)\
    ROM_FILL(0x1455,1,0x71)\
	ROM_FILL(0x1456,1,0x4E)\
	ROM_FILL(0x1457,1,0x71)\
	ROM_FILL(0x1458,1,0x4E)\
	ROM_FILL(0x1459,1,0x71)\
	ROM_FILL(0x1464,1,0x4E)\
	ROM_FILL(0x1465,1,0x71)\
    ROM_FILL(0x1466,1,0x4E)\
	ROM_FILL(0x1467,1,0x71)\
	ROM_FILL(0x1468,1,0x4E)\
	ROM_FILL(0x1469,1,0x71)\
	ROM_FILL(0x146A,1,0x4E)\
    ROM_FILL(0x146B,1,0x71)\
	ROM_FILL(0x146C,1,0x4E)\
	ROM_FILL(0x146D,1,0x71)\
	ROM_FILL(0x147D,1,0x50)\
    ROM_FILL(0x1487,1,0x46)\
	ROM_FILL(0x14D2,1,0x52)\
	ROM_FILL(0x14D3,1,0x2D)\
	ROM_FILL(0x14D4,1,0x80)\
	ROM_FILL(0x14D5,1,0x8D)\
	ROM_FILL(0x14D6,1,0x4E)\
	ROM_FILL(0x14D7,1,0x71)\
    ROM_FILL(0x1650,1,0x4E)\
	ROM_FILL(0x1651,1,0xF9)\
	ROM_FILL(0x1653,1,0x0D)\
	ROM_FILL(0x1655,1,0x00)\
	ROM_FILL(0x1656,1,0x4E)\
    ROM_FILL(0x1657,1,0x71)\
	ROM_FILL(0x165E,1,0x4E)\
	ROM_FILL(0x165F,1,0x71)\
	ROM_FILL(0x1660,1,0x4E)\
    ROM_FILL(0x1661,1,0x71)\
	ROM_FILL(0x1662,1,0x4E)\
	ROM_FILL(0x1663,1,0x71)\
	ROM_FILL(0xD8000,1,0x0C)\
	ROM_FILL(0xD8001,1,0x2D)\
	ROM_FILL(0xD8002,1,0x00)\
	ROM_FILL(0xD8003,1,0x02)\
    ROM_FILL(0xD8004,1,0x80)\
	ROM_FILL(0xD8005,1,0x8D)\
	ROM_FILL(0xD8006,1,0x65)\
	ROM_FILL(0xD8007,1,0xF8)\
	ROM_FILL(0xD8008,1,0x1B)\
    ROM_FILL(0xD8009,1,0x7C)\
	ROM_FILL(0xD800A,1,0x00)\
	ROM_FILL(0xD800B,1,0x00)\
	ROM_FILL(0xD800C,1,0x80)\
    ROM_FILL(0xD800D,1,0x8D)\
	ROM_FILL(0xD800E,1,0x4E)\
	ROM_FILL(0xD800F,1,0xF9)\
	ROM_FILL(0xD8010,1,0x00)\
	ROM_FILL(0xD8011,1,0x00)\
	ROM_FILL(0xD8012,1,0x16)\
	ROM_FILL(0xD8013,1,0x58)

#define MSLUG2_WEAPONANIMATION_MVS_FILL \
	ROM_FILL(0xF7769,1,0x0B)\
	ROM_FILL(0x4D139,1,0x07)\
	ROM_FILL(0x4D159,1,0x07)\
	ROM_FILL(0x4D169,1,0x07)\
	ROM_FILL(0x4D199,1,0x07)\
	ROM_FILL(0x4D1A9,1,0x07)\
	ROM_FILL(0x4D1B9,1,0x07)\
	ROM_FILL(0x4D8BD,1,0x0D)\
	ROM_FILL(0x4D8CD,1,0x0D)\
	ROM_FILL(0x4D8DD,1,0x0D)\
	ROM_FILL(0x4DE13,1,0x0B)\
	ROM_FILL(0x4DE23,1,0x0B)\
	ROM_FILL(0x38B7,1,0x0A)\
	ROM_FILL(0x38C7,1,0x0A)\
	ROM_FILL(0x38D7,1,0x0A)\
	ROM_FILL(0x38E7,1,0x0A)\
	ROM_FILL(0x38F7,1,0x0A)\
	ROM_FILL(0x3907,1,0x0A)\
	ROM_FILL(0x3917,1,0x0A)\
	ROM_FILL(0x3927,1,0x0A)\
	ROM_FILL(0x3937,1,0x0A)\
	ROM_FILL(0x3947,1,0x0A)\
	ROM_FILL(0x3957,1,0x0A)\
	ROM_FILL(0x3967,1,0x0A)\
	ROM_FILL(0x3977,1,0x0A)\
	ROM_FILL(0x3987,1,0x0A)\
	ROM_FILL(0x3997,1,0x0A)\
	ROM_FILL(0x39A7,1,0x0A)\
	ROM_FILL(0x8F61,1,0x09)\
	ROM_FILL(0x8F81,1,0x09)\
	ROM_FILL(0x8FB1,1,0x09)\
	ROM_FILL(0x8FC1,1,0x09)\

#define MSLUG2_SPEEDUPLEVELTEXTLEVEL_MVS_FILL \
	ROM_FILL(0x6FE88,1,0x67)

#define MSLUG2_STARTWALKINGALLLEVELS_MVS_FILL \
    ROM_FILL(0xE006D,1,0x03)\
	ROM_FILL(0xE02CD,1,0x03)\
	ROM_FILL(0xE0377,1,0x03)\
	ROM_FILL(0xE03E5,1,0x03)\
	ROM_FILL(0xE04CF,1,0x03)

#define MSLUG2_BOSS_MVS_FILL
	ROM_FILL(0xB00F2,1,0x50)

#define MSLUG2_ALIEN_MVS_FILL
	ROM_FILL(0xA4982,1,0x58)

#define MSLUG2_HELICOPTERSHOTELECTRICSHOT_MVS_FILL 
    ROM_FILL(0xC6C90,1,0x01)\
	ROM_FILL(0xC6C91,1,0x69)\
	ROM_FILL(0xC6C9F,1,0x0A)\
	ROM_FILL(0xC6CA0,1,0x74)\
	ROM_FILL(0xC6CA1,1,0x22)\
	ROM_FILL(0xC6CE7,1,0x0A)\
	ROM_FILL(0xC6CE8,1,0x47)\
	ROM_FILL(0xC6CE9,1,0xD0)

#define MSLUG2_SOLDIERDOESNTDISAPPEARWHENHEDIES_MVS_FILL \
    ROM_FILL(0x715D4,1,0x5E)\
	ROM_FILL(0x7178A,1,0x5E)\
	ROM_FILL(0x8BEF2,1,0x5E)\
	ROM_FILL(0xA89BA,1,0x5E)

#define MSLUG2_THEYTEARYOUAPARTWHENITDIES_MVS_FILL \
    ROM_FILL(0x943B7,1,0x0B)\
    ROM_FILL(0x943B8,1,0x5D)\
	ROM_FILL(0x943B9,1,0xB4)\
    ROM_FILL(0x94703,1,0x0B)\
    ROM_FILL(0x94704,1,0x5D)\
	ROM_FILL(0x94705,1,0xB4)

#define MSLUG2_FLASHOFF_MVS_FILL \
    ROM_FILL(0x859E6,1,0x4E)\
	ROM_FILL(0x859E7,1,0x71)\
	ROM_FILL(0x859E8,1,0x4E)\
	ROM_FILL(0x859E9,1,0x71)

#define MSLUG2_POWNEVERLOSE_MVS_FILL \
	ROM_FILL(0x4A423,1,0xDC)

#define MSLUG2_FAT_MVS_FILL \
	ROM_FILL(0x929B7,1,0x02) \
	ROM_FILL(0x94A28,1,0x02)

#define MSLUG2_BFIRE_MVS_FILL \
	ROM_FILL(0x929DF,1,0x02)

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

#define MSLUG3_AMMUNITION2X_MVS_FILL \
    ROM_FILL(0x21C47,1,0x3C)\
	ROM_FILL(0x21C51,1,0x3C)\
	ROM_FILL(0x21C5B,1,0x3C)\
	ROM_FILL(0x21C65,1,0xFF)\
	ROM_FILL(0x21C6F,1,0xFF)\
	ROM_FILL(0x21C79,1,0x1E)\
	ROM_FILL(0x21C83,1,0x3C)\
    ROM_FILL(0x21C8D,1,0x3C)\
    ROM_FILL(0x21C97,1,0xFF)\
	ROM_FILL(0x21CA1,1,0xFF)\
	ROM_FILL(0x21CAB,1,0x50)\
	ROM_FILL(0x21CB5,1,0x3C)\
	ROM_FILL(0x21CBF,1,0x3C)\
	ROM_FILL(0x21CC9,1,0x28)\
	ROM_FILL(0x21CD3,1,0xFF)\
    ROM_FILL(0x21CDD,1,0x3C)

#define MSLUG3_AUTOFIRE_MVS_FILL \
	ROM_FILL(0x3D03,1,0x00)

#define MSLUG3_SOLDIERDOESNTDISAPPEARWHENHEDIES_MVS_FILL \
    ROM_FILL(0x96902,1,0x5E)

#define MSLUG3_FLASHOFF_MVS_FILL \
    ROM_FILL(0xD300,1,0x4E)\
	ROM_FILL(0xD301,1,0x71)\
	ROM_FILL(0xD302,1,0x4E)\
	ROM_FILL(0xD303,1,0x71)

#define MSLUG3_POWNEVERLOSE_MVS_FILL \
    ROM_FILL(0x8E4BE,1,0x4E)\
	ROM_FILL(0x8E4BF,1,0x71)\
	ROM_FILL(0x8E4C0,1,0x4E)\
	ROM_FILL(0x8E4C1,1,0x71)

#define MSLUG3_FAT_MVS_FILL \
    ROM_FILL(0x21B3E,1,0x02)\
	ROM_FILL(0x21B46,1,0x02)\
	ROM_FILL(0x21B5E,1,0x02)\
	ROM_FILL(0x21B5F,1,0x02)\
	ROM_FILL(0x21B66,1,0x02)\
	ROM_FILL(0x21B67,1,0x02)\
	ROM_FILL(0x21B7E,1,0x02)\
    ROM_FILL(0x21B86,1,0x02)\
    ROM_FILL(0x21B88,1,0x02)\
	ROM_FILL(0x21B9E,1,0x02)\
	ROM_FILL(0x21BA6,1,0x02)\
	ROM_FILL(0x21BAA,1,0x02)\
	ROM_FILL(0x21BBE,1,0x02)\
	ROM_FILL(0x21BC6,1,0x02)\
    ROM_FILL(0x21BCB,1,0x02)\
	ROM_FILL(0x21BFE,1,0x02)\
	ROM_FILL(0x21C06,1,0x02)\
	ROM_FILL(0x21C09,1,0x02)\
	ROM_FILL(0x21C0A,1,0x02)\
	ROM_FILL(0x21C0C,1,0x02)\
	ROM_FILL(0x21C0D,1,0x02)

#define MSLUG3_BFIRE_MVS_FILL \
	ROM_FILL(0x2170D,1,0x02)

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

#define MSLUG3_THUNDERCLOUD_MVS_FILL \
	ROM_FILL(0x21719,1,0x11) \
	ROM_FILL(0x21C2A,1,0x11)

#define MSLUG3_ENEMYCHASER_MVS_FILL \
	ROM_FILL(0x21719,1,0x0C) \
	ROM_FILL(0x21C2A,1,0x0C)

#define MSLUG3_SHOOTINGLASERWEAPONUNDERWATER_MVS_FILL \
	ROM_FILL(0x331E0D,1,0x02)\
	ROM_FILL(0x331E0E,1,0x84)\
	ROM_FILL(0x331E0F,1,0xCE)\
	ROM_FILL(0x331E11,1,0x03)\
	ROM_FILL(0x331E12,1,0x98)\
	ROM_FILL(0x331E13,1,0x74)

#define MSLUG3_SHOOTINGTHUNDERCLOUDWEAPONUNDERWATER_MVS_FILL \
	ROM_FILL(0x333661,1,0x02)\
	ROM_FILL(0x333662,1,0x84)\
	ROM_FILL(0x333663,1,0xCE)\
	ROM_FILL(0x333665,1,0x03)\
	ROM_FILL(0x333666,1,0x98)\
	ROM_FILL(0x333667,1,0x74)

#define MSLUG4_CHANGEFROMBLACKTOWHITELOGOSCREEN_MVS_FILL \
	ROM_FILL(0x21B3F6,1,0x7F)\
	ROM_FILL(0x21B3F7,1,0xFF)\
	ROM_FILL(0x21B402,1,0x7F)\
	ROM_FILL(0x21B403,1,0xFF)

#define MSLUG4_AUTOFIRE_MVS_FILL \
	ROM_FILL(0xFCCD,1,0x00)

#define MSLUG4_SOLDIERDOESNTDISAPPEARWHENHEDIES_MVS_FILL \
    ROM_FILL(0x15456,1,0x5E)\
	ROM_FILL(0x1A764,1,0x5E)\
	ROM_FILL(0x56134,1,0x5E)\
	ROM_FILL(0x562E6,1,0x5E)\
	ROM_FILL(0x5AE16,1,0x5E)

#define MSLUG4_FLASHOFF_MVS_FILL \
    ROM_FILL(0xA7530,1,0x4E)\
	ROM_FILL(0xA7531,1,0x71)\
	ROM_FILL(0xA7532,1,0x4E)\
	ROM_FILL(0xA7533,1,0x71)

#define MSLUG4_POWNEVERLOSE_MVS_FILL \
	ROM_FILL(0x1F14E,1,0x4E)\
	ROM_FILL(0x1F14F,1,0x71)

#define MSLUG4_SKIPLEVEL6_1_MVS_FILL \
	ROM_FILL(0xEABCB,1,0x03)

#define MSLUG4_AMMUNITION2X_MVS_FILL \
    ROM_FILL(0xC4C95,1,0x3C)\
	ROM_FILL(0xC4C9F,1,0x3C)\
	ROM_FILL(0xC4CA9,1,0x3C)\
	ROM_FILL(0xC4CB3,1,0xFF)\
	ROM_FILL(0xC4CBD,1,0xFF)\
	ROM_FILL(0xC4CC7,1,0x1E)\
	ROM_FILL(0xC4CD1,1,0x3C)\
    ROM_FILL(0xC4CDB,1,0x3C)\
    ROM_FILL(0xC4CE5,1,0xFF)\
	ROM_FILL(0xC4CEF,1,0xFF)\
	ROM_FILL(0xC4CF9,1,0x50)\
	ROM_FILL(0xC4D03,1,0x3C)\
	ROM_FILL(0xC4D0D,1,0x3C)\
	ROM_FILL(0xC4D17,1,0x28)\
	ROM_FILL(0xC4D21,1,0xFF)\
    ROM_FILL(0xC4D2B,1,0x3C)\
    ROM_FILL(0xC4D35,1,0xFF)

#define MSLUG4_FAT_MVS_FILL \
    ROM_FILL(0xC4AE2,1,0x02)\
	ROM_FILL(0xC4B00,1,0x02)\
	ROM_FILL(0xC4B01,1,0x02)\
	ROM_FILL(0xC4B0A,1,0x02)\
	ROM_FILL(0xC4B0B,1,0x02)\
	ROM_FILL(0xC4B32,1,0x02)\
	ROM_FILL(0xC4B34,1,0x02)\
    ROM_FILL(0xC4B5E,1,0x02)\
    ROM_FILL(0xC4B5A,1,0x02)\
	ROM_FILL(0xC4B82,1,0x02)\
	ROM_FILL(0xC4B87,1,0x02)\
	ROM_FILL(0xC4BB2,1,0x02)\
	ROM_FILL(0xC4BB3,1,0x02)\
	ROM_FILL(0xC4BD2,1,0x02)\
    ROM_FILL(0xC4BD5,1,0x02)\
    ROM_FILL(0xC4BD6,1,0x02)\
	ROM_FILL(0xC4BD9,1,0x02)\
	ROM_FILL(0xC4BDA,1,0x02)\
	ROM_FILL(0xC4BDB,1,0x02)\
	ROM_FILL(0xC4BFA,1,0x02)\
	ROM_FILL(0xC4BFC,1,0x02)\
	ROM_FILL(0xC4BFE,1,0x02)\
	ROM_FILL(0xC4BFF,1,0x02)\
	ROM_FILL(0xC4C00,1,0x02)\
	ROM_FILL(0xC4607,1,0x02)	

#define MSLUG4_BFIRE_MVS_FILL \
	ROM_FILL(0xC4625,1,0x02)

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

#define MSLUG4_THUNDERCLOUD_MVS_FILL \
	ROM_FILL(0xC4631,1,0x11) \
	ROM_FILL(0xC4C7C,1,0x11)

#define MSLUG4_DUALMACHINEGUN_MVS_FILL \
	ROM_FILL(0xC4631,1,0x12) \
	ROM_FILL(0xC4C7C,1,0x12)

#define MSLUG4_ENEMYCHASER_MVS_FILL \
	ROM_FILL(0xC4631,1,0x0C) \
	ROM_FILL(0xC4C7C,1,0x0C)

#define MSLUG5H_AMMUNITION2X_MVS_FILL \
    ROM_FILL(0x1C2B1,1,0x3C)\
	ROM_FILL(0x1C2BB,1,0x3C)\
	ROM_FILL(0x1C2C5,1,0x3C)\
	ROM_FILL(0x1C2CF,1,0xFF)\
	ROM_FILL(0x1C2D9,1,0xFF)\
	ROM_FILL(0x1C2E3,1,0x1E)\
	ROM_FILL(0x1C2ED,1,0x3C)\
    ROM_FILL(0x1C2F7,1,0x3C)\
    ROM_FILL(0x1C301,1,0xFF)\
	ROM_FILL(0x1C30B,1,0xFF)\
	ROM_FILL(0x1C315,1,0x50)\
	ROM_FILL(0x1C31F,1,0x3C)\
	ROM_FILL(0x1C329,1,0x3C)\
	ROM_FILL(0x1C333,1,0x28)\
	ROM_FILL(0x1C33D,1,0xFF)\
    ROM_FILL(0x1C347,1,0x3C)\
    ROM_FILL(0x1C351,1,0xFF)

#define MSLUG5H_SOLDIERDOESNTDISAPPEARWHENHEDIES_MVS_FILL \
    ROM_FILL(0xCDD58,1,0x5E)
	
#define MSLUG5H_FLASHOFF_MVS_FILL \
    ROM_FILL(0x8724,1,0x4E)\
	ROM_FILL(0x8725,1,0x71)\
	ROM_FILL(0x8726,1,0x4E)\
	ROM_FILL(0x8727,1,0x71)

#define MSLUG5H_POWNEVERLOSE_MVS_FILL \
    ROM_FILL(0xB7A2E,1,0x4E)\
	ROM_FILL(0xB7A2F,1,0x71)\
	ROM_FILL(0xB7A48,1,0x4E)\
	ROM_FILL(0xB7A49,1,0x71)

#define MSLUG5H_FAT_MVS_FILL \
    ROM_FILL(0x1C251,1,0x03)\
	ROM_FILL(0x1C255,1,0x03)\
	ROM_FILL(0x1C259,1,0x04)\
	ROM_FILL(0x1C274,1,0x03)\
	ROM_FILL(0x1C278,1,0x03)\
	ROM_FILL(0x1C27C,1,0x04)

#define MSLUG5H_BFIRE_MVS_FILL \
	ROM_FILL(0x1BD67,1,0x02)

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

#define MSLUG5H_DUALMACHINEGUN_MVS_FILL \
	ROM_FILL(0x1BD73,1,0x12) \
	ROM_FILL(0x1C298,1,0x12)

#define MSLUG5H_ENEMYCHASER_MVS_FILL \
	ROM_FILL(0x1BD73,1,0x0C) \
	ROM_FILL(0x1C298,1,0x0C)

#define MSLUGX_AUTOFIRE_MVS_FILL \
	ROM_FILL(0x3CC17,1,0x00)

#define MSLUGX_CHANGETANKSLUGTEXT_MVS_FILL \
    ROM_FILL(0x35240,1,0xB1)\
    ROM_FILL(0x35241,1,0x9C)

#define MSLUGX_CHANGETHESKYOFLEVEL1_MVS_FILL \
    ROM_FILL(0xB537D,1,0x3C)\
	ROM_FILL(0xB537E,1,0xFB)\
    ROM_FILL(0xB537F,1,0x7C)\
	ROM_FILL(0xB5385,1,0x20)\
    ROM_FILL(0xB5387,1,0x13)

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

#define MSLUGX_BOSS_MVS_FILL
	ROM_FILL(0x892D8,1,0x5F)\
	ROM_FILL(0x4B6D6,1,0x50)

#define MSLUGX_STARTWALKINGALLLEVELS_MVS_FILL \
    ROM_FILL(0x2D5C20,1,0x03)\
	ROM_FILL(0x2D5F5C,1,0x03)\
	ROM_FILL(0x2D6034,1,0x03)

#define MSLUGX_SPEEDUPLEVELTEXTLEVEL_MVS_FILL \
	ROM_FILL(0x608FE,1,0x67)

#define MSLUGX_SOLDIERDOESNTDISAPPEARWHENHEDIES_MVS_FILL \
    ROM_FILL(0x399FC,1,0x5E)\
    ROM_FILL(0x39CBE,1,0x5E)\
	ROM_FILL(0x40E1A,1,0x5E)\
    ROM_FILL(0x45ABA,1,0x5E)

#define MSLUGX_THEYTEARYOUAPARTWHENITDIES_MVS_FILL \
    ROM_FILL(0xC370F,1,0x06)\
    ROM_FILL(0xC3710,1,0x7D)\
	ROM_FILL(0xC3711,1,0x06)\

#define MSLUGX_LIFE+_MVS_FILL \
    ROM_FILL(0xC95E6,1,0x52)

#define MSLUGX_ALLENO'NEILBLACK_MVS_FILL \
    ROM_FILL(0x3EC01,1,0x05)\
    ROM_FILL(0x3EC02,1,0x35)\
	ROM_FILL(0x3EC03,1,0xAE)

#define MSLUGX_FLASHOFF_MVS_FILL \
    ROM_FILL(0x9744,1,0x4E)\
	ROM_FILL(0x9745,1,0x71)\
    ROM_FILL(0x9746,1,0x4E)\
	ROM_FILL(0x9747,1,0x71)

#define MSLUGX_WEAPONANIMATION_MVS_FILL \
    ROM_FILL(0x2D0AFD,1,0x0B)\
    ROM_FILL(0x1B4CB,1,0x0A)\	
    ROM_FILL(0x1B4DB,1,0x0A)\	
    ROM_FILL(0x1B4EB,1,0x0A)\	
    ROM_FILL(0x1B4FB,1,0x0A)\	
    ROM_FILL(0x1B50B,1,0x0A)\	
    ROM_FILL(0x1B51B,1,0x0A)\	
    ROM_FILL(0x1B52B,1,0x0A)\	
    ROM_FILL(0x1B53B,1,0x0A)\	
    ROM_FILL(0x1B54B,1,0x0A)\	
    ROM_FILL(0x1B55B,1,0x0A)\	
    ROM_FILL(0x1B56B,1,0x0A)\
    ROM_FILL(0x1B57B,1,0x0A)\
    ROM_FILL(0x1B58B,1,0x0A)\
    ROM_FILL(0x1B59B,1,0x0A)\
    ROM_FILL(0x1B5AB,1,0x0A)\
    ROM_FILL(0x1B5BB,1,0x0A)\
    ROM_FILL(0xA714F,1,0x08)\
    ROM_FILL(0xA715F,1,0x08)\
    ROM_FILL(0x1F09F,1,0x09)\
    ROM_FILL(0x1F0BF,1,0x09)\
    ROM_FILL(0x1F0DF,1,0x09)\
    ROM_FILL(0x1F0EF,1,0x09)\
    ROM_FILL(0x1F10F,1,0x09)\
    ROM_FILL(0x1F13F,1,0x09)\
    ROM_FILL(0x1F14F,1,0x09)\
    ROM_FILL(0x1F15F,1,0x09)\
    ROM_FILL(0x635E9,1,0x07)\
    ROM_FILL(0x63609,1,0x07)\
    ROM_FILL(0x63629,1,0x07)\
    ROM_FILL(0x63639,1,0x07)\
    ROM_FILL(0x63649,1,0x07)\
    ROM_FILL(0x63659,1,0x07)\
    ROM_FILL(0x63689,1,0x07)\
    ROM_FILL(0x63699,1,0x07)\
    ROM_FILL(0x636A9,1,0x07)\
    ROM_FILL(0xE133B,1,0x0D)\
    ROM_FILL(0xE134B,1,0x0D)\
    ROM_FILL(0xE135B,1,0x0D)\
    ROM_FILL(0xE136B,1,0x0D)\
    ROM_FILL(0xE137B,1,0x0D)\
    ROM_FILL(0xE138B,1,0x0D)\
    ROM_FILL(0xE139B,1,0x0D)\
    ROM_FILL(0xE13AB,1,0x0D)\
    ROM_FILL(0xE13BB,1,0x0D)\
    ROM_FILL(0xE13CB,1,0x0D)\
    ROM_FILL(0xE13DB,1,0x0D)\
    ROM_FILL(0xE13EB,1,0x0D)\
    ROM_FILL(0xEB5DF,1,0x0B)\
    ROM_FILL(0xEB5EF,1,0x0B)\
    ROM_FILL(0xEB5FF,1,0x0B)\
    ROM_FILL(0xEB60F,1,0x0B)\
    ROM_FILL(0xEB61F,1,0x0B)\
    ROM_FILL(0xEB62F,1,0x0B)\
    ROM_FILL(0xEB63F,1,0x0B)\
    ROM_FILL(0xEB64F,1,0x0B)\
    ROM_FILL(0xE4E4D,1,0x0E)\
    ROM_FILL(0xE4E5D,1,0x05)\
    ROM_FILL(0xE4E6D,1,0x05)\
    ROM_FILL(0xE4E7D,1,0x05)

#define MSLUGX_LEVEL6START_FILL \
    ROM_FILL(0x2DF6CD,1,0x1C)\
	ROM_FILL(0x2DF6CF,1,0x58)\
    ROM_FILL(0x2DF6D1,1,0x58)\
	ROM_FILL(0x2DF6D3,1,0x4F)\
	ROM_FILL(0x2DF6D5,1,0x06)

#define MSLUGX_POWNEVERLOSE_MVS_FILL \
    ROM_FILL(0x9AAB3,1,0xFE)\

#define MSLUGX_FAT_MVS_FILL \
    ROM_FILL(0xC0E75,1,0x02)\
	ROM_FILL(0xC33DD,1,0x02)

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
/*************************************
    Game specific input definitions
 *************************************/

INPUT_PORTS_START( mslughb )
	PORT_INCLUDE( neogeo )

	PORT_MODIFY("DSW")
	PORT_DIPNAME( 0x02, 0x00, DEF_STR( Cabinet ) ) PORT_DIPLOCATION("SW:2")
	PORT_DIPSETTING(    0x00, DEF_STR( Normal ) )
	PORT_DIPSETTING(    0x02, "VS Mode" )
	PORT_DIPNAME( 0x40, 0x00, DEF_STR( Free_Play ) ) PORT_DIPLOCATION("SW:7")
	PORT_DIPSETTING(    0x00, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x40, DEF_STR( On ) )
INPUT_PORTS_END

INPUT_PORTS_START( mslughw )
	PORT_INCLUDE( neogeo )

	PORT_MODIFY("DSW")
	PORT_DIPNAME( 0x40, 0x00, DEF_STR( Free_Play ) ) PORT_DIPLOCATION("SW:7")
	PORT_DIPSETTING(    0x00, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x40, DEF_STR( On ) )
INPUT_PORTS_END

INPUT_PORTS_START( ms5pcb )
	PORT_INCLUDE( mslughb )

	PORT_MODIFY("DSW")
	PORT_DIPNAME( 0x04, 0x00, DEF_STR( Region ) ) PORT_DIPLOCATION("SW:3") PORT_CHANGED_MEMBER(DEVICE_SELF, neogeo_state, select_bios, 0)
	PORT_DIPSETTING(    0x00, DEF_STR( Asia ) )
	PORT_DIPSETTING(    0x04, DEF_STR( Japan ) )
INPUT_PORTS_END

INPUT_PORTS_START( mslug5sg )
	PORT_INCLUDE( mslughb )

	PORT_MODIFY("DSW")
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_UP )
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN )
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT )
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT )
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 )
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 )
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON3 )
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_BUTTON4 )

	PORT_MODIFY("P2")
	PORT_BIT( 0x00ff, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_CODE(KEYCODE_EQUALS) PORT_PLAYER(2)
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_CODE(KEYCODE_EQUALS) PORT_PLAYER(2)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_PLAYER(2)
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_PLAYER(2)
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(2)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(2)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(2)
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_BUTTON4 ) PORT_PLAYER(2)
INPUT_PORTS_END

/*************************************
   Game specific Rom_Fill definitions
 *************************************/

#define FIX_BIOS_TIME_FILL \
    ROM_FILL(0x1F00A,1,0x30)

#define FIX_BIOS_COIN_FILL \
    ROM_FILL(0x1F001,1,0x01) \
    ROM_FILL(0x1F003,1,0x01)

#define FIXED_BIOS_COIN_FILL \
    ROM_FILL(0x1F001,1,0x01)

#define MSLUG_MVS_FILL \
    ROM_FILL(0x1783E7,1,0x78)\
	ROM_FILL(0x1783EB,1,0x12)\
	ROM_FILL(0x1783E8,1,0x34)\
	ROM_FILL(0x1783EE,1,0x23)\
	ROM_FILL(0x1783EA,1,0x02)
//	ROM_FILL(0x1783ED,1,0x34)
//	ROM_FILL(0x1783E9,1,0x02)
//	ROM_FILL(0x1783E6,1,0x02)
//	ROM_FILL(0x1783E4,1,0x04)

#define MSLUG_AES_FILL \
	ROM_FILL(0x100B,1,0x99)

#define MSLUG_ESSENTIALPATCH_MODS_FILL \
    ROM_FILL(0x13830,1,0x4E)\
	ROM_FILL(0x13831,1,0x71)\
	ROM_FILL(0x13832,1,0x4E)\
	ROM_FILL(0x13833,1,0x71)\
    ROM_FILL(0x25A44,1,0x4E)\
	ROM_FILL(0x25A45,1,0x71)\
	ROM_FILL(0x25DEA,1,0x4E)\
	ROM_FILL(0x25DEB,1,0x71)\

#define MSLUG_CUSTOMPATCH_MODS_FILL \
    ROM_FILL(0x1F4C99,1,0x47)\
	ROM_FILL(0x1F4C9A,1,0x41)\
	ROM_FILL(0x1F4C9B,1,0x53)\
    ROM_FILL(0x1F4C9C,1,0x54)\
    ROM_FILL(0x1F4C9D,1,0x4F)\
    ROM_FILL(0x1F4C9E,1,0x4E)\
    ROM_FILL(0x1F4C9F,1,0x39)\
	ROM_FILL(0x1F4CA0,1,0x30)\
    ROM_FILL(0x1F4CA1,1,0x20)\
    ROM_FILL(0x1F4CA2,1,0x45)\
    ROM_FILL(0x1F4CA3,1,0x44)\
	ROM_FILL(0x1F4CA4,1,0x49)\
    ROM_FILL(0x1F4CA5,1,0x54)\
	ROM_FILL(0x1F4CA6,1,0x49)\
    ROM_FILL(0x1F4CA7,1,0x4F)\
	ROM_FILL(0x1F4CA8,1,0x4E)\
    ROM_FILL(0x1F4CA9,1,0x20)\
    ROM_FILL(0x1F4CAA,1,0x32)\
	ROM_FILL(0x1F4CAB,1,0x30)\
    ROM_FILL(0x1F4CAC,1,0x32)\
    ROM_FILL(0x1F4CAD,1,0x33)\
    ROM_FILL(0x1F4CAE,1,0x2E)\
    ROM_FILL(0x1F4CAF,1,0x20)
	
#define MSLUG2_MVS_FILL \
    ROM_FILL(0x100D,1,0x78)\
	ROM_FILL(0x1011,1,0x12)\
	ROM_FILL(0x1013,1,0x34)\
	ROM_FILL(0x100E,1,0x34)\
	ROM_FILL(0x1014,1,0x34)\
	ROM_FILL(0x1010,1,0x02)
//	ROM_FILL(0x100F,1,0x02)
//	ROM_FILL(0x100C,1,0x02)
//	ROM_FILL(0x100A,1,0x04)

#define MSLUG2_AES_FILL \
	ROM_FILL(0x902,1,0x99) \
	ROM_FILL(0x903,1,0x99) \
	ROM_FILL(0x1954,1,0x60)

#define MSLUG2_ESSENTIALPATCH_MODS_FILL \
	ROM_FILL(0x6FE88,1,0x67)\
    ROM_FILL(0xE006D,1,0x03)\
	ROM_FILL(0xE02CD,1,0x03)\
	ROM_FILL(0xE0377,1,0x03)\
	ROM_FILL(0xE03E5,1,0x03)\
	ROM_FILL(0xE04CF,1,0x03)\
    ROM_FILL(0x715D4,1,0x5E)\
	ROM_FILL(0x7178A,1,0x5E)\
	ROM_FILL(0x8BEF2,1,0x5E)\
	ROM_FILL(0xA89BA,1,0x5E)\
    ROM_FILL(0x859E6,1,0x4E)\
	ROM_FILL(0x859E7,1,0x71)\
	ROM_FILL(0x859E8,1,0x4E)\
	ROM_FILL(0x859E9,1,0x71)\
	ROM_FILL(0x4A423,1,0xDC)\
	ROM_FILL(0xA4982,1,0x58)\
	ROM_FILL(0xB00F2,1,0x50)

#define MSLUG2T_ESSENTIALPATCH_MODS_FILL \
	ROM_FILL(0x108,1,0x09)\
    ROM_FILL(0x11F7,1,0xCF)\
	ROM_FILL(0x11F8,1,0xF9)\
	ROM_FILL(0x11F9,1,0xDD)\
	ROM_FILL(0x11FA,1,0xF7)\
	ROM_FILL(0x1450,1,0x70)\
    ROM_FILL(0x1451,1,0x02)\
	ROM_FILL(0x1452,1,0x4E)\
	ROM_FILL(0x1453,1,0x71)\
	ROM_FILL(0x1454,1,0x4E)\
    ROM_FILL(0x1455,1,0x71)\
	ROM_FILL(0x1456,1,0x4E)\
	ROM_FILL(0x1457,1,0x71)\
	ROM_FILL(0x1458,1,0x4E)\
	ROM_FILL(0x1459,1,0x71)\
	ROM_FILL(0x1464,1,0x4E)\
	ROM_FILL(0x1465,1,0x71)\
    ROM_FILL(0x1466,1,0x4E)\
	ROM_FILL(0x1467,1,0x71)\
	ROM_FILL(0x1468,1,0x4E)\
	ROM_FILL(0x1469,1,0x71)\
	ROM_FILL(0x146A,1,0x4E)\
    ROM_FILL(0x146B,1,0x71)\
	ROM_FILL(0x146C,1,0x4E)\
	ROM_FILL(0x146D,1,0x71)\
	ROM_FILL(0x147D,1,0x50)\
    ROM_FILL(0x1487,1,0x46)\
	ROM_FILL(0x14D2,1,0x52)\
	ROM_FILL(0x14D3,1,0x2D)\
	ROM_FILL(0x14D4,1,0x80)\
	ROM_FILL(0x14D5,1,0x8D)\
	ROM_FILL(0x14D6,1,0x4E)\
	ROM_FILL(0x14D7,1,0x71)\
    ROM_FILL(0x1650,1,0x4E)\
	ROM_FILL(0x1651,1,0xF9)\
	ROM_FILL(0x1653,1,0x0D)\
	ROM_FILL(0x1655,1,0x00)\
	ROM_FILL(0x1656,1,0x4E)\
    ROM_FILL(0x1657,1,0x71)\
	ROM_FILL(0x165E,1,0x4E)\
	ROM_FILL(0x165F,1,0x71)\
	ROM_FILL(0x1660,1,0x4E)\
    ROM_FILL(0x1661,1,0x71)\
	ROM_FILL(0x1662,1,0x4E)\
	ROM_FILL(0x1663,1,0x71)\
	ROM_FILL(0xD8000,1,0x0C)\
	ROM_FILL(0xD8001,1,0x2D)\
	ROM_FILL(0xD8002,1,0x00)\
	ROM_FILL(0xD8003,1,0x02)\
    ROM_FILL(0xD8004,1,0x80)\
	ROM_FILL(0xD8005,1,0x8D)\
	ROM_FILL(0xD8006,1,0x65)\
	ROM_FILL(0xD8007,1,0xF8)\
	ROM_FILL(0xD8008,1,0x1B)\
    ROM_FILL(0xD8009,1,0x7C)\
	ROM_FILL(0xD800A,1,0x00)\
	ROM_FILL(0xD800B,1,0x00)\
	ROM_FILL(0xD800C,1,0x80)\
    ROM_FILL(0xD800D,1,0x8D)\
	ROM_FILL(0xD800E,1,0x4E)\
	ROM_FILL(0xD800F,1,0xF9)\
	ROM_FILL(0xD8010,1,0x00)\
	ROM_FILL(0xD8011,1,0x00)\
	ROM_FILL(0xD8012,1,0x16)\
	ROM_FILL(0xD8013,1,0x58)\
	ROM_FILL(0x6FE88,1,0x67)\
    ROM_FILL(0xE006D,1,0x03)\
	ROM_FILL(0xE02CD,1,0x03)\
	ROM_FILL(0xE0377,1,0x03)\
	ROM_FILL(0xE03E5,1,0x03)\
	ROM_FILL(0xE04CF,1,0x03)\
    ROM_FILL(0x715D4,1,0x5E)\
	ROM_FILL(0x7178A,1,0x5E)\
	ROM_FILL(0x8BEF2,1,0x5E)\
	ROM_FILL(0xA89BA,1,0x5E)\
    ROM_FILL(0x859E6,1,0x4E)\
	ROM_FILL(0x859E7,1,0x71)\
	ROM_FILL(0x859E8,1,0x4E)\
	ROM_FILL(0x859E9,1,0x71)\
	ROM_FILL(0x4A423,1,0xDC)\
	ROM_FILL(0xA4982,1,0x58)\
	ROM_FILL(0xB00F2,1,0x50)

#define MSLUG2_CUSTOMPATCH_MODS_FILL \
	ROM_FILL(0xF7769,1,0x0A)\
	ROM_FILL(0xB00F2,1,0x50)

#define MSLUG2_FATPLAYERS_MODS_FILL \
	ROM_FILL(0x929B7,1,0x02)\
	ROM_FILL(0x94A28,1,0x02)\
	ROM_FILL(0x929DF,1,0x02)

#define MSLUG3H_MVS_FILL \
    ROM_FILL(0x2EA7,1,0x78)\
	ROM_FILL(0x2EAE,1,0x12)\
	ROM_FILL(0x2EAF,1,0x12)\
	ROM_FILL(0x2EAB,1,0x34)\
	ROM_FILL(0x2EA8,1,0x34)\
	ROM_FILL(0x2EAD,1,0x23)\
	ROM_FILL(0x2EAA,1,0x02)
//	ROM_FILL(0x605A,1,0x92)
//	ROM_FILL(0x2EA9,1,0x02)
//	ROM_FILL(0x2EA6,1,0x02)
//	ROM_FILL(0x2EA4,1,0x04)

#define MSLUG3B6_MVS_FILL \
    ROM_FILL(0x2EA7,1,0x88)\
	ROM_FILL(0x2EAE,1,0x12)\
	ROM_FILL(0x2EAB,1,0x34)\
	ROM_FILL(0x2EA8,1,0x34)\
	ROM_FILL(0x2EAD,1,0x23)\
	ROM_FILL(0x2EAA,1,0x02)
//	ROM_FILL(0x605A,1,0x92)
//	ROM_FILL(0x2EA9,1,0x02)
//	ROM_FILL(0x2EA6,1,0x02)
//	ROM_FILL(0x2EA4,1,0x04)
//	ROM_FILL(0x2EAF,1,0x12)

#define MSLUG3H_AES_FILL \
	ROM_FILL(0x27C6,1,0x99)\
	ROM_FILL(0x27C7,1,0x99)\
	ROM_FILL(0x6058,1,0x60)

#define MSLUG3DD_ESSENTIALPATCH_MODS_FILL \
    ROM_FILL(0x96922,1,0x5E)\
    ROM_FILL(0x8E4DE,1,0x4E)\
	ROM_FILL(0x8E4DF,1,0x71)\
	ROM_FILL(0x8E4E0,1,0x4E)\
	ROM_FILL(0x8E4E1,1,0x71)\
    ROM_FILL(0xD300,1,0x4E)\
	ROM_FILL(0xD301,1,0x71)\
	ROM_FILL(0xD302,1,0x4E)\
	ROM_FILL(0xD303,1,0x71)

#define MSLUG3LW_FIX_FILL \
    ROM_FILL(0x39527,1,0x53) // Fix Remikare

#define MSLUG3WZ_FIX_FILL \
	ROM_FILL(0x3C26,1,0x4E)\
	ROM_FILL(0x3C27,1,0xB9)\
	ROM_FILL(0x3C29,1,0x0F)\
	ROM_FILL(0x3C2A,1,0xB2)\
	ROM_FILL(0x3C2B,1,0xD0)

#define MSLUG3GW_FIX_FILL \
    ROM_FILL(0xDF1FB,1,0x06)

#define MSLUG3H_ESSENTIALPATCH_MODS_FILL \
	ROM_FILL(0x333661,1,0x02)\
	ROM_FILL(0x333662,1,0x84)\
	ROM_FILL(0x333663,1,0xCE)\
	ROM_FILL(0x333665,1,0x03)\
	ROM_FILL(0x333666,1,0x98)\
	ROM_FILL(0x333667,1,0x74)\
	ROM_FILL(0x331E0D,1,0x02)\
	ROM_FILL(0x331E0E,1,0x84)\
	ROM_FILL(0x331E0F,1,0xCE)\
	ROM_FILL(0x331E11,1,0x03)\
	ROM_FILL(0x331E12,1,0x98)\
	ROM_FILL(0x331E13,1,0x74)\
    ROM_FILL(0x96902,1,0x5E)\
    ROM_FILL(0x8E4BE,1,0x4E)\
	ROM_FILL(0x8E4BF,1,0x71)\
	ROM_FILL(0x8E4C0,1,0x4E)\
	ROM_FILL(0x8E4C1,1,0x71)\
    ROM_FILL(0xD300,1,0x4E)\
	ROM_FILL(0xD301,1,0x71)\
	ROM_FILL(0xD302,1,0x4E)\
	ROM_FILL(0xD303,1,0x71)

#define MSLUG3H_CUSTOMPATCH_MODS_FILL \
	ROM_FILL(0x333661,1,0x02)\
	ROM_FILL(0x333662,1,0x84)\
	ROM_FILL(0x333663,1,0xCE)\
	ROM_FILL(0x333665,1,0x03)\
	ROM_FILL(0x333666,1,0x98)\
	ROM_FILL(0x333667,1,0x74)\
	ROM_FILL(0x331E0D,1,0x02)\
	ROM_FILL(0x331E0E,1,0x84)\
	ROM_FILL(0x331E0F,1,0xCE)\
	ROM_FILL(0x331E11,1,0x03)\
	ROM_FILL(0x331E12,1,0x98)\
	ROM_FILL(0x331E13,1,0x74)\
    ROM_FILL(0x3205A,1,0x47)\
	ROM_FILL(0x3205B,1,0x41)\
	ROM_FILL(0x3205C,1,0x53)\
    ROM_FILL(0x3205D,1,0x54)\
    ROM_FILL(0x3205E,1,0x4F)\
    ROM_FILL(0x3205F,1,0x4E)\
    ROM_FILL(0x32060,1,0x39)\
    ROM_FILL(0x32061,1,0x30)\
	ROM_FILL(0x32062,1,0x20)\
    ROM_FILL(0x32063,1,0x45)\
    ROM_FILL(0x32064,1,0x44)\
    ROM_FILL(0x32065,1,0x49)\
	ROM_FILL(0x32066,1,0x54)\
    ROM_FILL(0x32067,1,0x49)\
	ROM_FILL(0x32068,1,0x4F)\
    ROM_FILL(0x32069,1,0x4E)\
	ROM_FILL(0x3206A,1,0x20)\
	ROM_FILL(0x3206B,1,0x32)\
    ROM_FILL(0x3206C,1,0x30)\
    ROM_FILL(0x3206D,1,0x32)\
    ROM_FILL(0x3206E,1,0x33)\
    ROM_FILL(0x3206F,1,0x2E)\
    ROM_FILL(0x32070,1,0x20)\
	ROM_FILL(0x32071,1,0x20)\
	ROM_FILL(0x32072,1,0x20)

#define MSLUG3H_FATPLAYERS_MODS_FILL \
	ROM_FILL(0x21719,1,0x11)\
	ROM_FILL(0x21C2A,1,0x11)\
	ROM_FILL(0x2170D,1,0x02)\
    ROM_FILL(0x21B3E,1,0x02)\
	ROM_FILL(0x21B46,1,0x02)\
	ROM_FILL(0x21B5E,1,0x02)\
	ROM_FILL(0x21B5F,1,0x02)\
	ROM_FILL(0x21B66,1,0x02)\
	ROM_FILL(0x21B67,1,0x02)\
	ROM_FILL(0x21B7E,1,0x02)\
    ROM_FILL(0x21B86,1,0x02)\
    ROM_FILL(0x21B88,1,0x02)\
	ROM_FILL(0x21B9E,1,0x02)\
	ROM_FILL(0x21BA6,1,0x02)\
	ROM_FILL(0x21BAA,1,0x02)\
	ROM_FILL(0x21BBE,1,0x02)\
	ROM_FILL(0x21BC6,1,0x02)\
    ROM_FILL(0x21BCB,1,0x02)\
	ROM_FILL(0x21BFE,1,0x02)\
	ROM_FILL(0x21C06,1,0x02)\
	ROM_FILL(0x21C09,1,0x02)\
	ROM_FILL(0x21C0A,1,0x02)\
	ROM_FILL(0x21C0C,1,0x02)\
	ROM_FILL(0x21C0D,1,0x02)

#define MSLUG4_MVS_FILL \
    ROM_FILL(0x1741,1,0x78)\
	ROM_FILL(0x1748,1,0x12)\
	ROM_FILL(0x1749,1,0x12)\
	ROM_FILL(0x1745,1,0x34)\
	ROM_FILL(0x1742,1,0x34)\
	ROM_FILL(0x1747,1,0x23)\
	ROM_FILL(0x1744,1,0x02)
//	ROM_FILL(0x1743,1,0x02)
//	ROM_FILL(0x1740,1,0x02)
//	ROM_FILL(0x173E,1,0x04)

#define MSLUG4DD_MVS_FILL \
    ROM_FILL(0x1741,1,0x78)\
	ROM_FILL(0x1748,1,0x12)\
	ROM_FILL(0x1745,1,0x34)\
	ROM_FILL(0x1742,1,0x34)\
	ROM_FILL(0x1747,1,0x23)\
	ROM_FILL(0x1744,1,0x02)
//	ROM_FILL(0x1743,1,0x02)
//	ROM_FILL(0x1740,1,0x02)
//	ROM_FILL(0x173E,1,0x04)
//	ROM_FILL(0x1749,1,0x12)

#define MSLUG4_AES_FILL \
	ROM_FILL(0x7FE,1,0x99)\
	ROM_FILL(0x7FF,1,0x99)

#define MSLUG4H_AES_FILL \
	ROM_FILL(0x7FE,1,0x99)\
	ROM_FILL(0x7FF,1,0x99)\
	ROM_FILL(0xA864C,1,0x60)

#define MSLUG4_ESSENTIALPATCH_MODS_FILL \
	ROM_FILL(0x21B3F6,1,0x7F)\
	ROM_FILL(0x21B3F7,1,0xFF)\
	ROM_FILL(0x21B402,1,0x7F)\
	ROM_FILL(0x21B403,1,0xFF)\
    ROM_FILL(0x15456,1,0x5E)\
	ROM_FILL(0x1A764,1,0x5E)\
	ROM_FILL(0x56134,1,0x5E)\
	ROM_FILL(0x562E6,1,0x5E)\
	ROM_FILL(0x5AE16,1,0x5E)\
    ROM_FILL(0xA7530,1,0x4E)\
	ROM_FILL(0xA7531,1,0x71)\
	ROM_FILL(0xA7532,1,0x4E)\
	ROM_FILL(0xA7533,1,0x71)\
	ROM_FILL(0x1F14E,1,0x4E)\
	ROM_FILL(0x1F14F,1,0x71)

#define MSLUG4H_ESSENTIALPATCH_MODS_FILL \
	ROM_FILL(0x21B3F6,1,0x7F)\
	ROM_FILL(0x21B3F7,1,0xFF)\
	ROM_FILL(0x21B402,1,0x7F)\
	ROM_FILL(0x21B403,1,0xFF)\
    ROM_FILL(0x1551C,1,0x5E)\
	ROM_FILL(0x1A82A,1,0x5E)\
	ROM_FILL(0x561FA,1,0x5E)\
	ROM_FILL(0x563AC,1,0x5E)\
	ROM_FILL(0x5AEDC,1,0x5E)\
    ROM_FILL(0xA7ACA,1,0x4E)\
	ROM_FILL(0xA7ACB,1,0x71)\
	ROM_FILL(0xA7ACC,1,0x4E)\
	ROM_FILL(0xA7ACD,1,0x71)\
	ROM_FILL(0x1F214,1,0x4E)\
	ROM_FILL(0x1F215,1,0x71)

#define MSLUG4_CUSTOMPATCH_MODS_FILL \
    ROM_FILL(0x8EF4F,1,0x4F)\
    ROM_FILL(0x8EF50,1,0x4E)\
	ROM_FILL(0x8EF51,1,0x4C)\
	ROM_FILL(0x8EF52,1,0x59)\
    ROM_FILL(0x8EF54,1,0x45)\
    ROM_FILL(0x8EF55,1,0x58)\
    ROM_FILL(0x8EF56,1,0x43)\
    ROM_FILL(0x8EF57,1,0x4C)\
    ROM_FILL(0x8EF58,1,0x55)\
	ROM_FILL(0x8EF59,1,0x53)\
    ROM_FILL(0x8EF5A,1,0x49)\
    ROM_FILL(0x8EF5B,1,0x56)\
    ROM_FILL(0x8EF5C,1,0x45)\
	ROM_FILL(0x8EF5D,1,0x20)\
    ROM_FILL(0x8EF5E,1,0x41)\
	ROM_FILL(0x8EF5F,1,0x54)\
    ROM_FILL(0x8EF60,1,0x20)\
	ROM_FILL(0x8EF61,1,0x48)\
	ROM_FILL(0x8EF62,1,0x42)\
    ROM_FILL(0x8EF63,1,0x4D)\
    ROM_FILL(0x8EF64,1,0x41)\
    ROM_FILL(0x8EF65,1,0x4D)\
    ROM_FILL(0x8EF66,1,0x45)\
    ROM_FILL(0x8EF67,1,0x2E)\
	ROM_FILL(0x8EF68,1,0x20)\
	ROM_FILL(0x8EF69,1,0x20)\
    ROM_FILL(0x8EF75,1,0x47)\
	ROM_FILL(0x8EF76,1,0x41)\
	ROM_FILL(0x8EF77,1,0x53)\
    ROM_FILL(0x8EF78,1,0x54)\
    ROM_FILL(0x8EF79,1,0x4F)\
    ROM_FILL(0x8EF7A,1,0x4E)\
    ROM_FILL(0x8EF7B,1,0x39)\
    ROM_FILL(0x8EF7C,1,0x30)\
	ROM_FILL(0x8EF7D,1,0x20)\
    ROM_FILL(0x8EF7E,1,0x45)\
    ROM_FILL(0x8EF7F,1,0x44)\
    ROM_FILL(0x8EF80,1,0x49)\
	ROM_FILL(0x8EF81,1,0x54)\
    ROM_FILL(0x8EF82,1,0x49)\
	ROM_FILL(0x8EF83,1,0x4F)\
    ROM_FILL(0x8EF84,1,0x4E)\
	ROM_FILL(0x8EF85,1,0x20)\
	ROM_FILL(0x8EF86,1,0x32)\
    ROM_FILL(0x8EF87,1,0x30)\
    ROM_FILL(0x8EF88,1,0x32)\
    ROM_FILL(0x8EF89,1,0x33)\
    ROM_FILL(0x8EF8A,1,0x2E)\
    ROM_FILL(0x8EF8B,1,0x20)\
	ROM_FILL(0x8EF8C,1,0x20)\
	ROM_FILL(0x8EF8D,1,0x20)\
	ROM_FILL(0x8EF8E,1,0x20)\
    ROM_FILL(0x1F5E8,1,0x32)\
	ROM_FILL(0x1F5E9,1,0x30)\
	ROM_FILL(0x1F5EA,1,0x32)\
	ROM_FILL(0x1F5EB,1,0x33)

#define MSLUG4_FATPLAYERS_MODS_FILL \
	ROM_FILL(0xC4625,1,0x02)\
	ROM_FILL(0xC4631,1,0x11)\
	ROM_FILL(0xC4C7C,1,0x11)\
    ROM_FILL(0xC4AE2,1,0x02)\
	ROM_FILL(0xC4B00,1,0x02)\
	ROM_FILL(0xC4B01,1,0x02)\
	ROM_FILL(0xC4B0A,1,0x02)\
	ROM_FILL(0xC4B0B,1,0x02)\
	ROM_FILL(0xC4B32,1,0x02)\
	ROM_FILL(0xC4B34,1,0x02)\
    ROM_FILL(0xC4B5E,1,0x02)\
    ROM_FILL(0xC4B5A,1,0x02)\
	ROM_FILL(0xC4B82,1,0x02)\
	ROM_FILL(0xC4B87,1,0x02)\
	ROM_FILL(0xC4BB2,1,0x02)\
	ROM_FILL(0xC4BB3,1,0x02)\
	ROM_FILL(0xC4BD2,1,0x02)\
    ROM_FILL(0xC4BD5,1,0x02)\
    ROM_FILL(0xC4BD6,1,0x02)\
	ROM_FILL(0xC4BD9,1,0x02)\
	ROM_FILL(0xC4BDA,1,0x02)\
	ROM_FILL(0xC4BDB,1,0x02)\
	ROM_FILL(0xC4BFA,1,0x02)\
	ROM_FILL(0xC4BFC,1,0x02)\
	ROM_FILL(0xC4BFE,1,0x02)\
	ROM_FILL(0xC4BFF,1,0x02)\
	ROM_FILL(0xC4C00,1,0x02)\
	ROM_FILL(0xC4607,1,0x02)

#define FIX_FATPLAYERS_FILL \
    ROM_FILL(0xC4609,1,0x93)

#define MSLUG5_MVS_FILL \
    ROM_FILL(0x2CD3,1,0x75)\
	ROM_FILL(0x2CD7,1,0x3B)\
	ROM_FILL(0x2CDA,1,0x8B)\
    ROM_FILL(0x2CD4,1,0x71)\
	ROM_FILL(0x2CDB,1,0x09)\
	ROM_FILL(0x2CD6,1,0x26)
//	ROM_FILL(0x2CD5,1,0x70)
//	ROM_FILL(0x2CD2,1,0x80)
//	ROM_FILL(0x2CD0,1,0x70)

#define MSLUG5_AES_FILL \
	ROM_FILL(0x84A,1,0x57)\
	ROM_FILL(0x84B,1,0x60)

#define MSLUG5H_AES_FILL \
	ROM_FILL(0x84A,1,0x57)\
	ROM_FILL(0x84B,1,0x60)\
	ROM_FILL(0x928E,1,0x49)

#define MSLUG5HD_MVS_FILL \
    ROM_FILL(0x2CD3,1,0x78)\
	ROM_FILL(0x2CDA,1,0x12)\
	ROM_FILL(0x2CDB,1,0x12)\
	ROM_FILL(0x2CD7,1,0x34)\
	ROM_FILL(0x2CD4,1,0x34)\
	ROM_FILL(0x2CD9,1,0x23)\
	ROM_FILL(0x2CD6,1,0x02)
//	ROM_FILL(0x2CD5,1,0x02)
//	ROM_FILL(0x2CD2,1,0x02)
//	ROM_FILL(0x2CD0,1,0x04)

#define MSLUG5HD_AES_FILL \
	ROM_FILL(0x84A,1,0x99)\
	ROM_FILL(0x84B,1,0x99)

#define MSLUG5HDD_AES_FILL \
	ROM_FILL(0x84A,1,0x99)\
	ROM_FILL(0x84B,1,0x99)\
	ROM_FILL(0x928E,1,0x60)

#define MSLUG5SG_MVS_FILL \
    ROM_FILL(0x2CD3,1,0x78)\
	ROM_FILL(0x2CDA,1,0x12)\
	ROM_FILL(0x2CDB,1,0x12)\
	ROM_FILL(0x2CD7,1,0x34)\
	ROM_FILL(0x2CD4,1,0x34)\
	ROM_FILL(0x2CD9,1,0x23)
//	ROM_FILL(0x2CD6,1,0x02)
//	ROM_FILL(0x2CD5,1,0x02)
//	ROM_FILL(0x2CD2,1,0x02)
//	ROM_FILL(0x2CD0,1,0x04)

#define MSLUG5_ESSENTIALPATCH_MVS_FILL \
    ROM_FILL(0x8724,1,0x7A)\
	ROM_FILL(0x8725,1,0x7A)\
	ROM_FILL(0x8726,1,0x99)\
	ROM_FILL(0x8727,1,0x9A)
//  ROM_FILL(0xCDD58,1,0x67)

#define MSLUG5HD_ESSENTIALPATCH_MODS_FILL \
    ROM_FILL(0xCDD58,1,0x5E)\
    ROM_FILL(0x8724,1,0x4E)\
	ROM_FILL(0x8725,1,0x71)\
	ROM_FILL(0x8726,1,0x4E)\
	ROM_FILL(0x8727,1,0x71)\
    ROM_FILL(0xB7A2E,1,0x4E)\
	ROM_FILL(0xB7A2F,1,0x71)\
	ROM_FILL(0xB7A48,1,0x4E)\
	ROM_FILL(0xB7A49,1,0x71)	

#define MSLUG5HDD_ESSENTIALPATCH_MVS_FILL \
    ROM_FILL(0xCDDE0,1,0x5E)\
    ROM_FILL(0x8724,1,0x4E)\
	ROM_FILL(0x8725,1,0x71)\
	ROM_FILL(0x8726,1,0x4E)\
	ROM_FILL(0x8727,1,0x71)\
    ROM_FILL(0xB7A2E,1,0x4E)\
	ROM_FILL(0xB7A2F,1,0x71)\
	ROM_FILL(0xB7A48,1,0x4E)\
	ROM_FILL(0xB7A49,1,0x71)

#define MSLUG5HD_CUSTOMPATCH_MODS_FILL \
    ROM_FILL(0xDDF6A,1,0x47)\
	ROM_FILL(0xDDF6B,1,0x41)\
	ROM_FILL(0xDDF6C,1,0x53)\
    ROM_FILL(0xDDF6D,1,0x54)\
    ROM_FILL(0xDDF6E,1,0x4F)\
    ROM_FILL(0xDDF6F,1,0x4E)\
    ROM_FILL(0xDDF70,1,0x39)\
    ROM_FILL(0xDDF71,1,0x30)\
	ROM_FILL(0xDDF72,1,0x20)\
    ROM_FILL(0xDDF73,1,0x45)\
    ROM_FILL(0xDDF74,1,0x44)\
    ROM_FILL(0xDDF75,1,0x49)\
	ROM_FILL(0xDDF76,1,0x54)\
    ROM_FILL(0xDDF77,1,0x49)\
	ROM_FILL(0xDDF78,1,0x4F)\
    ROM_FILL(0xDDF79,1,0x4E)\
	ROM_FILL(0xDDF7A,1,0x2E)

#define MSLUGX_MVS_FILL \
    ROM_FILL(0x3185,1,0x78)\
	ROM_FILL(0x3189,1,0x12)\
	ROM_FILL(0x318D,1,0x12)\
	ROM_FILL(0x318B,1,0x34)\
	ROM_FILL(0x3186,1,0x34)\
	ROM_FILL(0x318C,1,0x34)\
	ROM_FILL(0x3188,1,0x02)\
    ROM_FILL(0x24F6,1,0x99)\
    ROM_FILL(0x24F7,1,0x99)\
	ROM_FILL(0x156F4,1,0x60)
//  ROM_FILL(0x3187,1,0x02)
//	ROM_FILL(0x3184,1,0x02)
//	ROM_FILL(0x3182,1,0x04)

#define MSLUGXSC_MVS_FILL \
    ROM_FILL(0xEB931,1,0x01)\
	ROM_FILL(0xEB930,1,0x00)\
    ROM_FILL(0xEB937,1,0x01)\
	ROM_FILL(0xEB936,1,0x00)\
    ROM_FILL(0xEB993,1,0x05)\
	ROM_FILL(0xEB9A1,1,0xFB)\
	ROM_FILL(0xEB9A0,1,0xFF)

#define MSLUGX_AES_FILL \
    ROM_FILL(0x24F6,1,0x99)\
    ROM_FILL(0x24F7,1,0x99)\
    ROM_FILL(0x156F4,1,0x60)

#define MSLUGX_ESSENTIALPATCH_MODS_FILL \
    ROM_FILL(0x2D5C20,1,0x03)\
	ROM_FILL(0x2D5E84,1,0x03)\
	ROM_FILL(0x2D5F5C,1,0x03)\
	ROM_FILL(0x2D6034,1,0x03)\
	ROM_FILL(0x2D6130,1,0x03)\
	ROM_FILL(0x2DF6CC,1,0x02)\
    ROM_FILL(0x2DF6CD,1,0x1C)\
	ROM_FILL(0x2DF6CF,1,0x58)\
    ROM_FILL(0x2DF6D1,1,0x58)\
	ROM_FILL(0x2DF6D3,1,0x4F)\
	ROM_FILL(0x2DF6D5,1,0x06)\
	ROM_FILL(0x892D8,1,0x5F)\
	ROM_FILL(0x4B6D6,1,0x50)\
    ROM_FILL(0x35240,1,0xB1)\
    ROM_FILL(0x35241,1,0x9C)\
    ROM_FILL(0x608FE,1,0x67)\
    ROM_FILL(0x399FC,1,0x5E)\
    ROM_FILL(0x39CBE,1,0x5E)\
	ROM_FILL(0x40E1A,1,0x5E)\
    ROM_FILL(0x45ABA,1,0x5E)\
    ROM_FILL(0x9AAB3,1,0xFE)\
    ROM_FILL(0x9744,1,0x4E)\
	ROM_FILL(0x9745,1,0x71)\
    ROM_FILL(0x9746,1,0x4E)\
	ROM_FILL(0x9747,1,0x71)

#define MSLUGXXR_ESSENTIALPATCH_MODS_FILL \
    ROM_FILL(0x2D5C20,1,0x03)\
	ROM_FILL(0x2D5E84,1,0x03)\
	ROM_FILL(0x2D5F5C,1,0x03)\
	ROM_FILL(0x2D6034,1,0x03)\
	ROM_FILL(0x2D6130,1,0x03)\
	ROM_FILL(0x892D8,1,0x5F)\
	ROM_FILL(0x4B6D6,1,0x50)\
    ROM_FILL(0x35240,1,0xB1)\
    ROM_FILL(0x35241,1,0x9C)\
    ROM_FILL(0x608FE,1,0x67)\
    ROM_FILL(0x399FC,1,0x5E)\
    ROM_FILL(0x39CBE,1,0x5E)\
	ROM_FILL(0x40E1A,1,0x5E)\
    ROM_FILL(0x45ABA,1,0x5E)\
    ROM_FILL(0x9AAB3,1,0xFE)\
    ROM_FILL(0x9744,1,0x4E)\
	ROM_FILL(0x9745,1,0x71)\
    ROM_FILL(0x9746,1,0x4E)\
	ROM_FILL(0x9747,1,0x71)

#define MSLUGXV_ESSENTIALPATCH_MODS_FILL \
	ROM_FILL(0x892D8,1,0x5F)\
	ROM_FILL(0x4B6D6,1,0x50)\
    ROM_FILL(0x35240,1,0xB1)\
    ROM_FILL(0x35241,1,0x9C)\
    ROM_FILL(0x608FE,1,0x67)\
    ROM_FILL(0x399FC,1,0x5E)\
    ROM_FILL(0x39CBE,1,0x5E)\
	ROM_FILL(0x40E1A,1,0x5E)\
    ROM_FILL(0x45ABA,1,0x5E)\
    ROM_FILL(0x9744,1,0x4E)\
	ROM_FILL(0x9745,1,0x71)\
    ROM_FILL(0x9746,1,0x4E)\
	ROM_FILL(0x9747,1,0x71)
//  ROM_FILL(0x9AAB3,1,0xFE)

#define MSLUGXSC_ESSENTIALPATCH_MODS_FILL \
    ROM_FILL(0x2D5C20,1,0x03)\
	ROM_FILL(0x2D5E84,1,0x03)\
	ROM_FILL(0x2D5F5C,1,0x03)\
	ROM_FILL(0x2D6034,1,0x03)\
	ROM_FILL(0x2D6130,1,0x03)\
    ROM_FILL(0x2DF695,1,0x1C)\
	ROM_FILL(0x892D8,1,0x5F)\
	ROM_FILL(0x4B6D6,1,0x50)\
    ROM_FILL(0x35240,1,0xB1)\
    ROM_FILL(0x35241,1,0x9C)\
    ROM_FILL(0x608FE,1,0x67)\
    ROM_FILL(0x399FC,1,0x5E)\
    ROM_FILL(0x39CBE,1,0x5E)\
	ROM_FILL(0x40E1A,1,0x5E)\
    ROM_FILL(0x45ABA,1,0x5E)\
    ROM_FILL(0x9AAB3,1,0xFE)\
    ROM_FILL(0x9744,1,0x4E)\
	ROM_FILL(0x9745,1,0x71)\
    ROM_FILL(0x9746,1,0x4E)\
	ROM_FILL(0x9747,1,0x71)

#define MSLUGXLB_ESSENTIALPATCH_MVS_FILL \
    ROM_FILL(0x2D5C20,1,0x03)\
	ROM_FILL(0x2D5F5C,1,0x03)\
	ROM_FILL(0x2D6034,1,0x03)\
	ROM_FILL(0x2D6130,1,0x03)\
	ROM_FILL(0x2DF6C0,1,0x02)\
	ROM_FILL(0x2DF6C1,1,0xF0)\
	ROM_FILL(0x2DF6C3,1,0x50)\
	ROM_FILL(0x2DF6C7,1,0x00)\
	ROM_FILL(0x892D8,1,0x5F)\
	ROM_FILL(0x4B6D6,1,0x50)\
    ROM_FILL(0x35240,1,0xB1)\
    ROM_FILL(0x35241,1,0x9C)\
    ROM_FILL(0x608FE,1,0x67)\
    ROM_FILL(0x399FC,1,0x5E)\
    ROM_FILL(0x39CBE,1,0x5E)\
	ROM_FILL(0x40E1A,1,0x5E)\
    ROM_FILL(0x45ABA,1,0x5E)\
    ROM_FILL(0x9AAB3,1,0xFE)\
    ROM_FILL(0x9744,1,0x4E)\
	ROM_FILL(0x9745,1,0x71)\
    ROM_FILL(0x9746,1,0x4E)\
	ROM_FILL(0x9747,1,0x71)

#define MSLUGX_CUSTOMPATCH_MODS_FILL \
    ROM_FILL(0x2D0AFD,1,0x0A)\
    ROM_FILL(0xA7E45,1,0x47)\
	ROM_FILL(0xA7E46,1,0x41)\
	ROM_FILL(0xA7E47,1,0x53)\
    ROM_FILL(0xA7E48,1,0x54)\
    ROM_FILL(0xA7E49,1,0x4F)\
    ROM_FILL(0xA7E4A,1,0x4E)\
    ROM_FILL(0xA7E4B,1,0x39)\
    ROM_FILL(0xA7E4C,1,0x30)\
	ROM_FILL(0xA7E4D,1,0x20)\
    ROM_FILL(0xA7E4E,1,0x45)\
    ROM_FILL(0xA7E4F,1,0x44)\
    ROM_FILL(0xA7E50,1,0x49)\
	ROM_FILL(0xA7E51,1,0x54)\
    ROM_FILL(0xA7E52,1,0x49)\
	ROM_FILL(0xA7E53,1,0x4F)\
    ROM_FILL(0xA7E54,1,0x4E)\
	ROM_FILL(0xA7E55,1,0x20)\
	ROM_FILL(0xA7E56,1,0x32)\
    ROM_FILL(0xA7E57,1,0x30)\
    ROM_FILL(0xA7E58,1,0x32)\
    ROM_FILL(0xA7E59,1,0x33)\
    ROM_FILL(0xA7E5A,1,0x2E)\
    ROM_FILL(0xA7E5B,1,0x20)\
	ROM_FILL(0xA7E5C,1,0x20)

#define FIX8_LEVEL6_FILL \
	ROM_FILL(0x2F3330,1,0x02)\
    ROM_FILL(0x2F3331,1,0xF0)\
	ROM_FILL(0x2F3333,1,0x50)\
    ROM_FILL(0x2F3337,1,0x00)\
	ROM_FILL(0x2F3324,1,0x02)\
    ROM_FILL(0x2F3325,1,0x1C)\
	ROM_FILL(0x2F3327,1,0x58)\
    ROM_FILL(0x2F3329,1,0x58)\
	ROM_FILL(0x2F332B,1,0x4F)\
    ROM_FILL(0x2D5C20,1,0x03)\
	ROM_FILL(0x2D5E84,1,0x03)\
	ROM_FILL(0x2D5F5C,1,0x03)\
	ROM_FILL(0x2D6034,1,0x03)\
	ROM_FILL(0x2D6130,1,0x03)
	
#define FIX7_LEVEL6_FILL \
    ROM_FILL(0x2DF695,1,0x1C)\
    ROM_FILL(0x2D5C20,1,0x03)\
	ROM_FILL(0x2D5E84,1,0x03)\
	ROM_FILL(0x2D5F5C,1,0x03)\
	ROM_FILL(0x2D6034,1,0x03)\
	ROM_FILL(0x2D6130,1,0x03)

#define FIX6_LEVEL6_FILL \
	ROM_FILL(0x2F3324,1,0x02)\
    ROM_FILL(0x2F3325,1,0x1C)\
	ROM_FILL(0x2F3327,1,0x58)\
    ROM_FILL(0x2F3329,1,0x58)\
	ROM_FILL(0x2F332B,1,0x4F)\
    ROM_FILL(0x2D5C20,1,0x03)\
	ROM_FILL(0x2D5E84,1,0x03)\
	ROM_FILL(0x2D5F5C,1,0x03)\
	ROM_FILL(0x2D6034,1,0x03)\
	ROM_FILL(0x2D6130,1,0x03)

#define FIX5_LEVEL6_FILL \
	ROM_FILL(0x2F6174,1,0x02)\
    ROM_FILL(0x2F6175,1,0x1C)\
	ROM_FILL(0x2F6177,1,0x58)\
    ROM_FILL(0x2F6179,1,0x58)\
	ROM_FILL(0x2F617B,1,0x4F)\
	ROM_FILL(0x2F617D,1,0x06)\
    ROM_FILL(0x2D5C20,1,0x03)\
	ROM_FILL(0x2D5E84,1,0x03)\
	ROM_FILL(0x2D5F5C,1,0x03)\
	ROM_FILL(0x2D6034,1,0x03)\
	ROM_FILL(0x2D6130,1,0x03)

#define FIX4_LEVEL6_FILL \
	ROM_FILL(0x2F6174,1,0x02)\
    ROM_FILL(0x2F6175,1,0x1C)\
	ROM_FILL(0x2F6177,1,0x58)\
    ROM_FILL(0x2F6179,1,0x58)\
	ROM_FILL(0x2F617B,1,0x4F)\
	ROM_FILL(0x2F617D,1,0x06)

#define FIX3_LEVEL6_FILL \
	ROM_FILL(0x2F3330,1,0x02)\
    ROM_FILL(0x2F3331,1,0xF0)\
	ROM_FILL(0x2F3333,1,0x50)\
    ROM_FILL(0x2F3337,1,0x00)\
	ROM_FILL(0x2F3324,1,0x02)\
    ROM_FILL(0x2F3325,1,0x1C)\
	ROM_FILL(0x2F3327,1,0x58)\
    ROM_FILL(0x2F3329,1,0x58)\
	ROM_FILL(0x2F332B,1,0x4F)

#define FIX2_LEVEL6_FILL \
    ROM_FILL(0x2D5C20,1,0x03)\
	ROM_FILL(0x2D5E84,1,0x03)\
	ROM_FILL(0x2D5F5C,1,0x03)\
	ROM_FILL(0x2D6034,1,0x03)\
	ROM_FILL(0x2D6130,1,0x03)

#define FIX1_LEVEL6_FILL \
	ROM_FILL(0x2DF6CC,1,0x02)\
    ROM_FILL(0x2DF6CD,1,0x1C)\
	ROM_FILL(0x2DF6CF,1,0x58)\
    ROM_FILL(0x2DF6D1,1,0x58)\
	ROM_FILL(0x2DF6D3,1,0x4F)\
	ROM_FILL(0x2DF6D5,1,0x06)\
    ROM_FILL(0x2D5C20,1,0x03)\
	ROM_FILL(0x2D5E84,1,0x03)\
	ROM_FILL(0x2D5F5C,1,0x03)\
	ROM_FILL(0x2D6034,1,0x03)\
	ROM_FILL(0x2D6130,1,0x03)

#define FIX_LEVEL4_FILL \
	ROM_FILL(0x2DF6CC,1,0x02)\
    ROM_FILL(0x2DF6CD,1,0x1C)\
	ROM_FILL(0x2DF6CF,1,0x58)\
    ROM_FILL(0x2DF6D1,1,0x58)\
	ROM_FILL(0x2DF6D3,1,0x4F)\
	ROM_FILL(0x2DF6D5,1,0x06)\
    ROM_FILL(0x2D5C20,1,0x03)\
	ROM_FILL(0x2D5F5C,1,0x03)\
	ROM_FILL(0x2D6130,1,0x03)

#define FIX_LEVEL3_FILL \
	ROM_FILL(0x2DF6CC,1,0x02)\
    ROM_FILL(0x2DF6CD,1,0x1C)\
	ROM_FILL(0x2DF6CF,1,0x58)\
    ROM_FILL(0x2DF6D1,1,0x58)\
	ROM_FILL(0x2DF6D3,1,0x4F)\
	ROM_FILL(0x2DF6D5,1,0x06)\
    ROM_FILL(0x2D5C20,1,0x03)\
	ROM_FILL(0x2D5F5C,1,0x03)\
	ROM_FILL(0x2D6034,1,0x03)\
	ROM_FILL(0x2D6130,1,0x03)

/*************************************
    Game specific Roms definitions
 *************************************/

#define DEFAULT_BIOS_BOOT_(EUROPE_MVS) \
	ROM_REGION16_BE( 0x20000, "mainbios", 0 ) \
	ROM_LOAD16_WORD_SWAP( "sp-s2.sp1",  0x00000, 0x20000, CRC(9b1a7cbe) SHA1(1695d3c488961a0f3667bd9b94ff678fd7c56d76) )

#define DEFAULT_BIOS_ASIA_(JAPAN_MVS) \
	ROM_REGION16_BE( 0x80000, "mainbios", 0 ) \
	ROM_LOAD16_WORD_SWAP( "sp-3.sp1", 0x00000, 0x80000, CRC(b4590283) SHA1(47047ed5b6062babc0a0bebcc30e4b3f021e115a) )

#define DEFAULT_BIOS_(MSLUG_FOREVER) \
	ROM_REGION16_BE( 0x20000, "mainbios", 0 ) \
	ROM_LOAD16_WORD_SWAP( "sp-1.sp1", 0x00000, 0x20000, CRC(0de70ac8) SHA1(d41ab190a2c9f91c52649f7e0faf85a9cfa8ed24) )

#define AUDIOBIOS_128K \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) 

#define MS5PCB_AUDIOBIOS_ENCRYPTED_512K \
	ROM_REGION( 0x80000, "audiocrypt", 0 ) \
	ROM_LOAD( "268.m1", 0x00000, 0x80000, CRC(4a5a6e0e) SHA1(df0f660f2465e1db7be5adfcaf5e88ad61a74a42) ) \
	ROM_REGION( 0x90000, "audiocpu", ROMREGION_ERASEFF )

#define MSLUG2_AUDIOBIOS_128K \
	ROM_REGION( 0x30000, "audiocpu", 0 ) \
	ROM_LOAD( "241.m1", 0x00000, 0x20000, CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) ) \
	ROM_RELOAD(     0x10000, 0x20000 )

#define MSLUG3_AUDIOBIOS_512K \
	ROM_REGION( 0x90000, "audiocpu", 0 ) \
	ROM_LOAD( "256.m1", 0x00000, 0x80000, CRC(eaeec116) SHA1(54419dbb21edc8c4b37eaac2e7ad9496d2de037a) ) \
	ROM_RELOAD(     0x10000, 0x80000 )

#define MSLUG3LW_AUDIOBIOS_512K \
	ROM_REGION( 0x90000, "audiocpu", 0 ) \
	ROM_LOAD( "256_hc34.m1", 0x00000, 0x80000, CRC(0c876e7f) SHA1(9d7b7fa03656af4b32f5b64265b98e9182821f82) ) \
	ROM_RELOAD(     0x10000, 0x80000 )

#define MSLUG4_AUDIOBIOS_ENCRYPTED_128K \
    ROM_REGION( 0x80000, "audiocrypt", 0 ) \
	ROM_LOAD( "263.m1", 0x00000, 0x20000, CRC(46ac8228) SHA1(5aeea221050c98e4bb0f16489ce772bf1c80f787) ) \
	ROM_REGION( 0x90000, "audiocpu", ROMREGION_ERASEFF )

#define MSLUG4LW_AUDIOBIOS_128K \
	ROM_REGION( 0x30000, "audiocpu", 0 ) \
	ROM_LOAD( "263_hc03.m1", 0x00000, 0x20000, CRC(49b1453e) SHA1(e6296e1d6bb604f1a15cf8d1b273e97b6eb7cced) ) \
	ROM_RELOAD(     0x10000, 0x20000 )

#define MSLUGX_AUDIOBIOS_128K \
	ROM_REGION( 0x30000, "audiocpu", 0 ) \
	ROM_LOAD( "250.m1", 0x00000, 0x20000, CRC(fd42a842) SHA1(55769bad4860f64ef53a333e0da9e073db483d6a) ) \
	ROM_RELOAD(     0x10000, 0x20000 )

#define MSLUG_SFIX_128K \
    NEO_SFIX_128K( "201.s1", CRC(2f55958d) SHA1(550b53628daec9f1e1e11a398854092d90f9505a) )

#define MSLUG_AUDIO_128K \
    NEO_BIOS_AUDIO_128K( "201.m1", CRC(c28b3253) SHA1(fd75bd15aed30266a8b3775f276f997af57d1c06) )

#define MSLUG_YMSND \
    ROM_REGION( 0x800000, "ymsnd", 0 )\
	ROM_LOAD( "201.v1", 0x000000, 0x400000, CRC(23d22ed1) SHA1(cd076928468ad6bcc5f19f88cb843ecb5e660681) )\
	ROM_LOAD( "201.v2", 0x400000, 0x400000, CRC(472cf9db) SHA1(5f79ea9286d22ed208128f9c31ca75552ce08b57) )

#define MSLUGDX_YMSND \
    ROM_REGION( 0x800000, "ymsnd", 0 )\
	ROM_LOAD( "201dd.v1", 0x000000, 0x800000, CRC(14cf8459) SHA1(d03f0c513cf5b76ae6193f619eb0b08d435e243a) )\

#define MSLUGB_YMSND \
	ROM_REGION( 0x800000, "ymsnd", 0 ) \
	ROM_LOAD( "201boot.v1", 0x000000, 0x200000, CRC(2c05fd7c) SHA1(4f28bc799da0e27b2f3cde364d8c9822468abb8f) )\
	ROM_LOAD( "201boot.v2", 0x200000, 0x200000, CRC(752de272) SHA1(1e9ffb296a1089e15b23455841ad91e8a565ba62) )\
	ROM_LOAD( "201boot.v3", 0x400000, 0x200000, CRC(aa48faa6) SHA1(4695b9dafdc13997410cbd7954c2a7f1b5e4649d) )\
	ROM_LOAD( "201boot.v4", 0x600000, 0x200000, CRC(4264444b) SHA1(7c248e8e559c67d6e8474ec6ce5cf2e3e41235e4) )

#define MSLUG_SPRITES \
	ROM_REGION( 0x1000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "201.c1", 0x000000, 0x400000, CRC(72813676) SHA1(7b045d1a48980cb1a140699011cb1a3d4acdc4d1) )\
	ROM_LOAD16_BYTE( "201.c2", 0x000001, 0x400000, CRC(96f62574) SHA1(cb7254b885989223bba597b8ff0972dfa5957816) )\
	ROM_LOAD16_BYTE( "201.c3", 0x800000, 0x400000, CRC(5121456a) SHA1(0a7a27d603d1bb2520b5570ebf5b34a106e255a6) )\
	ROM_LOAD16_BYTE( "201.c4", 0x800001, 0x400000, CRC(f4ad59a3) SHA1(4e94fda8ee63abf0f92afe08060a488546e5c280) )

#define MSLUGDX_SPRITES \
	ROM_REGION( 0x1000000, "sprites", 0 ) \
	ROM_LOAD( "201dd.c1", 0x000000, 0x1000000, CRC(d2955fc3) SHA1(4b69f4926766543ae289546569b27c80a82d53d5) )

#define MSLUGE_SPRITES \
	ROM_REGION( 0x1000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "201e.c1", 0x400000, 0x200000, CRC(d00bd152) SHA1(eb688dba2233bece1c3ba120ac8eb342f37fba37) )\
	ROM_CONTINUE(         0x000000, 0x200000 )\
	ROM_LOAD16_BYTE( "201e.c2", 0x400001, 0x200000, CRC(ddff1dea) SHA1(e6ac8950d8ad8498270097a248c4b49876804197) )\
	ROM_CONTINUE(         0x000001, 0x200000 )\
	ROM_LOAD16_BYTE( "201e.c3", 0xc00000, 0x200000, CRC(d3d5f9e5) SHA1(7d259314c2198ee81a380d76728c3c1ac2c8b528) )\
	ROM_CONTINUE(         0x800000, 0x200000 )\
	ROM_LOAD16_BYTE( "201e.c4", 0xc00001, 0x200000, CRC(5ac1d497) SHA1(313249ea47b3553974cde1c4c36f1ff3adeb07d1) )\
	ROM_CONTINUE(         0x800001, 0x200000 )

#define MSLUG2_SFIX_128K \
    NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

#define MSLUG2FR_SFIX_128K \
    NEO_SFIX_128K( "241_hc17.s1", CRC(e22801a7) SHA1(24120adfbc5e35efcea98cfb30a936b6630da7c5) )

#define MSLUG2EG_SFIX_128K \
	NEO_SFIX_128K( "241_hc05.s1", CRC(d983067f) SHA1(b9da5e7e2064bf11baa601773413192c3694710a) )

#define MSLUG2_AUDIO_128K \
    NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

#define MSLUG2_YMSND \
	ROM_REGION( 0x800000, "ymsnd", 0 ) \
	ROM_LOAD( "241.v1", 0x000000, 0x400000, CRC(99ec20e8) SHA1(80597707f1fe115eed1941bb0701fc00790ad504) )\
	ROM_LOAD( "241.v2", 0x400000, 0x400000, CRC(ecb16799) SHA1(b4b4ddc680836ed55942c66d7dfe756314e02211) )

#define MSLUG2DX_YMSND \
	ROM_REGION( 0x800000, "ymsnd", 0 ) \
	ROM_LOAD( "241dd.v1", 0x000000, 0x800000, CRC(d19e4594) SHA1(dd60bf9ec16af8718d698effb1eb48cb928fe267) )

#define MSLUG2_SPRITES \
	ROM_REGION( 0x2000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "241.c1", 0x0000000, 0x800000, CRC(394b5e0d) SHA1(4549926f5054ee6aa7689cf920be0327e3908a50) )\
	ROM_LOAD16_BYTE( "241.c2", 0x0000001, 0x800000, CRC(e5806221) SHA1(1e5475cfab129c77acc610f09369ca42ba5aafa5) )\
	ROM_LOAD16_BYTE( "241.c3", 0x1000000, 0x800000, CRC(9f6bfa6f) SHA1(a4319b48004e723f81a980887678e3e296049a53) )\
	ROM_LOAD16_BYTE( "241.c4", 0x1000001, 0x800000, CRC(7d3e306f) SHA1(1499316fb381775218d897b81a6a0c3465d1a37c) )

#define MSLUG2DX_SPRITES \
	ROM_REGION( 0x2000000, "sprites", 0 ) \
	ROM_LOAD( "241dd.c1", 0x0000000, 0x2000000, CRC(fc9260fe) SHA1(9bb1da87524326dd9fdfa73f202f09411f65f6c5) )

#define MSLUG2FR_SPRITES \
	ROM_REGION( 0x2000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "241_hc17.c1", 0x0000000, 0x800000, CRC(7df74035) SHA1(08322a2f4e87cd125ebc5b7a98754c7a5b8e91d2) )\
	ROM_LOAD16_BYTE( "241_hc17.c2", 0x0000001, 0x800000, CRC(97d9525d) SHA1(451a5bdafe1f2de63b76efb7d4afab454abdfff0) )\
	ROM_LOAD16_BYTE( "241.c3",      0x1000000, 0x800000, CRC(9f6bfa6f) SHA1(a4319b48004e723f81a980887678e3e296049a53) )\
	ROM_LOAD16_BYTE( "241.c4",      0x1000001, 0x800000, CRC(7d3e306f) SHA1(1499316fb381775218d897b81a6a0c3465d1a37c) )

#define MSLUG2DD_SPRITES \
	ROM_REGION( 0x2000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "241.c1",      0x0000000, 0x800000, CRC(394b5e0d) SHA1(4549926f5054ee6aa7689cf920be0327e3908a50) )\
	ROM_LOAD16_BYTE( "241.c2",      0x0000001, 0x800000, CRC(e5806221) SHA1(1e5475cfab129c77acc610f09369ca42ba5aafa5) )\
	ROM_LOAD16_BYTE( "241_hc15.c3", 0x1000000, 0x800000, CRC(c54c2548) SHA1(07045a7a004631b54ac35e02075ec8f6898a4b32) )\
	ROM_LOAD16_BYTE( "241_hc15.c4", 0x1000001, 0x800000, CRC(f8168521) SHA1(3bb16caeced227c8bee95bfb92cd22f171ac86d3) )

#define MSLUG2EG_SPRITES \
	ROM_REGION( 0x3000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "241.c1",      0x0000000, 0x800000, CRC(394b5e0d) SHA1(4549926f5054ee6aa7689cf920be0327e3908a50) )\
	ROM_LOAD16_BYTE( "241.c2",      0x0000001, 0x800000, CRC(e5806221) SHA1(1e5475cfab129c77acc610f09369ca42ba5aafa5) )\
	ROM_LOAD16_BYTE( "241.c3",      0x1000000, 0x800000, CRC(9f6bfa6f) SHA1(a4319b48004e723f81a980887678e3e296049a53) )\
	ROM_LOAD16_BYTE( "241.c4",      0x1000001, 0x800000, CRC(7d3e306f) SHA1(1499316fb381775218d897b81a6a0c3465d1a37c) )\
	ROM_LOAD16_BYTE( "241_hc05.c5", 0x2000000, 0x800000, CRC(cae9af4f) SHA1(85f32cdc8069901f2f5fb628a2eda5e44f7994f7) )\
	ROM_LOAD16_BYTE( "241_hc05.c6", 0x2000001, 0x800000, CRC(7cf51055) SHA1(ec5e78746190fc2bf087fa1b8efd9fc3433068d7) )

#define MSLUG3_SFIX_MT_512K \
    NEO_SFIX_MT_512K

#define MSLUG3HD_SFIX_128K \
	NEO_SFIX_128K( "256hd.s1", CRC(8458fff9) SHA1(b120d096deae8abf0ad98362ce230b66e7315a14) )

#define MSLUG3G_SFIX_128K \
    NEO_SFIX_128K( "256_hc03.s1", CRC(af90d166) SHA1(2e925b0bfbbf57aa5bf3522939502bfd97b381df) )

#define MSLUG3ND_SFIX_512K \
    NEO_SFIX_512K( "263nd.s1", CRC(2628d663) SHA1(a976bdac2d7908e3203c7ffdc6a103cd327c656e) )

#define MSLUG3ER_AUDIO_256K \
    NEO_BIOS_AUDIO_256K( "256_hc20.m1", CRC(2f88e0c0) SHA1(bf95881d1c8861cba1a154eb26552520a764c5ba) )

#define MSLUG3_AUDIO_512K \
    NEO_BIOS_AUDIO_512K( "256.m1", CRC(eaeec116) SHA1(54419dbb21edc8c4b37eaac2e7ad9496d2de037a) )

#define MSLUG3GW_AUDIO_512K \
    NEO_BIOS_AUDIO_512K( "256_hc10.m1", CRC(c84d22f2) SHA1(069d5eafa859acbebc35394344df78ea84055cf7) )

#define MSLUG3LW_AUDIO_512K \
    NEO_BIOS_AUDIO_512K( "256_hc34.m1", CRC(0c876e7f) SHA1(9d7b7fa03656af4b32f5b64265b98e9182821f82) )

#define MSLUG3_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "256.v1", 0x000000, 0x400000, CRC(f2690241) SHA1(fd56babc1934d10e0d27c32f032f9edda7ca8ce9) )\
	ROM_LOAD( "256.v2", 0x400000, 0x400000, CRC(7e2a10bd) SHA1(0d587fb9f64cba0315ce2d8a03e2b8fe34936dff) )\
	ROM_LOAD( "256.v3", 0x800000, 0x400000, CRC(0eaec17c) SHA1(c3ed613cc6993edd6fc0d62a90bcd85de8e21915) )\
	ROM_LOAD( "256.v4", 0xc00000, 0x400000, CRC(9b4b22d4) SHA1(9764fbf8453e52f80aa97a46fb9cf5937ef15a31) )

#define MSLUG3DX_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "256dd.v1", 0x000000, 0x1000000, CRC(644b999c) SHA1(b01d08f8e0fc35b22ace183f966e463ac9ce1696) )\

#define MSLUG3P_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "256.v1",  0x000000, 0x400000, CRC(f2690241) SHA1(fd56babc1934d10e0d27c32f032f9edda7ca8ce9) )\
	ROM_LOAD( "256p.v2", 0x400000, 0x400000, CRC(4cd5e822) SHA1(3f1f53df6589597ed64a4a16d6e0d22dc6f91b6a) )\
	ROM_LOAD( "256.v3",  0x800000, 0x400000, CRC(0eaec17c) SHA1(c3ed613cc6993edd6fc0d62a90bcd85de8e21915) )\
	ROM_LOAD( "256.v4",  0xc00000, 0x400000, CRC(9b4b22d4) SHA1(9764fbf8453e52f80aa97a46fb9cf5937ef15a31) )

#define MSLUG3GW_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "256.v1",      0x000000, 0x400000, CRC(f2690241) SHA1(fd56babc1934d10e0d27c32f032f9edda7ca8ce9) )\
	ROM_LOAD( "256.v2",      0x400000, 0x400000, CRC(7e2a10bd) SHA1(0d587fb9f64cba0315ce2d8a03e2b8fe34936dff) )\
	ROM_LOAD( "256.v3",      0x800000, 0x400000, CRC(0eaec17c) SHA1(c3ed613cc6993edd6fc0d62a90bcd85de8e21915) )\
	ROM_LOAD( "256_hc10.v4", 0xc00000, 0x400000, CRC(b45d9a3b) SHA1(eee342e11865facbbfcaf82b8e16b9e64b8c309c) )

#define MSLUG3LW_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "256.v1",      0x000000, 0x400000, CRC(f2690241) SHA1(fd56babc1934d10e0d27c32f032f9edda7ca8ce9) )\
	ROM_LOAD( "256.v2",      0x400000, 0x400000, CRC(7e2a10bd) SHA1(0d587fb9f64cba0315ce2d8a03e2b8fe34936dff) )\
	ROM_LOAD( "256.v3",      0x800000, 0x400000, CRC(0eaec17c) SHA1(c3ed613cc6993edd6fc0d62a90bcd85de8e21915) )\
	ROM_LOAD( "256_hc34.v4", 0xc00000, 0x400000, CRC(e4421cbf) SHA1(d4eb1e117112d5c75bcf301e05b0708cdb1cabcd) )

#define MSLUG3_SPRITES \
	ROM_REGION( 0x4000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "256.c1", 0x0000000, 0x800000, CRC(5a79c34e) SHA1(b8aa51fa50935cae62ab3d125b723ab888691e60) )\
	ROM_LOAD16_BYTE( "256.c2", 0x0000001, 0x800000, CRC(944c362c) SHA1(3843ab300f956280475469caee70135658f67089) )\
	ROM_LOAD16_BYTE( "256.c3", 0x1000000, 0x800000, CRC(6e69d36f) SHA1(94e8cf42e999114b4bd8b30e0aa2f365578c4c9a) )\
	ROM_LOAD16_BYTE( "256.c4", 0x1000001, 0x800000, CRC(b755b4eb) SHA1(804700a0966a48f130c434ede3f970792ea74fa5) )\
	ROM_LOAD16_BYTE( "256.c5", 0x2000000, 0x800000, CRC(7aacab47) SHA1(312c1c9846175fe1a3cad51d5ae230cf674fc93d) )\
	ROM_LOAD16_BYTE( "256.c6", 0x2000001, 0x800000, CRC(c698fd5d) SHA1(16818883b06849ba2f8d61bdd5e21aaf99bd8408) )\
	ROM_LOAD16_BYTE( "256.c7", 0x3000000, 0x800000, CRC(cfceddd2) SHA1(7def666adf8bd1703f40c61f182fc040b6362dc9) )\
	ROM_LOAD16_BYTE( "256.c8", 0x3000001, 0x800000, CRC(4d9be34c) SHA1(a737bdfa2b815aea7067e7af2636e83a9409c414) )

#define MSLUG3D_SPRITES \
    ROM_REGION( 0x4000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "256d.c1", 0x0000000, 0x800000, CRC(3540398c) SHA1(0a96f2360eb26c66bf02bbc6f52230b55cc95e4e) )\
	ROM_LOAD16_BYTE( "256d.c2", 0x0000001, 0x800000, CRC(bdd220f0) SHA1(f52851023f3bc120b05f622af0e0ab1bedc41604) )\
	ROM_LOAD16_BYTE( "256d.c3", 0x1000000, 0x800000, CRC(bfaade82) SHA1(66b07e592c9a9b35567fe463496f8f75c32a7db9) )\
	ROM_LOAD16_BYTE( "256d.c4", 0x1000001, 0x800000, CRC(1463add6) SHA1(4db91b46d6430da272d27d00a6dc0eb25949bea1) )\
	ROM_LOAD16_BYTE( "256d.c5", 0x2000000, 0x800000, CRC(48ca7f28) SHA1(e903876be5fb4fa582c988d74c6bef1c3b9c7083) )\
	ROM_LOAD16_BYTE( "256d.c6", 0x2000001, 0x800000, CRC(806eb36f) SHA1(a412a9cab80c326733dde7652d1db2a46afb3ebb) )\
	ROM_LOAD16_BYTE( "256d.c7", 0x3000000, 0x800000, CRC(9395b809) SHA1(ca9ac9832017094eee3623f0b6c4c4b7b4f1374d) )\
	ROM_LOAD16_BYTE( "256d.c8", 0x3000001, 0x800000, CRC(a369f9d4) SHA1(f8146ea80a1a23da7e7e04c88f778ee9abdfeb5c) )

#define MSLUG3DX_SPRITES \
    ROM_REGION( 0x4000000, "sprites", 0 ) \
	ROM_LOAD( "256dd.c1", 0x0000000, 0x4000000, CRC(8aeb46d2) SHA1(41d1ad1a168cb7a6299cd73d3671599471651c69) )

#define MSLUG3FR_SPRITES \
    ROM_REGION( 0x4000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "256_hc32.c1", 0x0000000, 0x800000, CRC(d799f41c) SHA1(d87cda305d054c56197112ba515299883d419bb4) )\
	ROM_LOAD16_BYTE( "256_hc32.c2", 0x0000001, 0x800000, CRC(c9725cd0) SHA1(59a0a2778ae35ddcac17fba05a81f3da5eaca1f1) )\
	ROM_LOAD16_BYTE( "256d.c3",     0x1000000, 0x800000, CRC(bfaade82) SHA1(66b07e592c9a9b35567fe463496f8f75c32a7db9) )\
	ROM_LOAD16_BYTE( "256d.c4",     0x1000001, 0x800000, CRC(1463add6) SHA1(4db91b46d6430da272d27d00a6dc0eb25949bea1) )\
	ROM_LOAD16_BYTE( "256d.c5",     0x2000000, 0x800000, CRC(48ca7f28) SHA1(e903876be5fb4fa582c988d74c6bef1c3b9c7083) )\
	ROM_LOAD16_BYTE( "256d.c6",     0x2000001, 0x800000, CRC(806eb36f) SHA1(a412a9cab80c326733dde7652d1db2a46afb3ebb) )\
	ROM_LOAD16_BYTE( "256_hc32.c7", 0x3000000, 0x800000, CRC(82097fdb) SHA1(04ff6755087df0995c196e8817827fda3b9f9d08) )\
	ROM_LOAD16_BYTE( "256_hc32.c8", 0x3000001, 0x800000, CRC(aa7ca14d) SHA1(876ed262200535b82f74e56b64128df23140338b) )

#define MSLUG3G_SPRITES \
	ROM_REGION( 0x4000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "256d.c1",     0x0000000, 0x800000, CRC(3540398c) SHA1(0a96f2360eb26c66bf02bbc6f52230b55cc95e4e) )\
	ROM_LOAD16_BYTE( "256d.c2",     0x0000001, 0x800000, CRC(bdd220f0) SHA1(f52851023f3bc120b05f622af0e0ab1bedc41604) )\
	ROM_LOAD16_BYTE( "256d.c3",     0x1000000, 0x800000, CRC(bfaade82) SHA1(66b07e592c9a9b35567fe463496f8f75c32a7db9) )\
	ROM_LOAD16_BYTE( "256d.c4",     0x1000001, 0x800000, CRC(1463add6) SHA1(4db91b46d6430da272d27d00a6dc0eb25949bea1) )\
	ROM_LOAD16_BYTE( "256d.c5",     0x2000000, 0x800000, CRC(48ca7f28) SHA1(e903876be5fb4fa582c988d74c6bef1c3b9c7083) )\
	ROM_LOAD16_BYTE( "256d.c6",     0x2000001, 0x800000, CRC(806eb36f) SHA1(a412a9cab80c326733dde7652d1db2a46afb3ebb) )\
	ROM_LOAD16_BYTE( "256_hc03.c7", 0x3000000, 0x800000, CRC(ed559fac) SHA1(e2e73b068785226cd97abbb8c2bd2b5800e9bf19) )\
	ROM_LOAD16_BYTE( "256_hc03.c8", 0x3000001, 0x800000, CRC(1c52378b) SHA1(05cd499f5444eae6360c96bfd3d3db8870d9656a) )

#define MSLUG3DD_SPRITES \
	ROM_REGION( 0x4000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "256d.c1",     0x0000000, 0x800000, CRC(3540398c) SHA1(0a96f2360eb26c66bf02bbc6f52230b55cc95e4e) )\
	ROM_LOAD16_BYTE( "256d.c2",     0x0000001, 0x800000, CRC(bdd220f0) SHA1(f52851023f3bc120b05f622af0e0ab1bedc41604) )\
	ROM_LOAD16_BYTE( "256d.c3",     0x1000000, 0x800000, CRC(bfaade82) SHA1(66b07e592c9a9b35567fe463496f8f75c32a7db9) )\
	ROM_LOAD16_BYTE( "256d.c4",     0x1000001, 0x800000, CRC(1463add6) SHA1(4db91b46d6430da272d27d00a6dc0eb25949bea1) )\
	ROM_LOAD16_BYTE( "256d.c5",     0x2000000, 0x800000, CRC(48ca7f28) SHA1(e903876be5fb4fa582c988d74c6bef1c3b9c7083) )\
	ROM_LOAD16_BYTE( "256d.c6",     0x2000001, 0x800000, CRC(806eb36f) SHA1(a412a9cab80c326733dde7652d1db2a46afb3ebb) )\
	ROM_LOAD16_BYTE( "256_hc26.c7", 0x3000000, 0x800000, CRC(ec74423d) SHA1(af76e917219e46102fe4c0231fbbdf96f5c78fe7) )\
	ROM_LOAD16_BYTE( "256_hc26.c8", 0x3000001, 0x800000, CRC(a9fe9b98) SHA1(165bf118ffde29c6434a6b3026e0b111889082af) )

#define MSLUG3CQ_SPRITES \
    ROM_REGION( 0x4000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "256d.c1",     0x0000000, 0x800000, CRC(3540398c) SHA1(0a96f2360eb26c66bf02bbc6f52230b55cc95e4e) )\
	ROM_LOAD16_BYTE( "256d.c2",     0x0000001, 0x800000, CRC(bdd220f0) SHA1(f52851023f3bc120b05f622af0e0ab1bedc41604) )\
	ROM_LOAD16_BYTE( "256d.c3",     0x1000000, 0x800000, CRC(bfaade82) SHA1(66b07e592c9a9b35567fe463496f8f75c32a7db9) )\
	ROM_LOAD16_BYTE( "256d.c4",     0x1000001, 0x800000, CRC(1463add6) SHA1(4db91b46d6430da272d27d00a6dc0eb25949bea1) )\
	ROM_LOAD16_BYTE( "256d.c5",     0x2000000, 0x800000, CRC(48ca7f28) SHA1(e903876be5fb4fa582c988d74c6bef1c3b9c7083) )\
	ROM_LOAD16_BYTE( "256d.c6",     0x2000001, 0x800000, CRC(806eb36f) SHA1(a412a9cab80c326733dde7652d1db2a46afb3ebb) )\
	ROM_LOAD16_BYTE( "256_hc28.c7", 0x3000000, 0x800000, CRC(b7bd7296) SHA1(c0514770b8ca92be620f74eabe94b9dfbd609fae) )\
	ROM_LOAD16_BYTE( "256_hc28.c8", 0x3000001, 0x800000, CRC(638e5920) SHA1(d00899d73e8193a471101e4efbd4774f5565d40c) )


#define MSLUG3SCB_SPRITES \
    ROM_REGION( 0x4000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "256d.c1",     0x0000000, 0x800000, CRC(3540398c) SHA1(0a96f2360eb26c66bf02bbc6f52230b55cc95e4e) )\
	ROM_LOAD16_BYTE( "256d.c2",     0x0000001, 0x800000, CRC(bdd220f0) SHA1(f52851023f3bc120b05f622af0e0ab1bedc41604) )\
	ROM_LOAD16_BYTE( "256d.c3",     0x1000000, 0x800000, CRC(bfaade82) SHA1(66b07e592c9a9b35567fe463496f8f75c32a7db9) )\
	ROM_LOAD16_BYTE( "256d.c4",     0x1000001, 0x800000, CRC(1463add6) SHA1(4db91b46d6430da272d27d00a6dc0eb25949bea1) )\
	ROM_LOAD16_BYTE( "256d.c5",     0x2000000, 0x800000, CRC(48ca7f28) SHA1(e903876be5fb4fa582c988d74c6bef1c3b9c7083) )\
	ROM_LOAD16_BYTE( "256d.c6",     0x2000001, 0x800000, CRC(806eb36f) SHA1(a412a9cab80c326733dde7652d1db2a46afb3ebb) )\
	ROM_LOAD16_BYTE( "256_hc25.c7", 0x3000000, 0x800000, CRC(f7a5eeeb) SHA1(fa3563d4f421d45b01828e1a1f984a1136ebb165) )\
	ROM_LOAD16_BYTE( "256_hc25.c8", 0x3000001, 0x800000, CRC(03c3ad8f) SHA1(4ccd4d850e11e78c35f467055ae612b7796dd3c2) )

#define MSLUG3LW_SPRITES \
    ROM_REGION( 0x4000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "256d.c1", 0x0000000, 0x800000, CRC(3540398c) SHA1(0a96f2360eb26c66bf02bbc6f52230b55cc95e4e) )\
	ROM_LOAD16_BYTE( "256d.c2", 0x0000001, 0x800000, CRC(bdd220f0) SHA1(f52851023f3bc120b05f622af0e0ab1bedc41604) )\
	ROM_LOAD16_BYTE( "256d.c3", 0x1000000, 0x800000, CRC(bfaade82) SHA1(66b07e592c9a9b35567fe463496f8f75c32a7db9) )\
	ROM_LOAD16_BYTE( "256d.c4", 0x1000001, 0x800000, CRC(1463add6) SHA1(4db91b46d6430da272d27d00a6dc0eb25949bea1) )\
	ROM_LOAD16_BYTE( "256_hc34.c5", 0x2000000, 0x800000, CRC(3dd2c01f) SHA1(8485ba8940ae60d0a2a9561d5a82fd5f32452e01) )\
	ROM_LOAD16_BYTE( "256_hc34.c6", 0x2000001, 0x800000, CRC(1ea253a8) SHA1(c3134199eff0dfe47b9c05caea0245ffbee4e8c3) )\
	ROM_LOAD16_BYTE( "256d.c7", 0x3000000, 0x800000, CRC(9395b809) SHA1(ca9ac9832017094eee3623f0b6c4c4b7b4f1374d) )\
	ROM_LOAD16_BYTE( "256d.c8", 0x3000001, 0x800000, CRC(a369f9d4) SHA1(f8146ea80a1a23da7e7e04c88f778ee9abdfeb5c) )

#define MSLUG3RMTERZ_SPRITES \
    ROM_REGION( 0x4000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "256d.c1",     0x0000000, 0x800000, CRC(3540398c) SHA1(0a96f2360eb26c66bf02bbc6f52230b55cc95e4e) )\
	ROM_LOAD16_BYTE( "256d.c2",     0x0000001, 0x800000, CRC(bdd220f0) SHA1(f52851023f3bc120b05f622af0e0ab1bedc41604) )\
	ROM_LOAD16_BYTE( "256d.c3",     0x1000000, 0x800000, CRC(bfaade82) SHA1(66b07e592c9a9b35567fe463496f8f75c32a7db9) )\
	ROM_LOAD16_BYTE( "256d.c4",     0x1000001, 0x800000, CRC(1463add6) SHA1(4db91b46d6430da272d27d00a6dc0eb25949bea1) )\
	ROM_LOAD16_BYTE( "256_hc34.c5", 0x2000000, 0x800000, CRC(3dd2c01f) SHA1(8485ba8940ae60d0a2a9561d5a82fd5f32452e01) )\
	ROM_LOAD16_BYTE( "256_hc34.c6", 0x2000001, 0x800000, CRC(1ea253a8) SHA1(c3134199eff0dfe47b9c05caea0245ffbee4e8c3) )\
	ROM_LOAD16_BYTE( "256_ly01.c7", 0x3000000, 0x800000, CRC(b8e017de) SHA1(fb88f2d12be6e9ea6cec4d5d5b33d828d34c28d3) )\
	ROM_LOAD16_BYTE( "256_ly01.c8", 0x3000001, 0x800000, CRC(def95742) SHA1(be76a3da972ee4dfe9f1f1b41d35fa3027c05c1d) )

#define MSLUG3LZ_SPRITES \
    ROM_REGION( 0x4000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "256d.c1", 0x0000000, 0x800000, CRC(3540398c) SHA1(0a96f2360eb26c66bf02bbc6f52230b55cc95e4e) )\
	ROM_LOAD16_BYTE( "256d.c2", 0x0000001, 0x800000, CRC(bdd220f0) SHA1(f52851023f3bc120b05f622af0e0ab1bedc41604) )\
	ROM_LOAD16_BYTE( "256d.c3", 0x1000000, 0x800000, CRC(bfaade82) SHA1(66b07e592c9a9b35567fe463496f8f75c32a7db9) )\
	ROM_LOAD16_BYTE( "256d.c4", 0x1000001, 0x800000, CRC(1463add6) SHA1(4db91b46d6430da272d27d00a6dc0eb25949bea1) )\
	ROM_LOAD16_BYTE( "256_hc34.c5", 0x2000000, 0x800000, CRC(3dd2c01f) SHA1(8485ba8940ae60d0a2a9561d5a82fd5f32452e01) )\
	ROM_LOAD16_BYTE( "256_hc34.c6", 0x2000001, 0x800000, CRC(1ea253a8) SHA1(c3134199eff0dfe47b9c05caea0245ffbee4e8c3) )\
	ROM_LOAD16_BYTE( "256_hc03.c7", 0x3000000, 0x800000, CRC(ed559fac) SHA1(e2e73b068785226cd97abbb8c2bd2b5800e9bf19) )\
	ROM_LOAD16_BYTE( "256_hc03.c8", 0x3000001, 0x800000, CRC(1c52378b) SHA1(05cd499f5444eae6360c96bfd3d3db8870d9656a) )

#define MSLUG3RMZ_SPRITES \
    ROM_REGION( 0x4000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "256_hc32.c1", 0x0000000, 0x800000, CRC(d799f41c) SHA1(d87cda305d054c56197112ba515299883d419bb4) )\
	ROM_LOAD16_BYTE( "256_hc32.c2", 0x0000001, 0x800000, CRC(c9725cd0) SHA1(59a0a2778ae35ddcac17fba05a81f3da5eaca1f1) )\
	ROM_LOAD16_BYTE( "256d.c3", 0x1000000, 0x800000, CRC(bfaade82) SHA1(66b07e592c9a9b35567fe463496f8f75c32a7db9) )\
	ROM_LOAD16_BYTE( "256d.c4", 0x1000001, 0x800000, CRC(1463add6) SHA1(4db91b46d6430da272d27d00a6dc0eb25949bea1) )\
	ROM_LOAD16_BYTE( "256_hc34.c5", 0x2000000, 0x800000, CRC(3dd2c01f) SHA1(8485ba8940ae60d0a2a9561d5a82fd5f32452e01) )\
	ROM_LOAD16_BYTE( "256_hc34.c6", 0x2000001, 0x800000, CRC(1ea253a8) SHA1(c3134199eff0dfe47b9c05caea0245ffbee4e8c3) )\
	ROM_LOAD16_BYTE( "256_hc32.c7", 0x3000000, 0x800000, CRC(82097fdb) SHA1(04ff6755087df0995c196e8817827fda3b9f9d08) )\
	ROM_LOAD16_BYTE( "256_hc32.c8", 0x3000001, 0x800000, CRC(aa7ca14d) SHA1(876ed262200535b82f74e56b64128df23140338b) )

#define MSLUG3N6P_SPRITES \
	ROM_REGION( 0x4000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "256d.c1",     0x0000000, 0x800000, CRC(3540398c) SHA1(0a96f2360eb26c66bf02bbc6f52230b55cc95e4e) )\
	ROM_LOAD16_BYTE( "256d.c2",     0x0000001, 0x800000, CRC(bdd220f0) SHA1(f52851023f3bc120b05f622af0e0ab1bedc41604) )\
	ROM_LOAD16_BYTE( "256d.c3",     0x1000000, 0x800000, CRC(bfaade82) SHA1(66b07e592c9a9b35567fe463496f8f75c32a7db9) )\
	ROM_LOAD16_BYTE( "256d.c4",     0x1000001, 0x800000, CRC(1463add6) SHA1(4db91b46d6430da272d27d00a6dc0eb25949bea1) )\
	ROM_LOAD16_BYTE( "256d.c5",     0x2000000, 0x800000, CRC(48ca7f28) SHA1(e903876be5fb4fa582c988d74c6bef1c3b9c7083) )\
	ROM_LOAD16_BYTE( "256d.c6",     0x2000001, 0x800000, CRC(806eb36f) SHA1(a412a9cab80c326733dde7652d1db2a46afb3ebb) )\
	ROM_LOAD16_BYTE( "299_hc01.c7", 0x3000000, 0x800000, CRC(f53108fe) SHA1(ee5a60410221c9e5139cc5bcffe19bb99f4745bc) )\
	ROM_LOAD16_BYTE( "299_hc01.c8", 0x3000001, 0x800000, CRC(64c33010) SHA1(6b1ef285228720fd828cf317ebfc17cace0bc5cd) )

#define MSLUG3B6_SFIX_128K \
    NEO_SFIX_128K( "299.s1", CRC(6f8b9635) SHA1(86b0c8c0ccac913c6192ed6a96c35d4e1a5e8061) )

#define MSLUG3B6P_SFIX_128K \
    NEO_SFIX_128K( "299p.s1", CRC(39f1a271) SHA1(07835758801f31876274a25bc7796abe1b5f052b) )

#define MSPLUS4_SFIX_128K \
    NEO_SFIX_128K( "ms4p.s1", CRC(07ff87ce) SHA1(96ddb439de2a26bf9869015d7fb19129d40f3fd9) )

#define MSLUG4_SFIX_MT_512K \
    NEO_SFIX_MT_512K

#define MSLUG4NDP_SFIX_128K \
	NEO_SFIX_128K( "263ndp.s1", CRC(c4f4ed0e) SHA1(bbf31c879d72cc843229b03db01399af98e02f01) )

#define MSLUG4DX_SFIX_512K \
    NEO_SFIX_512K( "263dd.s1", CRC(1eaa05e0) SHA1(73a7e158c3c4fa602e17dcb517190fd91a9dbab8) )

#define MSLUG4HD_SFIX_128K \
	NEO_SFIX_128K( "263hd.s1", CRC(a9446774) SHA1(c5a309fd8ee6d6750a15c82e710218a3755e38b2) )

#define MSLUG4FR_SFIX_128K \
	NEO_SFIX_128K( "263_hc20.s1", CRC(1c2e768f) SHA1(ae816bc2f7ab27b43c146f5a5f67efe79c309b74) )

#define MSLUG4IT_SFIX_128K \
	NEO_SFIX_128K( "263_hc21.s1", CRC(1f67801e) SHA1(87c33e74599ca063da459f3c8562447bccc104e3) )

#define MSLUG4lZW_SFIX_128K \
	NEO_SFIX_128K( "263_lz01.s1", CRC(df251c4f) SHA1(23bbc4ddfae0531de67a83e84f926e003753869d) )

#define MSLUG4D_AUDIO_64K \
	NEO_BIOS_AUDIO_64K( "263d.m1", CRC(0c4c42f8) SHA1(b7be47d909f5e4fcfe769ead0653d40e1e708d36) )

#define MSLUG4P_AUDIO_ENCRYPTED_64K \
	NEO_BIOS_AUDIO_ENCRYPTED_64K( "263p.m1", CRC(38ffad14) SHA1(03d526a887aad28306400c21abd131b9c301c221) )

#define MSLUG4_AUDIO_ENCRYPTED_128K \
	NEO_BIOS_AUDIO_ENCRYPTED_128K( "263.m1", CRC(46ac8228) SHA1(5aeea221050c98e4bb0f16489ce772bf1c80f787) )

#define MSLUG4LW_AUDIO_128K \
	NEO_BIOS_AUDIO_128K( "263_hc03.m1", CRC(49b1453e) SHA1(e6296e1d6bb604f1a15cf8d1b273e97b6eb7cced) )

#define MSLUG4ND_AUDIO_128K \
	NEO_BIOS_AUDIO_128K( "263nd.m1", CRC(ef5db532) SHA1(4aeba9e206b8f309610eb7e1891644f39aa61830) )

#define MSLUG4NDP_AUDIO_128K \
	NEO_BIOS_AUDIO_128K( "263ndp.m1", CRC(ee1e5580) SHA1(c98a33381a5e42959e71b701743743c64a61b704) )

#define MS4BOOT_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "263boot.v1", 0x000000, 0x800000, CRC(fd6b982e) SHA1(100313166c9ec57f1c540de05625c506b30ad13c) )\
	ROM_LOAD( "263boot.v2", 0x800000, 0x800000, CRC(20125227) SHA1(2e350c0c580e87445bf103c01fc62b14f0c19216) )

#define MSLUG4_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "263.v1", 0x000000, 0x800000, CRC(01e9b9cd) SHA1(0b045c2999449f7dab5ae8a42e957d5b6650431e) )\
	ROM_LOAD( "263.v2", 0x800000, 0x800000, CRC(4ab2bf81) SHA1(77ccfa48f7e3daddef5fe5229a0093eb2f803742) )

#define MSLUG4DX_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "263dd.v1", 0x000000, 0x1000000, CRC(3bf11f09) SHA1(2f43f454019e4cc32f54a66b510d2a60ca774f3b) )

#define MSLUG4P_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "263p.v1", 0x000000, 0x800000, CRC(b1a08c67) SHA1(aa774860633a8587ea7c68b672941f5c0e4a2e98) )\
	ROM_LOAD( "263p.v2", 0x800000, 0x800000, CRC(0040015b) SHA1(bba6759d5422a2e55df459306a00b9b5283cbebe) )

#define MSLUG4ND_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "263nd.v1", 0x000000, 0x400000, CRC(c1b2af81) SHA1(532dca0a2b2e03d50c6ac3adc9ebceb413f61690) )\
	ROM_LOAD( "263nd.v2", 0x400000, 0x400000, CRC(cbbdc6fa) SHA1(06abb738cf198804248ecfc92adea38f7f86f612) )\
	ROM_LOAD( "263nd.v3", 0x800000, 0x400000, CRC(c4f1a3cc) SHA1(109e8db93875e1b1f3db293d1756b2bbebe63a28) )\
	ROM_LOAD( "263nd.v4", 0xC00000, 0x400000, CRC(40126a0a) SHA1(4234e0f4d9a9dc486d7af1eec91a17840a57976d) )

#define MSLUG4NDP_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "263ndp.v1", 0x000000, 0x400000, CRC(8cb5a9ef) SHA1(272ad312f8694acf9190ebf48d1c8a5fec73c130) )\
	ROM_LOAD( "263ndp.v2", 0x400000, 0x400000, CRC(94217b1e) SHA1(c468a192e2ec0952a20cfd9e391cf6c12346efb3) )\
	ROM_LOAD( "263ndp.v3", 0x800000, 0x400000, CRC(7616fcec) SHA1(83006094379d0373b967603dcaa1cec69c2f746f) )\
	ROM_LOAD( "263ndp.v4", 0xC00000, 0x400000, CRC(7b0b92a1) SHA1(c14320c4652de16ff2535f8743ce0e71ba135e75) )

#define MSLUG4LW_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "263ndp.v1",   0x000000, 0x400000, CRC(8cb5a9ef) SHA1(272ad312f8694acf9190ebf48d1c8a5fec73c130) )\
	ROM_LOAD( "263_hc03.v2", 0x400000, 0x400000, CRC(c9572c14) SHA1(4338aaceada29ea1cd2baf0d6ada4911246f5b09) )\
	ROM_LOAD( "263_hc03.v3", 0x800000, 0x400000, CRC(e7c14624) SHA1(1d17f7e7cfe9bb03f1a374b31427c4e5203433f2) )\
	ROM_LOAD( "263_hc03.v4", 0xc00000, 0x400000, CRC(b1e5ac70) SHA1(0d6eea68085c0e6cd7c7e29edb06f05a712f6d62) )\
	ROM_IGNORE(0x400000)

#define MSLUG4DG_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "263ndp.v1", 0x000000, 0x400000, CRC(8cb5a9ef) SHA1(272ad312f8694acf9190ebf48d1c8a5fec73c130) )\
	ROM_LOAD( "263ndp.v2", 0x400000, 0x400000, CRC(94217b1e) SHA1(c468a192e2ec0952a20cfd9e391cf6c12346efb3) )\
	ROM_LOAD( "263ndp.v3", 0x800000, 0x400000, CRC(7616fcec) SHA1(83006094379d0373b967603dcaa1cec69c2f746f) )\
	ROM_LOAD( "263dg.v4",  0xC00000, 0x400000, CRC(c5967f91) SHA1(874562109c3df9e1fdefbb3970092128aaa31a17) )

#define MSLUG4_SPRITES \
	ROM_REGION( 0x3000000, "sprites", 0 ) \
 	ROM_LOAD16_BYTE( "263.c1", 0x0000000, 0x800000, CRC(84865f8a) SHA1(34467ada896eb7c7ca58658bf2a932936d8b632c) )\
	ROM_LOAD16_BYTE( "263.c2", 0x0000001, 0x800000, CRC(81df97f2) SHA1(2b74493b8ec8fd49216a627aeb3db493f76124e3) )\
	ROM_LOAD16_BYTE( "263.c3", 0x1000000, 0x800000, CRC(1a343323) SHA1(bbbb5232bba538c277ce2ee02e2956ca2243b787) )\
	ROM_LOAD16_BYTE( "263.c4", 0x1000001, 0x800000, CRC(942cfb44) SHA1(d9b46c71726383c4581fb042e63897e5a3c92d1b) )\
	ROM_LOAD16_BYTE( "263.c5", 0x2000000, 0x800000, CRC(a748854f) SHA1(2611bbedf9b5d8e82c6b2c99b88f842c46434d41) )\
	ROM_LOAD16_BYTE( "263.c6", 0x2000001, 0x800000, CRC(5c8ba116) SHA1(6034db09c8706d4ddbcefc053efbc47a0953eb92) )

#define MSLUG4DX_SPRITES \
	ROM_REGION( 0x3000000, "sprites", 0 ) \
 	ROM_LOAD( "263dd.c1", 0x0000000, 0x3000000, CRC(464a897d) SHA1(e6fd4dc9377c3cd3567d072ee50c944d7fd887bf) )

#define MSLUG4P_SPRITES \
	ROM_REGION( 0x3000000, "sprites", 0 ) \
 	ROM_LOAD16_BYTE( "263p.c1", 0x0000000, 0x800000, CRC(6c2b0856) SHA1(e46ecdd3e11c3018e3defb567758ca4579922a99) )\
	ROM_LOAD16_BYTE( "263p.c2", 0x0000001, 0x800000, CRC(c6035792) SHA1(4df46c8a80a33cb452d5c6c070930460f39fbebc) )\
	ROM_LOAD16_BYTE( "263p.c3", 0x1000000, 0x800000, CRC(0721d112) SHA1(e4ab659082231c32e09c28ebc5bf38dbdae5d2e4) )\
	ROM_LOAD16_BYTE( "263p.c4", 0x1000001, 0x800000, CRC(6aa688dd) SHA1(df18c4ff82c4e93f662416859311e53552ae1401) )\
	ROM_LOAD16_BYTE( "263p.c5", 0x2000000, 0x800000, CRC(794bc2d6) SHA1(c8112b42f3ea9f51cbd7dccec2071361fdc35bf3) )\
	ROM_LOAD16_BYTE( "263p.c6", 0x2000001, 0x800000, CRC(f85eae54) SHA1(d0e22937bc95b37c0bb212e0d712031a1e4ab290) )

#define MSLUG4ND_SPRITES \
	ROM_REGION( 0x3000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "263nd.c1", 0x0000000, 0x800000, CRC(361ddda6) SHA1(95f329019660f1ec7f15f6ea1e0c2bfc84b02ca8) )\
	ROM_LOAD16_BYTE( "263nd.c2", 0x0000001, 0x800000, CRC(15d192c4) SHA1(0b9afb62a1d4d764d616408b09e17a05fc4a87e7) )\
	ROM_LOAD16_BYTE( "263nd.c3", 0x1000000, 0x800000, CRC(63fb79ff) SHA1(a7da0a554034792721abda4369a71b0c8045f334) )\
	ROM_LOAD16_BYTE( "263nd.c4", 0x1000001, 0x800000, CRC(e8623126) SHA1(66c2b874cd55c628e7e6768d6f31180c29a734e7) )\
	ROM_LOAD16_BYTE( "263nd.c5", 0x2000000, 0x400000, CRC(3348dc5d) SHA1(a119e80aa2b36a7d8c7e8debd0eb13441a19adff) )\
	ROM_LOAD16_BYTE( "263nd.c6", 0x2000001, 0x400000, CRC(d90fc1a0) SHA1(0eaf5f658212c19a4cdbcdbff3b04389a2be76bb) )

#define MSLUG4NDP_SPRITES \
	ROM_REGION( 0x4000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "263nd.c1",  0x0000000, 0x800000, CRC(361ddda6) SHA1(95f329019660f1ec7f15f6ea1e0c2bfc84b02ca8) )\
	ROM_LOAD16_BYTE( "263nd.c2",  0x0000001, 0x800000, CRC(15d192c4) SHA1(0b9afb62a1d4d764d616408b09e17a05fc4a87e7) )\
	ROM_LOAD16_BYTE( "263nd.c3",  0x1000000, 0x800000, CRC(63fb79ff) SHA1(a7da0a554034792721abda4369a71b0c8045f334) )\
	ROM_LOAD16_BYTE( "263nd.c4",  0x1000001, 0x800000, CRC(e8623126) SHA1(66c2b874cd55c628e7e6768d6f31180c29a734e7) )\
	ROM_LOAD16_BYTE( "263ndp.c5", 0x2000000, 0x800000, CRC(0a4918cf) SHA1(d25f2acdaacfbee3190cf0c60c1d02ec45ada18a) )\
	ROM_LOAD16_BYTE( "263ndp.c6", 0x2000001, 0x800000, CRC(4d8bc320) SHA1(593a7a01f0e162106169a90900670eea096a0a92) )

#define MSLUG4LWD_SPRITES \
	ROM_REGION( 0x3000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "263nd.c1",  0x0000000, 0x800000, CRC(361ddda6) SHA1(95f329019660f1ec7f15f6ea1e0c2bfc84b02ca8) )\
	ROM_LOAD16_BYTE( "263nd.c2",  0x0000001, 0x800000, CRC(15d192c4) SHA1(0b9afb62a1d4d764d616408b09e17a05fc4a87e7) )\
	ROM_LOAD16_BYTE( "263lwd.c3", 0x1000000, 0x800000, CRC(e296612c) SHA1(57eb1861b738247aaf0643641268f676b71ed025) )\
	ROM_LOAD16_BYTE( "263lwd.c4", 0x1000001, 0x800000, CRC(c22e3ad0) SHA1(11ce301d4e5b4b1b76e2b82d18c4a9b8b56eeb20) )\
	ROM_LOAD16_BYTE( "263lwd.c5", 0x2000000, 0x400000, CRC(288cd91f) SHA1(a195be13d4ef19705cd3f08be1ec8cdacb29f159) )\
	ROM_LOAD16_BYTE( "263lwd.c6", 0x2000001, 0x400000, CRC(b015aeee) SHA1(24e12e72b82eea9e52a4cefc774efb3bd7db822f) )

#define MSLUG4D_SPRITES \
	ROM_REGION( 0x3000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "263d.c1", 0x0000000, 0x800000, CRC(a75ffcde) SHA1(97f405a95a56615ae49f79e1a69f98cc2f2434ef) )\
	ROM_LOAD16_BYTE( "263d.c2", 0x0000001, 0x800000, CRC(5ab0d12b) SHA1(8a3d95dd2e9cc1b6dcf6a957fed43ee390248307) )\
	ROM_LOAD16_BYTE( "263d.c3", 0x1000000, 0x800000, CRC(61af560c) SHA1(aa7bc45e03a6bbd18eb56d118d4932102ccb196a) )\
	ROM_LOAD16_BYTE( "263d.c4", 0x1000001, 0x800000, CRC(f2c544fd) SHA1(179b064f81b49f5808d7a7a5bce28e95b09e5abe) )\
	ROM_LOAD16_BYTE( "263d.c5", 0x2000000, 0x800000, CRC(84c66c44) SHA1(9273f44bf11891aa04ddd2cbb6442d084c2a2e04) )\
	ROM_LOAD16_BYTE( "263d.c6", 0x2000001, 0x800000, CRC(5ed018ab) SHA1(e78501fa8a80960093a4d54ce952681a98300148) )

#define MSLUG4HD_SPRITES \
	ROM_REGION( 0x3000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "263d.c1",  0x0000000, 0x800000, CRC(a75ffcde) SHA1(97f405a95a56615ae49f79e1a69f98cc2f2434ef) )\
	ROM_LOAD16_BYTE( "263d.c2",  0x0000001, 0x800000, CRC(5ab0d12b) SHA1(8a3d95dd2e9cc1b6dcf6a957fed43ee390248307) )\
	ROM_LOAD16_BYTE( "263d.c3",  0x1000000, 0x800000, CRC(61af560c) SHA1(aa7bc45e03a6bbd18eb56d118d4932102ccb196a) )\
	ROM_LOAD16_BYTE( "263d.c4",  0x1000001, 0x800000, CRC(f2c544fd) SHA1(179b064f81b49f5808d7a7a5bce28e95b09e5abe) )\
	ROM_LOAD16_BYTE( "263nd.c5", 0x2000000, 0x400000, CRC(3348dc5d) SHA1(a119e80aa2b36a7d8c7e8debd0eb13441a19adff) )\
	ROM_LOAD16_BYTE( "263nd.c6", 0x2000001, 0x400000, CRC(d90fc1a0) SHA1(0eaf5f658212c19a4cdbcdbff3b04389a2be76bb) )

#define MSLUG4DDH_SPRITES \
	ROM_REGION( 0x3000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "263d.c1",     0x0000000, 0x800000, CRC(a75ffcde) SHA1(97f405a95a56615ae49f79e1a69f98cc2f2434ef) )\
	ROM_LOAD16_BYTE( "263d.c2",     0x0000001, 0x800000, CRC(5ab0d12b) SHA1(8a3d95dd2e9cc1b6dcf6a957fed43ee390248307) )\
	ROM_LOAD16_BYTE( "263d.c3",     0x1000000, 0x800000, CRC(61af560c) SHA1(aa7bc45e03a6bbd18eb56d118d4932102ccb196a) )\
	ROM_LOAD16_BYTE( "263d.c4",     0x1000001, 0x800000, CRC(f2c544fd) SHA1(179b064f81b49f5808d7a7a5bce28e95b09e5abe) )\
	ROM_LOAD16_BYTE( "263_hc16.c5", 0x2000000, 0x800000, CRC(1d340215) SHA1(38f1380c286c6452c9d513b7761e9142126dcea4) )\
	ROM_LOAD16_BYTE( "263_hc16.c6", 0x2000001, 0x800000, CRC(231d54ea) SHA1(d9a7fd64661add60d8e4ff961f00e1aae9458a74) )

#define MSLUG4FR_SPRITES \
	ROM_REGION( 0x3000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "263_hc20.c1", 0x0000000, 0x800000, CRC(4586314e) SHA1(54a4b9731f0a3b48fce8a842b74fb699bfdf32f8) )\
	ROM_LOAD16_BYTE( "263_hc20.c2", 0x0000001, 0x800000, CRC(2e10ad0b) SHA1(38215adacd47a48c4640703c8a9f6234235c8ae8) )\
	ROM_LOAD16_BYTE( "263d.c3", 0x1000000, 0x800000, CRC(61af560c) SHA1(aa7bc45e03a6bbd18eb56d118d4932102ccb196a) )\
	ROM_LOAD16_BYTE( "263d.c4", 0x1000001, 0x800000, CRC(f2c544fd) SHA1(179b064f81b49f5808d7a7a5bce28e95b09e5abe) )\
	ROM_LOAD16_BYTE( "263d.c5", 0x2000000, 0x800000, CRC(84c66c44) SHA1(9273f44bf11891aa04ddd2cbb6442d084c2a2e04) )\
	ROM_LOAD16_BYTE( "263d.c6", 0x2000001, 0x800000, CRC(5ed018ab) SHA1(e78501fa8a80960093a4d54ce952681a98300148) )

#define MS5PCB_SFIX_MT_128K \
	NEO_SFIX_MT_128K

#define MS5PCBD_SFIX_MT_512K \
	NEO_SFIX_MT_512K

#define MSLUG5_SFIX_MT_128K \
	NEO_SFIX_MT_128K

#define MS5BOOT_SFIX_128K \
	NEO_SFIX_MT_128K \
	ROM_LOAD( "268boot.s1", 0x10000, 0x10000, CRC(52a8c09b) SHA1(3a90d8e44aa7cbc79945f8ece0e2fb9ce3e5a4c7) ) \
	ROM_CONTINUE(           0x00000, 0x10000 )

#define MS5PLUS_SFIX_128K \
    NEO_SFIX_128K("ms5p.s1", CRC(21e04432) SHA1(10057a2aa487087f7143d1d69fdad978a6bef0f7) )

#define MS5PLUSD_SFIX_128K \
    NEO_SFIX_128K("268_plusd.s1", CRC(99ef577b) SHA1(82f30b61ea4439a6673e0b70b7a9aceaaafd8943) )

#define MSLUG5B_SFIX_MT_128K \
    NEO_SFIX_128K( "ms5b.s1", CRC(3a427c9f) SHA1(6c6050640adb7148d42d35e3017cc171e53ae957) )

#define MSLUG5D_SFIX_128K \
	NEO_SFIX_128K( "268d.s1", CRC(64952683) SHA1(88ec728c2fe18a11fdd218bed5d73bb3affe2ec1) )

#define MSLUG5FR_SFIX_128K \
    NEO_SFIX_128K( "268_hc24.s1", CRC(77b18feb) SHA1(2d7cb5838730bfcb45eceeef11557cbcab8aa9da) )

#define MS5BOOT_AUDIO_128K \
	NEO_BIOS_AUDIO_256K( "268boot.m1", CRC(792e07c1) SHA1(117516e8ec9026c7682ab27857aab6639bef5835) )

#define MS5PLUSD_AUDIO_512K \
    NEO_BIOS_AUDIO_512K( "268_plusd.m1", CRC(39f3cbba) SHA1(56f9ba6a1ecfc28733b7b88c9796415cba0461f2) )

#define MSLUG5_AUDIO_ENCRYPTED_512K \
	NEO_BIOS_AUDIO_ENCRYPTED_512K( "268.m1", CRC(4a5a6e0e) SHA1(df0f660f2465e1db7be5adfcaf5e88ad61a74a42) )

#define MSLUG5B_AUDIO_128K \
    NEO_BIOS_AUDIO_128K( "268b.m1", CRC(bf1601bc) SHA1(5e285c98c65acefd77e893247482af0d09f3e1e4) )

#define MSLUG5P_AUDIO_256K \
	ROM_REGION( 0x50000, "audiocpu_m2", 0 ) \
	ROM_LOAD_OPTIONAL( "268p.m1", 0x00000, 0x40000, CRC(88c11f51) SHA1(5592819be64b69ab361d3b6b139fc68d8cabd29d) ) \
	ROM_RELOAD(     0x10000, 0x40000 ) \
	NEO_BIOS_AUDIO_256K( "268ndp.m1", CRC(6866d696) SHA1(3638b072e44277a6bffea5a78a915a14c6afcba0) )

#define MSLUG5N_AUDIO_512K \
	NEO_BIOS_AUDIO_512K( "268n.m1", CRC(2f621a2b) SHA1(e88f645b4935157608c32843f203180c796f5304) )

#define MSLUG5W_AUDIO_512K \
    NEO_BIOS_AUDIO_512K( "268_hc04.m1", CRC(464c72ad) SHA1(9e8a01c2bad897e2bbf32563a30f0474f8fcd2b5) )

#define MSLUG5ND_AUDIO_128K \
	NEO_BIOS_AUDIO_128K( "268nd.m1", CRC(6fa01c9a) SHA1(3dab7593bfcce318d22ec3df672ee3b4ab73dcf5) )

#define MSLUG5NDP_AUDIO_256K \
	NEO_BIOS_AUDIO_256K( "268ndp.m1", CRC(6866d696) SHA1(3638b072e44277a6bffea5a78a915a14c6afcba0) )

#define MSLUG5D_AUDIO_64K \
	NEO_BIOS_AUDIO_64K( "268d.m1", CRC(3c0655a7) SHA1(ae839d4c2b87a7aa3dd8e5caddc43eb75ee9b732) )

#define MS5PCB_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "268c.v1", 0x000000, 0x1000000, CRC(8458afe5) SHA1(62b4c6e7db763e9ff2697bbcdb43dc5a56b48c68) )

#define MS5PCBD_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
    ROM_LOAD( "268pcbd.v1", 0x000000, 0x1000000, CRC(4182838b) SHA1(03e58b6709db467e92397b26b84658f5adb0ff92) )

#define MS5PLUSD_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "268_plusd.v1", 0x000000, 0x800000, CRC(7ff6ca47) SHA1(e36c4e6a349dd9fd38d1a36b6760bbd943c2a42f) )\
	ROM_LOAD( "268_plusd.v2", 0x800000, 0x800000, CRC(696cce3b) SHA1(538d4a25befa4ffd25a48df97380469c13980f7a) )

#define MSLUG5_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "268.v1", 0x000000, 0x800000, CRC(ae31d60c) SHA1(c42285cf4e52fea74247860813e826df5aa7600a) )\
	ROM_LOAD( "268.v2", 0x800000, 0x800000, CRC(c40613ed) SHA1(af889570304e2867d7dfea1e94e388c06249fb67) )

#define MSLUG5B_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "268b.v1", 0x000000, 0x400000, CRC(e3f9fd75) SHA1(8772d0936c45623763b92c55816d0e56dd8d2ef2) ) \
	ROM_LOAD( "268b.v2", 0x400000, 0x400000, CRC(a53618f6) SHA1(002e37f3d45aa6153593c7939902e1a022de14c7) ) \
	ROM_LOAD( "268b.v3", 0x800000, 0x400000, CRC(14f000ee) SHA1(b30df60964cc8480b78a4bc2d323cad59e44a0ae) ) \
	ROM_LOAD( "268b.v4", 0xc00000, 0x400000, CRC(0ccee813) SHA1(4bc034f7f37da956b4116a2dea8a856b96e43c18) )

#define MSLUG5P_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "268p.v1", 0x000000, 0x800000, CRC(33c6305c) SHA1(67fce35a62941d2dcec75f0e6319677d6df7a4dc) )\
	ROM_LOAD( "268p.v2", 0x800000, 0x800000, CRC(1afb848e) SHA1(368e950043deebc91f7b38be770fa1045a0153af) )

#define MS5BOOT_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "268boot.v1", 0x000000, 0x400000, CRC(c3540e0d) SHA1(bf7ca3abe291b28a4cfaef791f0c556cc98ad8d8) )\
	ROM_LOAD( "268boot.v2", 0x400000, 0x400000, CRC(077bd2f4) SHA1(1699959d17f8c7113cebdb9da2e1cd18ce48486c) )\
	ROM_LOAD( "268boot.v3", 0x800000, 0x400000, CRC(39b14567) SHA1(1658612a93ba30130f9260bc41d3f18f6b90c1e7) )\
	ROM_LOAD( "268boot.v4", 0xc00000, 0x400000, CRC(969ff3b2) SHA1(50feceb741a1c08b000b077a33151ab1352eb798) )

#define MSLUG5N_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "268n.v1", 0x000000, 0x400000, CRC(dc7f03f0) SHA1(e1e31dcaff1f8d2c4b2d657aa856a60771d82c26) )\
	ROM_LOAD( "268n.v2", 0x400000, 0x400000, CRC(eeb7c926) SHA1(4d71f59948bdc5ed2e6daf101f16fd979e1ab193) )\
	ROM_LOAD( "268n.v3", 0x800000, 0x400000, CRC(02fd519e) SHA1(6fbda5bf8dbf52bc110aba7b9d20b24bdc2fe0d7) )\
	ROM_LOAD( "268n.v4", 0xc00000, 0x400000, CRC(d7c67794) SHA1(345dcbf76b25b2fbd10bcaf08ee395da0a52c5ce) )

#define MSLUG5NDP_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "268ndp.v1", 0x000000, 0x800000, CRC(e443be70) SHA1(0b0e3ee94b49c841f05504cabd8ceaf1fe1cace4) )\
	ROM_LOAD( "268ndp.v2", 0x800000, 0x800000, CRC(8dc25965) SHA1(194654d6cbe5149c4547f3d17d5550683698153c) )

#define MSLUG5F_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "268_hc06.v1", 0x000000, 0x400000, CRC(f61daa9e) SHA1(c9a64c48a37d9fcbd83f34580f44330aab0a0601) )\
	ROM_LOAD( "268_hc06.v2", 0x400000, 0x400010, CRC(7fed45cb) SHA1(13ba8955f4b3703b9d44bab526263d552e7e1916) )\
	ROM_LOAD( "268_hc06.v3", 0x800000, 0x400000, CRC(dc737e12) SHA1(f940ea767404f6a15dea526eda56ad66517ba79e) )\
	ROM_LOAD( "268_hc06.v4", 0xc00000, 0x400000, CRC(e3a76022) SHA1(58a7cd31728f8a5dcdf12fd1cac5f97f558b9f50) )\
	ROM_IGNORE(0x37510)

#define MSLUG5W_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "268_hc04.v1", 0x000000, 0x400000, CRC(a8e12a92) SHA1(b23d80d131649c1d243bb30cf5b2141354a7ac55) )\
	ROM_LOAD( "268_hc04.v2", 0x400000, 0x400000, CRC(0608cba3) SHA1(ad7c985a25abd68c58e502c008b45e0b14422829) )\
	ROM_LOAD( "268n.v3",     0x800000, 0x400000, CRC(02fd519e) SHA1(6fbda5bf8dbf52bc110aba7b9d20b24bdc2fe0d7) )\
	ROM_LOAD( "268_hc04.v4", 0xc00000, 0x400000, CRC(179cbca3) SHA1(fdcb0df0c2f73d11cd32a8625ad6fa24cedb9dc9) )\
	ROM_IGNORE(0x2f0)

#define MSLUG5EXT_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "268_hc03.v1",  0x000000, 0x800000, CRC(14848c5c) SHA1(8f67daa54738f8b217cce1f1d0a7872fd06d91b6) )\
	ROM_LOAD( "268_plusd.v2", 0x800000, 0x800000, CRC(696cce3b) SHA1(538d4a25befa4ffd25a48df97380469c13980f7a) )

#define MSLUG5LA_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "268_hc04.v1", 0x000000, 0x400000, CRC(a8e12a92) SHA1(b23d80d131649c1d243bb30cf5b2141354a7ac55) )\
	ROM_LOAD( "268_hc04.v2", 0x400000, 0x400000, CRC(0608cba3) SHA1(ad7c985a25abd68c58e502c008b45e0b14422829) )\
	ROM_LOAD( "268_la01.v3", 0x800000, 0x400000, CRC(aeff1982) SHA1(ac777a12639e21f0f227be84a59c7bb543c6ddd9) )\
	ROM_LOAD( "268_hc04.v4", 0xc00000, 0x400000, CRC(179cbca3) SHA1(fdcb0df0c2f73d11cd32a8625ad6fa24cedb9dc9) )\
	ROM_IGNORE(0x2f0)

#define MSLUG5RMXE_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "268_rma01.v1", 0x000000, 0x400000, CRC(fcc8ba01) SHA1(c187c318c65f6aefae05e6cef9f17492edf2e4db) )\
	ROM_LOAD( "268_rma01.v2", 0x400000, 0x400000, CRC(386f32bd) SHA1(d49fc812c442563b9e82da43bf5c6b9deea0f687) )\
	ROM_LOAD( "268_la01.v3",  0x800000, 0x400000, CRC(aeff1982) SHA1(ac777a12639e21f0f227be84a59c7bb543c6ddd9) )\
	ROM_LOAD( "268_rma01.v4", 0xc00000, 0x400000, CRC(2b310542) SHA1(5f0050d36cd1f722d78d9ae98db537eacc4d8548) )\
	ROM_IGNORE(0x37510)

#define MS5PCB_SPRITES \
	ROM_REGION( 0x4000000, "sprites", 0 ) \
	ROM_LOAD32_WORD( "268c.c1", 0x0000000, 0x1000000, CRC(802042e8) SHA1(ff028b65f60f0b51b255a380cc47ec19fdc0c0cf) )\
	ROM_LOAD32_WORD( "268c.c2", 0x0000002, 0x1000000, CRC(3b89fb9f) SHA1(cbc0729aae961f683b105ec3e1cda58b3f985abc) )\
	ROM_LOAD32_WORD( "268c.c3", 0x2000000, 0x1000000, CRC(0f3f59e3) SHA1(8cc751dc7d4e94864a9ce3346f23b8f011082fcc) )\
	ROM_LOAD32_WORD( "268c.c4", 0x2000002, 0x1000000, CRC(3ad8435a) SHA1(b333c8993c9b4c4ea59450ad0a3560e0b28056bc) )

#define MS5PCBD_SPRITES \
	ROM_REGION( 0x4000000, "sprites", 0 ) \
    ROM_LOAD16_BYTE( "268pcbd.c1", 0x0000000, 0x1000000, CRC(996debed) SHA1(ec6965a24862541f337a1b7e259038b9b40ad1d2) )\
	ROM_LOAD16_BYTE( "268pcbd.c2", 0x0000001, 0x1000000, CRC(960a9764) SHA1(687cf957d91ef9da219b573f444e668209dcea41) )\
	ROM_LOAD16_BYTE( "268pcbd.c3", 0x2000000, 0x1000000, CRC(f699994f) SHA1(ff079d3c126e9611760956d51c5df66d8013dd78) )\
	ROM_LOAD16_BYTE( "268pcbd.c4", 0x2000001, 0x1000000, CRC(49e902e8) SHA1(289a560ffe3d50abd773c61fa2df3c1f18d7e803) )

#define MSLUG5_SPRITES \
	ROM_REGION( 0x4000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "268.c1", 0x0000000, 0x800000, CRC(ab7c389a) SHA1(025a188de589500bf7637fa8e7a37ab24bf4312e) )\
	ROM_LOAD16_BYTE( "268.c2", 0x0000001, 0x800000, CRC(3560881b) SHA1(493d218c92290b4770024d6ee2917c4022753b07) )\
	ROM_LOAD16_BYTE( "268.c3", 0x1000000, 0x800000, CRC(3af955ea) SHA1(cf36b6ae9b0d12744b17cb7a928399214de894be) )\
	ROM_LOAD16_BYTE( "268.c4", 0x1000001, 0x800000, CRC(c329c373) SHA1(5073d4079958a0ef5426885af2c9e3178f37d5e0) )\
	ROM_LOAD16_BYTE( "268.c5", 0x2000000, 0x800000, CRC(959c8177) SHA1(889bda7c65d71172e7d89194d1269561888fe789) )\
	ROM_LOAD16_BYTE( "268.c6", 0x2000001, 0x800000, CRC(010a831b) SHA1(aec140661e3ae35d264df416478ba15188544d91) )\
	ROM_LOAD16_BYTE( "268.c7", 0x3000000, 0x800000, CRC(6d72a969) SHA1(968dd9a4d1209b770b9b85ea6532fa24d262a262) )\
	ROM_LOAD16_BYTE( "268.c8", 0x3000001, 0x800000, CRC(551d720e) SHA1(ebf69e334fcaba0fda6fd432fd0970283a365d12) )

#define MSLUG5B_SPRITES \
	ROM_REGION( 0x4000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "268b.c1", 0x0000000, 0x800000, CRC(4b0e5998) SHA1(458486d579db118ec4ba4f9fce9d62fedfef949b) )\
	ROM_LOAD16_BYTE( "268b.c2", 0x0000001, 0x800000, CRC(022fc30b) SHA1(7178900acbb377c3de95338c8fae56e308327cab) )\
	ROM_LOAD16_BYTE( "268b.c3", 0x1000000, 0x800000, CRC(ead86d28) SHA1(e1db4f839972748f49dddfe3bd4b0cf2e0ddf074) )\
	ROM_LOAD16_BYTE( "268b.c4", 0x1000001, 0x800000, CRC(0be6be35) SHA1(34e20e55423cefd2b98c15061f86198b64727173) )\
	ROM_LOAD16_BYTE( "268b.c5", 0x2000000, 0x200000, CRC(2a23e569) SHA1(576370a24a8ef5ca0f8e7afa4ccdb0cb3ad9bdaa) )\
	ROM_LOAD16_BYTE( "268b.c6", 0x2000001, 0x200000, CRC(6eb6bc9e) SHA1(4e54d904b0ce34cca429b3c86ab8bf972c66336e) )\
	ROM_LOAD16_BYTE( "268b.c7", 0x3000000, 0x800000, CRC(57f4e53f) SHA1(813d98175288045c0750d45afe03c74973d70cee) )\
	ROM_LOAD16_BYTE( "268b.c8", 0x3000001, 0x800000, CRC(9d59ff7c) SHA1(ff90dc79598de0880df17624c76df81c92f267ce) )

#define MSLUG5DX_SPRITES \
	ROM_REGION( 0x4000000, "sprites", 0 ) \
	ROM_LOAD( "268dd.c1", 0x0000000, 0x4000000, CRC(727f4b9c) SHA1(a57ec93ac27fc4d064cd2317dea912f9eff6c62b) )

#define MSLUG5P_SPRITES \
	ROM_REGION( 0x4000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "268p.c1", 0x0000000, 0x800000, CRC(27d59de8) SHA1(0447a675d885721cedc079788cf41ae3f797834b) )\
	ROM_LOAD16_BYTE( "268p.c2", 0x0000001, 0x800000, CRC(e600dee1) SHA1(e55e5a25616c4daf09692d1b53a92d6f31e842ac) )\
	ROM_LOAD16_BYTE( "268p.c3", 0x1000000, 0x800000, CRC(b650f098) SHA1(4cd729153bd5b2054fbe10c96d2bb370084d1d24) )\
	ROM_LOAD16_BYTE( "268p.c4", 0x1000001, 0x800000, CRC(10499589) SHA1(24542a3b70080e5a61fdab04ab314450a1d821ef) )\
	ROM_LOAD16_BYTE( "268p.c5", 0x2000000, 0x800000, CRC(19352405) SHA1(5ee255403739c11a65608dcff0984480f067d824) )\
	ROM_LOAD16_BYTE( "268p.c6", 0x2000001, 0x800000, CRC(b1531523) SHA1(786f342dbb7fea50139d6421e5b82e551772bf0a) )\
	ROM_LOAD16_BYTE( "268p.c7", 0x3000000, 0x800000, CRC(fe2c1338) SHA1(de9d257574881dd1684956f60011a20c1dd5a0d9) )\
	ROM_LOAD16_BYTE( "268p.c8", 0x3000001, 0x800000, CRC(ecce3141) SHA1(103247b57f8ea5746dd1cf92dda95a6dc9268c78) )

#define MSLUG5FR_SPRITES \
	ROM_REGION( 0x4000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "268_hc24.c1", 0x0000000, 0x800000, CRC(c115bcbd) SHA1(241b71cb442844df0f1c7005955c5ae85b95a0b9) )\
	ROM_LOAD16_BYTE( "268_hc24.c2", 0x0000001, 0x800000, CRC(a95f284f) SHA1(db6b18b15f871ac17e88d2eec72b95c8a63be959) )\
	ROM_LOAD16_BYTE( "268hd.c3",    0x1000000, 0x800000, CRC(3cda13a0) SHA1(5d029c92688384eafd65ad711a2954d0b86a3163) )\
	ROM_LOAD16_BYTE( "268hd.c4",    0x1000001, 0x800000, CRC(9c00160d) SHA1(c612102f9cd288bba4c245b5855d795e4362b217) )\
	ROM_LOAD16_BYTE( "268_hc24.c5", 0x2000000, 0x800000, CRC(dae4bdba) SHA1(c7da602cc59296fd264fd2f97b29bc242340760f) )\
	ROM_LOAD16_BYTE( "268_hc24.c6", 0x2000001, 0x800000, CRC(731a14ce) SHA1(2363d3f0f2e2a621051de0db6e465f7b1a387ef9) )\
	ROM_LOAD16_BYTE( "268_hc24.c7", 0x3000000, 0x800000, CRC(bc8296af) SHA1(4309d093c09219fb90104d30211c204a2abcf82e) )\
	ROM_LOAD16_BYTE( "268_hc24.c8", 0x3000001, 0x800000, CRC(6fabe6d5) SHA1(12c23b85de985b4daba7def1d9d9d9b4c050ab63) )

#define MS5BOOT_SPRITES \
	ROM_REGION( 0x4000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "268d.c1",   0x0000000, 0x800000, CRC(969c0d62) SHA1(DE3C5CFA980CCA2FAB0416AC0D292948B5D4C9C3) )\
	ROM_LOAD16_BYTE( "268d.c2",   0x0000001, 0x800000, CRC(c69ae867) SHA1(3198EE5C7C2C7563B49EBD9F7BA95D9B0B303F6C) )\
	ROM_LOAD16_BYTE( "268d.c3",   0x1000000, 0x800000, CRC(d7beaeaf) SHA1(99443EA4C1BAB45F1977A390EB7E1A0163915110) )\
	ROM_LOAD16_BYTE( "268boot.c4",0x1000001, 0x800000, CRC(e1b1131b) SHA1(68a36d336582069e79ad481638d92f57c4cd6523) )\
	ROM_LOAD16_BYTE( "268d.c5",   0x2000000, 0x800000, CRC(2fa1a5ad) SHA1(4AE15D29BA979601598EDDF8905072FE1D9E0A98) )\
	ROM_LOAD16_BYTE( "268d.c6",   0x2000001, 0x800000, CRC(6de89589) SHA1(86A6C036BF51AF516FEA83A30874026EC1586A83) )\
	ROM_LOAD16_BYTE( "268d.c7",   0x3000000, 0x800000, CRC(97bd0c0a) SHA1(30F3280FE527098ECF46541CC645A59B366105EA) )\
	ROM_LOAD16_BYTE( "268d.c8",   0x3000001, 0x800000, CRC(c0d5bc20) SHA1(b5d0d81d5cc624538b0651c568295e578a1330d1) )

#define MSLUG5D_SPRITES \
	ROM_REGION( 0x4000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "268d.c1",  0x0000000, 0x800000, CRC(969c0d62) SHA1(DE3C5CFA980CCA2FAB0416AC0D292948B5D4C9C3) )\
	ROM_LOAD16_BYTE( "268d.c2",  0x0000001, 0x800000, CRC(c69ae867) SHA1(3198EE5C7C2C7563B49EBD9F7BA95D9B0B303F6C) )\
	ROM_LOAD16_BYTE( "268d.c3",  0x1000000, 0x800000, CRC(d7beaeaf) SHA1(99443EA4C1BAB45F1977A390EB7E1A0163915110) )\
	ROM_LOAD16_BYTE( "268d.c4",  0x1000001, 0x800000, CRC(899fb2af) SHA1(A06A424C813C1B4F922C5404405779F605C90A06) )\
	ROM_LOAD16_BYTE( "268d.c5",  0x2000000, 0x800000, CRC(2fa1a5ad) SHA1(4AE15D29BA979601598EDDF8905072FE1D9E0A98) )\
	ROM_LOAD16_BYTE( "268d.c6",  0x2000001, 0x800000, CRC(6de89589) SHA1(86A6C036BF51AF516FEA83A30874026EC1586A83) )\
	ROM_LOAD16_BYTE( "268d.c7",  0x3000000, 0x800000, CRC(97bd0c0a) SHA1(30F3280FE527098ECF46541CC645A59B366105EA) )\
	ROM_LOAD16_BYTE( "268d.c8",  0x3000001, 0x800000, CRC(c0d5bc20) SHA1(b5d0d81d5cc624538b0651c568295e578a1330d1) )

#define MSLUG5SV_SPRITES \
	ROM_REGION( 0x4000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "268d.c1",  0x0000000, 0x800000, CRC(969c0d62) SHA1(DE3C5CFA980CCA2FAB0416AC0D292948B5D4C9C3) )\
	ROM_LOAD16_BYTE( "268d.c2",  0x0000001, 0x800000, CRC(c69ae867) SHA1(3198EE5C7C2C7563B49EBD9F7BA95D9B0B303F6C) )\
	ROM_LOAD16_BYTE( "268d.c3",  0x1000000, 0x800000, CRC(d7beaeaf) SHA1(99443EA4C1BAB45F1977A390EB7E1A0163915110) )\
	ROM_LOAD16_BYTE( "268boot.c4",0x1000001, 0x800000, CRC(e1b1131b) SHA1(68a36d336582069e79ad481638d92f57c4cd6523) )\
	ROM_LOAD16_BYTE( "268d.c5",  0x2000000, 0x800000, CRC(2fa1a5ad) SHA1(4AE15D29BA979601598EDDF8905072FE1D9E0A98) )\
	ROM_LOAD16_BYTE( "268d.c6",  0x2000001, 0x800000, CRC(6de89589) SHA1(86A6C036BF51AF516FEA83A30874026EC1586A83) )\
	ROM_LOAD16_BYTE( "268sv.c7",  0x3000000, 0x800000, CRC(080b585a) SHA1(ce1b8cce4377dd7543d79026de65d52b51172a93) )\
	ROM_LOAD16_BYTE( "268sv.c8",  0x3000001, 0x800000, CRC(a6450c3a) SHA1(db1891b7a6cf045f007191951a479062758ac3fa) )

#define MSLUG5HD_SPRITES \
	ROM_REGION( 0x4000000, "sprites", 0 ) \
    ROM_LOAD16_BYTE( "268hd.c1", 0x0000000, 0x800000, CRC(e8239365) SHA1(E0A75902A783110049730B66AD3CBCCDD804BF62) )\
	ROM_LOAD16_BYTE( "268hd.c2", 0x0000001, 0x800000, CRC(89b21d4c) SHA1(862AC31CE9570529B33E6F58ADA0AC867A442679) )\
	ROM_LOAD16_BYTE( "268hd.c3", 0x1000000, 0x800000, CRC(3cda13a0) SHA1(5D029C92688384EAFD65AD711A2954D0B86A3163) )\
	ROM_LOAD16_BYTE( "268hd.c4", 0x1000001, 0x800000, CRC(9c00160d) SHA1(C612102F9CD288BBA4C245B5855D795E4362B217) )\
	ROM_LOAD16_BYTE( "268hd.c5", 0x2000000, 0x800000, CRC(38754256) SHA1(744D91D041998CA27EE2781188746797C65377BD) )\
	ROM_LOAD16_BYTE( "268hd.c6", 0x2000001, 0x800000, CRC(59d33e9c) SHA1(ED7F5C7DB4C35EC5A7DB0AD5436110B3FE80B89A) )\
	ROM_LOAD16_BYTE( "268hd.c7", 0x3000000, 0x800000, CRC(c9f8c357) SHA1(7064224AFA887F57245F5479B0B46228539A131B) )\
	ROM_LOAD16_BYTE( "268hd.c8", 0x3000001, 0x800000, CRC(fafc3eb9) SHA1(F4F73194CC7FD151BE3CA2561F993B5BE7628369) )

#define MSLUG5W_SPRITES \
	ROM_REGION( 0x4000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "268hd.c1",    0x0000000, 0x800000, CRC(e8239365) SHA1(E0A75902A783110049730B66AD3CBCCDD804BF62) )\
	ROM_LOAD16_BYTE( "268hd.c2",    0x0000001, 0x800000, CRC(89b21d4c) SHA1(862AC31CE9570529B33E6F58ADA0AC867A442679) )\
	ROM_LOAD16_BYTE( "268hd.c3",    0x1000000, 0x800000, CRC(3cda13a0) SHA1(5D029C92688384EAFD65AD711A2954D0B86A3163) )\
	ROM_LOAD16_BYTE( "268hd.c4",    0x1000001, 0x800000, CRC(9c00160d) SHA1(C612102F9CD288BBA4C245B5855D795E4362B217) )\
	ROM_LOAD16_BYTE( "268_hc04.c5", 0x2000000, 0x800000, CRC(483a986c) SHA1(b6b1a08a340e4528575eff6fcf34e5965e4b6cda) )\
	ROM_LOAD16_BYTE( "268_hc04.c6", 0x2000001, 0x800000, CRC(d918f796) SHA1(fa81b7930f3f82571bc6f1f70768a613f1573325) )\
	ROM_LOAD16_BYTE( "268_hc04.c7", 0x3000000, 0x800000, CRC(bdb9a887) SHA1(f9984dbf5694afd42c2dde1ab0510c5d53719a1f) )\
	ROM_LOAD16_BYTE( "268_hc04.c8", 0x3000001, 0x800000, CRC(6f8ac6fb) SHA1(49244f0fddde4d11b3f99f52b0e0e74d73414c71) )

#define MSLUG5F_SPRITES \
	ROM_REGION( 0x4000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "268hd.c1",    0x0000000, 0x800000, CRC(e8239365) SHA1(E0A75902A783110049730B66AD3CBCCDD804BF62) )\
	ROM_LOAD16_BYTE( "268hd.c2",    0x0000001, 0x800000, CRC(89b21d4c) SHA1(862AC31CE9570529B33E6F58ADA0AC867A442679) )\
	ROM_LOAD16_BYTE( "268hd.c3",    0x1000000, 0x800000, CRC(3cda13a0) SHA1(5D029C92688384EAFD65AD711A2954D0B86A3163) )\
	ROM_LOAD16_BYTE( "268hd.c4",    0x1000001, 0x800000, CRC(9c00160d) SHA1(C612102F9CD288BBA4C245B5855D795E4362B217) )\
	ROM_LOAD16_BYTE( "268_hc06.c5", 0x2000000, 0x800000, CRC(3bc09dbf) SHA1(a47954a3295dc21e7db7dedc03ab789f8005eed5) )\
	ROM_LOAD16_BYTE( "268_hc06.c6", 0x2000001, 0x800000, CRC(0db5ce14) SHA1(aa2c4bb143e3bba18523df645c5be249eb9fc147) )\
	ROM_LOAD16_BYTE( "268_hc06.c7", 0x3000000, 0x800000, CRC(aa4f3214) SHA1(dc3a8fac2cc81e60abafc209eb4bcccdaafde380) )\
	ROM_LOAD16_BYTE( "268_hc06.c8", 0x3000001, 0x800000, CRC(c86d0d81) SHA1(1a00aa65481410c0b64fe971e547638c05c5a0ce) )

#define MSLUGX_SFIX_128K \
	NEO_SFIX_128K( "250.s1", CRC(fb6f441d) SHA1(2cc392ecde5d5afb28ddbaa1030552b48571dcfb) )

#define MSLUGXFR_SFIX_128K \
	NEO_SFIX_128K( "250_hc30.s1", CRC(a2bb2551) SHA1(fa22568bf15ac41afdf5e2bd7dc2dec4fe813f02) )

#define MSLUGXSC_SFIX_128K \
	NEO_SFIX_128K( "250_hc12.s1", CRC(03bce893) SHA1(cd8dbddf8c173de8cd26566c4451ebc3568496ac) )

#define MSLUGX_AUDIO_128K \
	NEO_BIOS_AUDIO_128K( "250.m1", CRC(fd42a842) SHA1(55769bad4860f64ef53a333e0da9e073db483d6a) )

#define MSLUGX_YMSND \
	ROM_REGION( 0xa00000, "ymsnd", 0 ) \
	ROM_LOAD( "250.v1", 0x000000, 0x400000, CRC(c79ede73) SHA1(ebfcc67204ff9677cf7972fd5b6b7faabf07280c) ) \
	ROM_LOAD( "250.v2", 0x400000, 0x400000, CRC(ea9aabe1) SHA1(526c42ca9a388f7435569400e2f132e2724c71ff) ) \
	ROM_LOAD( "250.v3", 0x800000, 0x200000, CRC(2ca65102) SHA1(45979d1edb1fc774a415d9386f98d7cb252a2043) )

#define MSLUGXDX_YMSND \
	ROM_REGION( 0xa00000, "ymsnd", 0 ) \
	ROM_LOAD( "250dd.v1", 0x000000, 0xa00000, CRC(3a0d8e6a) SHA1(e948707d450db2a6dfbf9b0ec1f116c78c89567d) ) \

#define MSLUGX_SPRITES \
	ROM_REGION( 0x3000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "250.c1", 0x0000000, 0x800000, CRC(09a52c6f) SHA1(c3e8a8ccdac0f8bddc4c3413277626532405fae2) )\
	ROM_LOAD16_BYTE( "250.c2", 0x0000001, 0x800000, CRC(31679821) SHA1(554f600a3aa09c16c13c625299b087a79d0d15c5) )\
	ROM_LOAD16_BYTE( "250.c3", 0x1000000, 0x800000, CRC(fd602019) SHA1(c56646c62387bc1439d46610258c755beb8d7dd8) )\
	ROM_LOAD16_BYTE( "250.c4", 0x1000001, 0x800000, CRC(31354513) SHA1(31be8ea2498001f68ce4b06b8b90acbf2dcab6af) )\
	ROM_LOAD16_BYTE( "250.c5", 0x2000000, 0x800000, CRC(a4b56124) SHA1(d41069856df990a1a99d39fb263c8303389d5475) )\
	ROM_LOAD16_BYTE( "250.c6", 0x2000001, 0x800000, CRC(83e3e69d) SHA1(39be66287696829d243fb71b3fb8b7dc2bc3298f) )

#define MSLUGXDD_SPRITES \
	ROM_REGION( 0x3000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "250.c1",      0x0000000, 0x800000, CRC(09a52c6f) SHA1(c3e8a8ccdac0f8bddc4c3413277626532405fae2) )\
	ROM_LOAD16_BYTE( "250.c2",      0x0000001, 0x800000, CRC(31679821) SHA1(554f600a3aa09c16c13c625299b087a79d0d15c5) )\
	ROM_LOAD16_BYTE( "250.c3",      0x1000000, 0x800000, CRC(fd602019) SHA1(c56646c62387bc1439d46610258c755beb8d7dd8) )\
	ROM_LOAD16_BYTE( "250.c4",      0x1000001, 0x800000, CRC(31354513) SHA1(31be8ea2498001f68ce4b06b8b90acbf2dcab6af) )\
	ROM_LOAD16_BYTE( "250_hc24.c5", 0x2000000, 0x800000, CRC(b2d7bf98) SHA1(1526564518aaf19a2eebc90175abbcc47c3e1147) )\
	ROM_LOAD16_BYTE( "250_hc24.c6", 0x2000001, 0x800000, CRC(e0f7a059) SHA1(571d67ed24512bffc81554599c29e585dd533cf4) )

#define MSLUGXDX_SPRITES \
	ROM_REGION( 0x3000000, "sprites", 0 ) \
	ROM_LOAD( "250dd.c1",     0x0000000, 0x3000000, CRC(a3710983) SHA1(196dc03485d3cb3e37d328dfdc79a494258fe6c4) )

#define MSLUGXP_SPRITES \
	ROM_REGION( 0x3000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "250.c1",  0x0000000, 0x800000, CRC(09a52c6f) SHA1(c3e8a8ccdac0f8bddc4c3413277626532405fae2) )\
	ROM_LOAD16_BYTE( "250p.c2", 0x0000001, 0x800000, CRC(cff5d557) SHA1(bbb9d97d01dc85074f1be75d9b14043fa526e00c) )\
	ROM_LOAD16_BYTE( "250.c3",  0x1000000, 0x800000, CRC(fd602019) SHA1(c56646c62387bc1439d46610258c755beb8d7dd8) )\
	ROM_LOAD16_BYTE( "250.c4",  0x1000001, 0x800000, CRC(31354513) SHA1(31be8ea2498001f68ce4b06b8b90acbf2dcab6af) )\
	ROM_LOAD16_BYTE( "250.c5",  0x2000000, 0x800000, CRC(a4b56124) SHA1(d41069856df990a1a99d39fb263c8303389d5475) )\
	ROM_LOAD16_BYTE( "250.c6",  0x2000001, 0x800000, CRC(83e3e69d) SHA1(39be66287696829d243fb71b3fb8b7dc2bc3298f) )

#define MSLUGXLB_SPRITES \
	ROM_REGION( 0x3000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "250_hc02.c1", 0x0000000, 0x800000, CRC(d52e8702) SHA1(e332e9c95679dbdbcdfdf868b3a0233ad6bd47c4) )\
	ROM_LOAD16_BYTE( "250_hc02.c2", 0x0000001, 0x800000, CRC(edec334c) SHA1(56c6d6d19dd891e1dc66b1089abb2dacd1ad2611) )\
	ROM_LOAD16_BYTE( "250.c3",      0x1000000, 0x800000, CRC(fd602019) SHA1(c56646c62387bc1439d46610258c755beb8d7dd8) )\
	ROM_LOAD16_BYTE( "250.c4",      0x1000001, 0x800000, CRC(31354513) SHA1(31be8ea2498001f68ce4b06b8b90acbf2dcab6af) )\
	ROM_LOAD16_BYTE( "250.c5",      0x2000000, 0x800000, CRC(a4b56124) SHA1(d41069856df990a1a99d39fb263c8303389d5475) )\
	ROM_LOAD16_BYTE( "250.c6",      0x2000001, 0x800000, CRC(83e3e69d) SHA1(39be66287696829d243fb71b3fb8b7dc2bc3298f) )

#define MSLUGXER_SPRITES \
	ROM_REGION( 0x3000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "250.c1",      0x0000000, 0x800000, CRC(09a52c6f) SHA1(c3e8a8ccdac0f8bddc4c3413277626532405fae2) )\
	ROM_LOAD16_BYTE( "250.c2",      0x0000001, 0x800000, CRC(31679821) SHA1(554f600a3aa09c16c13c625299b087a79d0d15c5) )\
	ROM_LOAD16_BYTE( "250.c3",      0x1000000, 0x800000, CRC(fd602019) SHA1(c56646c62387bc1439d46610258c755beb8d7dd8) )\
	ROM_LOAD16_BYTE( "250.c4",      0x1000001, 0x800000, CRC(31354513) SHA1(31be8ea2498001f68ce4b06b8b90acbf2dcab6af) )\
	ROM_LOAD16_BYTE( "250_er01.c5", 0x2000000, 0x800000, CRC(9a9422e4) SHA1(453b897a98574c7be881123398642cf5ec143896) )\
	ROM_LOAD16_BYTE( "250_er01.c6", 0x2000001, 0x800000, CRC(ef116b50) SHA1(de725caad51cc787fba5d21a709844fa96362488) )

#define MSLUGXFR_SPRITES \
	ROM_REGION( 0x3000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "250_hc30.c1", 0x0000000, 0x800000, CRC(eb7ce1ff) SHA1(e519b53c6938451f9bfb4d15c10baa7f152ecfcd) )\
	ROM_LOAD16_BYTE( "250_hc30.c2", 0x0000001, 0x800000, CRC(45c7e401) SHA1(b71754cc746631f1a70c09ef564c7be11aa577e9) )\
	ROM_LOAD16_BYTE( "250.c3",      0x1000000, 0x800000, CRC(fd602019) SHA1(c56646c62387bc1439d46610258c755beb8d7dd8) )\
	ROM_LOAD16_BYTE( "250.c4",      0x1000001, 0x800000, CRC(31354513) SHA1(31be8ea2498001f68ce4b06b8b90acbf2dcab6af) )\
	ROM_LOAD16_BYTE( "250.c5",      0x2000000, 0x800000, CRC(a4b56124) SHA1(d41069856df990a1a99d39fb263c8303389d5475) )\
	ROM_LOAD16_BYTE( "250.c6",      0x2000001, 0x800000, CRC(83e3e69d) SHA1(39be66287696829d243fb71b3fb8b7dc2bc3298f) )

#define MSLUGXSCU_SPRITES \
	ROM_REGION( 0x3000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "250.c1",       0x0000000, 0x800000, CRC(09a52c6f) SHA1(c3e8a8ccdac0f8bddc4c3413277626532405fae2) )\
	ROM_LOAD16_BYTE( "250.c2",       0x0000001, 0x800000, CRC(31679821) SHA1(554f600a3aa09c16c13c625299b087a79d0d15c5) )\
	ROM_LOAD16_BYTE( "250.c3",       0x1000000, 0x800000, CRC(fd602019) SHA1(c56646c62387bc1439d46610258c755beb8d7dd8) )\
	ROM_LOAD16_BYTE( "250.c4",       0x1000001, 0x800000, CRC(31354513) SHA1(31be8ea2498001f68ce4b06b8b90acbf2dcab6af) )\
	ROM_LOAD16_BYTE( "250_hc12.c5",  0x2000000, 0x800000, CRC(ce4ccd03) SHA1(c8ecff1d91165b47dc52311a81617e2a7a8faae5) )\
	ROM_LOAD16_BYTE( "250_hc12.c6",  0x2000001, 0x800000, CRC(b19552b7) SHA1(562bbe5048c573c5d7ecb9fa92611f3d9b052f7a) )

#define MSLUGXCQ_SPRITES \
	ROM_REGION( 0x3000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "250.c1",       0x0000000, 0x800000, CRC(09a52c6f) SHA1(c3e8a8ccdac0f8bddc4c3413277626532405fae2) )\
	ROM_LOAD16_BYTE( "250.c2",       0x0000001, 0x800000, CRC(31679821) SHA1(554f600a3aa09c16c13c625299b087a79d0d15c5) )\
	ROM_LOAD16_BYTE( "250.c3",       0x1000000, 0x800000, CRC(fd602019) SHA1(c56646c62387bc1439d46610258c755beb8d7dd8) )\
	ROM_LOAD16_BYTE( "250.c4",       0x1000001, 0x800000, CRC(31354513) SHA1(31be8ea2498001f68ce4b06b8b90acbf2dcab6af) )\
	ROM_LOAD16_BYTE( "250_hc25.c5",  0x2000000, 0x800000, CRC(916b7239) SHA1(f8fe77ba2f07cc60fd22887a1de81ccf0e933a69) )\
	ROM_LOAD16_BYTE( "250_hc25.c6",  0x2000001, 0x800000, CRC(23016767) SHA1(9292c129575bc1ef96f30e3564cbf46c0c1bfd30) )

#define MSLUG3X_SFIX_MT_128K \
	NEO_SFIX_128K( "268_hb.s1", CRC(d2af5597) SHA1(7a1c48a65214705327a747b44105cf847a0cba21) )

#define MSLUG3X_AUDIO_128K \
	NEO_BIOS_AUDIO_128K( "268_hb.m1", CRC(0e339fdf) SHA1(65f3c8f551050a798f42da8e8f8d94e51cce7cd1) )

#define MSLUG3X_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "268_hb.v1", 0x000000, 0x1000000, CRC(67cc9264) SHA1(701758422e1e6c0c0ea0ec15f3b9cd35b299b6ca) )\

#define MSLUG3X_SPRITES \
	ROM_REGION( 0x1000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "268_hb.c1", 0x000000, 0x800000, CRC(4a895201) SHA1(eab8d35a2fa141ffdd0997aa71771f20c64dc208) )\
	ROM_LOAD16_BYTE( "268_hb.c2", 0x000001, 0x800000, CRC(47c53b38) SHA1(f051068d9a529c91182edd7918e57c4af9f2cdd0) )

#define NEOPANG_SFIX_64K \
	NEO_SFIX_64K( "268_hwneo.s1", CRC(d78bd9a0) SHA1(17a237166aede98bee27d5b52654414c8a1b071a) )

#define NEOPANG_AUDIO_128K \
	NEO_BIOS_AUDIO_128K( "268_hwneo.m1", CRC(9c0291ea) SHA1(3fa67c62acba79be6b3a98cc1601e45569fa11ae) )

#define NEOPANG_YMSND \
	ROM_REGION( 0x80000, "ymsnd", 0 ) \
    ROM_LOAD( "268_hwneo.v1", 0x000000, 0x80000, CRC(debeb8fb) SHA1(49a3d3578c087f1a0050168571ef8d1b08c5dc05) )

#define NEOPANG_SPRITES \
	ROM_REGION( 0x200000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "268_hwneo.c1", 0x000000, 0x100000, CRC(62f5405c) SHA1(f9eb8d1838da9953aecf40c3314c608ab655cb8f) )\
	ROM_LOAD16_BYTE( "268_hwneo.c2", 0x000001, 0x100000, CRC(e1183030) SHA1(60262d53ab12314db5e5c00a94463500abe3e8b0) )

/*************************************************************************************************************************
    
	Official sets
    =============

    About supported sets:
    =====================

    MVS carts (arcade) were released before the AES carts (home)
    The actual codepath taken depends entirely on the BIOS rom, not the roms in the cartridge, which (with
    a few exceptions) support both codepaths.

    The initial AES releases are therefore later revisions of the game, often with bug fixes over the
    initial MVS releases. It isn't uncommon for later production runs and bootlegs to use these newer sets,
    so all of them are supported in MAME.

    Likewise, because the MVS carts were released first (and were produced in higher numbers and generally
    have a lower cost) it's not uncommon for AES units to operate with converted MVS carts, so, with the
    exception of the sets that specifically lock out the AES mode* these sets are all equally suitable
    for MESS.
    * nitd, kof2001 (initial release has no AES code), and a number of the hacked bootlegs.

    The 'MVS ONLY RELEASE' tagged sets were not officially released for the AES (home) system.
    Information about this can be found at 'The NeoGeo Master List' (unofficial) - http://www.neo-geo.com
    and the official NeoGeo museum - http://neogeomuseum.snkplaymore.co.jp/english/index.php
    Several unofficial 'conversions' of these sets can be found across the internet.
    For completeness sake: Some of these have sets have been released for the CD system.


    M1 (sound driver) rom information:
    ==================================
    . Many 'M1' roms contain mirrored data (64k mirrored or 128k mirrored).
    . Found on several early sets (ID 0001 ~ 0045) and on the last sets (ID 0267 ~ 0272).
    . This caused some confusion and incorrect rom sizes.
    . Minimum 'M1' size is 1mbit, maximum size 4mbit.
    . The remaining 64k 'M1' are marked BAD_DUMP.


    S1 (text layer) rom information:
    ================================
    . All 'S1' roms found on prom are 1mbit.
    . The remainig 64k 'S1' are marked BAD_DUMP.


    MULTI PLAY MODE:
    ================
    The NeoGeo has three games which support MULTI PLAY MODE (Riding Hero / League Bowling / Trash Rally).
    This allows you to 'link' 4 games (MVS) / 2 games (AES) using in game 'Multi-Play' option. To establish
    a link between the carts you have to connect the carts to each other by a communicator cable. The communicatior
    cable is a regular headphone cable with stereo pin jack. It has been reported that you can also 'link' MVS <-> AES.

    All three games use a special PROG board for MULTI PLAY MODE support:
    . Riding Hero    (AES - NEO-AEG PROG-HERO   / MVS NEO-MVS PROG-HERO)
    . League Bowling (AES - NEO-AEG PROG-HERO   / MVS NEO-MVS PROG-HERO)
    . Trash Rally    (AES - NEO-AEG PROG42G-COM / NEO-MVS PROG42G-COM)

    A HD6301V1P MCU on the above boards is used for establishing the 'link'. The MCU has a 4kb internal ROM which
    is not dumped.
    To use the MULTI PLAY MODE on your MVS you have to set the following hardware dips:
    HARD DIP SETTING  4   5   6
    CABINET 1:        OFF OFF ON
    CABINET 2:        OFF ON  ON
    CABINET 3:        ON  OFF ON
    CABINET 4:        ON  ON  ON

*************************************************************************************************************************/

ROM_START( ms5pcb ) /* Encrypted Set, JAMMA PCB */
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD32_WORD_SWAP( "268.p1", 0x000000, 0x400000, CRC(d0466792) SHA1(880819933d997fab398f91061e9dbccb959ae8a1) )
	ROM_LOAD32_WORD_SWAP( "268.p2", 0x000002, 0x400000, CRC(fbf6b61e) SHA1(9ec743d5988b5e3183f37f8edf45c72a8c0c893e) )
    MSLUG5_ESSENTIALPATCH_MVS_FILL
    MSLUG5_MVS_FILL
    MSLUG5_AES_FILL
    DEFAULT_BIOS_ASIA_(JAPAN_MVS)
	MS5PCB_SFIX_MT_128K
	MS5PCB_AUDIOBIOS_ENCRYPTED_512K
	MS5PCB_YMSND
	MS5PCB_SPRITES
ROM_END

ROM_START( ms4plus ) /* Metal Slug 4 bootleg */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "ms4p.p1", 0x000000, 0x100000, CRC(806a6e04) SHA1(df503772d607271ea51285154c9fd68e18b143ce) )
	ROM_LOAD16_WORD_SWAP( "263.p2",  0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
	MSPLUS4_SFIX_128K
	MSLUG4_AUDIO_ENCRYPTED_128K
	MSLUG4_YMSND
	MSLUG4_SPRITES
ROM_END

ROM_START( ms5plus ) /* Metal Slug 5 bootleg */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "ms5p.p1", 0x000000, 0x100000, CRC(106b276f) SHA1(0e840df95f3813145e5043573483c7610d2d3e68) )
	ROM_LOAD16_WORD_SWAP( "ms5p.p2", 0x100000, 0x200000, CRC(d6a458e8) SHA1(c0a8bdae06d62859fb6734766ccc190eb2a809a4) )
	ROM_LOAD16_WORD_SWAP( "ms5p.p3", 0x300000, 0x200000, CRC(439ec031) SHA1(f0ad8f9be7d26bc504593c1321bd23c286a221f0) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
	MS5PLUS_SFIX_128K
	MSLUG5_AUDIO_ENCRYPTED_512K
	MSLUG5_YMSND
	MSLUG5_SPRITES
ROM_END

ROM_START( mslug )
	ROM_REGION( 0xa00000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "201.p1", 0x100000, 0x100000, CRC(08d8daa5) SHA1(b888993dbb7e9f0a28a01d7d2e1da00ef9cf6f38) )
	ROM_CONTINUE( 0x000000, 0x100000 )
    MSLUG_ESSENTIALPATCH_MODS_FILL
    MSLUG_MVS_FILL
    MSLUG_AES_FILL
	MSLUG_SFIX_128K
	MSLUG_AUDIO_128K
	MSLUG_YMSND
	MSLUG_SPRITES
ROM_END

ROM_START( mslug2 ) /* MVS AND AES VERSION */
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241.p1", 0x000000, 0x100000, CRC(2a53c5da) SHA1(5a6aba482cac588a6c2c51179c95b487c6e11899) )
	ROM_LOAD16_WORD_SWAP( "241.p2", 0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
	MSLUG2_AES_FILL
	MSLUG2_SFIX_128K
	MSLUG2_AUDIO_128K
	MSLUG2_YMSND
	MSLUG2_SPRITES
ROM_END

ROM_START( mslug3 ) /* Original Version - Encrypted Code & GFX */ /* revision 2000.4.1 */ /* MVS VERSION */
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "neo-sma", 0x0c0000, 0x040000, CRC(9cd55736) SHA1(d6efb2b313127c2911d47d9324626b3f1e7c6ccb) )
	ROM_LOAD16_WORD_SWAP( "256.p1",  0x100000, 0x400000, CRC(b07edfd5) SHA1(dcbd9e500bfae98d754e55cdbbbbf9401013f8ee) )
	ROM_LOAD16_WORD_SWAP( "256.p2",  0x500000, 0x400000, CRC(6097c26b) SHA1(248ec29d21216f29dc6f5f3f0e1ad1601b3501b6) )
	MSLUG3_SFIX_MT_512K
	MSLUG3_AUDIO_512K
	MSLUG3_YMSND
	MSLUG3_SPRITES
ROM_END

/*Fixed by remikare*/
ROM_START( mslug3a ) /* Original Version - Encrypted Code & GFX */ /* MVS VERSION */
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "white.neo-sma", 0x0c0000, 0x040000, CRC(c60d29b2) SHA1(1647260ccbda833b35005608ef1fdc82fba02f04) ) /* stored in the custom SMA chip, the SMA has a white colour marking */
	ROM_LOAD16_WORD_SWAP( "256a.p1", 0x100000, 0x400000, CRC(a1177628) SHA1(4c4c379d9fc3a83265b7f32fbfce9d16b7d0f0fd) )
	ROM_LOAD16_WORD_SWAP( "256a.p2", 0x500000, 0x400000, CRC(9b659826) SHA1(d6bd03cf61879217922c18db4d3bd77095c0fe19) )
    MSLUG3_SFIX_MT_512K
	MSLUG3_AUDIO_512K
	MSLUG3_YMSND
	MSLUG3_SPRITES
ROM_END

ROM_START( mslug3h ) /* Original Version - Encrypted GFX */ /* revision 2000.3.17 */ /* AES VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256h.p1", 0x000000, 0x100000, CRC(9c42ca85) SHA1(7a8f77a89867b889295ae9b9dfd4ba28f02d234d) )
	ROM_LOAD16_WORD_SWAP( "256h.p2", 0x100000, 0x400000, CRC(1f3d8ce8) SHA1(08b05a8abfb86ec09a5e758d6273acf1489961f9) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
    MSLUG3_SFIX_MT_512K
	MSLUG3_AUDIO_512K
	MSLUG3_YMSND
	MSLUG3_SPRITES
ROM_END

ROM_START( mslug3b6 ) /* This "Metal Slug 6" is a hack/bootleg of Metal Slug 3, the real Metal Slug 6 is on Atomiswave Hardware */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "299.p1", 0x000000, 0x200000, CRC(5f2fe228) SHA1(747775a2dfc0da87ad2ddd4f57ce5b2522f23fa5) )
	ROM_LOAD16_WORD_SWAP( "299.p2", 0x100000, 0x400000, CRC(193fa835) SHA1(fb1f26db7998b0bb6b1c8b92500c1596ec5dfc71) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3B6_MVS_FILL
    MSLUG3H_AES_FILL
    MSLUG3B6_SFIX_128K
	MSLUG3_AUDIO_512K
	MSLUG3_YMSND
	MSLUG3_SPRITES
ROM_END

ROM_START( mslug4 ) /* Original Version - Encrypted GFX */ /* MVS VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263.p1", 0x000000, 0x100000, CRC(27e4def3) SHA1(a08785e8145981bb6b5332a3b2df7eb321253cca) )
	ROM_LOAD16_WORD_SWAP( "263.p2", 0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
	MSLUG4HD_SFIX_128K
	MSLUG4_AUDIO_ENCRYPTED_128K
	MSLUG4_YMSND
	MSLUG4_SPRITES
ROM_END

ROM_START( mslug4h ) /* Original Version - Encrypted GFX */ /* AES VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263h.p1", 0x000000, 0x100000, CRC(c67f5c8d) SHA1(12af74964843f103520d9f0825069ea2f67eeb2f) )
	ROM_LOAD16_WORD_SWAP( "263h.p2", 0x100000, 0x400000, CRC(bc3ec89e) SHA1(2cb0626bc4fa57e1d25f208e04532b570d87b3fb) )
    MSLUG4H_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4H_AES_FILL
	MSLUG4HD_SFIX_128K
	MSLUG4_AUDIO_ENCRYPTED_128K
	MSLUG4_YMSND
	MSLUG4_SPRITES
ROM_END

ROM_START( mslug5 ) /* Encrypted Set */ /* MVS VERSION */
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD32_WORD_SWAP( "268.p1", 0x000000, 0x400000, CRC(d0466792) SHA1(880819933d997fab398f91061e9dbccb959ae8a1) )
	ROM_LOAD32_WORD_SWAP( "268.p2", 0x000002, 0x400000, CRC(fbf6b61e) SHA1(9ec743d5988b5e3183f37f8edf45c72a8c0c893e) )
    MSLUG5_ESSENTIALPATCH_MVS_FILL
	MSLUG5_MVS_FILL
    MSLUG5_AES_FILL
	MSLUG5_SFIX_MT_128K
	MSLUG5_AUDIO_ENCRYPTED_512K
	MSLUG5_YMSND
	MSLUG5_SPRITES
ROM_END

ROM_START( mslug5h ) /* Encrypted Set */ /* AES release of the game but is also found in later MVS carts */
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD32_WORD_SWAP( "268h.p1", 0x000000, 0x400000, CRC(3636690a) SHA1(e0da714b4bdc6efffe1250ded02ebddb3ab6d7b3) )
	ROM_LOAD32_WORD_SWAP( "268h.p2", 0x000002, 0x400000, CRC(8dfc47a2) SHA1(27d618cfbd0107a4d2a836797e967b39d2eb4851) )
    MSLUG5_ESSENTIALPATCH_MVS_FILL
    MSLUG5_MVS_FILL
    MSLUG5H_AES_FILL
	MSLUG5_SFIX_MT_128K
	MSLUG5_AUDIO_ENCRYPTED_512K
	MSLUG5_YMSND
	MSLUG5_SPRITES
ROM_END

/*Fixed by remikare*/
ROM_START( mslug5b )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268b.p1", 0x000000, 0x100000, CRC(1376f43c) SHA1(7ca4a8b11c7effda2603d04e793cf664e7aa39bf) )
	ROM_LOAD16_WORD_SWAP( "268b.p2", 0x100000, 0x400000, CRC(4becfba0) SHA1(fd3708f6c8fa26133b29b4b033148dff54dc1e7d) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5B_SFIX_MT_128K
    MSLUG5B_AUDIO_128K
    MSLUG5B_YMSND
    MSLUG5B_SPRITES
ROM_END

ROM_START( mslugx ) /* MVS AND AES VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250.p1", 0x000000, 0x100000, CRC(81f1f60b) SHA1(4c19f2e9824e606178ac1c9d4b0516fbaa625035) )
	ROM_LOAD16_WORD_SWAP( "250.p2", 0x100000, 0x400000, CRC(1fda2e12) SHA1(18aaa7a3ba8da99f78c430e9be69ccde04bc04d9) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
	MSLUGX_SFIX_128K
	MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

 /******************************************************************************************************************************
  The prototype roms that had been published by the Neoragex emulator are included, in the NeoGeo system that presented some 
   copyrighted roms in that period of the year "1999-2000-2002-2003" that could not be legally emulated, they were Looked for 
   an alternate means to be able to play this roms by making an encrypted file.
***********************************************************************************************************************************/

ROM_START( ms4plusp )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "ms4pp.p1", 0x000000, 0x100000, CRC(ce15b634) SHA1(d4d73a1d464c472fc0961f6e62b21f52c19a3ba5) )
	ROM_LOAD16_WORD_SWAP( "263.p2",   0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSPLUS4_SFIX_128K
    MSLUG4ND_AUDIO_128K
    MS4BOOT_YMSND
	MSLUG4D_SPRITES
ROM_END

ROM_START( ms5plusp )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "ms5pp.p1", 0x000000, 0x100000, CRC(65639fcc) SHA1(4317c62e2e2548c8d83a9f3fcfe61921b36124a7) )
	ROM_LOAD16_WORD_SWAP( "ms5pp.p2", 0x100000, 0x400000, CRC(38b7a73a) SHA1(b0588a14ed99bbd930c3130b86625b3bbcdf6645) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MS5PLUSD_SFIX_128K
    MS5PLUSD_AUDIO_512K
    MS5PCBD_YMSND
    MS5PCBD_SPRITES
ROM_END

ROM_START( mslug3b6p )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "299p.p1", 0x000000, 0x100000, CRC(1f1079a2) SHA1(5d99358f0e513e2087c7594bab09c8d33db40f1f) )
	ROM_LOAD16_WORD_SWAP( "299.p2",  0x100000, 0x400000, CRC(193fa835) SHA1(fb1f26db7998b0bb6b1c8b92500c1596ec5dfc71) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3B6_MVS_FILL
    MSLUG3H_AES_FILL
    MSLUG3B6P_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3P_YMSND
	MSLUG3D_SPRITES
ROM_END

ROM_START( mslug4p )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263.p1", 0x000000, 0x100000, CRC(27e4def3) SHA1(a08785e8145981bb6b5332a3b2df7eb321253cca) )
	ROM_LOAD16_WORD_SWAP( "263.p2", 0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
    MSLUG4P_AUDIO_ENCRYPTED_64K
    MSLUG4P_YMSND
    MSLUG4P_SPRITES
ROM_END

ROM_START( mslug4hp )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263h.p1", 0x000000, 0x100000, CRC(c67f5c8d) SHA1(12af74964843f103520d9f0825069ea2f67eeb2f) )
	ROM_LOAD16_WORD_SWAP( "263h.p2", 0x100000, 0x400000, CRC(bc3ec89e) SHA1(2cb0626bc4fa57e1d25f208e04532b570d87b3fb) )
    MSLUG4H_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4H_AES_FILL
    MSLUG4HD_SFIX_128K
    MSLUG4P_AUDIO_ENCRYPTED_64K
    MSLUG4P_YMSND
    MSLUG4P_SPRITES
ROM_END

ROM_START( mslug4ndp )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263ndp.p1", 0x000000, 0x100000, CRC(249c1411) SHA1(47ff05641bb97c706e67cf58e36d857540ff5afd) )
	ROM_LOAD16_WORD_SWAP( "263.p2",    0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4NDP_SFIX_128K
    MSLUG4NDP_AUDIO_128K
    MSLUG4NDP_YMSND
    MSLUG4NDP_SPRITES
ROM_END

ROM_START( mslug5p )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD32_WORD_SWAP( "268.p1", 0x000000, 0x400000, CRC(d0466792) SHA1(880819933d997fab398f91061e9dbccb959ae8a1) )
	ROM_LOAD32_WORD_SWAP( "268.p2", 0x000002, 0x400000, CRC(fbf6b61e) SHA1(9ec743d5988b5e3183f37f8edf45c72a8c0c893e) )
    MSLUG5_ESSENTIALPATCH_MVS_FILL
    MSLUG5_MVS_FILL
    MSLUG5_AES_FILL
    MSLUG5_SFIX_MT_128K
	MSLUG5P_AUDIO_256K
    MSLUG5P_YMSND
    MSLUG5P_SPRITES
ROM_END

ROM_START( mslug5hp )
	ROM_REGION( 0xc00000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268hp.p1", 0x000000, 0x400000, CRC(5d1a8668) SHA1(bd35cb1e772e9406da1eda2daf0ed4782eb98dea) )
	ROM_LOAD16_WORD_SWAP( "268hp.p2", 0x400000, 0x400000, CRC(47662c5e) SHA1(68d055343e26d13f39dbc241d91f863364b04eaa) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MS5PLUSD_AUDIO_512K
    MS5PCBD_YMSND
    MS5PCBD_SPRITES
ROM_END

/*Fixed by remikare*/
ROM_START( mslug5np )
    ROM_REGION( 0x600000, "maincpu", 0 )
    ROM_LOAD16_WORD_SWAP( "268boot.p1", 0x000000, 0x100000, CRC(e6d297af) SHA1(5bb3f72ce26e3f46c523b955f425056eb246e855) )
    ROM_LOAD16_WORD_SWAP( "268np.p2",   0x200000, 0x100000, CRC(84def63e) SHA1(fddd68e8879d6f5c1aac42997ff2245ea54d5869) )
    ROM_CONTINUE( 0x400000, 0x100000 )
    ROM_CONTINUE( 0x300000, 0x100000 )
    ROM_CONTINUE( 0x500000, 0x100000 )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5D_AUDIO_64K
    MSLUG5N_YMSND
    MSLUG5D_SPRITES
ROM_END

ROM_START( mslug5ndp )
	ROM_REGION( 0x800000, "maincpu", 0 )
    ROM_LOAD16_WORD_SWAP( "268ndp.p1",  0x000000, 0x200000, CRC(f23968bf) SHA1(ed4caee7caf1b2b06a5a0c76f48952d883ae6922) )
    ROM_LOAD16_WORD_SWAP( "268n.p2",    0x200000, 0x400000, CRC(768ee64a) SHA1(76a65a69aee749758a2101aabdd44f3404838b54) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
	MSLUG5_SFIX_MT_128K
    MSLUG5NDP_AUDIO_256K
	MSLUG5NDP_YMSND
	MSLUG5D_SPRITES
ROM_END

ROM_START( mslugxp )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250p.p1", 0x000000, 0x100000, CRC(60c33b1a) SHA1(8999bfc42b233cdb58778857c87d9f3187c61025) )
	ROM_LOAD16_WORD_SWAP( "250.p2",  0x100000, 0x400000, CRC(1fda2e12) SHA1(18aaa7a3ba8da99f78c430e9be69ccde04bc04d9) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGXP_SPRITES
ROM_END

/********************************
 Decrypter, Earlier And Bootleg
**********************************/

ROM_START( msboot )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "201.p1", 0x100000, 0x100000, CRC(08d8daa5) SHA1(b888993dbb7e9f0a28a01d7d2e1da00ef9cf6f38) )
	ROM_CONTINUE( 0x000000, 0x100000 )
    MSLUG_ESSENTIALPATCH_MODS_FILL
    MSLUG_MVS_FILL
    MSLUG_AES_FILL
	MSLUG_SFIX_128K
	MSLUG_AUDIO_128K
    MSLUGB_YMSND
    MSLUG_SPRITES
ROM_END

ROM_START( ms4boot )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263nd.p1", 0x000000, 0x100000, CRC(4d7e6624) SHA1(125d5203e89cce23a851fa74cc8cbe003ef978f3) )
	ROM_LOAD16_WORD_SWAP( "263.p2",   0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
	MSLUG4ND_AUDIO_128K
	MS4BOOT_YMSND
	MSLUG4ND_SPRITES
ROM_END

/*Fixed by remikare*/
ROM_START( ms5boot )
    ROM_REGION( 0x600000, "maincpu", 0 )
    ROM_LOAD16_WORD_SWAP( "268boot.p1", 0x000000, 0x100000, CRC(e6d297af) SHA1(5bb3f72ce26e3f46c523b955f425056eb246e855) )
    ROM_LOAD16_WORD_SWAP( "268boot.p2", 0x200000, 0x100000, CRC(3fc46cfa) SHA1(f20d3d359f6cdbf6aabb6920020621b02bafee91) )
    ROM_CONTINUE(0x400000, 0x100000 )
    ROM_LOAD16_WORD_SWAP( "268boot.p3", 0x300000, 0x100000, CRC(742c955a) SHA1(96c0f08b1f2f6877f5169a96c13b67f3be6082c6) )
    ROM_CONTINUE(0x500000, 0x100000 )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MS5BOOT_SFIX_128K
    MS5BOOT_AUDIO_128K
    MS5BOOT_YMSND
    MS5BOOT_SPRITES
ROM_END

ROM_START( ms5pcbd )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD32_WORD_SWAP( "268.p1", 0x000000, 0x400000, CRC(d0466792) SHA1(880819933d997fab398f91061e9dbccb959ae8a1) )
	ROM_LOAD32_WORD_SWAP( "268.p2", 0x000002, 0x400000, CRC(fbf6b61e) SHA1(9ec743d5988b5e3183f37f8edf45c72a8c0c893e) )
    MSLUG5_ESSENTIALPATCH_MVS_FILL
    MSLUG5_MVS_FILL
    MSLUG5_AES_FILL
    DEFAULT_BIOS_ASIA_(JAPAN_MVS)
	MS5PCBD_SFIX_MT_512K
    MS5PCB_AUDIOBIOS_ENCRYPTED_512K
	MS5PCBD_YMSND
	MS5PCBD_SPRITES
ROM_END

ROM_START( ms4plusd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "ms4p.p1", 0x000000, 0x100000, CRC(806a6e04) SHA1(df503772d607271ea51285154c9fd68e18b143ce) )
	ROM_LOAD16_WORD_SWAP( "263.p2",  0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSPLUS4_SFIX_128K
	MSLUG4_AUDIO_ENCRYPTED_128K
	MSLUG4_YMSND
	MSLUG4D_SPRITES
ROM_END

ROM_START( ms5plusd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "ms5pd.p1", 0x000000, 0x100000, CRC(76af334f) SHA1(cbd890a9c14d42acd1923bb5074fb560a306cce3) )
	ROM_LOAD16_WORD_SWAP( "ms5p.p2",  0x100000, 0x200000, CRC(d6a458e8) SHA1(c0a8bdae06d62859fb6734766ccc190eb2a809a4) )
	ROM_LOAD16_WORD_SWAP( "ms5p.p3",  0x300000, 0x200000, CRC(439ec031) SHA1(f0ad8f9be7d26bc504593c1321bd23c286a221f0) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MS5PLUSD_SFIX_128K
    MS5PLUSD_AUDIO_512K
	MS5PLUSD_YMSND
	MSLUG5HD_SPRITES
ROM_END

ROM_START( ms5plusc )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "ms5pc.p1", 0x000000, 0x100000, CRC(c61e6444) SHA1(9aec69201472080d2205af14ecc3f9a30ab4c6c2) )
	ROM_LOAD16_WORD_SWAP( "ms5p.p2",  0x100000, 0x200000, CRC(d6a458e8) SHA1(c0a8bdae06d62859fb6734766ccc190eb2a809a4) )
	ROM_LOAD16_WORD_SWAP( "ms5p.p3",  0x300000, 0x200000, CRC(439ec031) SHA1(f0ad8f9be7d26bc504593c1321bd23c286a221f0) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MS5PLUSD_SFIX_128K
    MS5PLUSD_AUDIO_512K
	MS5PLUSD_YMSND
	MSLUG5HD_SPRITES
ROM_END

ROM_START( msluge )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "201.p1", 0x100000, 0x100000, CRC(08d8daa5) SHA1(b888993dbb7e9f0a28a01d7d2e1da00ef9cf6f38) )
	ROM_CONTINUE( 0x000000, 0x100000 )
    MSLUG_ESSENTIALPATCH_MODS_FILL
    MSLUG_MVS_FILL
    MSLUG_AES_FILL
	MSLUG_SFIX_128K
	MSLUG_AUDIO_128K
    MSLUG_YMSND
    MSLUGE_SPRITES
ROM_END

ROM_START( mslug2t )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241t.p1", 0x000000, 0x100000, CRC(df5d6fbc) SHA1(b9cc3e29afc12dc98daac9afb4f94e2cdd8b455c) )
	ROM_LOAD16_WORD_SWAP( "241.p2",  0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
    MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug3d )
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "neo-sma", 0x0c0000, 0x040000, CRC(9cd55736) SHA1(d6efb2b313127c2911d47d9324626b3f1e7c6ccb) )
	ROM_LOAD16_WORD_SWAP( "256.p1",  0x100000, 0x400000, CRC(b07edfd5) SHA1(dcbd9e500bfae98d754e55cdbbbbf9401013f8ee) )
	ROM_LOAD16_WORD_SWAP( "256.p2",  0x500000, 0x400000, CRC(6097c26b) SHA1(248ec29d21216f29dc6f5f3f0e1ad1601b3501b6) )
	MSLUG3_SFIX_MT_512K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3D_SPRITES
ROM_END

ROM_START( mslug3hd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256h.p1", 0x000000, 0x100000, CRC(9c42ca85) SHA1(7a8f77a89867b889295ae9b9dfd4ba28f02d234d) )
	ROM_LOAD16_WORD_SWAP( "256h.p2", 0x100000, 0x400000, CRC(1f3d8ce8) SHA1(08b05a8abfb86ec09a5e758d6273acf1489961f9) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3D_SPRITES
ROM_END

ROM_START( mslug3nd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256nd.p1", 0x000000, 0x100000, CRC(c871c036) SHA1(4d1cca29dc27300d52739bee183fa4edf3d36afd) )
	ROM_LOAD16_WORD_SWAP( "256h.p2",  0x100000, 0x400000, CRC(1f3d8ce8) SHA1(08b05a8abfb86ec09a5e758d6273acf1489961f9) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
    MSLUG3ND_SFIX_512K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3D_SPRITES
ROM_END

ROM_START( mslug3b6d )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "299.p1", 0x000000, 0x200000, CRC(5f2fe228) SHA1(747775a2dfc0da87ad2ddd4f57ce5b2522f23fa5) )
	ROM_LOAD16_WORD_SWAP( "299.p2", 0x100000, 0x400000, CRC(193fa835) SHA1(fb1f26db7998b0bb6b1c8b92500c1596ec5dfc71) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3B6_MVS_FILL
    MSLUG3H_AES_FILL
    MSLUG3B6_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3D_SPRITES
ROM_END

ROM_START( mslug4d )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263.p1", 0x000000, 0x100000, CRC(27e4def3) SHA1(a08785e8145981bb6b5332a3b2df7eb321253cca) )
	ROM_LOAD16_WORD_SWAP( "263.p2", 0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
    MSLUG4D_AUDIO_64K
    MSLUG4_YMSND
	MSLUG4D_SPRITES
ROM_END

ROM_START( mslug4hd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263h.p1", 0x000000, 0x100000, CRC(c67f5c8d) SHA1(12af74964843f103520d9f0825069ea2f67eeb2f) )
	ROM_LOAD16_WORD_SWAP( "263h.p2", 0x100000, 0x400000, CRC(bc3ec89e) SHA1(2cb0626bc4fa57e1d25f208e04532b570d87b3fb) )
    MSLUG4H_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4H_AES_FILL
    MSLUG4HD_SFIX_128K
	MSLUG4_AUDIO_ENCRYPTED_128K
    MSLUG4_YMSND
	MSLUG4HD_SPRITES
ROM_END

ROM_START( mslug4nd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263nd.p1", 0x000000, 0x100000, CRC(4d7e6624) SHA1(125d5203e89cce23a851fa74cc8cbe003ef978f3) )
	ROM_LOAD16_WORD_SWAP( "263.p2",   0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
	MSLUG4ND_AUDIO_128K
	MSLUG4ND_YMSND
	MSLUG4ND_SPRITES
ROM_END

ROM_START( mslug5d )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD32_WORD_SWAP( "268.p1", 0x000000, 0x400000, CRC(d0466792) SHA1(880819933d997fab398f91061e9dbccb959ae8a1) )
	ROM_LOAD32_WORD_SWAP( "268.p2", 0x000002, 0x400000, CRC(fbf6b61e) SHA1(9ec743d5988b5e3183f37f8edf45c72a8c0c893e) )
    MSLUG5_ESSENTIALPATCH_MVS_FILL
    MSLUG5_MVS_FILL
    MSLUG5_AES_FILL
    MSLUG5_SFIX_MT_128K
	MSLUG5_AUDIO_ENCRYPTED_512K
	MSLUG5_YMSND
	MSLUG5HD_SPRITES
ROM_END

ROM_START( mslug5hd )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD32_WORD_SWAP( "268h.p1", 0x000000, 0x400000, CRC(3636690a) SHA1(e0da714b4bdc6efffe1250ded02ebddb3ab6d7b3) )
	ROM_LOAD32_WORD_SWAP( "268h.p2", 0x000002, 0x400000, CRC(8dfc47a2) SHA1(27d618cfbd0107a4d2a836797e967b39d2eb4851) )
    MSLUG5_ESSENTIALPATCH_MVS_FILL
    MSLUG5_MVS_FILL
    MSLUG5H_AES_FILL
    MSLUG5_SFIX_MT_128K
	MSLUG5_AUDIO_ENCRYPTED_512K
	MSLUG5_YMSND
	MSLUG5HD_SPRITES
ROM_END

ROM_START( mslug5n )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268n.p1", 0x000000, 0x100000, CRC(ca50afdf) SHA1(e3780b77f20d139a0dcaa2ded2c6ee323b8b4279) )
	ROM_LOAD16_WORD_SWAP( "268n.p2", 0x100000, 0x400000, CRC(768ee64a) SHA1(76a65a69aee749758a2101aabdd44f3404838b54) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5_SFIX_MT_128K
	MSLUG5N_AUDIO_512K
	MSLUG5N_YMSND
	MS5BOOT_SPRITES
ROM_END

ROM_START( mslug5nd )
	ROM_REGION( 0x800000, "maincpu", 0 )
    ROM_LOAD16_WORD_SWAP( "268nd.p1", 0x000000, 0x600000, CRC(975eb06a) SHA1(d3d4824a0b9f077c6503959da54edb53820e6a8d) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
	MSLUG5_SFIX_MT_128K
    MSLUG5ND_AUDIO_128K
	MSLUG5_YMSND
	MSLUG5D_SPRITES
ROM_END

ROM_START( mslug5b1 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268b1.p1", 0x000000, 0x100000, CRC(d05853ea) SHA1(8bb284d8f937b1b50d28d207f5fd262e4ed1d96c) )
	ROM_CONTINUE( 0x200000, 0x100000 )
	ROM_CONTINUE( 0x400000, 0x100000 )
	ROM_CONTINUE( 0x300000, 0x100000 )
	ROM_CONTINUE( 0x500000, 0x100000 )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5_SFIX_MT_128K
	MSLUG5_AUDIO_ENCRYPTED_512K
	MSLUG5_YMSND
	MSLUG5_SPRITES
ROM_END

 /* Decrypt -> Encrypt P Roms Mslug5 */
ROM_START( mslug5b2 )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268b2.p1", 0x000000, 0x100000, CRC(3f1cf3d2) SHA1(2c85eb5acdede4816675b91f8989c9e13c1573f8) )
	ROM_CONTINUE( 0x200000, 0x100000 )
	ROM_CONTINUE( 0x400000, 0x100000 )
	ROM_CONTINUE( 0x300000, 0x100000 )
	ROM_CONTINUE( 0x500000, 0x100000 )
	ROM_CONTINUE( 0x100000, 0x100000 )
	ROM_CONTINUE( 0x600000, 0x200000 )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL 
    MSLUG5_SFIX_MT_128K
    MSLUG5_AUDIO_ENCRYPTED_512K
	MSLUG5_YMSND
	MSLUG5_SPRITES
ROM_END

 /****************************
  Darksoft Neo Geo Decrypter
*******************************/

/* Fixed by remikare */
ROM_START( ms4plusdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "ms4pdd.p1", 0x000000, 0x500000, CRC(474fa26d) SHA1(1a59429df71c85610d4656ef88ca490b7d2fe907) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
	MSPLUS4_SFIX_128K
	MSLUG4ND_AUDIO_128K
	MSLUG4DX_YMSND
    MSLUG4DX_SPRITES
ROM_END

/* Fixed by remikare */
ROM_START( ms5plusdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "ms5pdd.p1", 0x000000, 0x500000, CRC(85afbc9f) SHA1(269c17c14f89586e68848fc1731452de1ad790cb) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MS5PLUSD_SFIX_128K
    MS5PLUSD_AUDIO_512K
    MS5PCBD_YMSND
    MSLUG5DX_SPRITES
ROM_END

/* Fixed by remikare */
ROM_START( mslugdd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "201dd.p1", 0x000000, 0x200000, CRC(4952089b) SHA1(411d5560f4f4c13862edf72ee42cc5f3ce083778) )
    MSLUG_ESSENTIALPATCH_MODS_FILL
    MSLUG_MVS_FILL
    MSLUG_AES_FILL
	MSLUG_SFIX_128K
	MSLUG_AUDIO_128K
    MSLUGDX_YMSND
    MSLUGDX_SPRITES
ROM_END

/* Fixed by remikare */
ROM_START( mslug2dd )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241dd.p1", 0x000000, 0x300000, CRC(5e8c6aa0) SHA1(322e503e8323e8516861b58270311ac853104408) )
    MSLUG2_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
	MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2DX_YMSND
    MSLUG2DX_SPRITES
ROM_END

/* Fixed by remikare */
ROM_START( mslug2tdd )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241tdd.p1", 0x000000, 0x300000, CRC(90e900fb) SHA1(8c56fc19b73007d2c459b173b0f3709a9e0c529a) )
    MSLUG2_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
	MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2DX_YMSND
    MSLUG2DX_SPRITES
ROM_END

/* Fixed by remikare */
ROM_START( mslug3dd )
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256dd.p1", 0x000000, 0x900000, CRC(d015d8ad) SHA1(5e1faaef3da621d579eabc9172f1e03cba56a67d) )
    MSLUG3DD_ESSENTIALPATCH_MODS_FILL
	MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3ND_SFIX_512K
	MSLUG3_AUDIO_512K
    MSLUG3DX_YMSND
	MSLUG3DX_SPRITES
ROM_END

/* Fixed by remikare */
ROM_START( mslug3b6dd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "299dd.p1", 0x000000, 0x500000, CRC(dce39f91) SHA1(93b30050caae55bc0ee3ca5c0ad457383173d543) )
	MSLUG3H_ESSENTIALPATCH_MODS_FILL
	MSLUG3B6_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3B6P_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3DX_YMSND
	MSLUG3DX_SPRITES
ROM_END

/* Fixed by remikare */
ROM_START( mslug4dd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263dd.p1", 0x000000, 0x500000, CRC(c6dbdff1) SHA1(35f72712147cfa5bcfc39c3f5d8cb570757daa6b) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4DD_MVS_FILL
    MSLUG4_AES_FILL
	MSLUG4DX_SFIX_512K
	MSLUG4ND_AUDIO_128K
	MSLUG4DX_YMSND
    MSLUG4DX_SPRITES
ROM_END

/* Fixed by remikare */
ROM_START( mslug4hdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263hdd.p1", 0x000000, 0x500000, CRC(9dd8a0bd) SHA1(2330bca1d871ab4bd14e42c78f6cd2984eba63fa) )
    MSLUG4H_ESSENTIALPATCH_MODS_FILL
    MSLUG4DD_MVS_FILL
    MSLUG4H_AES_FILL
	MSLUG4DX_SFIX_512K
	MSLUG4ND_AUDIO_128K
	MSLUG4DX_YMSND
    MSLUG4DX_SPRITES
ROM_END

/* Fixed by remikare */
ROM_START( mslug5dd )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268dd.p1", 0x000000, 0x800000, CRC(3b0c2e7d) SHA1(7cacf8ad33c6bd3d73edd0364d57b3b0fd5b067f) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
	MS5PLUSD_AUDIO_512K
	MS5PCBD_YMSND
	MSLUG5DX_SPRITES
ROM_END

/* Fixed by remikare */
ROM_START( mslug5hdd )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268hdd.p1", 0x000000, 0x800000, CRC(5b57f81d) SHA1(9fb76ff39df11db5525e38cef9cfe617d553d0b6) )
    MSLUG5HDD_ESSENTIALPATCH_MVS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HDD_AES_FILL
    MSLUG5D_SFIX_128K
	MS5PLUSD_AUDIO_512K
	MS5PCBD_YMSND
	MSLUG5DX_SPRITES
ROM_END

/* Fixed by remikare */
ROM_START( mslugxdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250dd.p1", 0x000000, 0x500000, CRC(616ddfed) SHA1(1836af65f3505d753ab5b552d13fed2a932a9fbf) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGXDX_YMSND
	MSLUGXDX_SPRITES
ROM_END

 /******
  Hack
*********/

ROM_START( mslughc01 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "201_hc01.p1", 0x100000, 0x100000, CRC(61e1ba6e) SHA1(aafc5b39a61d330b95f29c663900fbc02b01bd1d) )
	ROM_CONTINUE( 0x000000, 0x100000 )
    MSLUG_ESSENTIALPATCH_MODS_FILL
    MSLUG_MVS_FILL
    MSLUG_AES_FILL
	MSLUG_SFIX_128K
	MSLUG_AUDIO_128K
    MSLUG_YMSND
    MSLUG_SPRITES
ROM_END

ROM_START( mslughc02 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "201_hc02.p1", 0x100000, 0x100000, CRC(09888e87) SHA1(d61adb16503c30b3290ea41b3955607b7ebba70f) )
	ROM_CONTINUE( 0x000000, 0x100000 )
    MSLUG_ESSENTIALPATCH_MODS_FILL
    MSLUG_MVS_FILL
    MSLUG_AES_FILL
	MSLUG_SFIX_128K
	MSLUG_AUDIO_128K
    MSLUG_YMSND
    MSLUG_SPRITES
ROM_END

ROM_START( mslughc03 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "201_hc03.p1", 0x100000, 0x100000, CRC(2b3d433f) SHA1(94a1a88bff5f1b6bdf8d8a0406004982ef9d7b0c) )
	ROM_CONTINUE( 0x000000, 0x100000 )
    MSLUG_ESSENTIALPATCH_MODS_FILL
    MSLUG_MVS_FILL
    MSLUG_AES_FILL
	MSLUG_SFIX_128K
	MSLUG_AUDIO_128K
    MSLUG_YMSND
    MSLUG_SPRITES
ROM_END

ROM_START( mslughc04 ) //mslugdg
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "201_hc04.p1", 0x100000, 0x100000, CRC(0a739521) SHA1(74e637a6a77140f8ce1128cb8f456ecae0a7a7ef) )
	ROM_CONTINUE( 0x000000, 0x100000 )
    MSLUG_ESSENTIALPATCH_MODS_FILL
    MSLUG_MVS_FILL
    MSLUG_AES_FILL
	MSLUG_SFIX_128K
	MSLUG_AUDIO_128K
    MSLUG_YMSND
    MSLUG_SPRITES
ROM_END

ROM_START( mslughc05 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "201_hc05.p1", 0x100000, 0x100000, CRC(582b4d77) SHA1(9de833c621d3b26153e3b22c86d6137beb58e5e4) )
	ROM_CONTINUE( 0x000000, 0x100000 )
    MSLUG_ESSENTIALPATCH_MODS_FILL
    MSLUG_MVS_FILL
    MSLUG_AES_FILL
	MSLUG_SFIX_128K
	MSLUG_AUDIO_128K
    MSLUG_YMSND
    MSLUG_SPRITES
ROM_END

ROM_START( mslughc06 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "201_hc06.p1", 0x100000, 0x100000, CRC(4d6af5bd) SHA1(2c8d782dba605d9148d8e519c803be2f14145642) )
	ROM_CONTINUE( 0x000000, 0x100000 )
    MSLUG_ESSENTIALPATCH_MODS_FILL
    MSLUG_MVS_FILL
    MSLUG_AES_FILL
	MSLUG_SFIX_128K
	MSLUG_AUDIO_128K
    MSLUG_YMSND
    MSLUG_SPRITES
ROM_END

ROM_START( mslughc07 ) //mslugunity
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "201_hc07.p1", 0x100000, 0x100000, CRC(a3186dfd) SHA1(9241e8bf40b878f2372d8da9f008c8895a87394b) )
	ROM_CONTINUE( 0x000000, 0x100000 )
    MSLUG_ESSENTIALPATCH_MODS_FILL
    MSLUG_MVS_FILL
    MSLUG_AES_FILL
	MSLUG_SFIX_128K
	MSLUG_AUDIO_128K
    MSLUG_YMSND
    MSLUG_SPRITES
ROM_END

ROM_START( mslughc08 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "201_hc08.p1", 0x100000, 0x100000, CRC(47ae2445) SHA1(615aeb5ed8f7e0197ed599b3f20eaed88ab1086d) )
	ROM_CONTINUE( 0x000000, 0x100000 )
    MSLUG_ESSENTIALPATCH_MODS_FILL
    MSLUG_MVS_FILL
    MSLUG_AES_FILL
	MSLUG_SFIX_128K
	MSLUG_AUDIO_128K
    MSLUG_YMSND
    MSLUG_SPRITES
ROM_END

ROM_START( mslughc09 ) //mslug1v2
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "201_hc09.p1", 0x100000, 0x100000, CRC(45822261) SHA1(65985bc4033987d7443242c43bbab009b828c09b) )
	ROM_CONTINUE( 0x000000, 0x100000 )
    MSLUG_ESSENTIALPATCH_MODS_FILL
    MSLUG_MVS_FILL
    MSLUG_AES_FILL
	MSLUG_SFIX_128K
	MSLUG_AUDIO_128K
    MSLUG_YMSND
    MSLUG_SPRITES
ROM_END

ROM_START( mslughc10 ) //mslugdqy
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "201_hc10.p1", 0x100000, 0x100000, CRC(1226d6b8) SHA1(8710a737e13c5537bc9e12766eb533205be14a82) )
	ROM_CONTINUE( 0x000000, 0x100000 )
    MSLUG_ESSENTIALPATCH_MODS_FILL
    MSLUG_MVS_FILL
    MSLUG_AES_FILL
	MSLUG_SFIX_128K
	MSLUG_AUDIO_128K
    MSLUG_YMSND
    MSLUG_SPRITES
ROM_END

ROM_START( mslughc11 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "201_hc11.p1", 0x100000, 0x100000, CRC(2750fe1b) SHA1(0de9e1cf728cdf21fb6ed243637576644e786fc8) )
	ROM_CONTINUE( 0x000000, 0x100000 )
    MSLUG_ESSENTIALPATCH_MODS_FILL
    MSLUG_MVS_FILL
    MSLUG_AES_FILL
	MSLUG_SFIX_128K
	MSLUG_AUDIO_128K
    MSLUG_YMSND
    MSLUG_SPRITES
ROM_END

ROM_START( mslughc12 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "201_hc12.p1", 0x100000, 0x100000, CRC(4b1e3452) SHA1(c117dcf66e2ed1ad57efae54b6b5cdeba7178278) )
	ROM_CONTINUE( 0x000000, 0x100000 )
    MSLUG_ESSENTIALPATCH_MODS_FILL
    MSLUG_MVS_FILL
    MSLUG_AES_FILL
	MSLUG_SFIX_128K
	MSLUG_AUDIO_128K
    MSLUG_YMSND
    MSLUG_SPRITES
ROM_END

/*************
 Metal Slug 2
***************/

ROM_START( mslug2hc01 ) //mslug2r
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hc01.p1", 0x000000, 0x100000, CRC(f882d50d) SHA1(77fa3169a5631de0a89ef3170bfbe2b45294e8cf) )
	ROM_LOAD16_WORD_SWAP( "241.p2",      0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2T_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
	MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hc02 ) //mslug21v2
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hc02.p1", 0x000000, 0x100000, CRC(c3efed6c) SHA1(ae11a5abf75548271bf26acb645e8b0e5fc22eaa) )
	ROM_LOAD16_WORD_SWAP( "241.p2",      0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2T_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
	MSLUG2_AES_FILL
	MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hc03 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hc03.p1", 0x000000, 0x100000, CRC(f680d167) SHA1(ebeed513de07928679ac4083fd705af51e21078d) )
	ROM_LOAD16_WORD_SWAP( "241.p2",      0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2T_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
	MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hc04 ) //mslug2sh
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hc04.p1", 0x000000, 0x100000, CRC(4c1a2f2c) SHA1(5e6b411187bce616066507a86b415ff69b8e9cf3) )
	ROM_LOAD16_WORD_SWAP( "241.p2",      0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2T_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
	MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

/* It is very conflictive to impose a modification to this roms hack, since there are usually crashes for all of them, the Address Error codes vary */
ROM_START( mslug2hc05 ) //mslug2eg
	ROM_REGION( 0x400000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hc05.p1", 0x000000, 0x100000, CRC(bb312904) SHA1(08766b1ffb8686aa4d07370dc825c9f09a100fa6) )
	ROM_LOAD16_WORD_SWAP( "241_hc05.p2", 0x100000, 0x300000, CRC(abf37360) SHA1(09347f0502fba4965dc14fd6db89bb3cabdeea1f) )
//  MSLUG2_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
	MSLUG2_AES_FILL
    MSLUG2EG_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2EG_SPRITES
ROM_END

ROM_START( mslug2hc06 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hc06.p1", 0x000000, 0x100000, CRC(c2fa15f2) SHA1(564b35c96daa8ebb44f2a5bafa73f218b120f5c3) )
	ROM_LOAD16_WORD_SWAP( "241.p2",      0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2T_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
	MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hc07 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hc07.p1", 0x000000, 0x100000, CRC(7080ed64) SHA1(f028273a636f3d82481cbb5325657acf59c3b455) )
	ROM_LOAD16_WORD_SWAP( "241.p2",      0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2T_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
	MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hc08 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hc08.p1", 0x000000, 0x100000, CRC(6d309ec1) SHA1(a9554d41f8d5bd96530ca441e5b68a3fa1ecb2c8) )
	ROM_LOAD16_WORD_SWAP( "241.p2",      0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2T_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
	MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hc09 ) //mslug2dg
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hc09.p1", 0x000000, 0x100000, CRC(00c455e7) SHA1(8a20c06a5f92032c0dc1ebd1e8a2709abd725330) )
	ROM_LOAD16_WORD_SWAP( "241_hc09.p2", 0x100000, 0x200000, CRC(1bf6b12a) SHA1(bdf1cee93c7cf1e57f61797ed4f176fe2a6ebf73) )
    MSLUG2T_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
	MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hc10 ) //mslug2ct
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hc10.p1", 0x000000, 0x100000, CRC(78ad6864) SHA1(d84b0b3fc5991d2ab9d04712d4df3b4318e65923) )
	ROM_LOAD16_WORD_SWAP( "241_hc10.p2", 0x100000, 0x200000, CRC(fe36f353) SHA1(61df20c7cd9f904552ec672dec11b679122bc5fe) )
    MSLUG2T_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
	MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hc11 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hc11.p1", 0x000000, 0x100000, CRC(fe803784) SHA1(1966f8c896d564570cceb108617021849a418484) )
	ROM_LOAD16_WORD_SWAP( "241.p2",  0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2T_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
    MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hc12 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hc12.p1", 0x000000, 0x100000, CRC(34233c1f) SHA1(eb137f71bbbdd06672cbb761bc37d39bc06d3d86) )
	ROM_LOAD16_WORD_SWAP( "241.p2",      0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2T_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
    MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hc13 ) //mslug2unity
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hc13.p1", 0x000000, 0x100000, CRC(1562cf23) SHA1(dfa2d7ea10f9eac6cd3b1a7a2f2c2f867edc28d1) )
	ROM_LOAD16_WORD_SWAP( "241.p2",      0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2T_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
    MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hc14 ) //mslug2f1
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hc14.p1", 0x000000, 0x100000, CRC(56f2c248) SHA1(688685dc3703885279d2e3f95538272474ee3e08) )
	ROM_LOAD16_WORD_SWAP( "241_hc14.p2", 0x100000, 0x200000, CRC(37a118fc) SHA1(37c913c3d6736362ad83b8aaadf94b9112669a52) )
    MSLUG2T_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
    MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hc15 ) //mslug2dd
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hc15.p1", 0x000000, 0x100000, CRC(da22fd32) SHA1(7ecbf665f3d6af1b8f658e22f8df32463d3b9e2d) )
	ROM_LOAD16_WORD_SWAP( "241_hc15.p2", 0x100000, 0x200000, CRC(89adbf97) SHA1(98b5382d51c7fd0b5ad52dd9649ef847a163a78a) )
    MSLUG2T_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
    MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2DD_SPRITES
ROM_END

ROM_START( mslug2hc16 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hc16.p1", 0x000000, 0x100000, CRC(300d800b) SHA1(3896179061b4025d717cdcc213699a0a9d6183ab) )
	ROM_LOAD16_WORD_SWAP( "241.p2",      0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2T_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
    MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2DD_SPRITES
ROM_END

ROM_START( mslug2hc17 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hc17.p1", 0x000000, 0x100000, CRC(d1b10ed0) SHA1(db992fa93d1afb4adea30d63903fcd7d0e6ce9dd) )
	ROM_LOAD16_WORD_SWAP( "241.p2",      0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2T_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
    MSLUG2FR_SFIX_128K
	MSLUG2_AUDIO_128K
    MSLUG2_YMSND
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2hc18 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hc18.p1",  0x000000, 0x100000, CRC(5261ffd7) SHA1(d514f35f4d8278c31d7619ff45df6af117c6ee0f) )
	ROM_LOAD16_WORD_SWAP( "241.p2",       0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2T_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
    MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2DD_SPRITES
ROM_END

ROM_START( mslug2hc19 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hc19.p1",  0x000000, 0x100000, CRC(0106f67c) SHA1(202a54f3cc81b94654816591a5c7a6dfd0219d3b) )
	ROM_LOAD16_WORD_SWAP( "241.p2",       0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2T_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
    MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2DD_SPRITES
ROM_END

 /************
 Metal Slug 3
***************/

ROM_START( mslug3hc01 ) //mslg3eha
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc01.p1", 0x000000, 0x100000, CRC(e04c6624) SHA1(de684f346ab9a2e5730a6753de6d53801a702cc8) )
	ROM_LOAD16_WORD_SWAP( "256h.p2",     0x100000, 0x400000, CRC(1f3d8ce8) SHA1(08b05a8abfb86ec09a5e758d6273acf1489961f9) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3D_SPRITES
ROM_END

ROM_START( mslug3hc02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc02.p1", 0x000000, 0x100000, CRC(b981e587) SHA1(7e193b1e73fe4e921d5809f942df2da41f34d177) )
	ROM_LOAD16_WORD_SWAP( "256h.p2",     0x100000, 0x400000, CRC(1f3d8ce8) SHA1(08b05a8abfb86ec09a5e758d6273acf1489961f9) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3D_SPRITES
ROM_END

ROM_START( mslug3hc03 ) //mslug3g
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc03.p1", 0x000000, 0x100000, CRC(b23bd9b7) SHA1(4a5e877bc0d4853dc9c5a2c179049fbdd5285239) )
	ROM_LOAD16_WORD_SWAP( "256_hc03.p2", 0x100000, 0x400000, CRC(8053a3fb) SHA1(baf40ca915d30f3dbf6cc440131e824e889940e7) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
    AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3_AUDIOBIOS_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3hc04 ) //mslug3se
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc04.p1", 0x000000, 0x100000, CRC(46330db5) SHA1(7d1df5cb86da40b11465e6e017670365cbe234ac) )
	ROM_LOAD16_WORD_SWAP( "256h.p2",     0x100000, 0x400000, CRC(1f3d8ce8) SHA1(08b05a8abfb86ec09a5e758d6273acf1489961f9) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3D_SPRITES
ROM_END

/* the roms hack crashes when one has a weapon in his possession by pressing the start button at any time, the curious thing is that this error also occurs in the gotvg emulator. */
ROM_START( mslug3hc05 ) //mslug3eb
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc05.p1", 0x000000, 0x900000, CRC(7c0e40f9) SHA1(b4e5795156e49957a6cb787bfcc65c43e211ea9a) )
    MSLUG3DD_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3_SFIX_MT_512K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3_SPRITES
ROM_END

ROM_START( mslug3hc06 ) //mslug3sd
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc06.p1", 0x000000, 0x100000, CRC(e1e21cc4) SHA1(c70ef18dfe8edbadadff6004508e838b246b88a5) )
	ROM_LOAD16_WORD_SWAP( "256_hc06.p2", 0x100000, 0x400000, CRC(7343335b) SHA1(2d694af0c876eb8b4844e918cb707ce011c61c5d) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3hc07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc07.p1", 0x000000, 0x100000, CRC(2591b1f7) SHA1(3af19aad19d741a342d83bf20c564d8294a8daca) )
	ROM_LOAD16_WORD_SWAP( "256h.p2",     0x100000, 0x400000, CRC(1f3d8ce8) SHA1(08b05a8abfb86ec09a5e758d6273acf1489961f9) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3D_SPRITES
ROM_END

ROM_START( mslug3hc08 ) //mslug3zh
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc08.p1", 0x000000, 0x100000, CRC(257fa6b9) SHA1(c9ccc0a42a5a34a08316a76dc977ccee74d91245) )
	ROM_LOAD16_WORD_SWAP( "256_hc08.p2", 0x100000, 0x400000, CRC(badc753c) SHA1(60eae0e02c05448c33cde2666a8b565ee6835216) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3hc09 ) //mslug3wz
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc09.p1", 0x000000, 0x100000, CRC(4e6753ee) SHA1(2df01bda8ed450761c5ed24a9ef1a4dfe324ab08) )
	ROM_LOAD16_WORD_SWAP( "256h.p2",     0x100000, 0x400000, CRC(1f3d8ce8) SHA1(08b05a8abfb86ec09a5e758d6273acf1489961f9) )
    MSLUG3WZ_FIX_FILL
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3D_SPRITES
ROM_END

ROM_START( mslug3hc10 ) // mslug3gw
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc10.p1", 0x000000, 0x100000, CRC(fafde0b4) SHA1(3eee501ddebda761d93c49cdea135fdf0aa0dc9c) )
	ROM_LOAD16_WORD_SWAP( "256h.p2",     0x100000, 0x400000, CRC(1f3d8ce8) SHA1(08b05a8abfb86ec09a5e758d6273acf1489961f9) )
    MSLUG3GW_FIX_FILL
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3GW_AUDIO_512K
    MSLUG3GW_YMSND
    MSLUG3D_SPRITES
ROM_END

ROM_START( mslug3hc11 )  // mslug3c+eb
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc11.p1", 0x000000, 0x100000, CRC(e575a406) SHA1(fcfab75f53c13353fcdd85293dee5bd71f614bb0) )
	ROM_LOAD16_WORD_SWAP( "256_hc11.p2", 0x100000, 0x400000, CRC(29de4e23) SHA1(1591403b39ecadd33380020e9f801688ed996e94) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3hc12 ) //mslug3es
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc12.p1", 0x000000, 0x100000, CRC(caac7e33) SHA1(098505f23e3a56e2e0cc0ae855e2457061138c9e) )
	ROM_LOAD16_WORD_SWAP( "256_hc12.p2", 0x100000, 0x400000, CRC(62e699b3) SHA1(eac088b21d2243198034a9796aa0815d686ccfac) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3GW_AUDIO_512K
    MSLUG3GW_YMSND
	MSLUG3D_SPRITES
ROM_END

ROM_START( mslug3hc13 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc13.p1", 0x000000, 0x100000, CRC(ea7d570f) SHA1(d2419b96347f75fdd386880bc5eaa5766fe07b0c) )
	ROM_LOAD16_WORD_SWAP( "256h.p2",     0x100000, 0x400000, CRC(1f3d8ce8) SHA1(08b05a8abfb86ec09a5e758d6273acf1489961f9) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3D_SPRITES
ROM_END

ROM_START( mslug3hc14 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc14.p1", 0x000000, 0x100000, CRC(003ae172) SHA1(63b0ba7c40f11a611904abc3c98a87ae1137b8e2) )
	ROM_LOAD16_WORD_SWAP( "256h.p2",     0x100000, 0x400000, CRC(1f3d8ce8) SHA1(08b05a8abfb86ec09a5e758d6273acf1489961f9) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3D_SPRITES
ROM_END

ROM_START( mslug3hc15 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc11.p1", 0x000000, 0x100000, CRC(e575a406) SHA1(fcfab75f53c13353fcdd85293dee5bd71f614bb0) )
	ROM_LOAD16_WORD_SWAP( "256_hc15.p2", 0x100000, 0x400000, CRC(d53d178c) SHA1(98f0cd74b18d0d63b74fd6d3830548f4c2ce401b) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3hc16 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc11.p1", 0x000000, 0x100000, CRC(e575a406) SHA1(fcfab75f53c13353fcdd85293dee5bd71f614bb0) )
	ROM_LOAD16_WORD_SWAP( "256_hc16.p2", 0x100000, 0x400000, CRC(f55ccb93) SHA1(c52e83c848ba63ca0323aa99f85e8278b6fe4cda) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3hc17 ) //mslug3lw
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc11.p1", 0x000000, 0x100000, CRC(e575a406) SHA1(fcfab75f53c13353fcdd85293dee5bd71f614bb0) )
	ROM_LOAD16_WORD_SWAP( "256_hc17.p2", 0x100000, 0x400000, CRC(7eed7c81) SHA1(1d9a18178b14226be60af683c9c4a7cfada7f0bb) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3hc18 ) //mslug3i
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc18.p1", 0x000000, 0x100000, CRC(6ea79265) SHA1(1930a3ff1260d56fdc7559bd5bb56f0ca5479588) )
	ROM_LOAD16_WORD_SWAP( "256h.p2",     0x100000, 0x400000, CRC(1f3d8ce8) SHA1(08b05a8abfb86ec09a5e758d6273acf1489961f9) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3D_SPRITES
ROM_END

ROM_START( mslug3hc19 ) //mslug3c
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc19.p1", 0x000000, 0x100000, CRC(05c99714) SHA1(da2e5b959d9327bce7b244629abaa8784af767a6) )
	ROM_LOAD16_WORD_SWAP( "256_hc19.p2", 0x100000, 0x400000, CRC(b948a472) SHA1(e0135911f7d7e21285e6965cc6b4446277eea405) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3hc20 ) //mslug3hcr, mslug3nsj
	ROM_REGION( 0x500000, "maincpu", 0 )
    ROM_LOAD16_WORD_SWAP( "256_hc20.p1", 0x000000, 0x100000, CRC(f804b927) SHA1(a1a6bcc0fe65416c3ab04f84513da2138515fed0) )
	ROM_LOAD16_WORD_SWAP( "256_hc20.p2", 0x100000, 0x400000, CRC(fd65040a) SHA1(246b35e8a4f8a85e4718812af0d70bd245d653a1) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3ER_AUDIO_256K
    MSLUG3_YMSND
    MSLUG3D_SPRITES
ROM_END

ROM_START( mslug3hc21 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc21.p1", 0x000000, 0x100000, CRC(bb448975) SHA1(3b9565ad6f2468ee95b953161d1701c88c9568e5) )
	ROM_LOAD16_WORD_SWAP( "256h.p2",     0x100000, 0x400000, CRC(1f3d8ce8) SHA1(08b05a8abfb86ec09a5e758d6273acf1489961f9) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3D_SPRITES
ROM_END

ROM_START( mslug3hc22 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc22.p1", 0x000000, 0x100000, CRC(c77e53c5) SHA1(4f066a55da42c87509456146cf6fa73ba3f6f582) )
	ROM_LOAD16_WORD_SWAP( "256h.p2",     0x100000, 0x400000, CRC(1f3d8ce8) SHA1(08b05a8abfb86ec09a5e758d6273acf1489961f9) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3D_SPRITES
ROM_END

ROM_START( mslug3hc23 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc23.p1", 0x000000, 0x100000, CRC(ec09383d) SHA1(6574976d540b776c6c1db0dbacc9c9e084207324) )
	ROM_LOAD16_WORD_SWAP( "256h.p2",     0x100000, 0x400000, CRC(1f3d8ce8) SHA1(08b05a8abfb86ec09a5e758d6273acf1489961f9) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3D_SPRITES
ROM_END

ROM_START( mslug3hc24 ) //mslug3unity
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc24.p1", 0x000000, 0x900000, CRC(9a1f8842) SHA1(464e12df13967219089d1694fd8bf65fa9521973) )
    MSLUG3DD_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3_SFIX_MT_512K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3_SPRITES
ROM_END

ROM_START( mslug3hc25 ) //mslug3cq, mslug3scb
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc25.p1", 0x000000, 0x100000, CRC(dc0b9622) SHA1(1d80f2349564e6b09fdaffa1306ef03a4e7f1899) )
	ROM_LOAD16_WORD_SWAP( "256_hc25.p2", 0x100000, 0x400000, CRC(3e880fe2) SHA1(0acc938ce512c9232279bac1e8d7dbe82c309a90) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
	MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3SCB_SPRITES
ROM_END

ROM_START( mslug3hc26 ) //mslug3dd
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc26.p1", 0x000000, 0x100000, CRC(9a83cb7a) SHA1(07f2c4602d7c4cc011a5271d39af92a329fbcff0) )
	ROM_LOAD16_WORD_SWAP( "256_hc26.p2", 0x100000, 0x400000, CRC(e82fc07a) SHA1(3fa3da5aff90229a1bbd636f761d4eb4a66958d8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3DD_SPRITES
ROM_END

ROM_START( mslug3hc27 ) //mslug3ki
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc27.p1", 0x000000, 0x100000, CRC(16a83b0a) SHA1(a898890bcd13d194333271c0d445913ba8d2cda7) )
	ROM_LOAD16_WORD_SWAP( "256_hc27.p2", 0x100000, 0x400000, CRC(57f01937) SHA1(da9e106619c2fb264a2ba492b78828468a7265d6) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3DD_SPRITES
ROM_END

ROM_START( mslug3hc28 ) //mslug3sc, 
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc28.p1", 0x000000, 0x100000, CRC(a1d0a37a) SHA1(059f464e733ffd9b1344b30c41d89683063468e4) )
	ROM_LOAD16_WORD_SWAP( "256_hc28.p2", 0x100000, 0x400000, CRC(8585d898) SHA1(ed35d67f339ba1bb78d3a36c438c2f5fdae95684) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
	MSLUG3H_MVS_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIOBIOS_512K
    MSLUG3_YMSND
	MSLUG3CQ_SPRITES
ROM_END

ROM_START( mslug3hc29 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc29.p1", 0x000000, 0x100000, CRC(6e9e2cdd) SHA1(3ed78c9d6adcf605432ecb2905fd39bba7356f08) )
	ROM_LOAD16_WORD_SWAP( "256h.p2",     0x100000, 0x400000, CRC(1f3d8ce8) SHA1(08b05a8abfb86ec09a5e758d6273acf1489961f9) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3D_SPRITES
ROM_END

ROM_START( mslug3hc30 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc30.p1", 0x000000, 0x100000, CRC(9c2063d2) SHA1(ded2a73388d9f50ade36c04625d62cd5ec26a244) )
	ROM_LOAD16_WORD_SWAP( "256h.p2",     0x100000, 0x400000, CRC(1f3d8ce8) SHA1(08b05a8abfb86ec09a5e758d6273acf1489961f9) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3D_SPRITES
ROM_END

ROM_START( mslug3hc31 ) //mslug3v
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc31.p1", 0x000000, 0x100000, CRC(47f9aeea) SHA1(db1c65681ac12b146e2fa21a8f28000f41a11fe2) )
	ROM_LOAD16_WORD_SWAP( "256h.p2",     0x100000, 0x400000, CRC(1f3d8ce8) SHA1(08b05a8abfb86ec09a5e758d6273acf1489961f9) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3D_SPRITES
ROM_END

ROM_START( mslug3hc32 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc32.p1", 0x000000, 0x100000, CRC(ac2fd576) SHA1(f605e6f900aadac0c8637c1b4890f9e0da04309c) )
	ROM_LOAD16_WORD_SWAP( "256h.p2",     0x100000, 0x400000, CRC(1f3d8ce8) SHA1(08b05a8abfb86ec09a5e758d6273acf1489961f9) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3_SFIX_MT_512K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3FR_SPRITES
ROM_END

ROM_START( mslug3hc33 )
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc33.p1", 0x000000, 0x900000, CRC(e15e9f6e) SHA1(cd0068ecbace9c375378eae7a9459984d1e1a148) )
    MSLUG3DD_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_COIN_FILL
	AUDIOBIOS_128K
	MSLUG3_SFIX_MT_512K
	MSLUG3_AUDIOBIOS_512K
    MSLUG3_YMSND
	MSLUG3_SPRITES
ROM_END

/*Fixed by remikare*/
ROM_START( mslug3hc34 ) //mslug3lw, mslug3nd
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc34.p1", 0x000000, 0x100000, CRC(94527837) SHA1(5af3de12ed91b38f84c96f91d10ca8f23826b8b4) )
	ROM_LOAD16_WORD_SWAP( "256_hc34.p2", 0x100000, 0x400000, CRC(2e3a433f) SHA1(5dffc05f346020d0bcab7c9280638bf901a5cf11) )
	MSLUG3LW_FIX_FILL
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3hc35 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc35.p1", 0x000000, 0x100000, CRC(f77edb2a) SHA1(825ebda68220217d56ac2f4e1a21805066800b61) )
	ROM_LOAD16_WORD_SWAP( "256h.p2",     0x100000, 0x400000, CRC(1f3d8ce8) SHA1(08b05a8abfb86ec09a5e758d6273acf1489961f9) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3D_SPRITES
ROM_END

ROM_START( mslug3hc36 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc36.p1", 0x000000, 0x100000, CRC(380d190c) SHA1(45abe6f04ac16be7b168d9334bfc858525379733) )
	ROM_LOAD16_WORD_SWAP( "256h.p2",     0x100000, 0x400000, CRC(1f3d8ce8) SHA1(08b05a8abfb86ec09a5e758d6273acf1489961f9) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3D_SPRITES
ROM_END

ROM_START( mslug3hc37 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc37.p1", 0x000000, 0x100000, CRC(c23a8e11) SHA1(ccf24e7734b85d45573d34319dfdd14327b0cb39) )
	ROM_LOAD16_WORD_SWAP( "256_hc37.p2", 0x100000, 0x400000, CRC(c31769f4) SHA1(94848f7e63d864102a79829c91eb867a61d6f87e) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3DD_SPRITES
ROM_END

ROM_START( mslug3hc38 ) //mslug31v2
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc38.p2", 0x000000, 0x900000, CRC(3eed1b04) SHA1(922805ec7178ebd0f4cdfc87a8395dfe5294561a) )
    MSLUG3DD_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3_SFIX_MT_512K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3_SPRITES
ROM_END

/****************************************************
 Metal Slug 6" is a hack/bootleg of Metal Slug 3
*******************************************************/

ROM_START( mslug3b6hc01 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "299_hc01.p1", 0x000000, 0x200000, CRC(6d89096c) SHA1(97c436657512576a954690385c58f08f6510f655) )
	ROM_LOAD16_WORD_SWAP( "299_hc01.p2", 0x100000, 0x400000, CRC(bf4a80af) SHA1(514f97892375a636b84fb8388261eea645a8da1a) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3B6_MVS_FILL
    MSLUG3H_AES_FILL
    MSLUG3B6_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3N6P_SPRITES
ROM_END

ROM_START( mslug3b6hc02 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "299_hc01.p1", 0x000000, 0x200000, CRC(6d89096c) SHA1(97c436657512576a954690385c58f08f6510f655) )
	ROM_LOAD16_WORD_SWAP( "299_hc02.p2", 0x100000, 0x400000, CRC(d33f3351) SHA1(e76fa46dcbade4c86f1c7e89b86e75e9c0d6b3b2) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3B6_MVS_FILL
    MSLUG3H_AES_FILL
    MSLUG3B6_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3N6P_SPRITES
ROM_END

ROM_START( mslug3b6hc03 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "299_hc01.p1", 0x000000, 0x200000, CRC(6d89096c) SHA1(97c436657512576a954690385c58f08f6510f655) )
	ROM_LOAD16_WORD_SWAP( "299_hc03.p2", 0x100000, 0x400000, CRC(f35eef4e) SHA1(569867c16142bbcb4153bf437407d9d266a3bffc) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3B6_MVS_FILL
    MSLUG3H_AES_FILL
    MSLUG3B6_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3N6P_SPRITES
ROM_END

ROM_START( mslug3b6hc04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "299p.p1",     0x000000, 0x100000, CRC(1f1079a2) SHA1(5d99358f0e513e2087c7594bab09c8d33db40f1f) )
	ROM_LOAD16_WORD_SWAP( "299_hc04.p2", 0x100000, 0x400000, CRC(2fdc6afe) SHA1(85ff8cfda7e34265a638efc5ed81a20846a1bbae) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3B6_MVS_FILL
    MSLUG3H_AES_FILL
    MSLUG3B6_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3N6P_SPRITES
ROM_END

ROM_START( mslug3b6hc05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "299_hc05.p1", 0x000000, 0x100000, CRC(5905b9ba) SHA1(c4a029e596729e46783ce8322a1320a106d209ac) )
	ROM_LOAD16_WORD_SWAP( "299_hc05.p2", 0x100000, 0x400000, CRC(6a5db17d) SHA1(cdc5d4cd5d4b1c300fff0de02b818a81b0be5c21) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3B6_MVS_FILL
    MSLUG3H_AES_FILL
    MSLUG3B6_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3N6P_SPRITES
ROM_END

ROM_START( mslug3b6hc06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "299_hc06.p1", 0x000000, 0x100000, CRC(a74aa435) SHA1(3b66b96133b4d80c5addfeed6c6d87254ee3b1bf) )
	ROM_LOAD16_WORD_SWAP( "299_hc05.p2", 0x100000, 0x400000, CRC(6a5db17d) SHA1(cdc5d4cd5d4b1c300fff0de02b818a81b0be5c21) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3B6_MVS_FILL
    MSLUG3H_AES_FILL
    MSLUG3B6_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3N6P_SPRITES
ROM_END

ROM_START( mslug3b6hc07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "299_hc07.p1", 0x000000, 0x100000, CRC(f3885036) SHA1(bb9f6fea9f7ac8dbfa17e02f25d12c3324a6bbb4) )
	ROM_LOAD16_WORD_SWAP( "299_hc05.p2", 0x100000, 0x400000, CRC(6a5db17d) SHA1(cdc5d4cd5d4b1c300fff0de02b818a81b0be5c21) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3B6_MVS_FILL
    MSLUG3H_AES_FILL
    MSLUG3B6_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3N6P_SPRITES
ROM_END

ROM_START( mslug3b6hc08 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "299_hc08.p1", 0x000000, 0x100000, CRC(0a8d7d23) SHA1(a0be73288ba215e4564d3e1814022efebb0cde9f) )
	ROM_LOAD16_WORD_SWAP( "299_hc08.p2", 0x100000, 0x400000, CRC(3c3d0ffa) SHA1(b39f0d02c3648dfa27c93f38e0e8285001aab23d) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3B6_MVS_FILL
    MSLUG3H_AES_FILL
    MSLUG3B6_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3b6hc09 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "299_hc09.p1", 0x000000, 0x100000, CRC(bd3488d9) SHA1(9afedcf1bd4d407ebd3fe8a3fe713220e550df45) )
	ROM_LOAD16_WORD_SWAP( "299_hc08.p2", 0x100000, 0x400000, CRC(3c3d0ffa) SHA1(b39f0d02c3648dfa27c93f38e0e8285001aab23d) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3B6_MVS_FILL
    MSLUG3H_AES_FILL
    MSLUG3B6_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3b6hc10 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "299_hc10.p1", 0x000000, 0x100000, CRC(38238bb5) SHA1(2be5966c219503d21e7a28a79c47321072b4b85f) )
	ROM_LOAD16_WORD_SWAP( "299_hc08.p2", 0x100000, 0x400000, CRC(3c3d0ffa) SHA1(b39f0d02c3648dfa27c93f38e0e8285001aab23d) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3B6_MVS_FILL
    MSLUG3H_AES_FILL
    MSLUG3B6_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3b6hc11 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "299_hc11.p1", 0x000000, 0x100000, CRC(ab91e13f) SHA1(d459e52352ea99f65d97b9d9ef917b4772829d9e) )
	ROM_LOAD16_WORD_SWAP( "299_hc08.p2", 0x100000, 0x400000, CRC(3c3d0ffa) SHA1(b39f0d02c3648dfa27c93f38e0e8285001aab23d) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3B6_MVS_FILL
    MSLUG3H_AES_FILL
    MSLUG3B6_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

/*************
 Metal Slug 4
***************/

ROM_START( mslug4hc01 ) //mslug4sd
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_hc01.p1", 0x000000, 0x100000, CRC(af69d959) SHA1(2bc9796003c8742d681e11ad842978d918fbae40) )
	ROM_LOAD16_WORD_SWAP( "263_hc01.p2", 0x100000, 0x400000, CRC(2b863b30) SHA1(b5edc43d87faf6540e3154fcbab42efb148cbd04) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4NDP_SFIX_128K
    MSLUG4D_AUDIO_64K
	MS4BOOT_YMSND
	MSLUG4D_SPRITES
ROM_END

ROM_START( mslug4hc02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_hc02.p1", 0x000000, 0x100000, CRC(e034a441) SHA1(54cda2ae0a998e9a5f64e207f53d681ed5dea186) )
	ROM_LOAD16_WORD_SWAP( "263.p2",      0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
	MSLUG4_AUDIO_ENCRYPTED_128K
    MSLUG4_YMSND
	MSLUG4D_SPRITES
ROM_END

ROM_START( mslug4hc03 ) //mslug4lw
	ROM_REGION( 0x900000, "maincpu", 0 )
    ROM_LOAD16_WORD_SWAP( "263_hc03.p1", 0x000000, 0x100000, CRC(ad713169) SHA1(51c10dfa1b8fc3b0e7850c71920091dbd91d1ba5) )
	ROM_LOAD16_WORD_SWAP( "263_hc03.p2", 0x100000, 0x800000, CRC(5aa184e7) SHA1(4850341a52e12d541271926a47714c2bbbcd7cba) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
	MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
    MSLUG4LWD_SPRITES
ROM_END

ROM_START( mslug4hc04 ) //mslug4ammor
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_hc04.p1", 0x000000, 0x100000, CRC(21b68d31) SHA1(97b287e2cbd4eb20fe65339c5d1d42b864e8a440) )
	ROM_LOAD16_WORD_SWAP( "263_hc03.p2", 0x100000, 0x800000, CRC(5aa184e7) SHA1(4850341a52e12d541271926a47714c2bbbcd7cba) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
    MSLUG4LWD_SPRITES
ROM_END

ROM_START( mslug4hc05 ) //mslug4c
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_hc05.p1", 0x000000, 0x100000, CRC(f8145f8d) SHA1(ba1df84c199e5f552c80ad7725f9cae5512fbb20) )
	ROM_LOAD16_WORD_SWAP( "263.p2",      0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
    MSLUG4LWD_SPRITES
ROM_END

ROM_START( mslug4hc06 ) //mslug4dg
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_hc06.p1", 0x000000, 0x100000, CRC(36dfa877) SHA1(dd49b6b40d3c2cabac8d5efa71cceea8cf9fc4f8) )
	ROM_LOAD16_WORD_SWAP( "263_hc06.p2", 0x100000, 0x400000, CRC(cf6feb75) SHA1(133e1d97a3ae14835dcb7b6a642c3968cd174547) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
	MSLUG4_AUDIO_ENCRYPTED_128K
    MSLUG4DG_YMSND
	MSLUG4_SPRITES
ROM_END

ROM_START( mslug4hc07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_hc07.p1", 0x000000, 0x100000, CRC(25f5f99f) SHA1(5cad2f17bfaff789de36e02a3b2e92d353924247) )
	ROM_LOAD16_WORD_SWAP( "263_hc06.p2", 0x100000, 0x400000, CRC(cf6feb75) SHA1(133e1d97a3ae14835dcb7b6a642c3968cd174547) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
	MSLUG4_AUDIO_ENCRYPTED_128K
    MSLUG4_YMSND
	MSLUG4_SPRITES
ROM_END

ROM_START( mslug4hc08 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_hc08.p1", 0x000000, 0x100000, CRC(414416d1) SHA1(78d3f7bc4a5e603c8035a2c9ece3969f9ee1b567) )
	ROM_LOAD16_WORD_SWAP( "263.p2",      0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
	MSLUG4_AUDIO_ENCRYPTED_128K
    MSLUG4_YMSND
	MSLUG4D_SPRITES
ROM_END

ROM_START( mslug4hc09 ) //mslug4q
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_hc09.p1", 0x000000, 0x100000, CRC(461579ae) SHA1(fe7da7ec3e4ee2e0b4281ea76a130a7fe3cac549) )
	ROM_LOAD16_WORD_SWAP( "263_hc09.p2", 0x100000, 0x400000, CRC(a4d2e871) SHA1(646ac0117a832f1642cffe17478b94635cf294a2) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
	MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
	MSLUG4_AUDIO_ENCRYPTED_128K
    MSLUG4_YMSND
	MSLUG4D_SPRITES
ROM_END

ROM_START( mslug4hc10 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_hc10.p1", 0x000000, 0x100000, CRC(3f7ce3c5) SHA1(a0a9cf5d887f2ff9c048d2bb22cfba168b393df0) )
	ROM_LOAD16_WORD_SWAP( "263.p2",      0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_COIN_FILL
	AUDIOBIOS_128K
	MSLUG4HD_SFIX_128K
	MSLUG4_AUDIOBIOS_ENCRYPTED_128K
    MSLUG4_YMSND
	MSLUG4D_SPRITES
ROM_END

ROM_START( mslug4hc11 ) //mslug41v2
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_hc11.p1", 0x000000, 0x100000, CRC(dddca463) SHA1(d93ca67aed8cdf0765713056a5b6a9a77f09c848) )
	ROM_LOAD16_WORD_SWAP( "263.p2",      0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
	MSLUG4_AUDIO_ENCRYPTED_128K
    MSLUG4_YMSND
	MSLUG4D_SPRITES
ROM_END

ROM_START( mslug4hc12 ) //mslug4lwq
	ROM_REGION( 0x900000, "maincpu", 0 )
    ROM_LOAD16_WORD_SWAP( "263_hc12.p1", 0x000000, 0x100000, CRC(9ebe335e) SHA1(7af10e13b84494393c0e32d01e881060236724db) )
	ROM_LOAD16_WORD_SWAP( "263_hc03.p2", 0x100000, 0x800000, CRC(5aa184e7) SHA1(4850341a52e12d541271926a47714c2bbbcd7cba) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
	MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
	MSLUG4LWD_SPRITES
ROM_END

ROM_START( mslug4hc13 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_hc13.p1", 0x000000, 0x100000, CRC(19836d5a) SHA1(0133872676d3936ca94aaa918d4e2e1d13d68979) )
    ROM_LOAD16_WORD_SWAP( "263.p2",      0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
	MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
    MSLUG4_AUDIO_ENCRYPTED_128K
    MSLUG4_YMSND
	MSLUG4D_SPRITES
ROM_END

ROM_START( mslug4hc14 ) //mslug4unity
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_hc14.p1", 0x000000, 0x100000, CRC(ef3501b6) SHA1(ffbf98407e9646590a59887c42aab47f3a2d67dd) )
	ROM_LOAD16_WORD_SWAP( "263.p2",      0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
	MSLUG4_AUDIO_ENCRYPTED_128K
    MSLUG4_YMSND
	MSLUG4D_SPRITES
ROM_END

ROM_START( mslug4hc15 ) //mslug4a
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_hc15.p1", 0x000000, 0x100000, CRC(0f2b0fc2) SHA1(8f12a7e703f331ad2e80ac2d2d9c5e7645066468) )
	ROM_LOAD16_WORD_SWAP( "263_hc15.p2", 0x100000, 0x400000, CRC(87dc01b9) SHA1(ddad7d72e53e0c6273384119f96b3b7f324ca237) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
	MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
	MSLUG4_AUDIO_ENCRYPTED_128K
    MSLUG4_YMSND
	MSLUG4D_SPRITES
ROM_END

ROM_START( mslug4hc16 ) //mslug4dd
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_hc16.p1", 0x000000, 0x100000, CRC(02ce0fcd) SHA1(67534a14ae4455f7b4f8456b395a6a648803fbdc) )
	ROM_LOAD16_WORD_SWAP( "263_hc16.p2", 0x100000, 0x400000, CRC(4569a092) SHA1(98cbc3a554a810c105a3044f09fa732ebc56cb4a) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
	MSLUG4_AUDIO_ENCRYPTED_128K
    MSLUG4_YMSND
	MSLUG4DDH_SPRITES
ROM_END

ROM_START( mslug4hc17 ) //mslug4ki
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_hc17.p1", 0x000000, 0x100000, CRC(4e2363d3) SHA1(f574745c5c385d7bb753539d8dbeff657c268ea2) )
	ROM_LOAD16_WORD_SWAP( "263_hc17.p2", 0x100000, 0x400000, CRC(e95f6bd8) SHA1(4aa293f984b5767bf2a640a08cc36a7cb13a9cfb) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
	MSLUG4_AUDIO_ENCRYPTED_128K
    MSLUG4_YMSND
	MSLUG4DDH_SPRITES
ROM_END

ROM_START( mslug4hc18 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_hc18.p1", 0x000000, 0x100000, CRC(6bb85c5b) SHA1(98c338826a8bc8c593a49525aeb3474208335763) )
	ROM_LOAD16_WORD_SWAP( "263.p2",      0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
	MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
	MSLUG4_AUDIO_ENCRYPTED_128K
    MSLUG4_YMSND
	MSLUG4D_SPRITES
ROM_END

ROM_START( mslug4hc19 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_hc19.p1", 0x000000, 0x100000, CRC(9a524c97) SHA1(6c2dd09f73e41a18a7e1a3290756d7fcfc8ec6b9) )
	ROM_LOAD16_WORD_SWAP( "263.p2",      0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
	MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
	MSLUG4_AUDIO_ENCRYPTED_128K
    MSLUG4_YMSND
	MSLUG4D_SPRITES
ROM_END

ROM_START( mslug4hc20 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_hc20.p1", 0x000000, 0x100000, CRC(a3ceab91) SHA1(f0e125e708bb466308e6846bb943022f4b5785a3) )
	ROM_LOAD16_WORD_SWAP( "263.p2",      0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4FR_SFIX_128K
	MSLUG4_AUDIO_ENCRYPTED_128K
    MSLUG4_YMSND
	MSLUG4FR_SPRITES
ROM_END

ROM_START( mslug4hc21 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_hc21.p1", 0x000000, 0x100000, CRC(ffb20602) SHA1(4d3103d613a2452c95ae15b70670664354dce67b) )
    ROM_LOAD16_WORD_SWAP( "263.p2",      0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
	MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4IT_SFIX_128K
    MSLUG4D_AUDIO_64K
    MSLUG4_YMSND
	MSLUG4D_SPRITES
ROM_END

ROM_START( mslug4hc22 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_hc22.p1", 0x000000, 0x100000, CRC(d62e607d) SHA1(b03e366dee84db44c1fac6327e909f224619bc73) )
    ROM_LOAD16_WORD_SWAP( "263.p2",      0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
	MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
	MSLUG4_AUDIO_ENCRYPTED_128K
    MSLUG4_YMSND
	MSLUG4D_SPRITES
ROM_END

ROM_START( mslug4hc23 ) //mslug4c
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_hc23.p1", 0x000000, 0x100000, CRC(4ae77816) SHA1(ba4284496d6db70d29fac720e73509c5bc277594) )
	ROM_LOAD16_WORD_SWAP( "263.p2",      0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
    MSLUG4LWD_SPRITES
ROM_END

/*************
 Metal Slug 5
***************/

ROM_START( mslug5hc01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc01.p1", 0x000000, 0x100000, CRC(3c8588d7) SHA1(5dada21b9530586f8941e027d3f2195e72a3ca5d) )
	ROM_LOAD16_WORD_SWAP( "268n.p2",     0x100000, 0x400000, CRC(768ee64a) SHA1(76a65a69aee749758a2101aabdd44f3404838b54) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5_SFIX_MT_128K
	MSLUG5_AUDIO_ENCRYPTED_512K
    MSLUG5_YMSND
	MSLUG5HD_SPRITES
ROM_END

ROM_START( mslug5hc02 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc02.p1", 0x000000, 0x600000, CRC(faeffb08) SHA1(9fe401d8252c5d46f3a84f59e1e182eecaa4c069) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5ND_AUDIO_128K
	MS5BOOT_YMSND
	MS5BOOT_SPRITES
ROM_END

ROM_START( mslug5hc03 ) //mslug5ext
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc03.p1", 0x000000, 0x600000, CRC(7ff5364b) SHA1(698373c6c3fb37fe20c4194c5c51251f6a251c18) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5ND_AUDIO_128K
	MSLUG5EXT_YMSND
	MS5BOOT_SPRITES
ROM_END

ROM_START( mslug5hc04 ) //mslug5w
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc04.p1", 0x000000, 0x100000, CRC(b0c126da) SHA1(9081ec2c3cfc27baf759417b24f2ebc07ceffab0) )
	ROM_LOAD16_WORD_SWAP( "268_hc04.p2", 0x100000, 0x400000, CRC(f06c589a) SHA1(0882ee5221ab873f87a719e34bd5250b79b82730) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5W_AUDIO_512K
	MSLUG5W_YMSND
	MSLUG5W_SPRITES
ROM_END

ROM_START( mslug5hc05 ) //mslug5es
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc05.p1", 0x000000, 0x100000, CRC(8eb95f3a) SHA1(4353d141544056d34b22adca0615f0ea9d32e376) )
    ROM_LOAD16_WORD_SWAP( "268n.p2",     0x100000, 0x400000, CRC(768ee64a) SHA1(76a65a69aee749758a2101aabdd44f3404838b54) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5ND_AUDIO_128K
	MS5BOOT_YMSND
	MS5BOOT_SPRITES
ROM_END

ROM_START( mslug5hc06 ) //mslug5f
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc06.p1", 0x000000, 0x100000, CRC(6be7043d) SHA1(caaf24cc653abbd435de7732f6489c613f3911ac) )
	ROM_LOAD16_WORD_SWAP( "268_hc04.p2", 0x100000, 0x400000, CRC(f06c589a) SHA1(0882ee5221ab873f87a719e34bd5250b79b82730) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5W_AUDIO_512K
	MSLUG5F_YMSND
	MSLUG5F_SPRITES
ROM_END

ROM_START( mslug5hc07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc07.p1", 0x000000, 0x100000, CRC(de60d4a5) SHA1(54a157cdb98dac018dae5f2ddae4fbcdf04857f2) )
	ROM_LOAD16_WORD_SWAP( "268n.p2",     0x100000, 0x400000, CRC(768ee64a) SHA1(76a65a69aee749758a2101aabdd44f3404838b54) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5_SFIX_MT_128K
	MSLUG5_AUDIO_ENCRYPTED_512K
	MSLUG5_YMSND
	MSLUG5HD_SPRITES
ROM_END

ROM_START( mslug5hc08 ) //mslug5unity
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD32_WORD_SWAP( "268_hc08.p1", 0x000000, 0x400000, CRC(ced9f5a8) SHA1(c1e6c8c9a7d2220b956486f2154540fcda38e650) )
	ROM_LOAD32_WORD_SWAP( "268_hc08.p2", 0x000002, 0x400000, CRC(1c08dbb6) SHA1(8796efebcfabb9bb5444ed0264d327abf7c32b98) )
    MSLUG5_ESSENTIALPATCH_MVS_FILL
    MSLUG5_MVS_FILL
    MSLUG5_AES_FILL
    MSLUG5_SFIX_MT_128K
	MSLUG5_AUDIO_ENCRYPTED_512K
	MSLUG5_YMSND
	MSLUG5_SPRITES
ROM_END

ROM_START( mslug5hc09 ) //mslug5x 
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc09.p1", 0x000000, 0x600000, CRC(afffcd5b) SHA1(4383bd6903e49a5c0a390b77b746b9f53509542d) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5ND_AUDIO_128K
	MS5BOOT_YMSND
	MS5BOOT_SPRITES
ROM_END

ROM_START( mslug5hc10 ) //mslug5es update mslug5es2
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc10.p1", 0x000000, 0x600000, CRC(760cd052) SHA1(70d9ef0c4e906fce940108dd84077d981efaacc0) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5ND_AUDIO_128K
	MS5BOOT_YMSND
	MS5BOOT_SPRITES
ROM_END

ROM_START( mslug5hc11 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc11.p1", 0x000000, 0x100000, CRC(f1f02331) SHA1(d768c70f86032b53aa1c3d55138c6c5ebc735ea2) )
	ROM_LOAD16_WORD_SWAP( "268n.p2",     0x100000, 0x400000, CRC(768ee64a) SHA1(76a65a69aee749758a2101aabdd44f3404838b54) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5_SFIX_MT_128K
	MSLUG5_AUDIO_ENCRYPTED_512K
	MSLUG5_YMSND
	MSLUG5HD_SPRITES
ROM_END

ROM_START( mslug5hc12 ) //mslug5c
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc12.p1", 0x000000, 0x600000, CRC(e876d1e7) SHA1(01508fc02789603e85ac13e0d5fcddda6fadc346) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5ND_AUDIO_128K
	MS5BOOT_YMSND
	MS5BOOT_SPRITES
ROM_END

ROM_START( mslug5hc13 ) //mslug5dbj
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc13.p1", 0x000000, 0x600000, CRC(1527c4dd) SHA1(5a83fa57e09b0529f30ee7f70e0b488dde3ba203) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5ND_AUDIO_128K
	MS5BOOT_YMSND
	MS5BOOT_SPRITES
ROM_END

ROM_START( mslug5hc14 ) //mslug5mg
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc14.p1", 0x000000, 0x600000, CRC(1fc7de70) SHA1(c9f8f70706db9832dacb70723d5525aab4bfb9ac) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5ND_AUDIO_128K
	MS5BOOT_YMSND
	MS5BOOT_SPRITES
ROM_END

ROM_START( mslug5hc15 ) //mslug51v2
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc15.p1", 0x000000, 0x600000, CRC(953d6e11) SHA1(d4faa3c515c7c4337e89513ea2bda13685b38a06) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5ND_AUDIO_128K
	MS5BOOT_YMSND
	MS5BOOT_SPRITES
ROM_END

ROM_START( mslug5hc16 ) //mslug5zh
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc16.p1", 0x000000, 0x600000, CRC(dc057a7a) SHA1(54ca7d543916424fad5dab82c67bb70cb4b5dc11) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5ND_AUDIO_128K
	MS5BOOT_YMSND
	MS5BOOT_SPRITES
ROM_END

ROM_START( mslug5hc17 ) //mslug5g
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc17.p1", 0x000000, 0x600000, CRC(3be747ab) SHA1(48ab8b6bedbd854a74b7fe4055d1a5c7a4b9cda8) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5ND_AUDIO_128K
	MS5BOOT_YMSND
	MS5BOOT_SPRITES
ROM_END

/*Fixed by remikare*/
ROM_START( mslug5hc18 ) //mslug5sg
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc18.p1", 0x000000, 0x600000, CRC(1b6a6163) SHA1(5e3e1a5a4d4f3c4cef9c8f0dda51c6bbdec20df7) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5SG_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5ND_AUDIO_128K
	MS5BOOT_YMSND
	MS5BOOT_SPRITES
ROM_END

ROM_START( mslug5hc19 ) //mslug5pv
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc19.p1", 0x000000, 0x600000, CRC(5288f47b) SHA1(137ca41e06f787204c50b2e6f1ceee91ffef3310) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5ND_AUDIO_128K
	MS5BOOT_YMSND
	MS5BOOT_SPRITES
ROM_END

ROM_START( mslug5hc20 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc20.p1", 0x000000, 0x100000, CRC(ce788ab1) SHA1(89061d49e40e8774ff337ae4601f5c7676eac583) )
	ROM_LOAD16_WORD_SWAP( "268n.p2",     0x100000, 0x400000, CRC(768ee64a) SHA1(76a65a69aee749758a2101aabdd44f3404838b54) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5_SFIX_MT_128K
	MSLUG5_AUDIO_ENCRYPTED_512K
	MSLUG5_YMSND
	MSLUG5HD_SPRITES
ROM_END

ROM_START( mslug5hc21 ) //mslug5dd
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc21.p1", 0x000000, 0x600000, CRC(40917fba) SHA1(7e8e407c2936435be2b1909f582ae9025b1c7a8d) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5ND_AUDIO_128K
	MS5BOOT_YMSND
	MS5BOOT_SPRITES
ROM_END

ROM_START( mslug5hc22 ) //mslug5ki
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc22.p1", 0x000000, 0x600000, CRC(846bc220) SHA1(d0a6ac7a5c04adc5bec65313f632f16b83b70628) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5ND_AUDIO_128K
	MS5BOOT_YMSND
	MS5BOOT_SPRITES
ROM_END

ROM_START( mslug5hc23 ) //mslug5boss
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc23.p1", 0x000000, 0x600000, CRC(15a8de68) SHA1(391fc8caae7099350c3ee1f1dcdef79b07bd18fb) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5ND_AUDIO_128K
	MS5BOOT_YMSND
	MS5BOOT_SPRITES
ROM_END

ROM_START( mslug5hc24 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc24.p1", 0x000000, 0x100000, CRC(63cc3c2d) SHA1(b4543c65427d15f784641617dcab53663031a9f3) )
	ROM_LOAD16_WORD_SWAP( "268n.p2",     0x100000, 0x400000, CRC(768ee64a) SHA1(76a65a69aee749758a2101aabdd44f3404838b54) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5FR_SFIX_128K
    MSLUG5D_AUDIO_64K
	MS5PLUSD_YMSND
	MSLUG5FR_SPRITES
ROM_END

ROM_START( mslug5hc25 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc25.p1", 0x000000, 0x100000, CRC(442642e2) SHA1(0c589ef5d1117a7f7fedd006040e30ab95257b19) )
	ROM_LOAD16_WORD_SWAP( "268n.p2",     0x100000, 0x400000, CRC(768ee64a) SHA1(76a65a69aee749758a2101aabdd44f3404838b54) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5ND_AUDIO_128K
	MS5BOOT_YMSND
	MS5BOOT_SPRITES
ROM_END

ROM_START( mslug5hc26 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc26.p1", 0x000000, 0x100000, CRC(b18a1826) SHA1(b424f40804561ce79115c7d64c45a650bad8635d) )
	ROM_LOAD16_WORD_SWAP( "268n.p2",     0x100000, 0x400000, CRC(768ee64a) SHA1(76a65a69aee749758a2101aabdd44f3404838b54) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MS5PLUSD_SFIX_128K
    MSLUG5ND_AUDIO_128K
	MS5BOOT_YMSND
	MS5BOOT_SPRITES
ROM_END

ROM_START( mslug5hc27 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc27.p1", 0x000000, 0x200000, CRC(257e6ed0) SHA1(a4c68014f19c3a0bf46a0ed7f6c928aa630dd6e0) )
	ROM_LOAD16_WORD_SWAP( "268n.p2",     0x200000, 0x400000, CRC(768ee64a) SHA1(76a65a69aee749758a2101aabdd44f3404838b54) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5ND_AUDIO_128K
	MS5BOOT_YMSND
	MS5BOOT_SPRITES
ROM_END

ROM_START( mslug5hc28 ) //mslug5sv
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hc28.p1", 0x000000, 0x600000, CRC(71a0953f) SHA1(d0852ef474d50c29096d2330edb54890f8444538) )
    MSLUG5HD_ESSENTIALPATCH_MODS_FILL
    MSLUG5HD_MVS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5ND_AUDIO_128K
	MS5BOOT_YMSND
	MSLUG5SV_SPRITES
ROM_END

/*************
 Metal Slug X
***************/

ROM_START( mslugxhc01 ) //mslugxc2
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc01.p1", 0x000000, 0x100000, CRC(944ac109) SHA1(4bba27627a565d60f807993e96efae2f256d1007) )
	ROM_LOAD16_WORD_SWAP( "250_hc01.p2", 0x100000, 0x400000, CRC(5d1c52cd) SHA1(b2b131fa845b0098cbf0750fee20b402e276483b) )
	MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc02 ) //mslugxlb
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc02.p1", 0x000000, 0x100000, CRC(41fc71cc) SHA1(82c9f78edb0cba74491f755fc2f349fc7131ade0) )
	ROM_LOAD16_WORD_SWAP( "250_hc02.p2", 0x100000, 0x400000, CRC(6a114e1a) SHA1(3da62274252d36226dcccda0e05593f7f18c7193) )
    MSLUGXLB_ESSENTIALPATCH_MVS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxhc03 ) //mslugxmax
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc03.p1", 0x000000, 0x100000, CRC(1ffd4613) SHA1(796c3f4af17692ef74cc9ddf771b1a23c53b914b) )
	ROM_LOAD16_WORD_SWAP( "250_hc03.p2", 0x100000, 0x400000, CRC(8d595131) SHA1(523401915e5b751c9d67c169173de7e17fe7ff00) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc04 ) //mslugxunity
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc04.p1", 0x000000, 0x100000, CRC(36102d34) SHA1(b60d41e7cd3395910e7aa5cc0a843d68bfcc2ac6) )
	ROM_LOAD16_WORD_SWAP( "250.p2",      0x100000, 0x400000, CRC(1fda2e12) SHA1(18aaa7a3ba8da99f78c430e9be69ccde04bc04d9) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc05 ) //mslugxeb
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc05.p1", 0x000000, 0x100000, CRC(764d1bb1) SHA1(e46824646aa46121e8591865f609f457fbb6521e) )
	ROM_LOAD16_WORD_SWAP( "250_hc05.p2", 0x100000, 0x400000, CRC(a51363d1) SHA1(7b6b3490a975ac1e549df60b9d70ccd6d2f2ba6e) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc06 ) //mslugxr
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc06.p1", 0x000000, 0x100000, CRC(a507546f) SHA1(ab6e9e969c2b3728cb0b13e0b1d62bda09037ac0) )
	ROM_LOAD16_WORD_SWAP( "250_hc06.p2", 0x100000, 0x400000, CRC(78a66189) SHA1(a0689ea58b12873c939ebe949b42145ef49aff3f) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc07 ) //mslugxhp
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc01.p1", 0x000000, 0x100000, CRC(944ac109) SHA1(4bba27627a565d60f807993e96efae2f256d1007) )
	ROM_LOAD16_WORD_SWAP( "250_hc07.p2", 0x100000, 0x400000, CRC(a2a2a303) SHA1(0a85555253dbff4f0d2ae4edf92dd36f7c0114d8) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc08 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc08.p1", 0x000000, 0x100000, CRC(c0911075) SHA1(2645c9d59915811addc2ab048afbfb9e605bca24) )
	ROM_LOAD16_WORD_SWAP( "250.p2",      0x100000, 0x400000, CRC(1fda2e12) SHA1(18aaa7a3ba8da99f78c430e9be69ccde04bc04d9) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc09 ) //mslugxsv
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc09.p1", 0x000000, 0x100000, CRC(1b213460) SHA1(23f14b2e97582552e6db1e95f98b12f73140d9a5) )
	ROM_LOAD16_WORD_SWAP( "250_hc09.p2", 0x100000, 0x400000, CRC(718d6d66) SHA1(d15f0394cab7c84f8434a3095b25014fd9bb3000) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc10 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc10.p1", 0x000000, 0x100000, CRC(c405753d) SHA1(bed7426145fd15e972334d7ef04759edcccd8864) )
	ROM_LOAD16_WORD_SWAP( "250.p2",      0x100000, 0x400000, CRC(1fda2e12) SHA1(18aaa7a3ba8da99f78c430e9be69ccde04bc04d9) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc11 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc01.p1", 0x000000, 0x100000, CRC(944ac109) SHA1(4bba27627a565d60f807993e96efae2f256d1007) )
	ROM_LOAD16_WORD_SWAP( "250_hc11.p2", 0x100000, 0x400000, CRC(dda3726f) SHA1(7bd181f10e0737e3284c787581cca5b8199485d4) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc12 ) //mslugxsc
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc12.p1", 0x000000, 0x100000, CRC(da458e67) SHA1(79d717e45e03d32ca46c73a0b55ae85e0e9c7b7e) )
	ROM_LOAD16_WORD_SWAP( "250_hc12.p2", 0x100000, 0x400000, CRC(7a27bd7f) SHA1(25c1bb147495f816c0ffd0da741c89b662216a1b) )
    MSLUGXSC_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
    AUDIOBIOS_128K
	MSLUGXSC_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXSCU_SPRITES
ROM_END

ROM_START( mslugxhc13 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc13.p1", 0x000000, 0x100000, CRC(b606e809) SHA1(a477647cf470a115b9df1d37ab859188de49f9a9) )
	ROM_LOAD16_WORD_SWAP( "250.p2",      0x100000, 0x400000, CRC(1fda2e12) SHA1(18aaa7a3ba8da99f78c430e9be69ccde04bc04d9) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc14 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc14.p1", 0x000000, 0x100000, CRC(a11473d5) SHA1(83f6665e88e8b9d33545e5c57ac8a5e923787bd2) )
	ROM_LOAD16_WORD_SWAP( "250.p2",      0x100000, 0x400000, CRC(1fda2e12) SHA1(18aaa7a3ba8da99f78c430e9be69ccde04bc04d9) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc15 ) //mslugxxr
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc15.p1", 0x000000, 0x100000, CRC(bea1f7e5) SHA1(52148032328e4f2e4b6fe93f9df816891ebd50bb) )
	ROM_LOAD16_WORD_SWAP( "250_hc15.p2", 0x100000, 0x400000, CRC(0efc5d67) SHA1(21a370ebc96e1b17ecfb12085732512dc51491d3) )
    MSLUGXXR_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc16 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc16.p1", 0x000000, 0x100000, CRC(e75a6d64) SHA1(529130f7ebb43231e6bf1b1703266b6c09356f9c) )
	ROM_LOAD16_WORD_SWAP( "250.p2",      0x100000, 0x400000, CRC(1fda2e12) SHA1(18aaa7a3ba8da99f78c430e9be69ccde04bc04d9) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc17 ) //mslugx1v2
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc17.p1", 0x000000, 0x100000, CRC(0cf1f95b) SHA1(857af8721c5929ba7c60e16223cab4879ec382b9) )
	ROM_LOAD16_WORD_SWAP( "250.p2",      0x100000, 0x400000, CRC(1fda2e12) SHA1(18aaa7a3ba8da99f78c430e9be69ccde04bc04d9) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc18 ) //mslugxh
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc18.p1", 0x000000, 0x100000, CRC(6a116211) SHA1(92b1d87248e03d21eb87201cbadc5de0eaaf4b47) )
	ROM_LOAD16_WORD_SWAP( "250_hc18.p2", 0x100000, 0x400000, CRC(91e82e00) SHA1(402790a5f99d4909d472b3ca45c8a27bf36c5de6) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc19 ) //mslugx2r
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc19.p1", 0x000000, 0x100000, CRC(721f11aa) SHA1(49c4c5f86f37d0e33a0ece707608de2ca1855be2) )
	ROM_LOAD16_WORD_SWAP( "250_hc19.p2", 0x100000, 0x400000, CRC(4f875278) SHA1(ca6e474171e8bebc63033c883a8acfbfbce43f28) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc20 ) //mslugxc1
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc20.p1", 0x000000, 0x100000, CRC(e74f36c2) SHA1(b17d66f36e6ac31433179566ea07a0ed8790b161) )
	ROM_LOAD16_WORD_SWAP( "250_hc20.p2", 0x100000, 0x400000, CRC(e954b8aa) SHA1(b339b1fd05d50ac3a9d3992bb0fc8e3fd1a95557) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc21 ) //mslugxmax+ 
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc06.p1", 0x000000, 0x100000, CRC(a507546f) SHA1(ab6e9e969c2b3728cb0b13e0b1d62bda09037ac0) )
	ROM_LOAD16_WORD_SWAP( "250_hc21.p2", 0x100000, 0x400000, CRC(9cf91e0f) SHA1(ed094f66d5b3e231ceb709bd578b47ce436709fe) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc22 ) //mslugx2reb
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc22.p1", 0x000000, 0x100000, CRC(dba3f1a1) SHA1(2d2a5b67bb1b23470d032dbcb6bd454a4ff86da7) )
	ROM_LOAD16_WORD_SWAP( "250_hc22.p2", 0x100000, 0x400000, CRC(3866eb68) SHA1(38fb15f428388a17c70841fea9d1503dad710c90) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc23 ) //mslugx2r1v2
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc23.p1", 0x000000, 0x100000, CRC(d13fd368) SHA1(ea2d8a78c23090ba0424ad41fcc9935bc1dcf277) )
	ROM_LOAD16_WORD_SWAP( "250_hc23.p2", 0x100000, 0x400000, CRC(730e94a2) SHA1(590b5950bce33b24122dcad99c91d9bc436d16d7) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc24 ) //mslugxdd
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc24.p1", 0x000000, 0x100000, CRC(aa09586a) SHA1(246579b58babcf696f988a2d57dc8fab0019b3de) )
	ROM_LOAD16_WORD_SWAP( "250_hc24.p2", 0x100000, 0x400000, CRC(1791d721) SHA1(cdc6231f1fde1eef90c51ef9a5c22e900055c3f5) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGXDD_SPRITES
ROM_END

ROM_START( mslugxhc25 ) //mslugxscb
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc25.p1", 0x000000, 0x100000, CRC(e0792609) SHA1(e98096a5ad7181e95cf544cd345693599ecce08a) )
	ROM_LOAD16_WORD_SWAP( "250_hc25.p2", 0x100000, 0x400000, CRC(01f48336) SHA1(a5c42ca203427bfd978df8119aa4f0306d074d47) )
    MSLUGXSC_ESSENTIALPATCH_MODS_FILL
    MSLUGXSC_MVS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
    AUDIOBIOS_128K
    MSLUGXSC_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXCQ_SPRITES
ROM_END

ROM_START( mslugxhc26 ) //mslugxdg
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc26.p1", 0x000000, 0x100000, CRC(f86ea146) SHA1(c30a69749da8b0bda5231ac4e121dd90a65d0a96) )
	ROM_LOAD16_WORD_SWAP( "250_hc26.p2", 0x100000, 0x400000, CRC(ef0c263f) SHA1(5348c842970fe0226455a24ca52e1d7419e77420) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGXDD_SPRITES
ROM_END

ROM_START( mslugxhc27 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc27.p1", 0x000000, 0x100000, CRC(27d836c8) SHA1(4b110e1f1094cea607914156c69298017153a9d8) )
	ROM_LOAD16_WORD_SWAP( "250.p2", 0x100000, 0x400000, CRC(1fda2e12) SHA1(18aaa7a3ba8da99f78c430e9be69ccde04bc04d9) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc28 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc28.p1", 0x000000, 0x100000, CRC(5836f4d7) SHA1(002c6a519c118d33e3cef92066b0e8fc96f52627) )
	ROM_LOAD16_WORD_SWAP( "250_hc28.p2", 0x100000, 0x400000, CRC(9033c16c) SHA1(13336d2d9a042973dd744966c37a0a3d5f574808) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
    FIX_BIOS_COIN_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc29 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc29.p1", 0x000000, 0x100000, CRC(a3764c51) SHA1(791e23b6953aba236fe18182efa7445291c991ba) )
	ROM_LOAD16_WORD_SWAP( "250.p2",      0x100000, 0x400000, CRC(1fda2e12) SHA1(18aaa7a3ba8da99f78c430e9be69ccde04bc04d9) )
    MSLUGXV_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc30 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc30.p1", 0x000000, 0x100000, CRC(d8834fcc) SHA1(2391af1873d33b49452fa5178c568bbd7154aaef) )
	ROM_LOAD16_WORD_SWAP( "250.p2",      0x100000, 0x400000, CRC(1fda2e12) SHA1(18aaa7a3ba8da99f78c430e9be69ccde04bc04d9) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGXFR_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGXFR_SPRITES
ROM_END

ROM_START( mslugxhc31 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc31.p1", 0x000000, 0x100000, CRC(f3e154ea) SHA1(bb8260deefa7b048772625085e6f41cab717a147) )
	ROM_LOAD16_WORD_SWAP( "250.p2",      0x100000, 0x400000, CRC(1fda2e12) SHA1(18aaa7a3ba8da99f78c430e9be69ccde04bc04d9) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc32 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc32.p1", 0x000000, 0x100000, CRC(a7edd6ea) SHA1(d0bca9bbcfd1458ed9777b319b92fd1ebf9e5a89) )
	ROM_LOAD16_WORD_SWAP( "250.p2",      0x100000, 0x400000, CRC(1fda2e12) SHA1(18aaa7a3ba8da99f78c430e9be69ccde04bc04d9) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc33 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc33.p1", 0x000000, 0x100000, CRC(971f8454) SHA1(73033339931de870bb5a5a64f34ce51c63c4ed15) )
	ROM_LOAD16_WORD_SWAP( "250.p2",      0x100000, 0x400000, CRC(1fda2e12) SHA1(18aaa7a3ba8da99f78c430e9be69ccde04bc04d9) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxhc34 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc34.p1", 0x000000, 0x100000, CRC(540ef88a) SHA1(4a2bab7359fc54760a8fb2dfc6fc8ed9b7b9e5a3) )
	ROM_LOAD16_WORD_SWAP( "250_hc34.p2", 0x100000, 0x400000, CRC(8082b833) SHA1(78d381950bb08b51a911a72b1a1c9f14823911d1) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

 /*********
  HomeBrew
************/

ROM_START( mslug3x )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hb.p1", 0x000000, 0x200000, CRC(64f596c5) SHA1(22423abd7688ceda121ccdc67505acb37921a563) )
	MSLUG3X_SFIX_MT_128K
    MSLUG3X_AUDIO_128K
    MSLUG3X_YMSND
    MSLUG3X_SPRITES
ROM_END

ROM_START( neopang )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hwneo.p1", 0x000000, 0x080000, CRC(dc5922ee) SHA1(08804fa9894b7e84375300acbdec8ea6829575d0) )
	NEOPANG_SFIX_64K
    NEOPANG_AUDIO_128K
    NEOPANG_YMSND
    NEOPANG_SPRITES
ROM_END


 /**************
 Only exclusive
*****************/
/*********************************************************************************
* This game sector is exclusive, its modifications that load have been customized
  241.p1 and 241.p2 files. Therefore, a unique and distinctive game will be displayed 
  from the rest, we have been working to Optimize performance and avoid any type of crash 
  that occurs during the game. This it just means there are some details of the roms that 
  still need to be improved, things to add and things that could later be updated or 
  permanently removed if some kind a problem is detected that cannot be solved ...
********************************************************************************************/
/*********************************************************************************************
* They are the first hack remix roms that I have made in a basic way for the HBMAME emulator.
**************************************************************************************************/
/***************
 Version Custom
*****************/

ROM_START( mslugctma01 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cma01.p1", 0x100000, 0x100000, CRC(47296de5) SHA1(36d939767547e5f0fa6f09098b5acf375a49300a) )
	ROM_CONTINUE( 0x000000, 0x100000 )
    MSLUG_ESSENTIALPATCH_MODS_FILL
    MSLUG_MVS_FILL
    MSLUG_AES_FILL
	MSLUG_SFIX_128K
	MSLUG_AUDIO_128K
    MSLUG_YMSND
    MSLUG_SPRITES
ROM_END

ROM_START( mslugctma02 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cma02.p1", 0x100000, 0x100000, CRC(9bb05912) SHA1(3712a163cf5465ba438a04d7d0cf18e1056860fe) )
	ROM_CONTINUE( 0x000000, 0x100000 )
    MSLUG_ESSENTIALPATCH_MODS_FILL
    MSLUG_MVS_FILL
    MSLUG_AES_FILL
	MSLUG_SFIX_128K
	MSLUG_AUDIO_128K
    MSLUG_YMSND
    MSLUG_SPRITES
ROM_END

ROM_START( mslugctma03 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cma03.p1", 0x100000, 0x100000, CRC(634af5ea) SHA1(590fe6d71484ead8947c56c1f380a2871ffe6023) )
	ROM_CONTINUE( 0x000000, 0x100000 )
    MSLUG_ESSENTIALPATCH_MODS_FILL
    MSLUG_MVS_FILL
    MSLUG_AES_FILL
	MSLUG_SFIX_128K
	MSLUG_AUDIO_128K
    MSLUG_YMSND
    MSLUG_SPRITES
ROM_END

ROM_START( mslugctma04 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cma04.p1", 0x100000, 0x100000, CRC(7f6c7da2) SHA1(a0aaaf1620afda351791f8c638a10da5dcbb7b2f) )
	ROM_CONTINUE( 0x000000, 0x100000 )
    MSLUG_ESSENTIALPATCH_MODS_FILL
    MSLUG_MVS_FILL
    MSLUG_AES_FILL
	MSLUG_SFIX_128K
	MSLUG_AUDIO_128K
    MSLUG_YMSND
    MSLUG_SPRITES
ROM_END

ROM_START( mslugctma05 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cma05.p1", 0x100000, 0x100000, CRC(49b57bd6) SHA1(c40a57092250b648fd814b5c2553f958e2c38936) )
	ROM_CONTINUE( 0x000000, 0x100000 )
    MSLUG_ESSENTIALPATCH_MODS_FILL
    MSLUG_MVS_FILL
    MSLUG_AES_FILL
	MSLUG_SFIX_128K
	MSLUG_AUDIO_128K
    MSLUG_YMSND
    MSLUG_SPRITES
ROM_END

ROM_START( mslugctma06 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cma06.p1", 0x100000, 0x100000, CRC(0b23c103) SHA1(fb546d1fdc7a1f8e843850a7a96c54fc5622f2b4) )
	ROM_CONTINUE( 0x000000, 0x100000 )
    MSLUG_ESSENTIALPATCH_MODS_FILL
    MSLUG_MVS_FILL
    MSLUG_AES_FILL
	MSLUG_SFIX_128K
	MSLUG_AUDIO_128K
    MSLUG_YMSND
    MSLUG_SPRITES
ROM_END

ROM_START( mslugctma07 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cma07.p1", 0x100000, 0x100000, CRC(29960cbb) SHA1(f292b1544c2ac106af1db9cf65f06a8b2cd8cbc1) )
	ROM_CONTINUE( 0x000000, 0x100000 )
    MSLUG_ESSENTIALPATCH_MODS_FILL
    MSLUG_MVS_FILL
    MSLUG_AES_FILL
	MSLUG_SFIX_128K
	MSLUG_AUDIO_128K
    MSLUG_YMSND
    MSLUG_SPRITES
ROM_END

ROM_START( mslug2ctma01 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmb01.p1", 0x000000, 0x100000, CRC(9c2229a1) SHA1(2cfab43389fdb44f74da4d5a01a9042c838f0a2b) )
	ROM_LOAD16_WORD_SWAP( "241_hc10.p2",  0x100000, 0x200000, CRC(fe36f353) SHA1(61df20c7cd9f904552ec672dec11b679122bc5fe) )
    MSLUG2_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
	MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2ctma02 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmb02.p1", 0x000000, 0x100000, CRC(154c5d3e) SHA1(576aa91c42b877b181eb681bac010705f6a67d56) )
	ROM_LOAD16_WORD_SWAP( "241_hc09.p2",  0x100000, 0x200000, CRC(1bf6b12a) SHA1(bdf1cee93c7cf1e57f61797ed4f176fe2a6ebf73) )
    MSLUG2_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
	MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2ctma03 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmb03.p1", 0x000000, 0x100000, CRC(29910e9b) SHA1(7521f21c92cd7aa71aeb4b90781a1b427e6e268d) )
	ROM_LOAD16_WORD_SWAP( "241.p2",       0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
	MSLUG2_AES_FILL
	MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2ctma04 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmb04.p1", 0x000000, 0x100000, CRC(ccac4851) SHA1(e715cae868e538ec62a4bde50b30fb44cfb831af) )
	ROM_LOAD16_WORD_SWAP( "241.p2",       0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
	MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2ctma05 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmb05.p1", 0x000000, 0x100000, CRC(89bfdf04) SHA1(ae62219a1b799fe001ffd3eb9e581dc47833b398) )
	ROM_LOAD16_WORD_SWAP( "241.p2",       0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
	MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2ctma06 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmb06.p1", 0x000000, 0x100000, CRC(13fc86ae) SHA1(9d8623ced6f412b922b4232ee587979028defe10) )
	ROM_LOAD16_WORD_SWAP( "241.p2",       0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
    MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2ctma07 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmb07.p1", 0x000000, 0x100000, CRC(1a0f7641) SHA1(5f96f51c28b4fb2f8a4a66339ef45fce7eb533ce) )
	ROM_LOAD16_WORD_SWAP( "241.p2",       0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
    MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2ctma08 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmb08.p1", 0x000000, 0x100000, CRC(32bd7592) SHA1(d369a9b6b21c93afc66431aa11d05e0869bdef55) )
	ROM_LOAD16_WORD_SWAP( "241.p2",       0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
    MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2ctma09 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmb09.p1", 0x000000, 0x100000, CRC(712d78f9) SHA1(39420ab087251179b89ef96da0e0509b5165650f) )
	ROM_LOAD16_WORD_SWAP( "241_hc14.p2",  0x100000, 0x200000, CRC(37a118fc) SHA1(37c913c3d6736362ad83b8aaadf94b9112669a52) )
    MSLUG2_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
    MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2ctma10 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmb10.p1", 0x000000, 0x100000, CRC(121dfef9) SHA1(e7c244256ebb5d3b41f3ebe48bf356a0898604c4) )
	ROM_LOAD16_WORD_SWAP( "241.p2",       0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
	MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2ctma11 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmb11.p1", 0x000000, 0x100000, CRC(575f57d5) SHA1(d032701aaf6f880672917f7925d9b6659808a2d2) )
	ROM_LOAD16_WORD_SWAP( "241.p2",       0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
	MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2ctma12 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmb12.p1", 0x000000, 0x100000, CRC(3eadbcf7) SHA1(58efde4f5bf8afe00942c232dab747919edb279a) )
	ROM_LOAD16_WORD_SWAP( "241_hc15.p2",  0x100000, 0x200000, CRC(89adbf97) SHA1(98b5382d51c7fd0b5ad52dd9649ef847a163a78a) )
    MSLUG2_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
    MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2DD_SPRITES
ROM_END

 /* It is very conflictive to impose a modification to this roms hack, since there are usually crashes for all of them, the Address Error codes vary */
ROM_START( mslug2ctma13 )
	ROM_REGION( 0x400000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmb13.p1", 0x000000, 0x100000, CRC(aab0c2a7) SHA1(8501f543ec2a26a870195ead3dd531133390f203) )
	ROM_LOAD16_WORD_SWAP( "241_hc05.p2",  0x100000, 0x300000, CRC(abf37360) SHA1(09347f0502fba4965dc14fd6db89bb3cabdeea1f) )
//  MSLUG2_ESSENTIALPATCH_MODS_FILL
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
	MSLUG2EG_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2EG_SPRITES
ROM_END

ROM_START( mslug3ctma01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc03.p1",  0x000000, 0x100000, CRC(b23bd9b7) SHA1(4a5e877bc0d4853dc9c5a2c179049fbdd5285239) )
	ROM_LOAD16_WORD_SWAP( "256_cma01.p2", 0x100000, 0x400000, CRC(bff515b4) SHA1(660f9d618b7bae50a05d9b6119ad57ea3bbb2a74) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
    AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3_AUDIOBIOS_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctma02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc10.p1", 0x000000, 0x100000, CRC(fafde0b4) SHA1(3eee501ddebda761d93c49cdea135fdf0aa0dc9c) )
	ROM_LOAD16_WORD_SWAP( "256_hc19.p2", 0x100000, 0x400000, CRC(b948a472) SHA1(e0135911f7d7e21285e6965cc6b4446277eea405) )
    MSLUG3GW_FIX_FILL
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3GW_AUDIO_512K
    MSLUG3GW_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctma03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cma03.p1", 0x000000, 0x100000, CRC(baa909c0) SHA1(f77d95b54051b2e5bf7e8c22768c045687c2ee97) )
	ROM_LOAD16_WORD_SWAP( "256_cma03.p2", 0x100000, 0x400000, CRC(f04b52fe) SHA1(e5233b0fc3b7d5ec8f7820fc3d307fb071cf1891) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctma04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc06.p1",  0x000000, 0x100000, CRC(e1e21cc4) SHA1(c70ef18dfe8edbadadff6004508e838b246b88a5) )
	ROM_LOAD16_WORD_SWAP( "256_cma04.p2", 0x100000, 0x400000, CRC(d5361bc1) SHA1(33f3274a17a010322d5cc6a182c422bf89f9ac05) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctma05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc09.p1", 0x000000, 0x100000, CRC(4e6753ee) SHA1(2df01bda8ed450761c5ed24a9ef1a4dfe324ab08) )
	ROM_LOAD16_WORD_SWAP( "256_hc19.p2", 0x100000, 0x400000, CRC(b948a472) SHA1(e0135911f7d7e21285e6965cc6b4446277eea405) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3WZ_FIX_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctma06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc02.p1", 0x000000, 0x100000, CRC(b981e587) SHA1(7e193b1e73fe4e921d5809f942df2da41f34d177) )
	ROM_LOAD16_WORD_SWAP( "256_hc19.p2", 0x100000, 0x400000, CRC(b948a472) SHA1(e0135911f7d7e21285e6965cc6b4446277eea405) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctma07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc01.p1", 0x000000, 0x100000, CRC(e04c6624) SHA1(de684f346ab9a2e5730a6753de6d53801a702cc8) )
	ROM_LOAD16_WORD_SWAP( "256_hc19.p2", 0x100000, 0x400000, CRC(b948a472) SHA1(e0135911f7d7e21285e6965cc6b4446277eea405) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctma08 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc31.p1", 0x000000, 0x100000, CRC(47f9aeea) SHA1(db1c65681ac12b146e2fa21a8f28000f41a11fe2) )
	ROM_LOAD16_WORD_SWAP( "256_hc19.p2", 0x100000, 0x400000, CRC(b948a472) SHA1(e0135911f7d7e21285e6965cc6b4446277eea405) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctma09 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc12.p1",  0x000000, 0x100000, CRC(caac7e33) SHA1(098505f23e3a56e2e0cc0ae855e2457061138c9e) )
	ROM_LOAD16_WORD_SWAP( "256_cma09.p2", 0x100000, 0x400000, CRC(7941558c) SHA1(29cb4e8589ae252ff77a2e41247aa7b7a46bb3e6) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3GW_AUDIO_512K
    MSLUG3GW_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctma10 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc18.p1", 0x000000, 0x100000, CRC(6ea79265) SHA1(1930a3ff1260d56fdc7559bd5bb56f0ca5479588) )
	ROM_LOAD16_WORD_SWAP( "256_hc19.p2", 0x100000, 0x400000, CRC(b948a472) SHA1(e0135911f7d7e21285e6965cc6b4446277eea405) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctma11 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc23.p1", 0x000000, 0x100000, CRC(ec09383d) SHA1(6574976d540b776c6c1db0dbacc9c9e084207324) )
	ROM_LOAD16_WORD_SWAP( "256_hc19.p2", 0x100000, 0x400000, CRC(b948a472) SHA1(e0135911f7d7e21285e6965cc6b4446277eea405) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctma12 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc36.p1", 0x000000, 0x100000, CRC(380d190c) SHA1(45abe6f04ac16be7b168d9334bfc858525379733) )
	ROM_LOAD16_WORD_SWAP( "256_hc19.p2", 0x100000, 0x400000, CRC(b948a472) SHA1(e0135911f7d7e21285e6965cc6b4446277eea405) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctma13 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc35.p1", 0x000000, 0x100000, CRC(f77edb2a) SHA1(825ebda68220217d56ac2f4e1a21805066800b61) )
	ROM_LOAD16_WORD_SWAP( "256_hc19.p2", 0x100000, 0x400000, CRC(b948a472) SHA1(e0135911f7d7e21285e6965cc6b4446277eea405) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctma14 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc13.p1", 0x000000, 0x100000, CRC(ea7d570f) SHA1(d2419b96347f75fdd386880bc5eaa5766fe07b0c) )
	ROM_LOAD16_WORD_SWAP( "256_hc19.p2", 0x100000, 0x400000, CRC(b948a472) SHA1(e0135911f7d7e21285e6965cc6b4446277eea405) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctma15 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc26.p1",  0x000000, 0x100000, CRC(9a83cb7a) SHA1(07f2c4602d7c4cc011a5271d39af92a329fbcff0) )
	ROM_LOAD16_WORD_SWAP( "256_cma15.p2", 0x100000, 0x400000, CRC(4e5ae8e0) SHA1(136f72c00cfe849786036e62409b3f53aa41b5ac) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3DD_SPRITES
ROM_END

ROM_START( mslug3ctmb01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc03.p1",  0x000000, 0x100000, CRC(b23bd9b7) SHA1(4a5e877bc0d4853dc9c5a2c179049fbdd5285239) )
	ROM_LOAD16_WORD_SWAP( "256_cmb01.p2", 0x100000, 0x400000, CRC(1529de61) SHA1(8db6a9856f236693071e74e664f2d819355ae180) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
    AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3_AUDIOBIOS_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmb02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc10.p1", 0x000000, 0x100000, CRC(fafde0b4) SHA1(3eee501ddebda761d93c49cdea135fdf0aa0dc9c) )
	ROM_LOAD16_WORD_SWAP( "256_hc15.p2", 0x100000, 0x400000, CRC(d53d178c) SHA1(98f0cd74b18d0d63b74fd6d3830548f4c2ce401b) )
    MSLUG3GW_FIX_FILL
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3GW_AUDIO_512K
    MSLUG3GW_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmb03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc08.p1",  0x000000, 0x100000, CRC(257fa6b9) SHA1(c9ccc0a42a5a34a08316a76dc977ccee74d91245) )
	ROM_LOAD16_WORD_SWAP( "256_cmb03.p2", 0x100000, 0x400000, CRC(05d94adb) SHA1(678957b8ceca1bec15e5f21d5b24f0bb82966a17) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmb04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc06.p1",  0x000000, 0x100000, CRC(e1e21cc4) SHA1(c70ef18dfe8edbadadff6004508e838b246b88a5) )
	ROM_LOAD16_WORD_SWAP( "256_cmb04.p2", 0x100000, 0x400000, CRC(7b6dba83) SHA1(613b692b1707399ad886ea1dca4746834ee29dd0) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmb05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc09.p1", 0x000000, 0x100000, CRC(4e6753ee) SHA1(2df01bda8ed450761c5ed24a9ef1a4dfe324ab08) )
	ROM_LOAD16_WORD_SWAP( "256_hc15.p2", 0x100000, 0x400000, CRC(d53d178c) SHA1(98f0cd74b18d0d63b74fd6d3830548f4c2ce401b) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3WZ_FIX_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmb06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc02.p1", 0x000000, 0x100000, CRC(b981e587) SHA1(7e193b1e73fe4e921d5809f942df2da41f34d177) )
	ROM_LOAD16_WORD_SWAP( "256_hc15.p2", 0x100000, 0x400000, CRC(d53d178c) SHA1(98f0cd74b18d0d63b74fd6d3830548f4c2ce401b) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmb07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc01.p1", 0x000000, 0x100000, CRC(e04c6624) SHA1(de684f346ab9a2e5730a6753de6d53801a702cc8) )
	ROM_LOAD16_WORD_SWAP( "256_hc15.p2", 0x100000, 0x400000, CRC(d53d178c) SHA1(98f0cd74b18d0d63b74fd6d3830548f4c2ce401b) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmb08 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc31.p1", 0x000000, 0x100000, CRC(47f9aeea) SHA1(db1c65681ac12b146e2fa21a8f28000f41a11fe2) )
	ROM_LOAD16_WORD_SWAP( "256_hc15.p2", 0x100000, 0x400000, CRC(d53d178c) SHA1(98f0cd74b18d0d63b74fd6d3830548f4c2ce401b) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmb09 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc12.p1",  0x000000, 0x100000, CRC(caac7e33) SHA1(098505f23e3a56e2e0cc0ae855e2457061138c9e) )
	ROM_LOAD16_WORD_SWAP( "256_cmb09.p2", 0x100000, 0x400000, CRC(1534e672) SHA1(b2a20513f9e0e8df798c741e63dcf8c2412dc76a) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3GW_AUDIO_512K
    MSLUG3GW_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmb10 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc18.p1", 0x000000, 0x100000, CRC(6ea79265) SHA1(1930a3ff1260d56fdc7559bd5bb56f0ca5479588) )
	ROM_LOAD16_WORD_SWAP( "256_hc15.p2", 0x100000, 0x400000, CRC(d53d178c) SHA1(98f0cd74b18d0d63b74fd6d3830548f4c2ce401b) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmb11 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc23.p1", 0x000000, 0x100000, CRC(ec09383d) SHA1(6574976d540b776c6c1db0dbacc9c9e084207324) )
	ROM_LOAD16_WORD_SWAP( "256_hc15.p2", 0x100000, 0x400000, CRC(d53d178c) SHA1(98f0cd74b18d0d63b74fd6d3830548f4c2ce401b) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmb12 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc36.p1", 0x000000, 0x100000, CRC(380d190c) SHA1(45abe6f04ac16be7b168d9334bfc858525379733) )
	ROM_LOAD16_WORD_SWAP( "256_hc15.p2", 0x100000, 0x400000, CRC(d53d178c) SHA1(98f0cd74b18d0d63b74fd6d3830548f4c2ce401b) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmb13 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc35.p1", 0x000000, 0x100000, CRC(f77edb2a) SHA1(825ebda68220217d56ac2f4e1a21805066800b61) )
	ROM_LOAD16_WORD_SWAP( "256_hc15.p2", 0x100000, 0x400000, CRC(d53d178c) SHA1(98f0cd74b18d0d63b74fd6d3830548f4c2ce401b) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmb14 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc13.p1", 0x000000, 0x100000, CRC(ea7d570f) SHA1(d2419b96347f75fdd386880bc5eaa5766fe07b0c) )
	ROM_LOAD16_WORD_SWAP( "256_hc15.p2", 0x100000, 0x400000, CRC(d53d178c) SHA1(98f0cd74b18d0d63b74fd6d3830548f4c2ce401b) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmb15 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc26.p1",  0x000000, 0x100000, CRC(9a83cb7a) SHA1(07f2c4602d7c4cc011a5271d39af92a329fbcff0) )
	ROM_LOAD16_WORD_SWAP( "256_cmb15.p2", 0x100000, 0x400000, CRC(222f5b1e) SHA1(a8513d3e3f0de3af4fe05d66bd92872c90008abe) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3DD_SPRITES
ROM_END

ROM_START( mslug3ctmc01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc03.p1",  0x000000, 0x100000, CRC(b23bd9b7) SHA1(4a5e877bc0d4853dc9c5a2c179049fbdd5285239) )
	ROM_LOAD16_WORD_SWAP( "256_cmc01.p2", 0x100000, 0x400000, CRC(2f63ffe5) SHA1(ebd1b25b45cea79d7d5dcc6855997c2d8bece250) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
    AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3_AUDIOBIOS_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmc02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc10.p1", 0x000000, 0x100000, CRC(fafde0b4) SHA1(3eee501ddebda761d93c49cdea135fdf0aa0dc9c) )
	ROM_LOAD16_WORD_SWAP( "256_hc11.p2", 0x100000, 0x400000, CRC(29de4e23) SHA1(1591403b39ecadd33380020e9f801688ed996e94) )
    MSLUG3GW_FIX_FILL
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3GW_AUDIO_512K
    MSLUG3GW_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmc03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cma03.p1", 0x000000, 0x100000, CRC(baa909c0) SHA1(f77d95b54051b2e5bf7e8c22768c045687c2ee97) )
	ROM_LOAD16_WORD_SWAP( "256_cmc03.p2", 0x100000, 0x400000, CRC(60ddb8af) SHA1(5734ab45d517cc86056b83c4d36c62cc706332a4) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmc04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc06.p1",  0x000000, 0x100000, CRC(e1e21cc4) SHA1(c70ef18dfe8edbadadff6004508e838b246b88a5) )
	ROM_LOAD16_WORD_SWAP( "256_cmc04.p2", 0x100000, 0x400000, CRC(45a0f190) SHA1(6a612da618c18fb42879fd524a2a061a955d3743) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmc05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc09.p1", 0x000000, 0x100000, CRC(4e6753ee) SHA1(2df01bda8ed450761c5ed24a9ef1a4dfe324ab08) )
	ROM_LOAD16_WORD_SWAP( "256_hc11.p2", 0x100000, 0x400000, CRC(29de4e23) SHA1(1591403b39ecadd33380020e9f801688ed996e94) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3WZ_FIX_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmc06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc02.p1", 0x000000, 0x100000, CRC(b981e587) SHA1(7e193b1e73fe4e921d5809f942df2da41f34d177) )
	ROM_LOAD16_WORD_SWAP( "256_hc11.p2", 0x100000, 0x400000, CRC(29de4e23) SHA1(1591403b39ecadd33380020e9f801688ed996e94) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmc07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc01.p1", 0x000000, 0x100000, CRC(e04c6624) SHA1(de684f346ab9a2e5730a6753de6d53801a702cc8) )
	ROM_LOAD16_WORD_SWAP( "256_hc11.p2", 0x100000, 0x400000, CRC(29de4e23) SHA1(1591403b39ecadd33380020e9f801688ed996e94) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmc08 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc31.p1", 0x000000, 0x100000, CRC(47f9aeea) SHA1(db1c65681ac12b146e2fa21a8f28000f41a11fe2) )
	ROM_LOAD16_WORD_SWAP( "256_hc11.p2", 0x100000, 0x400000, CRC(29de4e23) SHA1(1591403b39ecadd33380020e9f801688ed996e94) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmc09 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc12.p1",  0x000000, 0x100000, CRC(caac7e33) SHA1(098505f23e3a56e2e0cc0ae855e2457061138c9e) )
	ROM_LOAD16_WORD_SWAP( "256_cmc09.p2", 0x100000, 0x400000, CRC(e9d7bfdd) SHA1(99b8b2a1a800e07b9f2d6798b01435a0cf748ef1) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3GW_AUDIO_512K
    MSLUG3GW_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmc10 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc18.p1", 0x000000, 0x100000, CRC(6ea79265) SHA1(1930a3ff1260d56fdc7559bd5bb56f0ca5479588) )
	ROM_LOAD16_WORD_SWAP( "256_hc11.p2", 0x100000, 0x400000, CRC(29de4e23) SHA1(1591403b39ecadd33380020e9f801688ed996e94) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmc11 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc23.p1", 0x000000, 0x100000, CRC(ec09383d) SHA1(6574976d540b776c6c1db0dbacc9c9e084207324) )
	ROM_LOAD16_WORD_SWAP( "256_hc11.p2", 0x100000, 0x400000, CRC(29de4e23) SHA1(1591403b39ecadd33380020e9f801688ed996e94) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmc12 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc36.p1", 0x000000, 0x100000, CRC(380d190c) SHA1(45abe6f04ac16be7b168d9334bfc858525379733) )
	ROM_LOAD16_WORD_SWAP( "256_hc11.p2", 0x100000, 0x400000, CRC(29de4e23) SHA1(1591403b39ecadd33380020e9f801688ed996e94) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmc13 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc35.p1", 0x000000, 0x100000, CRC(f77edb2a) SHA1(825ebda68220217d56ac2f4e1a21805066800b61) )
	ROM_LOAD16_WORD_SWAP( "256_hc11.p2", 0x100000, 0x400000, CRC(29de4e23) SHA1(1591403b39ecadd33380020e9f801688ed996e94) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmc14 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc13.p1", 0x000000, 0x100000, CRC(ea7d570f) SHA1(d2419b96347f75fdd386880bc5eaa5766fe07b0c) )
	ROM_LOAD16_WORD_SWAP( "256_hc11.p2", 0x100000, 0x400000, CRC(29de4e23) SHA1(1591403b39ecadd33380020e9f801688ed996e94) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmc15 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc26.p1",  0x000000, 0x100000, CRC(9a83cb7a) SHA1(07f2c4602d7c4cc011a5271d39af92a329fbcff0) )
	ROM_LOAD16_WORD_SWAP( "256_cmc15.p2", 0x100000, 0x400000, CRC(decc02b1) SHA1(4960e1893be6ae0fbe00fd344e0fe4412c19c4e4) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3DD_SPRITES
ROM_END

ROM_START( mslug3ctmd01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc03.p1",  0x000000, 0x100000, CRC(b23bd9b7) SHA1(4a5e877bc0d4853dc9c5a2c179049fbdd5285239) )
	ROM_LOAD16_WORD_SWAP( "256_cmd01.p2", 0x100000, 0x400000, CRC(f3e17a55) SHA1(97ecb7c59e019b4a347b54d3b7e8f5e94891ca6e) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
    AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3_AUDIOBIOS_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmd02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc10.p1", 0x000000, 0x100000, CRC(fafde0b4) SHA1(3eee501ddebda761d93c49cdea135fdf0aa0dc9c) )
	ROM_LOAD16_WORD_SWAP( "256_hc16.p2", 0x100000, 0x400000, CRC(f55ccb93) SHA1(c52e83c848ba63ca0323aa99f85e8278b6fe4cda) )
    MSLUG3GW_FIX_FILL
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3GW_AUDIO_512K
    MSLUG3GW_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmd03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc08.p1",  0x000000, 0x100000, CRC(257fa6b9) SHA1(c9ccc0a42a5a34a08316a76dc977ccee74d91245) )
	ROM_LOAD16_WORD_SWAP( "256_cmd03.p2", 0x100000, 0x400000, CRC(bc5f3d1f) SHA1(8e03e780f7831f59bfb90389a7ce02a86b6e662e) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmd04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc06.p1",  0x000000, 0x100000, CRC(e1e21cc4) SHA1(c70ef18dfe8edbadadff6004508e838b246b88a5) )
	ROM_LOAD16_WORD_SWAP( "256_cmd04.p2", 0x100000, 0x400000, CRC(99227420) SHA1(d509cd4422a1d1cff3b2bb5a4cc726b73e851fb3) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmd05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc09.p1", 0x000000, 0x100000, CRC(4e6753ee) SHA1(2df01bda8ed450761c5ed24a9ef1a4dfe324ab08) )
	ROM_LOAD16_WORD_SWAP( "256_hc16.p2", 0x100000, 0x400000, CRC(f55ccb93) SHA1(c52e83c848ba63ca0323aa99f85e8278b6fe4cda) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3WZ_FIX_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmd06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc02.p1", 0x000000, 0x100000, CRC(b981e587) SHA1(7e193b1e73fe4e921d5809f942df2da41f34d177) )
	ROM_LOAD16_WORD_SWAP( "256_hc16.p2", 0x100000, 0x400000, CRC(f55ccb93) SHA1(c52e83c848ba63ca0323aa99f85e8278b6fe4cda) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmd07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc01.p1", 0x000000, 0x100000, CRC(e04c6624) SHA1(de684f346ab9a2e5730a6753de6d53801a702cc8) )
	ROM_LOAD16_WORD_SWAP( "256_hc16.p2", 0x100000, 0x400000, CRC(f55ccb93) SHA1(c52e83c848ba63ca0323aa99f85e8278b6fe4cda) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmd08 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc31.p1", 0x000000, 0x100000, CRC(47f9aeea) SHA1(db1c65681ac12b146e2fa21a8f28000f41a11fe2) )
	ROM_LOAD16_WORD_SWAP( "256_hc16.p2", 0x100000, 0x400000, CRC(f55ccb93) SHA1(c52e83c848ba63ca0323aa99f85e8278b6fe4cda) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmd09 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc12.p1",  0x000000, 0x100000, CRC(caac7e33) SHA1(098505f23e3a56e2e0cc0ae855e2457061138c9e) )
	ROM_LOAD16_WORD_SWAP( "256_cmd09.p2", 0x100000, 0x400000, CRC(35553a6d) SHA1(862c48cf5d62c52a768ed9efc1cb52aa3f9be002) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3GW_AUDIO_512K
    MSLUG3GW_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmd10 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc18.p1", 0x000000, 0x100000, CRC(6ea79265) SHA1(1930a3ff1260d56fdc7559bd5bb56f0ca5479588) )
	ROM_LOAD16_WORD_SWAP( "256_hc16.p2", 0x100000, 0x400000, CRC(f55ccb93) SHA1(c52e83c848ba63ca0323aa99f85e8278b6fe4cda) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmd11 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc23.p1", 0x000000, 0x100000, CRC(ec09383d) SHA1(6574976d540b776c6c1db0dbacc9c9e084207324) )
	ROM_LOAD16_WORD_SWAP( "256_hc16.p2", 0x100000, 0x400000, CRC(f55ccb93) SHA1(c52e83c848ba63ca0323aa99f85e8278b6fe4cda) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmd12 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc36.p1", 0x000000, 0x100000, CRC(380d190c) SHA1(45abe6f04ac16be7b168d9334bfc858525379733) )
	ROM_LOAD16_WORD_SWAP( "256_hc16.p2", 0x100000, 0x400000, CRC(f55ccb93) SHA1(c52e83c848ba63ca0323aa99f85e8278b6fe4cda) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmd13 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc35.p1", 0x000000, 0x100000, CRC(f77edb2a) SHA1(825ebda68220217d56ac2f4e1a21805066800b61) )
	ROM_LOAD16_WORD_SWAP( "256_hc16.p2", 0x100000, 0x400000, CRC(f55ccb93) SHA1(c52e83c848ba63ca0323aa99f85e8278b6fe4cda) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmd14 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc13.p1", 0x000000, 0x100000, CRC(ea7d570f) SHA1(d2419b96347f75fdd386880bc5eaa5766fe07b0c) )
	ROM_LOAD16_WORD_SWAP( "256_hc16.p2", 0x100000, 0x400000, CRC(f55ccb93) SHA1(c52e83c848ba63ca0323aa99f85e8278b6fe4cda) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmd15 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_hc26.p1",  0x000000, 0x100000, CRC(9a83cb7a) SHA1(07f2c4602d7c4cc011a5271d39af92a329fbcff0) )
	ROM_LOAD16_WORD_SWAP( "256_cmd15.p2", 0x100000, 0x400000, CRC(024e8701) SHA1(eb99f4670305d29ce31e60febf788b6db96736b9) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3DD_SPRITES
ROM_END

ROM_START( mslug3ctme01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cme01.p1", 0x000000, 0x100000, CRC(2b4f11f6) SHA1(e7eec428c74046b6083e94a3a771d876ac0862b9) )
	ROM_LOAD16_WORD_SWAP( "256_cme01.p2", 0x100000, 0x400000, CRC(1d210b1e) SHA1(6a67cf8e02776ab6a4c03ca897426f4a2013598b) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
    AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3_AUDIOBIOS_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctme02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p1", 0x000000, 0x100000, CRC(41bf0d6d) SHA1(d78ef90b23c757ade259d13f1aa4f066ac5bd6e2) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3GW_FIX_FILL
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3GW_AUDIO_512K
    MSLUG3GW_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctme03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cme03.p1", 0x000000, 0x100000, CRC(fcbcc9d8) SHA1(37bda8af3457a72cb22f5a9b8ce47977edf7d50a) )
	ROM_LOAD16_WORD_SWAP( "256_cme03.p2", 0x100000, 0x400000, CRC(e0face27) SHA1(981b468b68e83ab9e2a4911650de7e49b3230c4b) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctme04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cme04.p1", 0x000000, 0x100000, CRC(a7f7dcdc) SHA1(a257e45d6c9432013318dfe73be0cfb6b82959c1) )
	ROM_LOAD16_WORD_SWAP( "256_cme04.p2", 0x100000, 0x400000, CRC(7fb4fcf4) SHA1(76d6b92b4862baa08037efa80d8b9e361f8d5e9f) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctme05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cme05.p1", 0x000000, 0x100000, CRC(087293f6) SHA1(bac11c8cbabfe300974d076b930940a707bf1a69) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3WZ_FIX_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctme06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cme06.p1", 0x000000, 0x100000, CRC(ff94259f) SHA1(872e143b035b7934713ed0c4e5d7ce9df3cf7e46) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctme07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cme07.p1", 0x000000, 0x100000, CRC(a659a63c) SHA1(e03a4930cbd0a06f465a01587d44e4feaefe5c20) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctme08 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cme08.p1", 0x000000, 0x100000, CRC(01ec6ef2) SHA1(baa3f658be451cd3bbe622250a03c19a8aa91673) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctme09 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cme09.p1", 0x000000, 0x100000, CRC(8cb9be2b) SHA1(b1d95058df37c7705f57fecbf00364da3036337b) )
	ROM_LOAD16_WORD_SWAP( "256_cme09.p2", 0x100000, 0x400000, CRC(69f0c955) SHA1(6bcc047d934432fb1616ec159133c8c2a276838b) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3GW_AUDIO_512K
    MSLUG3GW_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctme10 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cme10.p1", 0x000000, 0x100000, CRC(28b2527d) SHA1(995d5bcecdd387320ebab126a644526d946dc344) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctme11 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cme11.p1", 0x000000, 0x100000, CRC(aa1cf825) SHA1(4b17998fb5f255baf043e9d54afcd6d1df66281e) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctme12 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cme12.p1", 0x000000, 0x100000, CRC(7e18d914) SHA1(e079c7c93708d0ad315f6fcfbc693c021f57ffe8) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctme13 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cme13.p1", 0x000000, 0x100000, CRC(4fcb9d82) SHA1(26524613eb8e95e4f07ec2987683a8da17e130c3) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctme14 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cme14.p1", 0x000000, 0x100000, CRC(ac689717) SHA1(2c9ca19e55c4d07e90076853a722e3b92500e5d2) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmf01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmf01.p1", 0x000000, 0x100000, CRC(d5000c79) SHA1(5609d445302a7f7f741b9c321798c6ec078572c0) )
	ROM_LOAD16_WORD_SWAP( "256_cme01.p2", 0x100000, 0x400000, CRC(1d210b1e) SHA1(6a67cf8e02776ab6a4c03ca897426f4a2013598b) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
    AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3_AUDIOBIOS_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmf02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmf02.p1", 0x000000, 0x100000, CRC(bff010e2) SHA1(f8505abb55178ba6e3f84fbcab1d5260294301e0) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3GW_FIX_FILL
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3GW_AUDIO_512K
    MSLUG3GW_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmf03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmf03.p1", 0x000000, 0x100000, CRC(43954df9) SHA1(afdaf6f8b20423e6d8e075dd50730ad2e727d69d) )
	ROM_LOAD16_WORD_SWAP( "256_cme03.p2", 0x100000, 0x400000, CRC(e0face27) SHA1(981b468b68e83ab9e2a4911650de7e49b3230c4b) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmf04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmf04.p1", 0x000000, 0x100000, CRC(59b8c153) SHA1(865ef5863c8e6581d4c1556425a87e3e5a80c37c) )
	ROM_LOAD16_WORD_SWAP( "256_cme04.p2", 0x100000, 0x400000, CRC(7fb4fcf4) SHA1(76d6b92b4862baa08037efa80d8b9e361f8d5e9f) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmf05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmf05.p1", 0x000000, 0x100000, CRC(f63d8e79) SHA1(5975a576b78b3617044dc41da49e46c7958babcb) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3WZ_FIX_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmf06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmf06.p1", 0x000000, 0x100000, CRC(01db3810) SHA1(a59772b310236eaff4cf5c0a50c66219e26f741b) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmf07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmf07.p1", 0x000000, 0x100000, CRC(5816bbb3) SHA1(0eb80311b7cf5a67bb3d92cb26ecaf17f481c1be) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmf08 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmf08.p1", 0x000000, 0x100000, CRC(ffa3737d) SHA1(ec2d4fcd64f90e6174fa6aa6a92d5d6ec4788842) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmf09 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmf09.p1", 0x000000, 0x100000, CRC(33903a0a) SHA1(f38dbe93a272792137442c985d77dcb147c4eeea) )
	ROM_LOAD16_WORD_SWAP( "256_cme09.p2", 0x100000, 0x400000, CRC(69f0c955) SHA1(6bcc047d934432fb1616ec159133c8c2a276838b) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3GW_AUDIO_512K
    MSLUG3GW_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmf10 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmf10.p1", 0x000000, 0x100000, CRC(d6fd4ff2) SHA1(82890361e5c01ba7d5aabbf5fefa1db8c06d3c81) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmf11 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmf11.p1", 0x000000, 0x100000, CRC(5453e5aa) SHA1(7a45f05204020ba0bcb403381ab3de23ab657436) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmf12 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmf12.p1", 0x000000, 0x100000, CRC(8057c49b) SHA1(ad94a377255600d6be400f5b2394560c4cd72299) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmf13 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmf13.p1", 0x000000, 0x100000, CRC(b184800d) SHA1(387a2194a5adaaaf9caa3ab17f21b240f6d0376b) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmf14 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmf14.p1", 0x000000, 0x100000, CRC(52278a98) SHA1(5edb9d6067a501ca78a9ac30c91feb7d0e09eda4) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmg01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmg01.p1", 0x000000, 0x100000, CRC(89f870e6) SHA1(5e2f422ad8b999a6599cbd9d95aed8d39299012e) )
	ROM_LOAD16_WORD_SWAP( "256_cme01.p2", 0x100000, 0x400000, CRC(1d210b1e) SHA1(6a67cf8e02776ab6a4c03ca897426f4a2013598b) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
    AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3_AUDIOBIOS_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmg02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmg02.p1", 0x000000, 0x100000, CRC(e3086c7d) SHA1(90369db5b8bcd60824c893bdc0e80eabb83610a8) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3GW_FIX_FILL
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3GW_AUDIO_512K
    MSLUG3GW_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmg03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmg03.p1", 0x000000, 0x100000, CRC(88808ea3) SHA1(7dcd8709ee2c5bb64888e3b9d58b8ed44c578212) )
	ROM_LOAD16_WORD_SWAP( "256_cme03.p2", 0x100000, 0x400000, CRC(e0face27) SHA1(981b468b68e83ab9e2a4911650de7e49b3230c4b) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
    MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmg04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmg04.p1", 0x000000, 0x100000, CRC(0540bdcc) SHA1(3cbb75b8deea238ae09918afb175a124736fe4ce) )
	ROM_LOAD16_WORD_SWAP( "256_cme04.p2", 0x100000, 0x400000, CRC(7fb4fcf4) SHA1(76d6b92b4862baa08037efa80d8b9e361f8d5e9f) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmg05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmg05.p1", 0x000000, 0x100000, CRC(aac5f2e6) SHA1(83c9f88c0d261cf1acc60dc99be47d175daac6e0) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3WZ_FIX_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmg06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmg06.p1", 0x000000, 0x100000, CRC(5d23448f) SHA1(9c0dfa20e7d0a0037a818f9c5f85e5cf7f9810f7) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmg07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmg07.p1", 0x000000, 0x100000, CRC(04eec72c) SHA1(5be77bfc0cd30eae2c408fa438bc4c728bec4a72) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmg08 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmg08.p1", 0x000000, 0x100000, CRC(a35b0fe2) SHA1(c020e7e2e82e724f5fb70847e3087f6617210f00) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmg09 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmg09.p1", 0x000000, 0x100000, CRC(f885f950) SHA1(02cc8e0148d0be288be497ebafcd2ffdb3b06ae8) )
	ROM_LOAD16_WORD_SWAP( "256_cme09.p2", 0x100000, 0x400000, CRC(69f0c955) SHA1(6bcc047d934432fb1616ec159133c8c2a276838b) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3GW_AUDIO_512K
    MSLUG3GW_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmg10 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmg10.p1", 0x000000, 0x100000, CRC(8a05336d) SHA1(7ffc26ca001a1776029d1aaf57114d6d6b3ddd90) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmg11 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmg11.p1", 0x000000, 0x100000, CRC(08ab9935) SHA1(dda98517c7597dc1a91f146893e4170b5e52ea5f) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmg12 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmg12.p1", 0x000000, 0x100000, CRC(dcafb804) SHA1(42f06d47d71cd32aa391ecdfa1656b88a3af36e8) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmg13 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmg13.p1", 0x000000, 0x100000, CRC(ed7cfc92) SHA1(6f4c24911b142569be8e86bed3a66f40a4e91a4b) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmg14 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmg14.p1", 0x000000, 0x100000, CRC(0edff607) SHA1(db5df70d1a4ded40b695e65185bf4694d70d568a) )
	ROM_LOAD16_WORD_SWAP( "256_cme02.p2", 0x100000, 0x400000, CRC(a9f938ab) SHA1(f1ef4bc5bb06444f6a77924ad30421996d65c980) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3_AUDIO_512K
    MSLUG3_YMSND
	MSLUG3G_SPRITES
ROM_END

ROM_START( mslug3ctmh01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmh01.p1", 0x000000, 0x100000, CRC(c7419d4f) SHA1(a66e484cc23a6691dddb9fbe4785cd466ee1717e) )
	ROM_LOAD16_WORD_SWAP( "256_cmh01.p2", 0x100000, 0x400000, CRC(1f82ab76) SHA1(8a21634a5e75e15355c86f478f5ad811e4326b7a) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
    AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
    MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmh02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p1", 0x000000, 0x100000, CRC(adb181d4) SHA1(ac0681eecd09558dce97c48ac7c09ef5b33c4f21) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3GW_FIX_FILL
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmh03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmh03.p1", 0x000000, 0x100000, CRC(f7033333) SHA1(0a6a67af93ac2529c3c980daae3c44203098b569) )
	ROM_LOAD16_WORD_SWAP( "256_cmh03.p2", 0x100000, 0x400000, CRC(e2596e4f) SHA1(d6692b68a221298b3e44d4db993a43b4dee04305) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmh04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmh04.p1", 0x000000, 0x100000, CRC(4bf95065) SHA1(7c5f28c922a7a1a2b310c488cf8837bb3050457e) )
	ROM_LOAD16_WORD_SWAP( "256_cmh04.p2", 0x100000, 0x400000, CRC(5c88fe59) SHA1(3f60bc6b53497bb431477e0066f6a9a84e29f567) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmh05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmh05.p1", 0x000000, 0x100000, CRC(e47c1f4f) SHA1(c96aacf5c4cef05dcbaae60765e42b3b10a18c6c) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3WZ_FIX_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmh06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmh06.p1", 0x000000, 0x100000, CRC(139aa926) SHA1(592a746be3e817ad3bec723d593be7286b956ea5) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmh07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmh07.p1", 0x000000, 0x100000, CRC(4a572a85) SHA1(6556c09c4790476a5f5fa94e8b8ab26b4e93bf99) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmh08 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmh08.p1", 0x000000, 0x100000, CRC(ede2e24b) SHA1(205644ff8b5e06ca1bf3f4a3023fcb636fcc52b9) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmh09 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmh09.p1", 0x000000, 0x100000, CRC(870644c0) SHA1(fd89dba20c1ae88a7b0fd513e95765919b632cae) )
	ROM_LOAD16_WORD_SWAP( "256_cmh09.p2", 0x100000, 0x400000, CRC(6b53693d) SHA1(1bbf99c6435404c930c15193d0bbf88746329eba) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmh10 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmh10.p1", 0x000000, 0x100000, CRC(c4bcdec4) SHA1(15ade68bdf984b040b6e492143344fd82a950f08) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmh11 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmh11.p1", 0x000000, 0x100000, CRC(4612749c) SHA1(1d92d1b74371dd14a9fc601b7165aae14140c25e) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmh12 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmh12.p1", 0x000000, 0x100000, CRC(921655ad) SHA1(1c005d8dfef838a9d0b20be59772d115e48608b1) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmh13 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmg13.p1", 0x000000, 0x100000, CRC(ed7cfc92) SHA1(6f4c24911b142569be8e86bed3a66f40a4e91a4b) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmh14 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmh14.p1", 0x000000, 0x100000, CRC(40661bae) SHA1(78b71a952e3b8feef4015289cc55295666e939b4) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmi01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmi01.p1", 0x000000, 0x100000, CRC(70f868b5) SHA1(45a0ec6d81a5fe260fdcff6a93a856ea536e1d60) )
	ROM_LOAD16_WORD_SWAP( "256_cmh01.p2", 0x100000, 0x400000, CRC(1f82ab76) SHA1(8a21634a5e75e15355c86f478f5ad811e4326b7a) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
    AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
    MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmi02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmi02.p1", 0x000000, 0x100000, CRC(1a08742e) SHA1(b940855e27905848823aa21b96e41d926674cb32) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3GW_FIX_FILL
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmi03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmi03.p1", 0x000000, 0x100000, CRC(e66d2935) SHA1(8df1299327222330d6f91fe6884ffb4b12462b46) )
	ROM_LOAD16_WORD_SWAP( "256_cmh03.p2", 0x100000, 0x400000, CRC(e2596e4f) SHA1(d6692b68a221298b3e44d4db993a43b4dee04305) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmi04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmi04.p1", 0x000000, 0x100000, CRC(fc40a59f) SHA1(93a2e7dce3502b00c13bb1a87edc336c5dbf6acb) )
	ROM_LOAD16_WORD_SWAP( "256_cmh04.p2", 0x100000, 0x400000, CRC(5c88fe59) SHA1(3f60bc6b53497bb431477e0066f6a9a84e29f567) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmi05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmi05.p1", 0x000000, 0x100000, CRC(53c5eab5) SHA1(6d0f16754b0045f68b3efd1aee6b7e5c16f7fdd2) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3WZ_FIX_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmi06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmi06.p1", 0x000000, 0x100000, CRC(a4235cdc) SHA1(28c412730547d2a27de1f60e137ed6ab743c262a) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmi07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmi07.p1", 0x000000, 0x100000, CRC(fdeedf7f) SHA1(4057893a47665942943a9cdf5fcbbaf9874e6f84) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmi08 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmi08.p1", 0x000000, 0x100000, CRC(5a5b17b1) SHA1(c6462bfed3d254a79b511a11e45db7bf6b3a72ed) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmi09 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmi09.p1", 0x000000, 0x100000, CRC(96685ec6) SHA1(ef78deea6f5214776eaf31290a199ba36d0ae500) )
	ROM_LOAD16_WORD_SWAP( "256_cmh09.p2", 0x100000, 0x400000, CRC(6b53693d) SHA1(1bbf99c6435404c930c15193d0bbf88746329eba) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmi10 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmi10.p1", 0x000000, 0x100000, CRC(73052b3e) SHA1(1917e96f51831bff788e648f3a2e374889dd0fa2) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmi11 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmi11.p1", 0x000000, 0x100000, CRC(f1ab8166) SHA1(9b7c6a3e6430bce7eb70da785ed54f1fdac87707) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmi12 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmi12.p1", 0x000000, 0x100000, CRC(25afa057) SHA1(7b849659399c7cb98b5c26d3e40bfc1d66cc822b) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmi13 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmg13.p1", 0x000000, 0x100000, CRC(ed7cfc92) SHA1(6f4c24911b142569be8e86bed3a66f40a4e91a4b) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmi14 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmi14.p1", 0x000000, 0x100000, CRC(f7dfee54) SHA1(cbdf4362cd4f07573c4262ffc0b16f0824ea2db0) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmj01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmj01.p1", 0x000000, 0x100000, CRC(9a833ab9) SHA1(1bcaf5c01b795248199743ecfb86e18ea75eb505) )
	ROM_LOAD16_WORD_SWAP( "256_cmh01.p2", 0x100000, 0x400000, CRC(1f82ab76) SHA1(8a21634a5e75e15355c86f478f5ad811e4326b7a) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
    AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
    MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmj02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmj02.p1", 0x000000, 0x100000, CRC(f0732622) SHA1(01e5e31cb84ca4f13c593053fa9e76ded1b63af3) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3GW_FIX_FILL
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmj03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmj03.p1", 0x000000, 0x100000, CRC(9bfbc4fc) SHA1(357171b630ac3d27ed3c285ecb3921ab8fbcf36d) )
	ROM_LOAD16_WORD_SWAP( "256_cmh03.p2", 0x100000, 0x400000, CRC(e2596e4f) SHA1(d6692b68a221298b3e44d4db993a43b4dee04305) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmj04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmj04.p1", 0x000000, 0x100000, CRC(163bf793) SHA1(f3d6edd530945f73e292083077e886d6ecad479f) )
	ROM_LOAD16_WORD_SWAP( "256_cmh04.p2", 0x100000, 0x400000, CRC(5c88fe59) SHA1(3f60bc6b53497bb431477e0066f6a9a84e29f567) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmj05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmj05.p1", 0x000000, 0x100000, CRC(b9beb8b9) SHA1(ec178b29310aabb88193362f7d9e3556c4fe6679) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3WZ_FIX_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmj06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmj06.p1", 0x000000, 0x100000, CRC(4e580ed0) SHA1(efc86b97dceb6e1b99d7b7b9f28548e0cd24e19e) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmj07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmj07.p1", 0x000000, 0x100000, CRC(17958d73) SHA1(8c7fa4a579346f1fb495599742f36697e4f5f17e) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmj08 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmj08.p1", 0x000000, 0x100000, CRC(b02045bd) SHA1(9ea0f0b2f8834cfeaa5b1004faf102daaa5f8eae) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmj09 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmj09.p1", 0x000000, 0x100000, CRC(ebfeb30f) SHA1(19aebcdd7b99e8c00f8e964b3377de636d4127b6) )
	ROM_LOAD16_WORD_SWAP( "256_cmh09.p2", 0x100000, 0x400000, CRC(6b53693d) SHA1(1bbf99c6435404c930c15193d0bbf88746329eba) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmj10 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmj10.p1", 0x000000, 0x100000, CRC(997e7932) SHA1(dc718b63379f65bfd3f2682119aca49e0647b1a9) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmj11 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmj11.p1", 0x000000, 0x100000, CRC(1bd0d36a) SHA1(4c98ce68de7f4d53bbdfcedfb925ce52e44e040e) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmj12 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmj12.p1", 0x000000, 0x100000, CRC(cfd4f25b) SHA1(f428ce1b35ce21e13ff114ff5ad915d95ac6829c) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmj13 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmg13.p1", 0x000000, 0x100000, CRC(ed7cfc92) SHA1(6f4c24911b142569be8e86bed3a66f40a4e91a4b) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmj14 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmj14.p1", 0x000000, 0x100000, CRC(1da4bc58) SHA1(8bb414bba83c34c7f13089ef0aed2f8550273695) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmk01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmk01.p1", 0x000000, 0x100000, CRC(665d0153) SHA1(98e1e7a0f0be40a944ac7406c32da3d9a586b977) )
	ROM_LOAD16_WORD_SWAP( "256_cmh01.p2", 0x100000, 0x400000, CRC(1f82ab76) SHA1(8a21634a5e75e15355c86f478f5ad811e4326b7a) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
    AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
    MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmk02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmk02.p1", 0x000000, 0x100000, CRC(0cad1dc8) SHA1(3c2858cb2629b633c2eb1023b11235d77af88c62) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3GW_FIX_FILL
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmk03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmk03.p1", 0x000000, 0x100000, CRC(b1aed97d) SHA1(448679d48a13582bbaf27022a9465cf66e0de68b) )
	ROM_LOAD16_WORD_SWAP( "256_cmh03.p2", 0x100000, 0x400000, CRC(e2596e4f) SHA1(d6692b68a221298b3e44d4db993a43b4dee04305) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmk04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmk04.p1", 0x000000, 0x100000, CRC(eae5cc79) SHA1(8463f526bfac31f82ffe3dea2e368a0f3d054209) )
	ROM_LOAD16_WORD_SWAP( "256_cmh04.p2", 0x100000, 0x400000, CRC(5c88fe59) SHA1(3f60bc6b53497bb431477e0066f6a9a84e29f567) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmk05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmk05.p1", 0x000000, 0x100000, CRC(45608353) SHA1(ce1a56bd73bdbb1771aeb768376b610ea21b521d) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3WZ_FIX_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmk06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmk06.p1", 0x000000, 0x100000, CRC(b286353a) SHA1(6e17292df80ad52d5c97aa744e6dce790092836a) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmk07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmk07.p1", 0x000000, 0x100000, CRC(eb4bb699) SHA1(905e135dc84e6ef10dd4bd7d916b526a8a0196f6) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmk08 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmk08.p1", 0x000000, 0x100000, CRC(4cfe7e57) SHA1(b682a64232bbdf690d368d7b4a7e9da73086fbfa) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmk09 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmk09.p1", 0x000000, 0x100000, CRC(c1abae8e) SHA1(89f3c97b2382bd2df9a8f0bcbba69e5514ef032f) )
	ROM_LOAD16_WORD_SWAP( "256_cmh09.p2", 0x100000, 0x400000, CRC(6b53693d) SHA1(1bbf99c6435404c930c15193d0bbf88746329eba) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmk10 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmk10.p1", 0x000000, 0x100000, CRC(65a042d8) SHA1(cd4d51a6aa08d7c7ff7ae827699e8a11db64c899) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmk11 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmk11.p1", 0x000000, 0x100000, CRC(e70ee880) SHA1(9dde31bc94770765984a43d16b4989a7a213b330) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmk12 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmk12.p1", 0x000000, 0x100000, CRC(330ac9b1) SHA1(39704b06c09cf887903e7cc64f01d0b0401f303c) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmk13 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmg13.p1", 0x000000, 0x100000, CRC(ed7cfc92) SHA1(6f4c24911b142569be8e86bed3a66f40a4e91a4b) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctmk14 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cmk14.p1", 0x000000, 0x100000, CRC(a750860f) SHA1(924f3baf0e539bf2fd82a45abc77ebab8d615d71) )
	ROM_LOAD16_WORD_SWAP( "256_cmh02.p2", 0x100000, 0x400000, CRC(ab5a98c3) SHA1(e13baf82d4f2d7862cc142a961e63d082f3157e8) )
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug3ctml01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_cml01.p1", 0x000000, 0x100000, CRC(d3203b4c) SHA1(6ad5442e872c0eb4ec5004146e17f0dc939b883b) )
	ROM_LOAD16_WORD_SWAP( "256_cml01.p2", 0x100000, 0x400000, CRC(f9ca4e01) SHA1(f4547d5f525c20c15612c705d7bbe250df59e089) )
    MSLUG3LW_FIX_FILL
    MSLUG3H_ESSENTIALPATCH_MODS_FILL
    MSLUG3H_MVS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LW_SPRITES
ROM_END

ROM_START( mslug4ctma01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_cma01.p1", 0x000000, 0x100000, CRC(04f30726) SHA1(44dbe75a5546d68852c20b81c532d77c79512c6c) )
	ROM_LOAD16_WORD_SWAP( "263_hc09.p2",  0x100000, 0x400000, CRC(a4d2e871) SHA1(646ac0117a832f1642cffe17478b94635cf294a2) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
	MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
	MSLUG4_AUDIO_ENCRYPTED_128K
    MSLUG4_YMSND
	MSLUG4D_SPRITES
ROM_END

ROM_START( mslug4ctma02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_cma02.p1", 0x000000, 0x100000, CRC(ff836d7e) SHA1(d4e340615ea5c0fd85512165bc6c53a315ecae81) )
	ROM_LOAD16_WORD_SWAP( "263_hc06.p2",  0x100000, 0x400000, CRC(cf6feb75) SHA1(133e1d97a3ae14835dcb7b6a642c3968cd174547) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
	MSLUG4_AUDIO_ENCRYPTED_128K
    MSLUG4DG_YMSND
	MSLUG4_SPRITES
ROM_END

ROM_START( mslug4ctma03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_cma03.p1", 0x000000, 0x100000, CRC(a842fc07) SHA1(301d0ec0bb2fa7b082a2677af3241691309c95eb) )
	ROM_LOAD16_WORD_SWAP( "263.p2",       0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
    MSLUG4LWD_SPRITES
ROM_END

ROM_START( mslug4ctma04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_cma04.p1", 0x000000, 0x100000, CRC(1e26043f) SHA1(ecdf8208dc6596c5a9856d2743a2d871935ed77c) )
	ROM_LOAD16_WORD_SWAP( "263.p2",       0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
    MSLUG4LWD_SPRITES
ROM_END

ROM_START( mslug4ctma05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_cma05.p1", 0x000000, 0x100000, CRC(506ba1fb) SHA1(2de64cce0a1d65eeef09a59d24148763c32db436) )
	ROM_LOAD16_WORD_SWAP( "263.p2",       0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
    MSLUG4LWD_SPRITES
ROM_END

ROM_START( mslug4ctma06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_cma06.p1", 0x000000, 0x100000, CRC(6c1d353e) SHA1(d6544effb01807f6dee1a31887323b42e0e87fc2) )
	ROM_LOAD16_WORD_SWAP( "263.p2",       0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
    MSLUG4LWD_SPRITES
ROM_END

ROM_START( mslug4ctma07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_cma07.p1", 0x000000, 0x100000, CRC(9aab59d2) SHA1(0db7325b61c464821501eee0bfa0b936a01920c2) )
	ROM_LOAD16_WORD_SWAP( "263.p2",       0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
    MSLUG4LWD_SPRITES
ROM_END

ROM_START( mslug4ctma08 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_cma08.p1", 0x000000, 0x100000, CRC(4ae2bba1) SHA1(2739547cf41b9140c7f11c5c5467ab57d8c7ed4f) )
	ROM_LOAD16_WORD_SWAP( "263.p2",       0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
    FIX_BIOS_COIN_FILL
	AUDIOBIOS_128K   
    MSLUG4HD_SFIX_128K
    MSLUG4LW_AUDIOBIOS_128K
	MSLUG4LW_YMSND
    MSLUG4LWD_SPRITES
ROM_END

ROM_START( mslug4ctma09 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_cma09.p1", 0x000000, 0x100000, CRC(b37ccd21) SHA1(0edd9994875dbd392ad6b0e4248b6172e792a17c) )
	ROM_LOAD16_WORD_SWAP( "263.p2",       0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
    MSLUG4LWD_SPRITES
ROM_END

ROM_START( mslug4ctma10 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_cma10.p1", 0x000000, 0x100000, CRC(daf7813d) SHA1(039f476e2e22797659c8b0b91603fb64b3ba406f) )
	ROM_LOAD16_WORD_SWAP( "263_hc01.p2",  0x100000, 0x400000, CRC(2b863b30) SHA1(b5edc43d87faf6540e3154fcbab42efb148cbd04) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
    MSLUG4LWD_SPRITES
ROM_END

ROM_START( mslug4ctma11 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_cma11.p1", 0x000000, 0x100000, CRC(a3b03819) SHA1(9d5cd6d258348d4b83ff96f0a1c730267ac20d5b) )
	ROM_LOAD16_WORD_SWAP( "263.p2",       0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
    MSLUG4LWD_SPRITES
ROM_END

ROM_START( mslug4ctma12 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_cma12.p1", 0x000000, 0x100000, CRC(518666ad) SHA1(4b10d885e6ee83c8bcd3e0cfae9a6b47bc7cb9e6) )
	ROM_LOAD16_WORD_SWAP( "263_hc16.p2",  0x100000, 0x400000, CRC(4569a092) SHA1(98cbc3a554a810c105a3044f09fa732ebc56cb4a) )
    MSLUG4_ESSENTIALPATCH_MODS_FILL
    MSLUG4_MVS_FILL
    MSLUG4_AES_FILL
    MSLUG4HD_SFIX_128K
	MSLUG4_AUDIO_ENCRYPTED_128K
    MSLUG4_YMSND
	MSLUG4DDH_SPRITES
ROM_END

ROM_START( mslugxctma01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc06.p1", 0x000000, 0x100000, CRC(a507546f) SHA1(ab6e9e969c2b3728cb0b13e0b1d62bda09037ac0) )
	ROM_LOAD16_WORD_SWAP( "250_hc03.p2", 0x100000, 0x400000, CRC(8d595131) SHA1(523401915e5b751c9d67c169173de7e17fe7ff00) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctma02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc13.p1", 0x000000, 0x100000, CRC(b606e809) SHA1(a477647cf470a115b9df1d37ab859188de49f9a9) )
	ROM_LOAD16_WORD_SWAP( "250_hc03.p2", 0x100000, 0x400000, CRC(8d595131) SHA1(523401915e5b751c9d67c169173de7e17fe7ff00) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctma03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc14.p1", 0x000000, 0x100000, CRC(a11473d5) SHA1(83f6665e88e8b9d33545e5c57ac8a5e923787bd2) )
	ROM_LOAD16_WORD_SWAP( "250_hc03.p2", 0x100000, 0x400000, CRC(8d595131) SHA1(523401915e5b751c9d67c169173de7e17fe7ff00) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctma04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc17.p1", 0x000000, 0x100000, CRC(0cf1f95b) SHA1(857af8721c5929ba7c60e16223cab4879ec382b9) )
	ROM_LOAD16_WORD_SWAP( "250_hc03.p2", 0x100000, 0x400000, CRC(8d595131) SHA1(523401915e5b751c9d67c169173de7e17fe7ff00) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctma05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc18.p1",  0x000000, 0x100000, CRC(6a116211) SHA1(92b1d87248e03d21eb87201cbadc5de0eaaf4b47) )
	ROM_LOAD16_WORD_SWAP( "250_cma05.p2", 0x100000, 0x400000, CRC(036b5123) SHA1(dfdb2b3919bf3a2a1bfb90b937cce32a999d0526) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctma06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc29.p1", 0x000000, 0x100000, CRC(a3764c51) SHA1(791e23b6953aba236fe18182efa7445291c991ba) )
	ROM_LOAD16_WORD_SWAP( "250_hc03.p2", 0x100000, 0x400000, CRC(8d595131) SHA1(523401915e5b751c9d67c169173de7e17fe7ff00) )
    MSLUGXV_ESSENTIALPATCH_MODS_FILL
    FIX1_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctma07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc32.p1", 0x000000, 0x100000, CRC(a7edd6ea) SHA1(d0bca9bbcfd1458ed9777b319b92fd1ebf9e5a89) )
	ROM_LOAD16_WORD_SWAP( "250_hc03.p2", 0x100000, 0x400000, CRC(8d595131) SHA1(523401915e5b751c9d67c169173de7e17fe7ff00) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctma08 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc34.p1", 0x000000, 0x100000, CRC(32cea24b) SHA1(059a2f3d70667e8202918f14c9a6d6142f6866d8) )
	ROM_LOAD16_WORD_SWAP( "250_hc03.p2", 0x100000, 0x400000, CRC(8d595131) SHA1(523401915e5b751c9d67c169173de7e17fe7ff00) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctma09 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc04.p1", 0x000000, 0x100000, CRC(36102d34) SHA1(b60d41e7cd3395910e7aa5cc0a843d68bfcc2ac6) )
	ROM_LOAD16_WORD_SWAP( "250_hc03.p2", 0x100000, 0x400000, CRC(8d595131) SHA1(523401915e5b751c9d67c169173de7e17fe7ff00) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctma10 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc36.p1", 0x000000, 0x100000, CRC(971f8454) SHA1(73033339931de870bb5a5a64f34ce51c63c4ed15) )
	ROM_LOAD16_WORD_SWAP( "250_hc03.p2", 0x100000, 0x400000, CRC(8d595131) SHA1(523401915e5b751c9d67c169173de7e17fe7ff00) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctma11 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc26.p1",  0x000000, 0x100000, CRC(f86ea146) SHA1(c30a69749da8b0bda5231ac4e121dd90a65d0a96) )
	ROM_LOAD16_WORD_SWAP( "250_cma11.p2", 0x100000, 0x400000, CRC(e7d12923) SHA1(d3a1d43d21ea78900b26578511ab612158dad801) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctma12 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc10.p1", 0x000000, 0x100000, CRC(c405753d) SHA1(bed7426145fd15e972334d7ef04759edcccd8864) )
	ROM_LOAD16_WORD_SWAP( "250_hc03.p2", 0x100000, 0x400000, CRC(8d595131) SHA1(523401915e5b751c9d67c169173de7e17fe7ff00) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctma13 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc16.p1", 0x000000, 0x100000, CRC(e75a6d64) SHA1(529130f7ebb43231e6bf1b1703266b6c09356f9c) )
	ROM_LOAD16_WORD_SWAP( "250_hc03.p2", 0x100000, 0x400000, CRC(8d595131) SHA1(523401915e5b751c9d67c169173de7e17fe7ff00) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctma14 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc08.p1", 0x000000, 0x100000, CRC(c0911075) SHA1(2645c9d59915811addc2ab048afbfb9e605bca24) )
	ROM_LOAD16_WORD_SWAP( "250_hc03.p2", 0x100000, 0x400000, CRC(8d595131) SHA1(523401915e5b751c9d67c169173de7e17fe7ff00) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctma15 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc28.p1",  0x000000, 0x100000, CRC(5836f4d7) SHA1(002c6a519c118d33e3cef92066b0e8fc96f52627) )
	ROM_LOAD16_WORD_SWAP( "250_cma15.p2", 0x100000, 0x400000, CRC(fb30100d) SHA1(580732135054a66e32ebbf7466840cf40a47482b) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
    FIX_BIOS_COIN_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctma16 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc24.p1",  0x000000, 0x100000, CRC(aa09586a) SHA1(246579b58babcf696f988a2d57dc8fab0019b3de) )
	ROM_LOAD16_WORD_SWAP( "250_cma16.p2", 0x100000, 0x400000, CRC(5d7308ba) SHA1(bed63942cca5c759fad52dce8d89f2c9d3978f96) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGXDD_SPRITES
ROM_END

ROM_START( mslugxctmb01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc06.p1", 0x000000, 0x100000, CRC(a507546f) SHA1(ab6e9e969c2b3728cb0b13e0b1d62bda09037ac0) )
	ROM_LOAD16_WORD_SWAP( "250_hc07.p2", 0x100000, 0x400000, CRC(a2a2a303) SHA1(0a85555253dbff4f0d2ae4edf92dd36f7c0114d8) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmb02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc13.p1", 0x000000, 0x100000, CRC(b606e809) SHA1(a477647cf470a115b9df1d37ab859188de49f9a9) )
	ROM_LOAD16_WORD_SWAP( "250_hc07.p2", 0x100000, 0x400000, CRC(a2a2a303) SHA1(0a85555253dbff4f0d2ae4edf92dd36f7c0114d8) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmb03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc14.p1", 0x000000, 0x100000, CRC(a11473d5) SHA1(83f6665e88e8b9d33545e5c57ac8a5e923787bd2) )
	ROM_LOAD16_WORD_SWAP( "250_hc07.p2", 0x100000, 0x400000, CRC(a2a2a303) SHA1(0a85555253dbff4f0d2ae4edf92dd36f7c0114d8) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmb04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc17.p1", 0x000000, 0x100000, CRC(0cf1f95b) SHA1(857af8721c5929ba7c60e16223cab4879ec382b9) )
	ROM_LOAD16_WORD_SWAP( "250_hc07.p2", 0x100000, 0x400000, CRC(a2a2a303) SHA1(0a85555253dbff4f0d2ae4edf92dd36f7c0114d8) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmb05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc18.p1",  0x000000, 0x100000, CRC(6a116211) SHA1(92b1d87248e03d21eb87201cbadc5de0eaaf4b47) )
	ROM_LOAD16_WORD_SWAP( "250_cmb05.p2", 0x100000, 0x400000, CRC(2c90a311) SHA1(610910428aa206a87d76218f6bd6fb82c60f5225) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmb06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc29.p1", 0x000000, 0x100000, CRC(a3764c51) SHA1(791e23b6953aba236fe18182efa7445291c991ba) )
	ROM_LOAD16_WORD_SWAP( "250_hc07.p2", 0x100000, 0x400000, CRC(a2a2a303) SHA1(0a85555253dbff4f0d2ae4edf92dd36f7c0114d8) )
    MSLUGXV_ESSENTIALPATCH_MODS_FILL
    FIX1_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmb07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc32.p1", 0x000000, 0x100000, CRC(a7edd6ea) SHA1(d0bca9bbcfd1458ed9777b319b92fd1ebf9e5a89) )
	ROM_LOAD16_WORD_SWAP( "250_hc07.p2", 0x100000, 0x400000, CRC(a2a2a303) SHA1(0a85555253dbff4f0d2ae4edf92dd36f7c0114d8) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmb08 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc34.p1", 0x000000, 0x100000, CRC(32cea24b) SHA1(059a2f3d70667e8202918f14c9a6d6142f6866d8) )
	ROM_LOAD16_WORD_SWAP( "250_hc07.p2", 0x100000, 0x400000, CRC(a2a2a303) SHA1(0a85555253dbff4f0d2ae4edf92dd36f7c0114d8) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmb09 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc04.p1", 0x000000, 0x100000, CRC(36102d34) SHA1(b60d41e7cd3395910e7aa5cc0a843d68bfcc2ac6) )
	ROM_LOAD16_WORD_SWAP( "250_hc07.p2", 0x100000, 0x400000, CRC(a2a2a303) SHA1(0a85555253dbff4f0d2ae4edf92dd36f7c0114d8) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmb10 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc36.p1", 0x000000, 0x100000, CRC(971f8454) SHA1(73033339931de870bb5a5a64f34ce51c63c4ed15) )
	ROM_LOAD16_WORD_SWAP( "250_hc07.p2", 0x100000, 0x400000, CRC(a2a2a303) SHA1(0a85555253dbff4f0d2ae4edf92dd36f7c0114d8) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmb11 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc26.p1",  0x000000, 0x100000, CRC(f86ea146) SHA1(c30a69749da8b0bda5231ac4e121dd90a65d0a96) )
	ROM_LOAD16_WORD_SWAP( "250_cmb11.p2", 0x100000, 0x400000, CRC(753ec741) SHA1(d0375b0d00209b95924894b23098ce6bae98777a) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmb12 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc10.p1", 0x000000, 0x100000, CRC(c405753d) SHA1(bed7426145fd15e972334d7ef04759edcccd8864) )
	ROM_LOAD16_WORD_SWAP( "250_hc07.p2", 0x100000, 0x400000, CRC(a2a2a303) SHA1(0a85555253dbff4f0d2ae4edf92dd36f7c0114d8) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmb13 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc16.p1", 0x000000, 0x100000, CRC(e75a6d64) SHA1(529130f7ebb43231e6bf1b1703266b6c09356f9c) )
	ROM_LOAD16_WORD_SWAP( "250_hc07.p2", 0x100000, 0x400000, CRC(a2a2a303) SHA1(0a85555253dbff4f0d2ae4edf92dd36f7c0114d8) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmb14 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc08.p1", 0x000000, 0x100000, CRC(c0911075) SHA1(2645c9d59915811addc2ab048afbfb9e605bca24) )
	ROM_LOAD16_WORD_SWAP( "250_hc07.p2", 0x100000, 0x400000, CRC(a2a2a303) SHA1(0a85555253dbff4f0d2ae4edf92dd36f7c0114d8) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmb15 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc28.p1",  0x000000, 0x100000, CRC(5836f4d7) SHA1(002c6a519c118d33e3cef92066b0e8fc96f52627) )
	ROM_LOAD16_WORD_SWAP( "250_cmb15.p2", 0x100000, 0x400000, CRC(73585020) SHA1(482e5ee2a6516c32c14acc3c51de284636b97611) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
    FIX_BIOS_COIN_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmb16 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc24.p1",  0x000000, 0x100000, CRC(aa09586a) SHA1(246579b58babcf696f988a2d57dc8fab0019b3de) )
	ROM_LOAD16_WORD_SWAP( "250_cmb16.p2", 0x100000, 0x400000, CRC(d51b4897) SHA1(37f14f46cafa88f610a31a98f141f87006f906ae) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGXDD_SPRITES
ROM_END

ROM_START( mslugxctmc01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc06.p1", 0x000000, 0x100000, CRC(a507546f) SHA1(ab6e9e969c2b3728cb0b13e0b1d62bda09037ac0) )
	ROM_LOAD16_WORD_SWAP( "250_hc11.p2", 0x100000, 0x400000, CRC(dda3726f) SHA1(7bd181f10e0737e3284c787581cca5b8199485d4) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmc02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc13.p1", 0x000000, 0x100000, CRC(b606e809) SHA1(a477647cf470a115b9df1d37ab859188de49f9a9) )
	ROM_LOAD16_WORD_SWAP( "250_hc11.p2", 0x100000, 0x400000, CRC(dda3726f) SHA1(7bd181f10e0737e3284c787581cca5b8199485d4) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmc03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc14.p1", 0x000000, 0x100000, CRC(a11473d5) SHA1(83f6665e88e8b9d33545e5c57ac8a5e923787bd2) )
	ROM_LOAD16_WORD_SWAP( "250_hc11.p2", 0x100000, 0x400000, CRC(dda3726f) SHA1(7bd181f10e0737e3284c787581cca5b8199485d4) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmc04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc17.p1", 0x000000, 0x100000, CRC(0cf1f95b) SHA1(857af8721c5929ba7c60e16223cab4879ec382b9) )
	ROM_LOAD16_WORD_SWAP( "250_hc11.p2", 0x100000, 0x400000, CRC(dda3726f) SHA1(7bd181f10e0737e3284c787581cca5b8199485d4) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmc05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc18.p1",  0x000000, 0x100000, CRC(6a116211) SHA1(92b1d87248e03d21eb87201cbadc5de0eaaf4b47) )
	ROM_LOAD16_WORD_SWAP( "250_cmc05.p2", 0x100000, 0x400000, CRC(5391727d) SHA1(49424024ec84d7b42e1fbfb4bc49d345eaef415e) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmc06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc29.p1", 0x000000, 0x100000, CRC(a3764c51) SHA1(791e23b6953aba236fe18182efa7445291c991ba) )
	ROM_LOAD16_WORD_SWAP( "250_hc11.p2", 0x100000, 0x400000, CRC(dda3726f) SHA1(7bd181f10e0737e3284c787581cca5b8199485d4) )
    MSLUGXV_ESSENTIALPATCH_MODS_FILL
    FIX1_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmc07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc32.p1", 0x000000, 0x100000, CRC(a7edd6ea) SHA1(d0bca9bbcfd1458ed9777b319b92fd1ebf9e5a89) )
	ROM_LOAD16_WORD_SWAP( "250_hc11.p2", 0x100000, 0x400000, CRC(dda3726f) SHA1(7bd181f10e0737e3284c787581cca5b8199485d4) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmc08 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc34.p1", 0x000000, 0x100000, CRC(32cea24b) SHA1(059a2f3d70667e8202918f14c9a6d6142f6866d8) )
	ROM_LOAD16_WORD_SWAP( "250_hc11.p2", 0x100000, 0x400000, CRC(dda3726f) SHA1(7bd181f10e0737e3284c787581cca5b8199485d4) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmc09 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc04.p1", 0x000000, 0x100000, CRC(36102d34) SHA1(b60d41e7cd3395910e7aa5cc0a843d68bfcc2ac6) )
	ROM_LOAD16_WORD_SWAP( "250_hc11.p2", 0x100000, 0x400000, CRC(dda3726f) SHA1(7bd181f10e0737e3284c787581cca5b8199485d4) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmc10 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc36.p1", 0x000000, 0x100000, CRC(971f8454) SHA1(73033339931de870bb5a5a64f34ce51c63c4ed15) )
	ROM_LOAD16_WORD_SWAP( "250_hc11.p2", 0x100000, 0x400000, CRC(dda3726f) SHA1(7bd181f10e0737e3284c787581cca5b8199485d4) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmc11 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc26.p1",  0x000000, 0x100000, CRC(f86ea146) SHA1(c30a69749da8b0bda5231ac4e121dd90a65d0a96) )
	ROM_LOAD16_WORD_SWAP( "250_cmc11.p2", 0x100000, 0x400000, CRC(c9f8fa26) SHA1(7bcbbce0fe6c09e074a5cf4160bf15ce62c75991) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmc12 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc10.p1", 0x000000, 0x100000, CRC(c405753d) SHA1(bed7426145fd15e972334d7ef04759edcccd8864) )
	ROM_LOAD16_WORD_SWAP( "250_hc11.p2", 0x100000, 0x400000, CRC(dda3726f) SHA1(7bd181f10e0737e3284c787581cca5b8199485d4) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmc13 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc16.p1", 0x000000, 0x100000, CRC(e75a6d64) SHA1(529130f7ebb43231e6bf1b1703266b6c09356f9c) )
	ROM_LOAD16_WORD_SWAP( "250_hc11.p2", 0x100000, 0x400000, CRC(dda3726f) SHA1(7bd181f10e0737e3284c787581cca5b8199485d4) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmc14 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc08.p1", 0x000000, 0x100000, CRC(c0911075) SHA1(2645c9d59915811addc2ab048afbfb9e605bca24) )
	ROM_LOAD16_WORD_SWAP( "250_hc11.p2", 0x100000, 0x400000, CRC(dda3726f) SHA1(7bd181f10e0737e3284c787581cca5b8199485d4) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmc15 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc28.p1",  0x000000, 0x100000, CRC(5836f4d7) SHA1(002c6a519c118d33e3cef92066b0e8fc96f52627) )
	ROM_LOAD16_WORD_SWAP( "250_cmc15.p2", 0x100000, 0x400000, CRC(cf9e6d47) SHA1(6e0448b15adfff6720db534eeb322624248b5867) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
    FIX_BIOS_COIN_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmc16 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc24.p1",  0x000000, 0x100000, CRC(aa09586a) SHA1(246579b58babcf696f988a2d57dc8fab0019b3de) )
	ROM_LOAD16_WORD_SWAP( "250_cmc16.p2", 0x100000, 0x400000, CRC(69dd75f0) SHA1(92d49e9d63e7fbbe21aea7af95c7c894cafc1284) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGXDD_SPRITES
ROM_END

ROM_START( mslugxctmd01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cmd01.p1", 0x000000, 0x100000, CRC(a21a958f) SHA1(26b7b4008bd42473a334636193f6ffcbd30e8180) )
	ROM_LOAD16_WORD_SWAP( "250_cmd01.p2", 0x100000, 0x400000, CRC(4b2d73fb) SHA1(6db9c31083c9b94d320fd2ce051cd8dacfb077ec) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX4_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmd02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cmd02.p1", 0x000000, 0x100000, CRC(b11b29e9) SHA1(7d8f1eee1d8417e7aa68e2894e671a4f0599da89) )
	ROM_LOAD16_WORD_SWAP( "250_cmd01.p2", 0x100000, 0x400000, CRC(4b2d73fb) SHA1(6db9c31083c9b94d320fd2ce051cd8dacfb077ec) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX4_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmd03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cmd03.p1", 0x000000, 0x100000, CRC(a609b235) SHA1(918e94c446e1b8402cb171a7f963c1b198b0c461) )
	ROM_LOAD16_WORD_SWAP( "250_cmd01.p2", 0x100000, 0x400000, CRC(4b2d73fb) SHA1(6db9c31083c9b94d320fd2ce051cd8dacfb077ec) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX4_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmd04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cmd04.p1", 0x000000, 0x100000, CRC(0bec38bb) SHA1(9f08d76e5092eb841124ec62ca16ace20a4f3fd2) )
	ROM_LOAD16_WORD_SWAP( "250_cmd01.p2", 0x100000, 0x400000, CRC(4b2d73fb) SHA1(6db9c31083c9b94d320fd2ce051cd8dacfb077ec) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX4_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmd05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cmd05.p1", 0x000000, 0x100000, CRC(6d0ca3f1) SHA1(a20da89bd13a166de4a22ecf1d77bfbc06b1a639) )
	ROM_LOAD16_WORD_SWAP( "250_cmd05.p2", 0x100000, 0x400000, CRC(c51f73e9) SHA1(6bdfc8742bcaadffb96308d8264c6cd523f002b5) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX4_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmd06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cmd06.p1", 0x000000, 0x100000, CRC(a46b8db1) SHA1(d88155377bc88e6420df65041520b09c799cd4ed) )
	ROM_LOAD16_WORD_SWAP( "250_cmd01.p2", 0x100000, 0x400000, CRC(4b2d73fb) SHA1(6db9c31083c9b94d320fd2ce051cd8dacfb077ec) )
    MSLUGXV_ESSENTIALPATCH_MODS_FILL
    FIX5_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmd07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cmd07.p1", 0x000000, 0x100000, CRC(a0f0170a) SHA1(094f0b2c44a8e849e4a1319aa65f2611bf95dd98) )
	ROM_LOAD16_WORD_SWAP( "250_cmd01.p2", 0x100000, 0x400000, CRC(4b2d73fb) SHA1(6db9c31083c9b94d320fd2ce051cd8dacfb077ec) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX4_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmd08 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cmd08.p1", 0x000000, 0x100000, CRC(35d363ab) SHA1(3ec436c5e1bd8487a51425b88493d25bf484fd4a) )
	ROM_LOAD16_WORD_SWAP( "250_cmd01.p2", 0x100000, 0x400000, CRC(4b2d73fb) SHA1(6db9c31083c9b94d320fd2ce051cd8dacfb077ec) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX4_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmd09 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cmd09.p1", 0x000000, 0x100000, CRC(310decd4) SHA1(2255205562b8ae75ae073cb5f23818586d31d65e) )
	ROM_LOAD16_WORD_SWAP( "250_cmd01.p2", 0x100000, 0x400000, CRC(4b2d73fb) SHA1(6db9c31083c9b94d320fd2ce051cd8dacfb077ec) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX4_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmd10 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cmd10.p1", 0x000000, 0x100000, CRC(900245b4) SHA1(30b72d81ce9bc4a8118a4d4e52a2bc09ad57c5a7) )
	ROM_LOAD16_WORD_SWAP( "250_cmd01.p2", 0x100000, 0x400000, CRC(4b2d73fb) SHA1(6db9c31083c9b94d320fd2ce051cd8dacfb077ec) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX4_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmd11 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cmd11.p1", 0x000000, 0x100000, CRC(ff7360a6) SHA1(97baed0d4eddb31d582319f8dd6e999b15d4e68a) )
	ROM_LOAD16_WORD_SWAP( "250_cmd11.p2", 0x100000, 0x400000, CRC(380d51b1) SHA1(9ededbb7d57953a614df14f7aede08fb42db7594) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX4_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmd12 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cmd12.p1", 0x000000, 0x100000, CRC(c318b4dd) SHA1(22f0034e37eed6054fb160d68c91ff6ff571b2c3) )
	ROM_LOAD16_WORD_SWAP( "250_cmd01.p2", 0x100000, 0x400000, CRC(4b2d73fb) SHA1(6db9c31083c9b94d320fd2ce051cd8dacfb077ec) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX4_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmd13 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cmd13.p1", 0x000000, 0x100000, CRC(e047ac84) SHA1(9fc0f53a5654c173fbb7dca99f2821d0ed14d23e) )
	ROM_LOAD16_WORD_SWAP( "250_cmd01.p2", 0x100000, 0x400000, CRC(4b2d73fb) SHA1(6db9c31083c9b94d320fd2ce051cd8dacfb077ec) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX4_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmd14 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cmd14.p1", 0x000000, 0x100000, CRC(c78cd195) SHA1(55eb25ec21fededa2154e8d4745d1a71d77db612) )
	ROM_LOAD16_WORD_SWAP( "250_cmd01.p2", 0x100000, 0x400000, CRC(4b2d73fb) SHA1(6db9c31083c9b94d320fd2ce051cd8dacfb077ec) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX4_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmd15 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cmd15.p1", 0x000000, 0x100000, CRC(5f2b3537) SHA1(3c6e25dd76f3daae0c274f8fc9bd68bc716ec1b8) )
	ROM_LOAD16_WORD_SWAP( "250_cmd15.p2", 0x100000, 0x400000, CRC(4732b6e2) SHA1(d1ed7707c0ec20ac135e6953510d65cd1ba038ac) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX4_LEVEL6_FILL
    MSLUGX_MVS_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
    FIX_BIOS_COIN_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmd16 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cmd16.p1", 0x000000, 0x100000, CRC(ad14998a) SHA1(1e4088ec0141bce4106c7baaa36fc8bdb172b604) )
	ROM_LOAD16_WORD_SWAP( "250_cmd16.p2", 0x100000, 0x400000, CRC(c090a0af) SHA1(2412914e337c4fd8e20a9f1ee44ff12b9acb06e3) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX4_LEVEL6_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGXDD_SPRITES
ROM_END

ROM_START( mslugxctme01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cme01.p1", 0x000000, 0x100000, CRC(d0e07e78) SHA1(84fd2f03dda0bccac6eb70d6ec8cbfcc4bb303e6) )
	ROM_LOAD16_WORD_SWAP( "250_cme01.p2", 0x100000, 0x400000, CRC(86d1585d) SHA1(fd3ff56d90a9d2b02c2d96de827ac89d224ccd9c) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX3_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctme02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cme02.p1", 0x000000, 0x100000, CRC(c3e1c21e) SHA1(27bcda5d64a43be3b9818503912a81e3e87ad8d9) )
	ROM_LOAD16_WORD_SWAP( "250_cme01.p2", 0x100000, 0x400000, CRC(86d1585d) SHA1(fd3ff56d90a9d2b02c2d96de827ac89d224ccd9c) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX3_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctme03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cme03.p1", 0x000000, 0x100000, CRC(d4f359c2) SHA1(1ebad248946cba7bc481656c500ae2fc98e886fc) )
	ROM_LOAD16_WORD_SWAP( "250_cme01.p2", 0x100000, 0x400000, CRC(86d1585d) SHA1(fd3ff56d90a9d2b02c2d96de827ac89d224ccd9c) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX3_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctme04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cme04.p1", 0x000000, 0x100000, CRC(7916d34c) SHA1(dd76fd36cc46e9bd2c711ca54bf72d275e8ec35d) )
	ROM_LOAD16_WORD_SWAP( "250_cme01.p2", 0x100000, 0x400000, CRC(86d1585d) SHA1(fd3ff56d90a9d2b02c2d96de827ac89d224ccd9c) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX3_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctme05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cme05.p1", 0x000000, 0x100000, CRC(1ff64806) SHA1(b87aa174aef575bcf7ced71724c29c55e110d20f) )
	ROM_LOAD16_WORD_SWAP( "250_cme05.p2", 0x100000, 0x400000, CRC(08e3584f) SHA1(06a6deb762c707376c0e2511bd4829e7004a0d05) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX3_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctme06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cme06.p1", 0x000000, 0x100000, CRC(d6916646) SHA1(2cb32312ba9d884f2dbe1f7c90c8402146b2ee9c) )
	ROM_LOAD16_WORD_SWAP( "250_cme01.p2", 0x100000, 0x400000, CRC(86d1585d) SHA1(fd3ff56d90a9d2b02c2d96de827ac89d224ccd9c) )
    MSLUGXV_ESSENTIALPATCH_MODS_FILL
    FIX8_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctme07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cme07.p1", 0x000000, 0x100000, CRC(d20afcfd) SHA1(33e796b91fda896394c22ae864a6482410836493) )
	ROM_LOAD16_WORD_SWAP( "250_cme01.p2", 0x100000, 0x400000, CRC(86d1585d) SHA1(fd3ff56d90a9d2b02c2d96de827ac89d224ccd9c) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX3_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctme08 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cme08.p1", 0x000000, 0x100000, CRC(4729885c) SHA1(feeb5cf02a0479de0f36363cafe9cc87d1880a84) )
	ROM_LOAD16_WORD_SWAP( "250_cme01.p2", 0x100000, 0x400000, CRC(86d1585d) SHA1(fd3ff56d90a9d2b02c2d96de827ac89d224ccd9c) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX3_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctme09 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cme09.p1", 0x000000, 0x100000, CRC(43f70723) SHA1(5a85d5ebb8a6a239b728ee5e51add8a5136d00bc) )
	ROM_LOAD16_WORD_SWAP( "250_cme01.p2", 0x100000, 0x400000, CRC(86d1585d) SHA1(fd3ff56d90a9d2b02c2d96de827ac89d224ccd9c) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX3_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctme10 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cme10.p1", 0x000000, 0x100000, CRC(e2f8ae43) SHA1(c0de81f255dfe024d15dec3636214dbed5bbd30b) )
	ROM_LOAD16_WORD_SWAP( "250_cme01.p2", 0x100000, 0x400000, CRC(86d1585d) SHA1(fd3ff56d90a9d2b02c2d96de827ac89d224ccd9c) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX3_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctme11 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cme11.p1", 0x000000, 0x100000, CRC(f350451f) SHA1(6f64cdd06658d0124ff1e11c4c72baa6799832c6) )
	ROM_LOAD16_WORD_SWAP( "250_cme11.p2", 0x100000, 0x400000, CRC(727d86e6) SHA1(860c97954dc0f037881bd40966ff4472c81b4f51) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX3_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctme12 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cme12.p1", 0x000000, 0x100000, CRC(b1e25f2a) SHA1(d6380b3c036b069aa7d716138d2b0b24a40d9542) )
	ROM_LOAD16_WORD_SWAP( "250_cme01.p2", 0x100000, 0x400000, CRC(86d1585d) SHA1(fd3ff56d90a9d2b02c2d96de827ac89d224ccd9c) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX3_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctme13 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cme13.p1", 0x000000, 0x100000, CRC(92bd4773) SHA1(959e67c218691b19135958a29826f1c3b9d35965) )
	ROM_LOAD16_WORD_SWAP( "250_cme01.p2", 0x100000, 0x400000, CRC(86d1585d) SHA1(fd3ff56d90a9d2b02c2d96de827ac89d224ccd9c) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX3_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctme14 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cme14.p1", 0x000000, 0x100000, CRC(b5763a62) SHA1(cc3324e7ab2ac749335429fb0f13a170633a619d) )
	ROM_LOAD16_WORD_SWAP( "250_cme01.p2", 0x100000, 0x400000, CRC(86d1585d) SHA1(fd3ff56d90a9d2b02c2d96de827ac89d224ccd9c) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX3_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctme15 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cme15.p1", 0x000000, 0x100000, CRC(2dd1dec0) SHA1(eb046fe0a2f122f3e9df87bd7f40245eb5da1f7a) )
	ROM_LOAD16_WORD_SWAP( "250_cme15.p2", 0x100000, 0x400000, CRC(0938b723) SHA1(5b62af4179dadf1e1c9a78add515c60f098e8ced) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX3_LEVEL6_FILL
    MSLUGX_MVS_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
    FIX_BIOS_COIN_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctme16 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_cme16.p1", 0x000000, 0x100000, CRC(dfee727d) SHA1(c0236b53f5bbf34c996ad036a7d2c5fe4fde19e3) )
	ROM_LOAD16_WORD_SWAP( "250_cme16.p2", 0x100000, 0x400000, CRC(8e9aa16e) SHA1(c87450f0bfa9a7498e84d952501f2b61902fa409) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    FIX3_LEVEL6_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGXDD_SPRITES
ROM_END

ROM_START( mslugxctmf01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc06.p1", 0x000000, 0x100000, CRC(a507546f) SHA1(ab6e9e969c2b3728cb0b13e0b1d62bda09037ac0) )
	ROM_LOAD16_WORD_SWAP( "250_hc01.p2", 0x100000, 0x400000, CRC(5d1c52cd) SHA1(b2b131fa845b0098cbf0750fee20b402e276483b) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmf02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc13.p1", 0x000000, 0x100000, CRC(b606e809) SHA1(a477647cf470a115b9df1d37ab859188de49f9a9) )
	ROM_LOAD16_WORD_SWAP( "250_hc01.p2", 0x100000, 0x400000, CRC(5d1c52cd) SHA1(b2b131fa845b0098cbf0750fee20b402e276483b) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmf03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc14.p1", 0x000000, 0x100000, CRC(a11473d5) SHA1(83f6665e88e8b9d33545e5c57ac8a5e923787bd2) )
	ROM_LOAD16_WORD_SWAP( "250_hc01.p2", 0x100000, 0x400000, CRC(5d1c52cd) SHA1(b2b131fa845b0098cbf0750fee20b402e276483b) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmf04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc17.p1", 0x000000, 0x100000, CRC(0cf1f95b) SHA1(857af8721c5929ba7c60e16223cab4879ec382b9) )
	ROM_LOAD16_WORD_SWAP( "250_hc01.p2", 0x100000, 0x400000, CRC(5d1c52cd) SHA1(b2b131fa845b0098cbf0750fee20b402e276483b) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmf05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc18.p1",  0x000000, 0x100000, CRC(6a116211) SHA1(92b1d87248e03d21eb87201cbadc5de0eaaf4b47) )
	ROM_LOAD16_WORD_SWAP( "250_cmf05.p2", 0x100000, 0x400000, CRC(d32e52df) SHA1(ce14485e8b89d65a623bcb95a178d72e666ea53d) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmf06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc29.p1", 0x000000, 0x100000, CRC(a3764c51) SHA1(791e23b6953aba236fe18182efa7445291c991ba) )
	ROM_LOAD16_WORD_SWAP( "250_hc01.p2", 0x100000, 0x400000, CRC(5d1c52cd) SHA1(b2b131fa845b0098cbf0750fee20b402e276483b) )
    MSLUGXV_ESSENTIALPATCH_MODS_FILL
    FIX1_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmf07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc32.p1", 0x000000, 0x100000, CRC(a7edd6ea) SHA1(d0bca9bbcfd1458ed9777b319b92fd1ebf9e5a89) )
	ROM_LOAD16_WORD_SWAP( "250_hc01.p2", 0x100000, 0x400000, CRC(5d1c52cd) SHA1(b2b131fa845b0098cbf0750fee20b402e276483b) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmf08 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc34.p1", 0x000000, 0x100000, CRC(32cea24b) SHA1(059a2f3d70667e8202918f14c9a6d6142f6866d8) )
	ROM_LOAD16_WORD_SWAP( "250_hc01.p2", 0x100000, 0x400000, CRC(5d1c52cd) SHA1(b2b131fa845b0098cbf0750fee20b402e276483b) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmf09 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc04.p1", 0x000000, 0x100000, CRC(36102d34) SHA1(b60d41e7cd3395910e7aa5cc0a843d68bfcc2ac6) )
	ROM_LOAD16_WORD_SWAP( "250_hc01.p2", 0x100000, 0x400000, CRC(5d1c52cd) SHA1(b2b131fa845b0098cbf0750fee20b402e276483b) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmf10 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc36.p1", 0x000000, 0x100000, CRC(971f8454) SHA1(73033339931de870bb5a5a64f34ce51c63c4ed15) )
	ROM_LOAD16_WORD_SWAP( "250_hc01.p2", 0x100000, 0x400000, CRC(5d1c52cd) SHA1(b2b131fa845b0098cbf0750fee20b402e276483b) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmf11 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc26.p1",  0x000000, 0x100000, CRC(f86ea146) SHA1(c30a69749da8b0bda5231ac4e121dd90a65d0a96) )
	ROM_LOAD16_WORD_SWAP( "250_cmf11.p2", 0x100000, 0x400000, CRC(4977e13c) SHA1(78668f284eadc31e8304bc4ba1baff34ae85615b) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmf12 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc10.p1", 0x000000, 0x100000, CRC(c405753d) SHA1(bed7426145fd15e972334d7ef04759edcccd8864) )
	ROM_LOAD16_WORD_SWAP( "250_hc01.p2", 0x100000, 0x400000, CRC(5d1c52cd) SHA1(b2b131fa845b0098cbf0750fee20b402e276483b) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmf13 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc16.p1", 0x000000, 0x100000, CRC(e75a6d64) SHA1(529130f7ebb43231e6bf1b1703266b6c09356f9c) )
	ROM_LOAD16_WORD_SWAP( "250_hc01.p2", 0x100000, 0x400000, CRC(5d1c52cd) SHA1(b2b131fa845b0098cbf0750fee20b402e276483b) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmf14 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc08.p1", 0x000000, 0x100000, CRC(c0911075) SHA1(2645c9d59915811addc2ab048afbfb9e605bca24) )
	ROM_LOAD16_WORD_SWAP( "250_hc01.p2", 0x100000, 0x400000, CRC(5d1c52cd) SHA1(b2b131fa845b0098cbf0750fee20b402e276483b) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmf15 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc28.p1",  0x000000, 0x100000, CRC(5836f4d7) SHA1(002c6a519c118d33e3cef92066b0e8fc96f52627) )
	ROM_LOAD16_WORD_SWAP( "250_cmf15.p2", 0x100000, 0x400000, CRC(4f11765d) SHA1(86d51eecc66229fb7c5ae8ff5ec78cc94ac9c030) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
    FIX_BIOS_COIN_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmf16 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc24.p1",  0x000000, 0x100000, CRC(aa09586a) SHA1(246579b58babcf696f988a2d57dc8fab0019b3de) )
	ROM_LOAD16_WORD_SWAP( "250_cmf16.p2", 0x100000, 0x400000, CRC(e9526eea) SHA1(e6e87c7c8c90c931d744855704de3fccf7cbfccd) )
    MSLUGX_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGXDD_SPRITES
ROM_END

ROM_START( mslugxctmg01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc06.p1", 0x000000, 0x100000, CRC(a507546f) SHA1(ab6e9e969c2b3728cb0b13e0b1d62bda09037ac0) )
	ROM_LOAD16_WORD_SWAP( "250_hc15.p2", 0x100000, 0x400000, CRC(0efc5d67) SHA1(21a370ebc96e1b17ecfb12085732512dc51491d3) )
    MSLUGXXR_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmg02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc13.p1", 0x000000, 0x100000, CRC(b606e809) SHA1(a477647cf470a115b9df1d37ab859188de49f9a9) )
	ROM_LOAD16_WORD_SWAP( "250_hc15.p2", 0x100000, 0x400000, CRC(0efc5d67) SHA1(21a370ebc96e1b17ecfb12085732512dc51491d3) )
    MSLUGXXR_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmg03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc14.p1", 0x000000, 0x100000, CRC(a11473d5) SHA1(83f6665e88e8b9d33545e5c57ac8a5e923787bd2) )
	ROM_LOAD16_WORD_SWAP( "250_hc15.p2", 0x100000, 0x400000, CRC(0efc5d67) SHA1(21a370ebc96e1b17ecfb12085732512dc51491d3) )
    MSLUGXXR_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmg04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc17.p1", 0x000000, 0x100000, CRC(0cf1f95b) SHA1(857af8721c5929ba7c60e16223cab4879ec382b9) )
	ROM_LOAD16_WORD_SWAP( "250_hc15.p2", 0x100000, 0x400000, CRC(0efc5d67) SHA1(21a370ebc96e1b17ecfb12085732512dc51491d3) )
    MSLUGXXR_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmg05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc18.p1",  0x000000, 0x100000, CRC(6a116211) SHA1(92b1d87248e03d21eb87201cbadc5de0eaaf4b47) )
	ROM_LOAD16_WORD_SWAP( "250_cmg05.p2", 0x100000, 0x400000, CRC(80ce5d75) SHA1(4fc3dd33b0040513848574a744712abf9abd9736) )
    MSLUGXXR_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmg06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc29.p1", 0x000000, 0x100000, CRC(a3764c51) SHA1(791e23b6953aba236fe18182efa7445291c991ba) )
	ROM_LOAD16_WORD_SWAP( "250_hc15.p2", 0x100000, 0x400000, CRC(0efc5d67) SHA1(21a370ebc96e1b17ecfb12085732512dc51491d3) )
    MSLUGXV_ESSENTIALPATCH_MODS_FILL
	FIX2_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmg07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc32.p1", 0x000000, 0x100000, CRC(a7edd6ea) SHA1(d0bca9bbcfd1458ed9777b319b92fd1ebf9e5a89) )
	ROM_LOAD16_WORD_SWAP( "250_hc15.p2", 0x100000, 0x400000, CRC(0efc5d67) SHA1(21a370ebc96e1b17ecfb12085732512dc51491d3) )
    MSLUGXXR_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmg08 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc34.p1", 0x000000, 0x100000, CRC(32cea24b) SHA1(059a2f3d70667e8202918f14c9a6d6142f6866d8) )
	ROM_LOAD16_WORD_SWAP( "250_hc15.p2", 0x100000, 0x400000, CRC(0efc5d67) SHA1(21a370ebc96e1b17ecfb12085732512dc51491d3) )
    MSLUGXXR_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmg09 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc04.p1", 0x000000, 0x100000, CRC(36102d34) SHA1(b60d41e7cd3395910e7aa5cc0a843d68bfcc2ac6) )
	ROM_LOAD16_WORD_SWAP( "250_hc15.p2", 0x100000, 0x400000, CRC(0efc5d67) SHA1(21a370ebc96e1b17ecfb12085732512dc51491d3) )
    MSLUGXXR_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmg10 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc36.p1", 0x000000, 0x100000, CRC(971f8454) SHA1(73033339931de870bb5a5a64f34ce51c63c4ed15) )
	ROM_LOAD16_WORD_SWAP( "250_hc15.p2", 0x100000, 0x400000, CRC(0efc5d67) SHA1(21a370ebc96e1b17ecfb12085732512dc51491d3) )
    MSLUGXXR_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmg11 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc26.p1",  0x000000, 0x100000, CRC(f86ea146) SHA1(c30a69749da8b0bda5231ac4e121dd90a65d0a96) )
	ROM_LOAD16_WORD_SWAP( "250_cmg11.p2", 0x100000, 0x400000, CRC(debe6726) SHA1(f7a6c1387952accfd86afcaa353d65ea33410cff) )
    MSLUGXXR_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmg12 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc10.p1", 0x000000, 0x100000, CRC(c405753d) SHA1(bed7426145fd15e972334d7ef04759edcccd8864) )
	ROM_LOAD16_WORD_SWAP( "250_hc15.p2", 0x100000, 0x400000, CRC(0efc5d67) SHA1(21a370ebc96e1b17ecfb12085732512dc51491d3) )
    MSLUGXXR_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmg13 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc16.p1", 0x000000, 0x100000, CRC(e75a6d64) SHA1(529130f7ebb43231e6bf1b1703266b6c09356f9c) )
	ROM_LOAD16_WORD_SWAP( "250_hc15.p2", 0x100000, 0x400000, CRC(0efc5d67) SHA1(21a370ebc96e1b17ecfb12085732512dc51491d3) )
    MSLUGXXR_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmg14 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc08.p1", 0x000000, 0x100000, CRC(c0911075) SHA1(2645c9d59915811addc2ab048afbfb9e605bca24) )
	ROM_LOAD16_WORD_SWAP( "250_hc15.p2", 0x100000, 0x400000, CRC(0efc5d67) SHA1(21a370ebc96e1b17ecfb12085732512dc51491d3) )
    MSLUGXXR_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmg15 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc28.p1",  0x000000, 0x100000, CRC(5836f4d7) SHA1(002c6a519c118d33e3cef92066b0e8fc96f52627) )
	ROM_LOAD16_WORD_SWAP( "250_cmg15.p2", 0x100000, 0x400000, CRC(d8d8f047) SHA1(ccf7bc4d4eab7ac626387f38a1a8f9d93035d069) )
    MSLUGXXR_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
    FIX_BIOS_COIN_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmg16 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc24.p1",  0x000000, 0x100000, CRC(aa09586a) SHA1(246579b58babcf696f988a2d57dc8fab0019b3de) )
	ROM_LOAD16_WORD_SWAP( "250_cmg16.p2", 0x100000, 0x400000, CRC(7e9be8f0) SHA1(a9dbbddbc73fbdeb94dc15d35cb4a7e75c007241) )
    MSLUGXXR_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGXDD_SPRITES
ROM_END

ROM_START( mslugxctmh01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc06.p1",  0x000000, 0x100000, CRC(a507546f) SHA1(ab6e9e969c2b3728cb0b13e0b1d62bda09037ac0) )
	ROM_LOAD16_WORD_SWAP( "250_cmh01.p2", 0x100000, 0x400000, CRC(509261ef) SHA1(4c740c8cbf47d3fbd84f913944240a31c1add208) )
    MSLUGXSC_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmh02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc13.p1",  0x000000, 0x100000, CRC(b606e809) SHA1(a477647cf470a115b9df1d37ab859188de49f9a9) )
	ROM_LOAD16_WORD_SWAP( "250_cmh01.p2", 0x100000, 0x400000, CRC(509261ef) SHA1(4c740c8cbf47d3fbd84f913944240a31c1add208) )
    MSLUGXSC_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmh03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc14.p1",  0x000000, 0x100000, CRC(a11473d5) SHA1(83f6665e88e8b9d33545e5c57ac8a5e923787bd2) )
	ROM_LOAD16_WORD_SWAP( "250_cmh01.p2", 0x100000, 0x400000, CRC(509261ef) SHA1(4c740c8cbf47d3fbd84f913944240a31c1add208) )
    MSLUGXSC_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmh04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc17.p1",  0x000000, 0x100000, CRC(0cf1f95b) SHA1(857af8721c5929ba7c60e16223cab4879ec382b9) )
	ROM_LOAD16_WORD_SWAP( "250_cmh01.p2", 0x100000, 0x400000, CRC(509261ef) SHA1(4c740c8cbf47d3fbd84f913944240a31c1add208) )
    MSLUGXSC_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmh05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc18.p1",  0x000000, 0x100000, CRC(6a116211) SHA1(92b1d87248e03d21eb87201cbadc5de0eaaf4b47) )
	ROM_LOAD16_WORD_SWAP( "250_cmh05.p2", 0x100000, 0x400000, CRC(dea061fd) SHA1(5acff7c0b734a80fc22434f4eba2a1490f164bcd) )
    MSLUGXSC_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmh06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc29.p1",  0x000000, 0x100000, CRC(a3764c51) SHA1(791e23b6953aba236fe18182efa7445291c991ba) )
	ROM_LOAD16_WORD_SWAP( "250_cmh01.p2", 0x100000, 0x400000, CRC(509261ef) SHA1(4c740c8cbf47d3fbd84f913944240a31c1add208) )
    MSLUGXV_ESSENTIALPATCH_MODS_FILL
    FIX7_LEVEL6_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmh07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc32.p1",  0x000000, 0x100000, CRC(a7edd6ea) SHA1(d0bca9bbcfd1458ed9777b319b92fd1ebf9e5a89) )
	ROM_LOAD16_WORD_SWAP( "250_cmh01.p2", 0x100000, 0x400000, CRC(509261ef) SHA1(4c740c8cbf47d3fbd84f913944240a31c1add208) )
    MSLUGXSC_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmh08 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc34.p1",  0x000000, 0x100000, CRC(32cea24b) SHA1(059a2f3d70667e8202918f14c9a6d6142f6866d8) )
	ROM_LOAD16_WORD_SWAP( "250_cmh01.p2", 0x100000, 0x400000, CRC(509261ef) SHA1(4c740c8cbf47d3fbd84f913944240a31c1add208) )
    MSLUGXSC_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmh09 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc04.p1",  0x000000, 0x100000, CRC(36102d34) SHA1(b60d41e7cd3395910e7aa5cc0a843d68bfcc2ac6) )
	ROM_LOAD16_WORD_SWAP( "250_cmh01.p2", 0x100000, 0x400000, CRC(509261ef) SHA1(4c740c8cbf47d3fbd84f913944240a31c1add208) )
    MSLUGXSC_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmh10 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc36.p1",  0x000000, 0x100000, CRC(971f8454) SHA1(73033339931de870bb5a5a64f34ce51c63c4ed15) )
	ROM_LOAD16_WORD_SWAP( "250_cmh01.p2", 0x100000, 0x400000, CRC(509261ef) SHA1(4c740c8cbf47d3fbd84f913944240a31c1add208) )
    MSLUGXSC_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmh11 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc26.p1",  0x000000, 0x100000, CRC(f86ea146) SHA1(c30a69749da8b0bda5231ac4e121dd90a65d0a96) )
	ROM_LOAD16_WORD_SWAP( "250_cmh11.p2", 0x100000, 0x400000, CRC(52ef6d68) SHA1(e7bb45f78565d95285972928cffb9c8ec007df78) )
    MSLUGXSC_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmh12 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc10.p1",  0x000000, 0x100000, CRC(c405753d) SHA1(bed7426145fd15e972334d7ef04759edcccd8864) )
	ROM_LOAD16_WORD_SWAP( "250_cmh01.p2", 0x100000, 0x400000, CRC(509261ef) SHA1(4c740c8cbf47d3fbd84f913944240a31c1add208) )
    MSLUGXSC_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmh13 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc16.p1",  0x000000, 0x100000, CRC(e75a6d64) SHA1(529130f7ebb43231e6bf1b1703266b6c09356f9c) )
	ROM_LOAD16_WORD_SWAP( "250_cmh01.p2", 0x100000, 0x400000, CRC(509261ef) SHA1(4c740c8cbf47d3fbd84f913944240a31c1add208) )
    MSLUGXSC_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmh14 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc08.p1",  0x000000, 0x100000, CRC(c0911075) SHA1(2645c9d59915811addc2ab048afbfb9e605bca24) )
	ROM_LOAD16_WORD_SWAP( "250_cmh01.p2", 0x100000, 0x400000, CRC(509261ef) SHA1(4c740c8cbf47d3fbd84f913944240a31c1add208) )
    MSLUGXSC_ESSENTIALPATCH_MODS_FILL
	MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
    MSLUGX_YMSND
    MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmh15 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc28.p1",  0x000000, 0x100000, CRC(5836f4d7) SHA1(002c6a519c118d33e3cef92066b0e8fc96f52627) )
	ROM_LOAD16_WORD_SWAP( "250_cmh15.p2", 0x100000, 0x400000, CRC(5489fa09) SHA1(d570a3aae609c2ff4eeb72a6c25d6a6a81b483a7) )
    MSLUGXSC_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
    FIX_BIOS_COIN_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxctmh16 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc24.p1",  0x000000, 0x100000, CRC(aa09586a) SHA1(246579b58babcf696f988a2d57dc8fab0019b3de) )
	ROM_LOAD16_WORD_SWAP( "250_cmh16.p2", 0x100000, 0x400000, CRC(f2cae2be) SHA1(b29db91de158ad63b663af8e874a446b643ae8b9) )
    MSLUGXSC_ESSENTIALPATCH_MODS_FILL
    MSLUGX_MVS_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGXDD_SPRITES
ROM_END

ROM_START( mslugxctmi01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_hc25.p1",  0x000000, 0x100000, CRC(e0792609) SHA1(e98096a5ad7181e95cf544cd345693599ecce08a) )
	ROM_LOAD16_WORD_SWAP( "250_cmi01.p2", 0x100000, 0x400000, CRC(b8ae4218) SHA1(7bed062d527fb0dca6086159383a604831ff7c9f) )
    MSLUGXSC_ESSENTIALPATCH_MODS_FILL
    MSLUGXSC_MVS_FILL
    MSLUGX_MVS_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
    AUDIOBIOS_128K
    MSLUGXSC_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXCQ_SPRITES
ROM_END

/************************
 Version Remastering
**************************/

ROM_START( mslug3ly01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_ly01.p1", 0x000000, 0x100000, CRC(c721577c) SHA1(43fc3cbcccc0e181282d24d74a46d7c3e077dde3) )
	ROM_LOAD16_WORD_SWAP( "256_ly01.p2", 0x100000, 0x400000, CRC(2e73c3e6) SHA1(9daf7b0b0fdb01e85913520c247bd282b2abbb25) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
	MSLUG3RMTERZ_SPRITES
ROM_END

ROM_START( mslug3ly02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_ly02.p1", 0x000000, 0x100000, CRC(332ae55e) SHA1(1cebb668278be9b8eaaba61a4e48256bf9f75f99) )
	ROM_LOAD16_WORD_SWAP( "256_ly01.p2", 0x100000, 0x400000, CRC(2e73c3e6) SHA1(9daf7b0b0fdb01e85913520c247bd282b2abbb25) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
	MSLUG3RMTERZ_SPRITES
ROM_END

ROM_START( mslug3ly03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_ly03.p1", 0x000000, 0x100000, CRC(7c43b5a0) SHA1(28106f26cfe16bbb01baf3598171e0386ba82b4f) )
	ROM_LOAD16_WORD_SWAP( "256_ly01.p2", 0x100000, 0x400000, CRC(2e73c3e6) SHA1(9daf7b0b0fdb01e85913520c247bd282b2abbb25) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
	MSLUG3RMTERZ_SPRITES
ROM_END

ROM_START( mslug3ly04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_ly04.p1", 0x000000, 0x100000, CRC(2d877c3a) SHA1(1c93d648708c7879b77936b349f9ccef972e9f6e) )
	ROM_LOAD16_WORD_SWAP( "256_ly01.p2", 0x100000, 0x400000, CRC(2e73c3e6) SHA1(9daf7b0b0fdb01e85913520c247bd282b2abbb25) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
	MSLUG3RMTERZ_SPRITES
ROM_END

ROM_START( mslug3ly05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_ly05.p1", 0x000000, 0x100000, CRC(4c7e5522) SHA1(39fa7c1403b9752a31db09c37eecc85a7ba02dbd) )
	ROM_LOAD16_WORD_SWAP( "256_ly01.p2", 0x100000, 0x400000, CRC(2e73c3e6) SHA1(9daf7b0b0fdb01e85913520c247bd282b2abbb25) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
	MSLUG3RMTERZ_SPRITES
ROM_END

ROM_START( mslug3ly06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_ly06.p1", 0x000000, 0x100000, CRC(a68853ce) SHA1(cfbcad74e012f7cf914b1ce4646fbb015a358c66) )
	ROM_LOAD16_WORD_SWAP( "256_ly01.p2", 0x100000, 0x400000, CRC(2e73c3e6) SHA1(9daf7b0b0fdb01e85913520c247bd282b2abbb25) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
	MSLUG3RMTERZ_SPRITES
ROM_END

ROM_START( mslug3ly07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_ly07.p1", 0x000000, 0x100000, CRC(2a40ac4f) SHA1(1147c9425b645a3785c84d19869cb275aab2c4de) )
	ROM_LOAD16_WORD_SWAP( "256_ly01.p2", 0x100000, 0x400000, CRC(2e73c3e6) SHA1(9daf7b0b0fdb01e85913520c247bd282b2abbb25) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
	MSLUG3RMTERZ_SPRITES
ROM_END

ROM_START( mslugxer01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_er01.p1", 0x000000, 0x100000, CRC(5a1a32e4) SHA1(59955cb295904dd542a1d1ae4ff573edd71f6939) )
	ROM_LOAD16_WORD_SWAP( "250_er01.p2", 0x100000, 0x400000, CRC(26c43520) SHA1(0001d35829021df68a65ded4bc2955c3c5d29f15) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
    AUDIOBIOS_128K
    MSLUGXSC_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXER_SPRITES
ROM_END

ROM_START( mslugxer02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_er01.p1", 0x000000, 0x100000, CRC(5a1a32e4) SHA1(59955cb295904dd542a1d1ae4ff573edd71f6939) )
	ROM_LOAD16_WORD_SWAP( "250_er02.p2", 0x100000, 0x400000, CRC(0e9c591d) SHA1(3a41579e79e6150f4644ec4b9fac6fe106bf3c0d) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
    AUDIOBIOS_128K
    MSLUGXSC_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXER_SPRITES
ROM_END

ROM_START( mslugxer03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_er01.p1", 0x000000, 0x100000, CRC(5a1a32e4) SHA1(59955cb295904dd542a1d1ae4ff573edd71f6939) )
	ROM_LOAD16_WORD_SWAP( "250_er03.p2", 0x100000, 0x400000, CRC(c156661f) SHA1(c9d2b43c237851d319a2ed8c6e7348d0f2e2ce70) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
    AUDIOBIOS_128K
    MSLUGXSC_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXER_SPRITES
ROM_END

ROM_START( mslugxer04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_er04.p1", 0x000000, 0x100000, CRC(bead154b) SHA1(10ca67164a9ab349199f10511c9fb53da7ce81e8) )
	ROM_LOAD16_WORD_SWAP( "250_er04.p2", 0x100000, 0x400000, CRC(b79b9f68) SHA1(aa33e9e450b8530b31af76aa55f5322ac5888e6e) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
    AUDIOBIOS_128K
    MSLUGXSC_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXER_SPRITES
ROM_END

ROM_START( mslugxer05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_er05.p1", 0x000000, 0x100000, CRC(3db2a16d) SHA1(b3eed3cab35f5a55d68dd6612b703e45e8142307) )
	ROM_LOAD16_WORD_SWAP( "250_er05.p2", 0x100000, 0x400000, CRC(8f1c7d24) SHA1(d32127573a7473a16d0b4c0f8e1cbae54aacd699) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
    AUDIOBIOS_128K
    MSLUGXSC_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXER_SPRITES
ROM_END

ROM_START( mslugxer06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_er01.p1", 0x000000, 0x100000, CRC(5a1a32e4) SHA1(59955cb295904dd542a1d1ae4ff573edd71f6939) )
	ROM_LOAD16_WORD_SWAP( "250_er06.p2", 0x100000, 0x400000, CRC(9edf51d1) SHA1(8b16e82c5b0c76c33350d3c4d69d5b07f20d1b96) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
    AUDIOBIOS_128K
    MSLUGXSC_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXER_SPRITES
ROM_END

ROM_START( mslugxer07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_er01.p1", 0x000000, 0x100000, CRC(5a1a32e4) SHA1(59955cb295904dd542a1d1ae4ff573edd71f6939) )
	ROM_LOAD16_WORD_SWAP( "250_er07.p2", 0x100000, 0x400000, CRC(68bd7a19) SHA1(f1c216e6fd23fb1fdfba50650989605f8cea2e2b) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
    AUDIOBIOS_128K
    MSLUGXSC_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXER_SPRITES
ROM_END

/**************************
 Apocalyptic Time Edition
*****************************/

ROM_START( mslug2at01 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_at01.p1",     0x000000, 0x100000, CRC(323786b0) SHA1(fcc7ce4c5c61862800c02dc15ed9d831ec2d2eee) )
	ROM_LOAD16_WORD_SWAP( "241_at01.p2",     0x100000, 0x200000, CRC(83931ab6) SHA1(bd5b527180b3a01eda89d862c08f5414d538fab9) )
    MSLUG2_MVS_FILL
    MSLUG2_AES_FILL
    MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslugxtst01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_at01.p1",  0x000000, 0x100000, CRC(be79f97a) SHA1(970284113cd7683b511fa6fc562fdc17796e93cc) )
	ROM_LOAD16_WORD_SWAP( "250_tst01.p2", 0x100000, 0x400000, CRC(9ddd0f21) SHA1(bbeea5ed3c4021bd14249b416e25ff88731b8a65) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    FIX_LEVEL3_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxtao01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_at01.p1",  0x000000, 0x100000, CRC(be79f97a) SHA1(970284113cd7683b511fa6fc562fdc17796e93cc) )
	ROM_LOAD16_WORD_SWAP( "250_ao01.p2",  0x100000, 0x400000, CRC(ee8f9d31) SHA1(d99ca53fc94b869b4ddd2d4de633a0a78827d01e) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    FIX_LEVEL3_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxat01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_at01.p1", 0x000000, 0x100000, CRC(be79f97a) SHA1(970284113cd7683b511fa6fc562fdc17796e93cc) )
	ROM_LOAD16_WORD_SWAP( "250_at01.p2", 0x100000, 0x400000, CRC(94fce740) SHA1(9cb3ac56df2104eb2b623eb238fd3734df46e52d) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    FIX1_LEVEL6_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxat02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_at01.p1", 0x000000, 0x100000, CRC(be79f97a) SHA1(970284113cd7683b511fa6fc562fdc17796e93cc) )
	ROM_LOAD16_WORD_SWAP( "250_at02.p2", 0x100000, 0x400000, CRC(0da76952) SHA1(d2544a4153fa8e6edd593bd9b672f76c73a9f123) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    FIX_LEVEL3_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxat03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_at01.p1", 0x000000, 0x100000, CRC(be79f97a) SHA1(970284113cd7683b511fa6fc562fdc17796e93cc) )
	ROM_LOAD16_WORD_SWAP( "250_at03.p2", 0x100000, 0x400000, CRC(97839838) SHA1(1186ba34ca4423ee0fa19db19d9ae79811c8117d) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    FIX_LEVEL3_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxat04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_at01.p1", 0x000000, 0x100000, CRC(be79f97a) SHA1(970284113cd7683b511fa6fc562fdc17796e93cc) )
	ROM_LOAD16_WORD_SWAP( "250_at04.p2", 0x100000, 0x400000, CRC(1ad67b97) SHA1(70ec0cc7f4316027dcd4108bcbc06780df69067a) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    FIX_LEVEL3_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxat05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_at01.p1", 0x000000, 0x100000, CRC(be79f97a) SHA1(970284113cd7683b511fa6fc562fdc17796e93cc) )
	ROM_LOAD16_WORD_SWAP( "250_at05.p2", 0x100000, 0x400000, CRC(8713362a) SHA1(52f4fd9f34aa9738f30fec6e418163ebf3cf8417) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    FIX_LEVEL3_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxat06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_at01.p1", 0x000000, 0x100000, CRC(be79f97a) SHA1(970284113cd7683b511fa6fc562fdc17796e93cc) )
	ROM_LOAD16_WORD_SWAP( "250_at06.p2", 0x100000, 0x400000, CRC(e17e2ba5) SHA1(5ded8fc351926555c71edbab66e7b6e8a82729a0) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    FIX_LEVEL4_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxat07 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_at01.p1", 0x000000, 0x100000, CRC(be79f97a) SHA1(970284113cd7683b511fa6fc562fdc17796e93cc) )
	ROM_LOAD16_WORD_SWAP( "250_at07.p2", 0x100000, 0x400000, CRC(67e0d521) SHA1(aac12a294c031fe8b06228ee2a01b87537d5b49a) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    FIX2_LEVEL6_FILL
    MSLUGX_AES_FILL
    MSLUGX_SFIX_128K
    MSLUGX_AUDIO_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxat08 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_at08.p1", 0x000000, 0x100000, CRC(a6bc7d09) SHA1(f6818072d0f5123526b2f7c0852599e2b5a665b4) )
	ROM_LOAD16_WORD_SWAP( "250_at08.p2", 0x100000, 0x400000, CRC(96cda2b9) SHA1(d9eff5de6578c04d05110239c61b3390f35e2547) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGX_SPRITES
ROM_END

ROM_START( mslugxat09 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_at09.p1", 0x000000, 0x100000, CRC(4f365912) SHA1(a4fd6ab9bad2093323676e8877e2b9ef0688156d) )
	ROM_LOAD16_WORD_SWAP( "250_at09.p2", 0x100000, 0x400000, CRC(9d8ec80f) SHA1(9b75d57a7e71574144936c05073e8538ad2fed83) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxat10 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_at10.p1", 0x000000, 0x100000, CRC(76aed1e2) SHA1(0308d3d49a7967657ef5e6b1f2784484654af312) )
	ROM_LOAD16_WORD_SWAP( "250_at10.p2", 0x100000, 0x400000, CRC(fd7f67ae) SHA1(2f60ae3a130d766acf21c89d6b557018e30c5252) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

 /**************
 Remix Edition
*****************/

ROM_START( mslugla01 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "201_la01.p1", 0x100000, 0x100000, CRC(a81e2fd3) SHA1(a86667791e162986b5cc5a4ab5469e1991849b99) )
	ROM_CONTINUE( 0x000000, 0x100000 )
    MSLUG_CUSTOMPATCH_MODS_FILL
    MSLUG_AES_FILL
	MSLUG_SFIX_128K
	MSLUG_AUDIO_128K
    MSLUG_YMSND
    MSLUG_SPRITES
ROM_END

ROM_START( mslug2la01 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_la01.p1", 0x000000, 0x100000, CRC(2efbb752) SHA1(009928a09a1ab39a45e37ddc6ba5f20f5a073774) )
	ROM_LOAD16_WORD_SWAP( "241_la01.p2", 0x100000, 0x200000, CRC(3a55eb87) SHA1(b82c41988f3d6752bd5de78eef254f924785f6a1) )
    MSLUG2_CUSTOMPATCH_MODS_FILL
    MSLUG2_AES_FILL
    MSLUG2FR_SFIX_128K
	MSLUG2_AUDIO_128K
    MSLUG2_YMSND
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2la02 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_la01.p1", 0x000000, 0x100000, CRC(2efbb752) SHA1(009928a09a1ab39a45e37ddc6ba5f20f5a073774) )
	ROM_LOAD16_WORD_SWAP( "241_la01.p2", 0x100000, 0x200000, CRC(3a55eb87) SHA1(b82c41988f3d6752bd5de78eef254f924785f6a1) )
    MSLUG2_CUSTOMPATCH_MODS_FILL
    MSLUG2_FATPLAYERS_MODS_FILL
    MSLUG2_AES_FILL
    MSLUG2FR_SFIX_128K
	MSLUG2_AUDIO_128K
    MSLUG2_YMSND
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2la03 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_la03.p1", 0x000000, 0x100000, CRC(61af823f) SHA1(4df1ede8bfa4ef484acae5da8cc81e239024cf13) )
	ROM_LOAD16_WORD_SWAP( "241_la03.p2", 0x100000, 0x200000, CRC(192b65e9) SHA1(40b8380306f96a95abe6b638eb786400655535b1) )
    MSLUG2_CUSTOMPATCH_MODS_FILL
    MSLUG2_AES_FILL
    MSLUG2FR_SFIX_128K
	MSLUG2_AUDIO_128K
    MSLUG2_YMSND
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2la04 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_la03.p1", 0x000000, 0x100000, CRC(61af823f) SHA1(4df1ede8bfa4ef484acae5da8cc81e239024cf13) )
	ROM_LOAD16_WORD_SWAP( "241_la03.p2", 0x100000, 0x200000, CRC(192b65e9) SHA1(40b8380306f96a95abe6b638eb786400655535b1) )
    MSLUG2_CUSTOMPATCH_MODS_FILL
    MSLUG2_FATPLAYERS_MODS_FILL
    MSLUG2_AES_FILL
    MSLUG2FR_SFIX_128K
	MSLUG2_AUDIO_128K
    MSLUG2_YMSND
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2la05 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_la05.p1", 0x000000, 0x100000, CRC(780b24cc) SHA1(9e7f05a325723adf28e6941ce138b41ede35d388) )
	ROM_LOAD16_WORD_SWAP( "241_la05.p2", 0x100000, 0x200000, CRC(fceb2790) SHA1(6ed39a7b521ee32df92ac7ec580734128b8ad5ee) )
    MSLUG2_CUSTOMPATCH_MODS_FILL
    MSLUG2_AES_FILL
    MSLUG2FR_SFIX_128K
	MSLUG2_AUDIO_128K
    MSLUG2_YMSND
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2la06 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_la05.p1", 0x000000, 0x100000, CRC(780b24cc) SHA1(9e7f05a325723adf28e6941ce138b41ede35d388) )
	ROM_LOAD16_WORD_SWAP( "241_la05.p2", 0x100000, 0x200000, CRC(fceb2790) SHA1(6ed39a7b521ee32df92ac7ec580734128b8ad5ee) )
    MSLUG2_CUSTOMPATCH_MODS_FILL
    MSLUG2_FATPLAYERS_MODS_FILL
    MSLUG2_AES_FILL
    MSLUG2FR_SFIX_128K
	MSLUG2_AUDIO_128K
    MSLUG2_YMSND
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2la07 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_la04.p1", 0x000000, 0x100000, CRC(b29a8226) SHA1(34a2997fa085afc00c1fe3ebc8d01fe45b44f9f6) )
	ROM_LOAD16_WORD_SWAP( "241_la05.p2", 0x100000, 0x200000, CRC(fceb2790) SHA1(6ed39a7b521ee32df92ac7ec580734128b8ad5ee) )
    MSLUG2_CUSTOMPATCH_MODS_FILL
    MSLUG2_AES_FILL
    MSLUG2FR_SFIX_128K
	MSLUG2_AUDIO_128K
    MSLUG2_YMSND
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2la08 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_la08.p1", 0x000000, 0x100000, CRC(8119c049) SHA1(254bbfe7d66b2465fa1fa62ab6f0de33587ac171) )
	ROM_LOAD16_WORD_SWAP( "241_la01.p2", 0x100000, 0x200000, CRC(3a55eb87) SHA1(b82c41988f3d6752bd5de78eef254f924785f6a1) )
    MSLUG2_CUSTOMPATCH_MODS_FILL
    MSLUG2_AES_FILL
    MSLUG2FR_SFIX_128K
	MSLUG2_AUDIO_128K
    MSLUG2_YMSND
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2lb01 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_lb01.p1", 0x000000, 0x100000, CRC(0a51cefc) SHA1(f843927ff3ed4d2a74d23314d0484500a5c0b43c) )
	ROM_LOAD16_WORD_SWAP( "241_la01.p2", 0x100000, 0x200000, CRC(3a55eb87) SHA1(b82c41988f3d6752bd5de78eef254f924785f6a1) )
    MSLUG2_CUSTOMPATCH_MODS_FILL
    MSLUG2_AES_FILL
    MSLUG2FR_SFIX_128K
	MSLUG2_AUDIO_128K
    MSLUG2_YMSND
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2lb02 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_lb01.p1", 0x000000, 0x100000, CRC(0a51cefc) SHA1(f843927ff3ed4d2a74d23314d0484500a5c0b43c) )
	ROM_LOAD16_WORD_SWAP( "241_la01.p2", 0x100000, 0x200000, CRC(3a55eb87) SHA1(b82c41988f3d6752bd5de78eef254f924785f6a1) )
    MSLUG2_CUSTOMPATCH_MODS_FILL
    MSLUG2_FATPLAYERS_MODS_FILL
    MSLUG2_AES_FILL
    MSLUG2FR_SFIX_128K
	MSLUG2_AUDIO_128K
    MSLUG2_YMSND
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2lb03 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_lb03.p1", 0x000000, 0x100000, CRC(b402b28d) SHA1(2d6a532bd8f5be8a86a7f4e44c635a73d3709ac7) )
	ROM_LOAD16_WORD_SWAP( "241_la03.p2", 0x100000, 0x200000, CRC(192b65e9) SHA1(40b8380306f96a95abe6b638eb786400655535b1) )
    MSLUG2_CUSTOMPATCH_MODS_FILL
    MSLUG2_AES_FILL
    MSLUG2FR_SFIX_128K
	MSLUG2_AUDIO_128K
    MSLUG2_YMSND
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2lb04 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_lb02.p1", 0x000000, 0x100000, CRC(b402b28d) SHA1(2d6a532bd8f5be8a86a7f4e44c635a73d3709ac7) )
	ROM_LOAD16_WORD_SWAP( "241_la03.p2", 0x100000, 0x200000, CRC(192b65e9) SHA1(40b8380306f96a95abe6b638eb786400655535b1) )
    MSLUG2_CUSTOMPATCH_MODS_FILL
    MSLUG2_FATPLAYERS_MODS_FILL
    MSLUG2_AES_FILL
    MSLUG2FR_SFIX_128K
	MSLUG2_AUDIO_128K
    MSLUG2_YMSND
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2lb05 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_lb05.p1", 0x000000, 0x100000, CRC(5ca15d62) SHA1(241a14edec2d8749396d3e7be54e23a5a72b28d2) )
	ROM_LOAD16_WORD_SWAP( "241_la05.p2", 0x100000, 0x200000, CRC(fceb2790) SHA1(6ed39a7b521ee32df92ac7ec580734128b8ad5ee) )
    MSLUG2_CUSTOMPATCH_MODS_FILL
    MSLUG2_AES_FILL
    MSLUG2FR_SFIX_128K
	MSLUG2_AUDIO_128K
    MSLUG2_YMSND
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2lb06 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_lb05.p1", 0x000000, 0x100000, CRC(5ca15d62) SHA1(241a14edec2d8749396d3e7be54e23a5a72b28d2) )
	ROM_LOAD16_WORD_SWAP( "241_la05.p2", 0x100000, 0x200000, CRC(fceb2790) SHA1(6ed39a7b521ee32df92ac7ec580734128b8ad5ee) )
    MSLUG2_CUSTOMPATCH_MODS_FILL
    MSLUG2_FATPLAYERS_MODS_FILL
    MSLUG2_AES_FILL
    MSLUG2FR_SFIX_128K
	MSLUG2_AUDIO_128K
    MSLUG2_YMSND
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2lb07 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_lb04.p1", 0x000000, 0x100000, CRC(f209dd30) SHA1(afb1bf21c9f01d665d5b5ccb8a4eacc0731203ae) )
	ROM_LOAD16_WORD_SWAP( "241_la05.p2", 0x100000, 0x200000, CRC(fceb2790) SHA1(6ed39a7b521ee32df92ac7ec580734128b8ad5ee) )
    MSLUG2_CUSTOMPATCH_MODS_FILL
    MSLUG2_AES_FILL
    MSLUG2FR_SFIX_128K
	MSLUG2_AUDIO_128K
    MSLUG2_YMSND
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2lb08 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_lb08.p1", 0x000000, 0x100000, CRC(bbc4524f) SHA1(59ebce01b53338f7d4cc2173239ddd78a3b27880) )
	ROM_LOAD16_WORD_SWAP( "241_la01.p2", 0x100000, 0x200000, CRC(3a55eb87) SHA1(b82c41988f3d6752bd5de78eef254f924785f6a1) )
    MSLUG2_CUSTOMPATCH_MODS_FILL
    MSLUG2_AES_FILL
    MSLUG2FR_SFIX_128K
	MSLUG2_AUDIO_128K
    MSLUG2_YMSND
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug3la01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_la01.p1", 0x000000, 0x100000, CRC(9d9bea4f) SHA1(e1e39b68582940f456af39f31af1aa51f4cd159d) )
	ROM_LOAD16_WORD_SWAP( "256_la01.p2", 0x100000, 0x400000, CRC(f9123ba1) SHA1(86e1647ebde622445813b3b09a86bdc5c09b465c) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3la02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_la01.p1", 0x000000, 0x100000, CRC(9d9bea4f) SHA1(e1e39b68582940f456af39f31af1aa51f4cd159d) )
	ROM_LOAD16_WORD_SWAP( "256_la01.p2", 0x100000, 0x400000, CRC(f9123ba1) SHA1(86e1647ebde622445813b3b09a86bdc5c09b465c) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_FATPLAYERS_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3la03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_la03.p1", 0x000000, 0x100000, CRC(1c8ced15) SHA1(8e8552bc6a8457cf1b6472bf012aca4d2bcee54b) )
	ROM_LOAD16_WORD_SWAP( "256_la03.p2", 0x100000, 0x400000, CRC(6ea68fd8) SHA1(5caefc3c950fd5c2cd8a24315cdac8f5404d0d74) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3la04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_la04.p1", 0x000000, 0x100000, CRC(ed7b282b) SHA1(5ba3d9f1dadfcb9d5b767aba0dd3c826ce5448bb) )
	ROM_LOAD16_WORD_SWAP( "256_la03.p2", 0x100000, 0x400000, CRC(6ea68fd8) SHA1(5caefc3c950fd5c2cd8a24315cdac8f5404d0d74) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3la05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_la05.p1", 0x000000, 0x100000, CRC(662e1769) SHA1(c4130d75b3a22627e4453e2ada3cf0e8828691cc) )
	ROM_LOAD16_WORD_SWAP( "256_la03.p2", 0x100000, 0x400000, CRC(6ea68fd8) SHA1(5caefc3c950fd5c2cd8a24315cdac8f5404d0d74) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3la06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_la06.p1", 0x000000, 0x100000, CRC(0c7c259c) SHA1(d29c4f08b5893a77e93b5ab1d517da25c861c724) )
	ROM_LOAD16_WORD_SWAP( "256_la03.p2", 0x100000, 0x400000, CRC(6ea68fd8) SHA1(5caefc3c950fd5c2cd8a24315cdac8f5404d0d74) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lb01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lb01.p1", 0x000000, 0x100000, CRC(d5356919) SHA1(c738f7d4a44a09431c90dd235e9692197bb77d52) )
	ROM_LOAD16_WORD_SWAP( "256_lb01.p2", 0x100000, 0x400000, CRC(043861a9) SHA1(49e97d22c9549e9f428bb59035527c34a6bfc5f9) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lb02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lb01.p1", 0x000000, 0x100000, CRC(d5356919) SHA1(c738f7d4a44a09431c90dd235e9692197bb77d52) )
	ROM_LOAD16_WORD_SWAP( "256_lb01.p2", 0x100000, 0x400000, CRC(043861a9) SHA1(49e97d22c9549e9f428bb59035527c34a6bfc5f9) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_FATPLAYERS_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lb03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lb03.p1", 0x000000, 0x100000, CRC(27276b03) SHA1(dcf2f67648535d0d5ae76c9856d2589e348384fe) )
	ROM_LOAD16_WORD_SWAP( "256_lb03.p2", 0x100000, 0x400000, CRC(bca10026) SHA1(81eb562262901077921d15a89e1f15e0758abd2b) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lb04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lb04.p1", 0x000000, 0x100000, CRC(d6d0ae3d) SHA1(5e7b946e987b5b9b43b187a6f16d5056f1816342) )
	ROM_LOAD16_WORD_SWAP( "256_lb03.p2", 0x100000, 0x400000, CRC(bca10026) SHA1(81eb562262901077921d15a89e1f15e0758abd2b) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lb05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lb05.p1", 0x000000, 0x100000, CRC(5d85917f) SHA1(0a2172e3a34bd9dcb4075f0f21197cd53d5a94bc) )
	ROM_LOAD16_WORD_SWAP( "256_lb03.p2", 0x100000, 0x400000, CRC(bca10026) SHA1(81eb562262901077921d15a89e1f15e0758abd2b) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lb06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lb06.p1", 0x000000, 0x100000, CRC(37d7a38a) SHA1(d595da050d025d534d596007021a001fb8ddbf35) )
	ROM_LOAD16_WORD_SWAP( "256_lb03.p2", 0x100000, 0x400000, CRC(bca10026) SHA1(81eb562262901077921d15a89e1f15e0758abd2b) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lc01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lc01.p1", 0x000000, 0x100000, CRC(f08a0dde) SHA1(8309a20f36ba1a31469601e479a6dd95f4243f13) )
	ROM_LOAD16_WORD_SWAP( "256_lc01.p2", 0x100000, 0x400000, CRC(e9a0234f) SHA1(2f2d2f28a3ffa119fdb40ab06bace4bc210bfc0a) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lc02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lc01.p1", 0x000000, 0x100000, CRC(f08a0dde) SHA1(8309a20f36ba1a31469601e479a6dd95f4243f13) )
	ROM_LOAD16_WORD_SWAP( "256_lc01.p2", 0x100000, 0x400000, CRC(e9a0234f) SHA1(2f2d2f28a3ffa119fdb40ab06bace4bc210bfc0a) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_FATPLAYERS_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lc03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lc03.p1", 0x000000, 0x100000, CRC(02980fc4) SHA1(a32d18d893cde1e94dd15ebecbb74e7e5ba8a362) )
	ROM_LOAD16_WORD_SWAP( "256_lc03.p2", 0x100000, 0x400000, CRC(513942c0) SHA1(a3a523128288c546435c990469dcbe9fdf185407) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lc04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lc04.p1", 0x000000, 0x100000, CRC(f36fcafa) SHA1(a1225d1711772bc8ea382288089d3ec726e4c24a) )
	ROM_LOAD16_WORD_SWAP( "256_lc03.p2", 0x100000, 0x400000, CRC(513942c0) SHA1(a3a523128288c546435c990469dcbe9fdf185407) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lc05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lc05.p1", 0x000000, 0x100000, CRC(783af5b8) SHA1(729ee563e0f893b1e075d860df48112fdb53cf52) )
	ROM_LOAD16_WORD_SWAP( "256_lc03.p2", 0x100000, 0x400000, CRC(513942c0) SHA1(a3a523128288c546435c990469dcbe9fdf185407) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lc06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lc06.p1", 0x000000, 0x100000, CRC(1268c74d) SHA1(f2f3096cbd9db9b2bb9b15a50ef7fd383c8458f9) )
	ROM_LOAD16_WORD_SWAP( "256_lc03.p2", 0x100000, 0x400000, CRC(513942c0) SHA1(a3a523128288c546435c990469dcbe9fdf185407) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3ld01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_ld01.p1", 0x000000, 0x100000, CRC(bfe35d20) SHA1(e42fdef3572577bced2c9a6f8cc46b5bb70eb1b1) )
	ROM_LOAD16_WORD_SWAP( "256_ld01.p2", 0x100000, 0x400000, CRC(c609b95d) SHA1(37b1644b8d7120c3d73fbf6597e38c440255fc8a) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3ld02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_ld01.p1", 0x000000, 0x100000, CRC(bfe35d20) SHA1(e42fdef3572577bced2c9a6f8cc46b5bb70eb1b1) )
	ROM_LOAD16_WORD_SWAP( "256_ld01.p2", 0x100000, 0x400000, CRC(c609b95d) SHA1(37b1644b8d7120c3d73fbf6597e38c440255fc8a) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_FATPLAYERS_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3ld03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_ld03.p1", 0x000000, 0x100000, CRC(4df15f3a) SHA1(a5135582db9f2b9fa74eb0d3f0299c78c3c42b9a) )
	ROM_LOAD16_WORD_SWAP( "256_ld03.p2", 0x100000, 0x400000, CRC(7e90d8d2) SHA1(806435d31ea534d059b2e18d2dfdd1bf726fb335) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3ld04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_ld04.p1", 0x000000, 0x100000, CRC(bc069a04) SHA1(bb6a5454988911af599d92939f2d8947e288024a) )
	ROM_LOAD16_WORD_SWAP( "256_ld03.p2", 0x100000, 0x400000, CRC(7e90d8d2) SHA1(806435d31ea534d059b2e18d2dfdd1bf726fb335) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3ld05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_ld05.p1", 0x000000, 0x100000, CRC(3753a546) SHA1(9666cef8064202f4675166ee46155ab1414a48a9) )
	ROM_LOAD16_WORD_SWAP( "256_ld03.p2", 0x100000, 0x400000, CRC(7e90d8d2) SHA1(806435d31ea534d059b2e18d2dfdd1bf726fb335) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3ld06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_ld06.p1", 0x000000, 0x100000, CRC(5d0197b3) SHA1(800c68f7916c5b474d4b8da567936077c61bafcc) )
	ROM_LOAD16_WORD_SWAP( "256_ld03.p2", 0x100000, 0x400000, CRC(7e90d8d2) SHA1(806435d31ea534d059b2e18d2dfdd1bf726fb335) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3le01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_le01.p1", 0x000000, 0x100000, CRC(ee2794ba) SHA1(1d3c28404b1c25edc2f234ed01d49f81a24b7d18) )
	ROM_LOAD16_WORD_SWAP( "256_le01.p2", 0x100000, 0x400000, CRC(33f5f4a1) SHA1(99ae19842608d255df916e9ff43d824e306a46f2) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3le02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_le01.p1", 0x000000, 0x100000, CRC(ee2794ba) SHA1(1d3c28404b1c25edc2f234ed01d49f81a24b7d18) )
	ROM_LOAD16_WORD_SWAP( "256_le01.p2", 0x100000, 0x400000, CRC(33f5f4a1) SHA1(99ae19842608d255df916e9ff43d824e306a46f2) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_FATPLAYERS_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3le03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_le03.p1", 0x000000, 0x100000, CRC(1c3596a0) SHA1(02e0215481a009d89d06f2cba701c65957766789) )
	ROM_LOAD16_WORD_SWAP( "256_le03.p2", 0x100000, 0x400000, CRC(8b6c952e) SHA1(582f513d88c9303ee780997f8baa3022c30d915d) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3le04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_le04.p1", 0x000000, 0x100000, CRC(edc2539e) SHA1(f06ba1060f5c601fd0647890dde7cddff76f6cb7) )
	ROM_LOAD16_WORD_SWAP( "256_le03.p2", 0x100000, 0x400000, CRC(8b6c952e) SHA1(582f513d88c9303ee780997f8baa3022c30d915d) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3le05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_le05.p1", 0x000000, 0x100000, CRC(66976cdc) SHA1(db8457ef0307afcd8e12b8e1d7396362ab36a54e) )
	ROM_LOAD16_WORD_SWAP( "256_le03.p2", 0x100000, 0x400000, CRC(8b6c952e) SHA1(582f513d88c9303ee780997f8baa3022c30d915d) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3le06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_le06.p1", 0x000000, 0x100000, CRC(0cc55e29) SHA1(77671e41f63651ce061eae07f61e5f025e7df94a) )
	ROM_LOAD16_WORD_SWAP( "256_le03.p2", 0x100000, 0x400000, CRC(8b6c952e) SHA1(582f513d88c9303ee780997f8baa3022c30d915d) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lf01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lf01.p1", 0x000000, 0x100000, CRC(5e6a6b47) SHA1(622ad0f57781d5d422eb7c5b5996f5284d9132b1) )
	ROM_LOAD16_WORD_SWAP( "256_lf01.p2", 0x100000, 0x400000, CRC(603e738f) SHA1(5c3f5f9d8c1af36836fe08be0d6a84801a208fd9) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lf02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lf01.p1", 0x000000, 0x100000, CRC(5e6a6b47) SHA1(622ad0f57781d5d422eb7c5b5996f5284d9132b1) )
	ROM_LOAD16_WORD_SWAP( "256_lf01.p2", 0x100000, 0x400000, CRC(603e738f) SHA1(5c3f5f9d8c1af36836fe08be0d6a84801a208fd9) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_FATPLAYERS_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lf03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lf03.p1", 0x000000, 0x100000, CRC(ac78695d) SHA1(748b5b34a1d10fe2f65e41a171cdcf7efb6d5bc1) )
	ROM_LOAD16_WORD_SWAP( "256_lf03.p2", 0x100000, 0x400000, CRC(d8a71200) SHA1(319a5f4e4483af6b71eaf8815d1ba3947a71042b) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lf04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lf04.p1", 0x000000, 0x100000, CRC(5d8fac63) SHA1(0d9bb2e30fc512cd9727bc34b4add52dafdfadd7) )
	ROM_LOAD16_WORD_SWAP( "256_lf03.p2", 0x100000, 0x400000, CRC(d8a71200) SHA1(319a5f4e4483af6b71eaf8815d1ba3947a71042b) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lf05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lf05.p1", 0x000000, 0x100000, CRC(d6da9321) SHA1(8ae89cc04b194e761f25fb351378dc8f935015df) )
	ROM_LOAD16_WORD_SWAP( "256_lf03.p2", 0x100000, 0x400000, CRC(d8a71200) SHA1(319a5f4e4483af6b71eaf8815d1ba3947a71042b) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lf06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lf06.p1", 0x000000, 0x100000, CRC(bc88a1d4) SHA1(0e09770b0ad641f63cc610c148881d034af872b1) )
	ROM_LOAD16_WORD_SWAP( "256_lf03.p2", 0x100000, 0x400000, CRC(d8a71200) SHA1(319a5f4e4483af6b71eaf8815d1ba3947a71042b) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lg01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lg01.p1", 0x000000, 0x100000, CRC(6528bb4e) SHA1(c77af097972402a62b8e42be52b53c0c20597390) )
	ROM_LOAD16_WORD_SWAP( "256_lg01.p2", 0x100000, 0x400000, CRC(71387ea0) SHA1(345636d254742d216b1819bdd5ecff4a431ba22e) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lg02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lg01.p1", 0x000000, 0x100000, CRC(6528bb4e) SHA1(c77af097972402a62b8e42be52b53c0c20597390) )
	ROM_LOAD16_WORD_SWAP( "256_lg01.p2", 0x100000, 0x400000, CRC(71387ea0) SHA1(345636d254742d216b1819bdd5ecff4a431ba22e) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_FATPLAYERS_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lg03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lg03.p1", 0x000000, 0x100000, CRC(973ab954) SHA1(4e211b8073e018ae2371e941fc6cc71c9e5f3eeb) )
	ROM_LOAD16_WORD_SWAP( "256_lg03.p2", 0x100000, 0x400000, CRC(c9a11f2f) SHA1(67c4fedc96414112da0fad5947f93d7bf3974448) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lg04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lg04.p1", 0x000000, 0x100000, CRC(66cd7c6a) SHA1(e5b8bca44beeb1bfebd93eb45a0dd8ba1ec1186a) )
	ROM_LOAD16_WORD_SWAP( "256_lg03.p2", 0x100000, 0x400000, CRC(c9a11f2f) SHA1(67c4fedc96414112da0fad5947f93d7bf3974448) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lg05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lg05.p1", 0x000000, 0x100000, CRC(ed984328) SHA1(6b26d8a2e5248161eae5e90bf46f2366c2160435) )
	ROM_LOAD16_WORD_SWAP( "256_lg03.p2", 0x100000, 0x400000, CRC(c9a11f2f) SHA1(67c4fedc96414112da0fad5947f93d7bf3974448) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lg06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lg06.p1", 0x000000, 0x100000, CRC(87ca71dd) SHA1(cb24f004d5623c76e0d296b07885e20596870ecd) )
	ROM_LOAD16_WORD_SWAP( "256_lg03.p2", 0x100000, 0x400000, CRC(c9a11f2f) SHA1(67c4fedc96414112da0fad5947f93d7bf3974448) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lh01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lh01.p1", 0x000000, 0x100000, CRC(365e4ea4) SHA1(0a4944d099b7028a6d95a83f912fd99f18447bd8) )
	ROM_LOAD16_WORD_SWAP( "256_lh01.p2", 0x100000, 0x400000, CRC(057fec10) SHA1(997064c45d72c0c7aead9626255d6adc2ccab55f) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lh02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lh01.p1", 0x000000, 0x100000, CRC(365e4ea4) SHA1(0a4944d099b7028a6d95a83f912fd99f18447bd8) )
	ROM_LOAD16_WORD_SWAP( "256_lh01.p2", 0x100000, 0x400000, CRC(057fec10) SHA1(997064c45d72c0c7aead9626255d6adc2ccab55f) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_FATPLAYERS_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lh03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lh03.p1", 0x000000, 0x100000, CRC(c44c4cbe) SHA1(1f09e77c2f31ffb22ee7260c16722b59a6b47cd0) )
	ROM_LOAD16_WORD_SWAP( "256_lh03.p2", 0x100000, 0x400000, CRC(bde68d9f) SHA1(e252f7f0bfc9d2642c1331c42e24ac694fe79f35) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lh04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lh04.p1", 0x000000, 0x100000, CRC(35bb8980) SHA1(102fa35ad8f592bded470137fcdc85eabf679320) )
	ROM_LOAD16_WORD_SWAP( "256_lh03.p2", 0x100000, 0x400000, CRC(bde68d9f) SHA1(e252f7f0bfc9d2642c1331c42e24ac694fe79f35) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lh05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lh05.p1", 0x000000, 0x100000, CRC(beeeb6c2) SHA1(740436df71116e9de703136c8bafe6e7d20b6f2f) )
	ROM_LOAD16_WORD_SWAP( "256_lh03.p2", 0x100000, 0x400000, CRC(bde68d9f) SHA1(e252f7f0bfc9d2642c1331c42e24ac694fe79f35) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
    DEFAULT_BIOS_BOOT_(EUROPE_MVS)
	AUDIOBIOS_128K
    MSLUG3G_SFIX_128K
	MSLUG3LW_AUDIOBIOS_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3lh06 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_lh06.p1", 0x000000, 0x100000, CRC(d4bc8437) SHA1(8856c4d1a26695c5d048d1f62670d4f1d2f30b57) )
	ROM_LOAD16_WORD_SWAP( "256_lh03.p2", 0x100000, 0x400000, CRC(bde68d9f) SHA1(e252f7f0bfc9d2642c1331c42e24ac694fe79f35) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
	MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
	MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug3li01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_li01.p1", 0x000000, 0x100000, CRC(852a2d77) SHA1(fecbed715bf7d3f59c844d7f4afab80525aa5a5b) )
	ROM_LOAD16_WORD_SWAP( "256_li01.p2", 0x100000, 0x400000, CRC(97083d5d) SHA1(c716aa3acec2976b469b4c5b91ad0d5ad12d80c3) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug4la01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_la01.p1", 0x000000, 0x100000, CRC(6e09fdc0) SHA1(b0a7cbd648b020cdc8f5a0ef434fbe8c84dcac04) )
	ROM_LOAD16_WORD_SWAP( "263_la01.p2", 0x100000, 0x400000, CRC(1782d963) SHA1(207d0c1384db302b61a3efb025d677cdef253049) )
    MSLUG4_CUSTOMPATCH_MODS_FILL
    MSLUG4_AES_FILL
    MSLUG4lZW_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
	MSLUG4FR_SPRITES
ROM_END

ROM_START( mslug4la02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_la01.p1", 0x000000, 0x100000, CRC(6e09fdc0) SHA1(b0a7cbd648b020cdc8f5a0ef434fbe8c84dcac04) )
	ROM_LOAD16_WORD_SWAP( "263_la01.p2", 0x100000, 0x400000, CRC(1782d963) SHA1(207d0c1384db302b61a3efb025d677cdef253049) )
    MSLUG4_CUSTOMPATCH_MODS_FILL
    MSLUG4_FATPLAYERS_MODS_FILL
    FIX_FATPLAYERS_FILL
    MSLUG4_AES_FILL
    MSLUG4lZW_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
	MSLUG4FR_SPRITES
ROM_END

ROM_START( mslug4la03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_la03.p1", 0x000000, 0x100000, CRC(b8be5350) SHA1(ab4109a46d564470187733fc7dbb1497d15429a4) )
	ROM_LOAD16_WORD_SWAP( "263_la03.p2", 0x100000, 0x400000, CRC(3842f3f5) SHA1(7d519ac718b0558f534c3dc0dfb7503cb8a592e2) )
    MSLUG4_CUSTOMPATCH_MODS_FILL
    MSLUG4_AES_FILL
    MSLUG4lZW_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
	MSLUG4FR_SPRITES
ROM_END

ROM_START( mslug4la04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_la04.p1", 0x000000, 0x100000, CRC(e5e2de07) SHA1(05689bb895b7dddc1f7133528e25c8da91ef246b) )
	ROM_LOAD16_WORD_SWAP( "263_la04.p2", 0x100000, 0x400000, CRC(4724c370) SHA1(e6d3890ffeaff36c85b6d92f32220082d2d164cc) )
    MSLUG4_CUSTOMPATCH_MODS_FILL
    MSLUG4_AES_FILL
    MSLUG4lZW_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
	MSLUG4FR_SPRITES
ROM_END

ROM_START( mslug4la05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_la05.p1", 0x000000, 0x100000, CRC(7c10d072) SHA1(c17feadc909b01b344a76c70990bcb3a49f16b79) )
	ROM_LOAD16_WORD_SWAP( "263_la05.p2", 0x100000, 0x400000, CRC(fb4ce2cc) SHA1(9da1cee1833e694b37b8a1fd52963e50f456c25f) )
    MSLUG4_CUSTOMPATCH_MODS_FILL
    MSLUG4_AES_FILL
    MSLUG4lZW_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
	MSLUG4FR_SPRITES
ROM_END

ROM_START( mslug4lb01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_lb01.p1", 0x000000, 0x100000, CRC(972f4dba) SHA1(176be24559eea5507db2b89a0bd6f5699c408d40) )
	ROM_LOAD16_WORD_SWAP( "263_la01.p2", 0x100000, 0x400000, CRC(1782d963) SHA1(207d0c1384db302b61a3efb025d677cdef253049) )
    MSLUG4_CUSTOMPATCH_MODS_FILL
    MSLUG4_AES_FILL
    MSLUG4lZW_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
	MSLUG4FR_SPRITES
ROM_END

ROM_START( mslug4lb02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_lb01.p1", 0x000000, 0x100000, CRC(972f4dba) SHA1(176be24559eea5507db2b89a0bd6f5699c408d40) )
	ROM_LOAD16_WORD_SWAP( "263_la01.p2", 0x100000, 0x400000, CRC(1782d963) SHA1(207d0c1384db302b61a3efb025d677cdef253049) )
    MSLUG4_CUSTOMPATCH_MODS_FILL
    MSLUG4_FATPLAYERS_MODS_FILL
    FIX_FATPLAYERS_FILL
    MSLUG4_AES_FILL
    MSLUG4lZW_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
	MSLUG4FR_SPRITES
ROM_END

ROM_START( mslug4lb03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_lb03.p1", 0x000000, 0x100000, CRC(4198e32a) SHA1(365afa321923e4be0b9139e071704c79c2091506) )
	ROM_LOAD16_WORD_SWAP( "263_la03.p2", 0x100000, 0x400000, CRC(3842f3f5) SHA1(7d519ac718b0558f534c3dc0dfb7503cb8a592e2) )
    MSLUG4_CUSTOMPATCH_MODS_FILL
    MSLUG4_AES_FILL
    MSLUG4lZW_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
	MSLUG4FR_SPRITES
ROM_END

ROM_START( mslug4lb04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_lb04.p1", 0x000000, 0x100000, CRC(1cc46e7d) SHA1(72fbbd0f3f4449c9503b2d2d25f1a5b1085336a1) )
	ROM_LOAD16_WORD_SWAP( "263_la04.p2", 0x100000, 0x400000, CRC(4724c370) SHA1(e6d3890ffeaff36c85b6d92f32220082d2d164cc) )
    MSLUG4_CUSTOMPATCH_MODS_FILL
    MSLUG4_AES_FILL
    MSLUG4lZW_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
	MSLUG4FR_SPRITES
ROM_END

ROM_START( mslug4lb05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_lb05.p1", 0x000000, 0x100000, CRC(85366008) SHA1(ce225ef9bb1818f718337ea9a0e9ef7e72e11c33) )
	ROM_LOAD16_WORD_SWAP( "263_la05.p2", 0x100000, 0x400000, CRC(fb4ce2cc) SHA1(9da1cee1833e694b37b8a1fd52963e50f456c25f) )
    MSLUG4_CUSTOMPATCH_MODS_FILL
    MSLUG4_AES_FILL
    MSLUG4lZW_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
	MSLUG4FR_SPRITES
ROM_END

ROM_START( mslug4lc01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_lc01.p1", 0x000000, 0x100000, CRC(dc4f47cf) SHA1(8a718ef086a3610d6fa7a1c9ab75dea598e2308f) )
	ROM_LOAD16_WORD_SWAP( "263_lc01.p2", 0x100000, 0x400000, CRC(daf31aca) SHA1(9e807c89733ff1e77c38436d44430cd65f1b5d29) )
    MSLUG4_CUSTOMPATCH_MODS_FILL
    MSLUG4_AES_FILL
    MSLUG4FR_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
	MSLUG4FR_SPRITES
ROM_END

ROM_START( mslug4lc02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_lc01.p1", 0x000000, 0x100000, CRC(dc4f47cf) SHA1(8a718ef086a3610d6fa7a1c9ab75dea598e2308f) )
	ROM_LOAD16_WORD_SWAP( "263_lc01.p2", 0x100000, 0x400000, CRC(daf31aca) SHA1(9e807c89733ff1e77c38436d44430cd65f1b5d29) )
    MSLUG4_CUSTOMPATCH_MODS_FILL
    MSLUG4_FATPLAYERS_MODS_FILL
    MSLUG4_AES_FILL
    MSLUG4FR_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
	MSLUG4FR_SPRITES
ROM_END

ROM_START( mslug4lc03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_lc03.p1", 0x000000, 0x100000, CRC(69eac633) SHA1(7e217aab4467f50090323b595151c43851ce289b) )
	ROM_LOAD16_WORD_SWAP( "263_lc03.p2", 0x100000, 0x400000, CRC(f533305c) SHA1(50c63f30a419c080d0d9c51e1befb332b8a03147) )
    MSLUG4_CUSTOMPATCH_MODS_FILL
    MSLUG4_AES_FILL
    MSLUG4FR_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
	MSLUG4FR_SPRITES
ROM_END

ROM_START( mslug4lc04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_lc04.p1", 0x000000, 0x100000, CRC(34b64b64) SHA1(cec429891ef214c869874497b750fa3699ab6512) )
	ROM_LOAD16_WORD_SWAP( "263_lc04.p2", 0x100000, 0x400000, CRC(8a5500d9) SHA1(7c96c092b72faf688a14e64ef2561bd5a5a74355) )
    MSLUG4_CUSTOMPATCH_MODS_FILL
    MSLUG4_AES_FILL
    MSLUG4FR_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
	MSLUG4FR_SPRITES
ROM_END

ROM_START( mslug4lc05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_lc05.p1", 0x000000, 0x100000, CRC(ad444511) SHA1(251a29b85a7ab67d9b4279de4b48dc37d1e4e77d) )
	ROM_LOAD16_WORD_SWAP( "263_lc05.p2", 0x100000, 0x400000, CRC(363d2165) SHA1(ff395dcc4ec9bf556062bfd9d834eee30f7356bd) )
    MSLUG4_CUSTOMPATCH_MODS_FILL
    MSLUG4_AES_FILL
    MSLUG4FR_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
	MSLUG4FR_SPRITES
ROM_END

ROM_START( mslug4ld01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_ld01.p1", 0x000000, 0x100000, CRC(51a93b29) SHA1(e1a30656b416e9c6f1839f065a16971d6119d6ac) )
	ROM_LOAD16_WORD_SWAP( "263_lc01.p2", 0x100000, 0x400000, CRC(daf31aca) SHA1(9e807c89733ff1e77c38436d44430cd65f1b5d29) )
    MSLUG4_CUSTOMPATCH_MODS_FILL
    MSLUG4_AES_FILL
    MSLUG4FR_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
	MSLUG4FR_SPRITES
ROM_END

ROM_START( mslug4ld02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_ld01.p1", 0x000000, 0x100000, CRC(51a93b29) SHA1(e1a30656b416e9c6f1839f065a16971d6119d6ac) )
	ROM_LOAD16_WORD_SWAP( "263_lc01.p2", 0x100000, 0x400000, CRC(daf31aca) SHA1(9e807c89733ff1e77c38436d44430cd65f1b5d29) )
    MSLUG4_CUSTOMPATCH_MODS_FILL
    MSLUG4_FATPLAYERS_MODS_FILL
    MSLUG4_AES_FILL
    MSLUG4FR_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
	MSLUG4FR_SPRITES
ROM_END

ROM_START( mslug4ld03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_ld03.p1", 0x000000, 0x100000, CRC(8f44bed5) SHA1(1cc5401e197c107f97b32be3a5808ccc6d293db8) )
	ROM_LOAD16_WORD_SWAP( "263_lc03.p2", 0x100000, 0x400000, CRC(f533305c) SHA1(50c63f30a419c080d0d9c51e1befb332b8a03147) )
    MSLUG4_CUSTOMPATCH_MODS_FILL
    MSLUG4_AES_FILL
    MSLUG4FR_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
	MSLUG4FR_SPRITES
ROM_END

ROM_START( mslug4ld04 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_ld04.p1", 0x000000, 0x100000, CRC(d2183382) SHA1(bd4fa65fccfb08d3859e7268bc9df58b94b32c67) )
	ROM_LOAD16_WORD_SWAP( "263_lc04.p2", 0x100000, 0x400000, CRC(8a5500d9) SHA1(7c96c092b72faf688a14e64ef2561bd5a5a74355) )
    MSLUG4_CUSTOMPATCH_MODS_FILL
    MSLUG4_AES_FILL
    MSLUG4FR_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
	MSLUG4FR_SPRITES
ROM_END

ROM_START( mslug4ld05 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_ld05.p1", 0x000000, 0x100000, CRC(4bea3df7) SHA1(bb9bb441a70cdac01f59eea6184dbfdbd748f80a) )
	ROM_LOAD16_WORD_SWAP( "263_lc05.p2", 0x100000, 0x400000, CRC(363d2165) SHA1(ff395dcc4ec9bf556062bfd9d834eee30f7356bd) )
    MSLUG4_CUSTOMPATCH_MODS_FILL
    MSLUG4_AES_FILL
    MSLUG4FR_SFIX_128K
    MSLUG4LW_AUDIO_128K
	MSLUG4LW_YMSND
	MSLUG4FR_SPRITES
ROM_END

ROM_START( mslug5la01 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_la01.p1", 0x000000, 0x200000, CRC(bd808e1e) SHA1(871866d48e177c2515e4ab4c2d090054aa5cb87d) )
	ROM_LOAD16_WORD_SWAP( "268_la01.p2", 0x200000, 0x400000, CRC(20dd03ac) SHA1(2edfbe5975b43a9b304ec4f113e8de31d96b0ae6) )
    MSLUG5HD_CUSTOMPATCH_MODS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5W_AUDIO_512K
	MSLUG5LA_YMSND
	MSLUG5F_SPRITES
ROM_END

ROM_START( mslug5lb01 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_lb01.p1", 0x000000, 0x200000, CRC(b72798e5) SHA1(371b22a9de2e47aa4661567da13e413894246a76) )
	ROM_LOAD16_WORD_SWAP( "268_lb01.p2", 0x200000, 0x400000, CRC(b3110397) SHA1(57d8f35d46475d95ee843adfd9387d863cc6718e) )
    MSLUG5HD_CUSTOMPATCH_MODS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5W_AUDIO_512K
	MSLUG5LA_YMSND
	MSLUG5F_SPRITES
ROM_END

ROM_START( mslug5lc01 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_lc01.p1", 0x000000, 0x200000, CRC(c32454bc) SHA1(aff0c47053e77bef22fe1466accd157b6c8340aa) )
	ROM_LOAD16_WORD_SWAP( "268_lc01.p2", 0x200000, 0x400000, CRC(131013dc) SHA1(52f4cb85ebd395fdf0aa19fbd66e3c39e3d08689) )
    MSLUG5HD_CUSTOMPATCH_MODS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5W_AUDIO_512K
	MSLUG5LA_YMSND
	MSLUG5F_SPRITES
ROM_END

ROM_START( mslugxla01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_la01.p1", 0x000000, 0x100000, CRC(f1a138f8) SHA1(8d6392c4d6991e93bcf0ccec9a7bf9082f7e89ed) )
	ROM_LOAD16_WORD_SWAP( "250_la01.p2", 0x100000, 0x400000, CRC(4de6a6eb) SHA1(24c45c7bab6259a80e977056eabbbced2164d377) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxla02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_la02.p1", 0x000000, 0x100000, CRC(198025f5) SHA1(83c28d8c716563d3b12a4123382d6bcc207cd0aa) )
	ROM_LOAD16_WORD_SWAP( "250_la01.p2", 0x100000, 0x400000, CRC(4de6a6eb) SHA1(24c45c7bab6259a80e977056eabbbced2164d377) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxla03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_la03.p1", 0x000000, 0x100000, CRC(f63fc5b3) SHA1(3eb806120c25a9e26c2ddcb83a5b5ad59ddeb8ea) )
	ROM_LOAD16_WORD_SWAP( "250_la01.p2", 0x100000, 0x400000, CRC(4de6a6eb) SHA1(24c45c7bab6259a80e977056eabbbced2164d377) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxlb01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_lb01.p1", 0x000000, 0x100000, CRC(876e94d3) SHA1(b21a987c27615071b45130613ab4201afcc6cbe2) )
	ROM_LOAD16_WORD_SWAP( "250_lb01.p2", 0x100000, 0x400000, CRC(a91dda63) SHA1(7241ca4d01f915cc5b67d906935e7c9de2d2a274) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxlb02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_la02.p1", 0x000000, 0x100000, CRC(198025f5) SHA1(83c28d8c716563d3b12a4123382d6bcc207cd0aa) )
	ROM_LOAD16_WORD_SWAP( "250_lb01.p2", 0x100000, 0x400000, CRC(a91dda63) SHA1(7241ca4d01f915cc5b67d906935e7c9de2d2a274) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxlb03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_la03.p1", 0x000000, 0x100000, CRC(f63fc5b3) SHA1(3eb806120c25a9e26c2ddcb83a5b5ad59ddeb8ea) )
	ROM_LOAD16_WORD_SWAP( "250_lb01.p2", 0x100000, 0x400000, CRC(a91dda63) SHA1(7241ca4d01f915cc5b67d906935e7c9de2d2a274) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxlc01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_lc01.p1", 0x000000, 0x100000, CRC(c12d22ac) SHA1(118a0622f2d76b2b0c529adc0a4255d39b911849) )
	ROM_LOAD16_WORD_SWAP( "250_lc01.p2", 0x100000, 0x400000, CRC(ff7c136d) SHA1(395f3e019a1ac8be7c37514fd70d7b5389895cc5) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxlc02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_la02.p1", 0x000000, 0x100000, CRC(198025f5) SHA1(83c28d8c716563d3b12a4123382d6bcc207cd0aa) )
	ROM_LOAD16_WORD_SWAP( "250_lc01.p2", 0x100000, 0x400000, CRC(ff7c136d) SHA1(395f3e019a1ac8be7c37514fd70d7b5389895cc5) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxlc03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_la03.p1", 0x000000, 0x100000, CRC(f63fc5b3) SHA1(3eb806120c25a9e26c2ddcb83a5b5ad59ddeb8ea) )
	ROM_LOAD16_WORD_SWAP( "250_lc01.p2", 0x100000, 0x400000, CRC(ff7c136d) SHA1(395f3e019a1ac8be7c37514fd70d7b5389895cc5) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxld01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_ld01.p1", 0x000000, 0x100000, CRC(e5b3658f) SHA1(78a262f8e8e6454377d4c397fafc50c799c2c9f4) )
	ROM_LOAD16_WORD_SWAP( "250_ld01.p2", 0x100000, 0x400000, CRC(deb7fa5c) SHA1(8974de3205ab29e921ce8ecde4a78e6c5b1c7e5e) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxld02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_ld02.p1", 0x000000, 0x100000, CRC(5658f8af) SHA1(0054f333e274d7106678fb4a8c46a2fcc4727a3c) )
	ROM_LOAD16_WORD_SWAP( "250_ld01.p2", 0x100000, 0x400000, CRC(deb7fa5c) SHA1(8974de3205ab29e921ce8ecde4a78e6c5b1c7e5e) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxld03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_ld03.p1", 0x000000, 0x100000, CRC(f3bd7cea) SHA1(f8c078e627974eac9f0d4facb9094ac73b28ff33) )
	ROM_LOAD16_WORD_SWAP( "250_ld01.p2", 0x100000, 0x400000, CRC(deb7fa5c) SHA1(8974de3205ab29e921ce8ecde4a78e6c5b1c7e5e) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxle01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_le01.p1", 0x000000, 0x100000, CRC(9cf98757) SHA1(4e046fafe8c01fb5b3f97c714863415a45da7293) )
	ROM_LOAD16_WORD_SWAP( "250_le01.p2", 0x100000, 0x400000, CRC(d995fe03) SHA1(74b6556e2cb2cdd7096594a0e5c898a646a0099b) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxle02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_le02.p1", 0x000000, 0x100000, CRC(76ff5b42) SHA1(4be7e2f36ffe06c9b0cf85b71efd9aecfac38956) )
	ROM_LOAD16_WORD_SWAP( "250_le01.p2", 0x100000, 0x400000, CRC(d995fe03) SHA1(74b6556e2cb2cdd7096594a0e5c898a646a0099b) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxle03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_le03.p1", 0x000000, 0x100000, CRC(9940bb04) SHA1(cb11c9e5afd6e9e31f7e6466bad690df3cd86ccc) )
	ROM_LOAD16_WORD_SWAP( "250_le01.p2", 0x100000, 0x400000, CRC(d995fe03) SHA1(74b6556e2cb2cdd7096594a0e5c898a646a0099b) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxlf01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_lf01.p1", 0x000000, 0x100000, CRC(2822dd8f) SHA1(495a833da447b0a62d0b7e7093776319991ee225) )
	ROM_LOAD16_WORD_SWAP( "250_lf01.p2", 0x100000, 0x400000, CRC(87935bdb) SHA1(2129a1516ed5509a09293ba3c6f66be215e860d6) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxlf02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_lf02.p1", 0x000000, 0x100000, CRC(c003c082) SHA1(11618bba560951bae6b34f7e23dd2a23b62498af) )
	ROM_LOAD16_WORD_SWAP( "250_lf01.p2", 0x100000, 0x400000, CRC(87935bdb) SHA1(2129a1516ed5509a09293ba3c6f66be215e860d6) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxlf03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_lf03.p1", 0x000000, 0x100000, CRC(2fbc20c4) SHA1(bccfddc500104fd6733a25fe078391919a4c52d2) )
	ROM_LOAD16_WORD_SWAP( "250_lf01.p2", 0x100000, 0x400000, CRC(87935bdb) SHA1(2129a1516ed5509a09293ba3c6f66be215e860d6) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxlg01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_lg01.p1", 0x000000, 0x100000, CRC(cb1441e1) SHA1(3aec8c5eb13fb02ab129f4d9fd662775c50c415c) )
	ROM_LOAD16_WORD_SWAP( "250_lg01.p2", 0x100000, 0x400000, CRC(a93dd4f8) SHA1(e5593e703983ee44b0c9bab91843c5624998e821) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxlg02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_la02.p1", 0x000000, 0x100000, CRC(198025f5) SHA1(83c28d8c716563d3b12a4123382d6bcc207cd0aa) )
	ROM_LOAD16_WORD_SWAP( "250_lg01.p2", 0x100000, 0x400000, CRC(a93dd4f8) SHA1(e5593e703983ee44b0c9bab91843c5624998e821) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxlg03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_la03.p1", 0x000000, 0x100000, CRC(f63fc5b3) SHA1(3eb806120c25a9e26c2ddcb83a5b5ad59ddeb8ea) )
	ROM_LOAD16_WORD_SWAP( "250_lg01.p2", 0x100000, 0x400000, CRC(a93dd4f8) SHA1(e5593e703983ee44b0c9bab91843c5624998e821) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxlh01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_lh01.p1", 0x000000, 0x100000, CRC(ac2ee0a4) SHA1(88e879ee294d6452e1c4d4cb31c0b4c34252b5e9) )
	ROM_LOAD16_WORD_SWAP( "250_lh01.p2", 0x100000, 0x400000, CRC(4f516f2a) SHA1(b35045631f3a5291ba0bd3caf09549a9ee4c96bf) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxlh02 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_la02.p1", 0x000000, 0x100000, CRC(198025f5) SHA1(83c28d8c716563d3b12a4123382d6bcc207cd0aa) )
	ROM_LOAD16_WORD_SWAP( "250_lh01.p2", 0x100000, 0x400000, CRC(4f516f2a) SHA1(b35045631f3a5291ba0bd3caf09549a9ee4c96bf) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxlh03 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_la03.p1", 0x000000, 0x100000, CRC(f63fc5b3) SHA1(3eb806120c25a9e26c2ddcb83a5b5ad59ddeb8ea) )
	ROM_LOAD16_WORD_SWAP( "250_lh01.p2", 0x100000, 0x400000, CRC(4f516f2a) SHA1(b35045631f3a5291ba0bd3caf09549a9ee4c96bf) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
	FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

/****************
 Extreme Edition
******************/

ROM_START( mslugrma01 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "201_rma01.p1", 0x100000, 0x100000, CRC(8259891f) SHA1(dca073ebd236daa2845da428ed59f0540f19f4a3) )
	ROM_CONTINUE( 0x000000, 0x100000 )
    MSLUG_CUSTOMPATCH_MODS_FILL
    MSLUG_AES_FILL
	MSLUG_SFIX_128K
	MSLUG_AUDIO_128K
    MSLUG_YMSND
    MSLUG_SPRITES
ROM_END

ROM_START( mslug2rma01 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_rma01.p1", 0x000000, 0x100000, CRC(0bf338c7) SHA1(cf686bf4ac52cc67d60e95e472b7ffe2c7abf858) )
	ROM_LOAD16_WORD_SWAP( "241_rma01.p2", 0x100000, 0x200000, CRC(287f541b) SHA1(3f30846026edc499b0c6126f117e1cb859976dd4) )
    MSLUG2_CUSTOMPATCH_MODS_FILL
    MSLUG2_AES_FILL
    MSLUG2FR_SFIX_128K
	MSLUG2_AUDIO_128K
    MSLUG2_YMSND
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2rma02 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_rma02.p1", 0x000000, 0x100000, CRC(a2732c55) SHA1(4e73aab0b34fdd8033639990fd30551ebede3138) )
	ROM_LOAD16_WORD_SWAP( "241_rma02.p2", 0x100000, 0x200000, CRC(eec1980c) SHA1(557529010fba8ed728aa0a89474d0af3b9fd2b50) )
    MSLUG2_CUSTOMPATCH_MODS_FILL
    MSLUG2_AES_FILL
	MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2rmb01 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_rmb01.p1", 0x000000, 0x100000, CRC(2f594169) SHA1(44004ecb455ef31123dc442a7dd8ad5e8ce81dcb) )
	ROM_LOAD16_WORD_SWAP( "241_rma01.p2", 0x100000, 0x200000, CRC(287f541b) SHA1(3f30846026edc499b0c6126f117e1cb859976dd4) )
    MSLUG2_CUSTOMPATCH_MODS_FILL
    MSLUG2_AES_FILL
    MSLUG2FR_SFIX_128K
	MSLUG2_AUDIO_128K
    MSLUG2_YMSND
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2rmb02 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_rmb02.p1", 0x000000, 0x100000, CRC(86d955fb) SHA1(d96dafbb8db563667067c2f86c1336a008f5849f) )
	ROM_LOAD16_WORD_SWAP( "241_rma02.p2", 0x100000, 0x200000, CRC(eec1980c) SHA1(557529010fba8ed728aa0a89474d0af3b9fd2b50) )
    MSLUG2_CUSTOMPATCH_MODS_FILL
    MSLUG2_AES_FILL
	MSLUG2_SFIX_128K
    MSLUG2_AUDIO_128K
    MSLUG2_YMSND
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug3rma01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_rma01.p1", 0x000000, 0x100000, CRC(8b2862d0) SHA1(37966a69e0cba7427903435fee1ae378eda400b5) )
	ROM_LOAD16_WORD_SWAP( "256_rma01.p2", 0x100000, 0x400000, CRC(7a0efee4) SHA1(1ddb4636a1ed14df8c3bb7423adae67376729566) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
	MSLUG3_SFIX_MT_512K
	MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
	MSLUG3RMZ_SPRITES
ROM_END

ROM_START( mslug3rmb01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_rmb01.p1", 0x000000, 0x100000, CRC(dc2efbc3) SHA1(1de4d5de1940d92274700dc09afd3f39204addee) )
	ROM_LOAD16_WORD_SWAP( "256_rmb01.p2", 0x100000, 0x400000, CRC(4b628980) SHA1(bb7ec234be5c8fe1be1e18fb5675a29e4c008160) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
	MSLUG3_SFIX_MT_512K
	MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
	MSLUG3RMZ_SPRITES
ROM_END

ROM_START( mslug3rmc01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_rmc01.p1", 0x000000, 0x100000, CRC(f9919f04) SHA1(09d24723f13872503194aa9fa20ae377495623e3) )
	ROM_LOAD16_WORD_SWAP( "256_rmc01.p2", 0x100000, 0x400000, CRC(c1d1ab89) SHA1(622df39e8eb94a6dc9deeb3fedf01dbcfc554edf) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
	MSLUG3_SFIX_MT_512K
	MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
	MSLUG3RMZ_SPRITES
ROM_END

ROM_START( mslug3rmd01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_rmd01.p1", 0x000000, 0x100000, CRC(b6f8cffa) SHA1(9fb5a9845826a663fb766675793197a41a4093aa) )
	ROM_LOAD16_WORD_SWAP( "256_rmd01.p2", 0x100000, 0x400000, CRC(3006025a) SHA1(849d35c0bf06459b8eb0d46956461d5a798571f4) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
	MSLUG3_SFIX_MT_512K
	MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
	MSLUG3RMZ_SPRITES
ROM_END

ROM_START( mslug3rme01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_rme01.p1", 0x000000, 0x100000, CRC(e73c0660) SHA1(9e13c3ee054d90e384537d88fa6af7c185f38e1e) )
	ROM_LOAD16_WORD_SWAP( "256_rme01.p2", 0x100000, 0x400000, CRC(3beff11f) SHA1(8c1b658966a353d8a181f00cf3b2bed187427c2d) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
	MSLUG3_SFIX_MT_512K
	MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
	MSLUG3RMZ_SPRITES
ROM_END

ROM_START( mslug3rmf01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_rmf01.p1", 0x000000, 0x100000, CRC(5771f99d) SHA1(f49fcb083a214d73005317b737f4f4cd339a860d) )
	ROM_LOAD16_WORD_SWAP( "256_rmf01.p2", 0x100000, 0x400000, CRC(cd253ca2) SHA1(dcb75f38bf037aa72e867836e297ffbd4612a6ce) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
	MSLUG3_SFIX_MT_512K
	MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
	MSLUG3RMZ_SPRITES
ROM_END

ROM_START( mslug3rmg01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_rmg01.p1", 0x000000, 0x100000, CRC(6c332994) SHA1(40d165c37c09c1d2af80f8293d50942242b9af11) )
	ROM_LOAD16_WORD_SWAP( "256_rmg01.p2", 0x100000, 0x400000, CRC(72cb885b) SHA1(5fc0034f4d864cb9017bb117a970bc21f62f9226) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
	MSLUG3_SFIX_MT_512K
	MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
	MSLUG3RMZ_SPRITES
ROM_END

ROM_START( mslug3rmh01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_rmh01.p1", 0x000000, 0x100000, CRC(3f45dc7e) SHA1(18e24448d61d183e1115dba1284da54099b0f3ba) )
	ROM_LOAD16_WORD_SWAP( "256_rmh01.p2", 0x100000, 0x400000, CRC(06d4ffd2) SHA1(1b37059fefaf4ebe5f90af0d1f13a44fa17a42ff) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
	MSLUG3_SFIX_MT_512K
	MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
	MSLUG3RMZ_SPRITES
ROM_END


ROM_START( mslug3rmi01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256_rmi01.p1", 0x000000, 0x100000, CRC(430cc6cc) SHA1(ffaf4329ab5d958d9f819da17358dedc3a3ab235) )
	ROM_LOAD16_WORD_SWAP( "256_rmi01.p2", 0x100000, 0x400000, CRC(3beaf121) SHA1(8b5722067c471b216e2d15a2b1afb0b4999fadee) )
    MSLUG3H_CUSTOMPATCH_MODS_FILL
    MSLUG3H_AES_FILL
	MSLUG3HD_SFIX_128K
    MSLUG3LW_AUDIO_512K
    MSLUG3LW_YMSND
    MSLUG3LZ_SPRITES
ROM_END

ROM_START( mslug4rma01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_rma01.p1", 0x000000, 0x100000, CRC(118b91b4) SHA1(3722a5f8f3831616c4dceed6b765a6d22a2a7329) )
	ROM_LOAD16_WORD_SWAP( "263_rma01.p2", 0x100000, 0x400000, CRC(dcc2cc7d) SHA1(70e2be80829f078d4494aa3a173592ae5fcc5c20) )
    MSLUG4_CUSTOMPATCH_MODS_FILL
    MSLUG4_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
    FIX_BIOS_COIN_FILL
    AUDIOBIOS_128K    
	MSLUG4lZW_SFIX_128K
    MSLUG4LW_AUDIOBIOS_128K
	MSLUG4LW_YMSND
	MSLUG4FR_SPRITES
ROM_END

ROM_START( mslug4rmb01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_rmb01.p1", 0x000000, 0x100000, CRC(3af6db10) SHA1(f95ae4610c6ded2a95a4506d86ad4cb6d7a6ca96) )
	ROM_LOAD16_WORD_SWAP( "263_rmb01.p2", 0x100000, 0x400000, CRC(c86b7563) SHA1(27b4c17cca341dc049ee003dcc4067aab6a491ff) )
    MSLUG4_CUSTOMPATCH_MODS_FILL
    MSLUG4_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
    FIX_BIOS_COIN_FILL
    AUDIOBIOS_128K    
	MSLUG4lZW_SFIX_128K
    MSLUG4LW_AUDIOBIOS_128K
	MSLUG4LW_YMSND
	MSLUG4FR_SPRITES
ROM_END

ROM_START( mslug4rmc01 )
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_rmc01.p1", 0x000000, 0x100000, CRC(2a54918f) SHA1(3515f01e81add336bdbae93659f2cff14e96b189) )
	ROM_LOAD16_WORD_SWAP( "263_rmc01.p2", 0x100000, 0x400000, CRC(6982e3a2) SHA1(dedca273c1b05325f6054db389d34eecf604ccb2) )
    MSLUG4_CUSTOMPATCH_MODS_FILL
    MSLUG4_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
    FIX_BIOS_COIN_FILL
    AUDIOBIOS_128K
    MSLUG4FR_SFIX_128K
    MSLUG4LW_AUDIOBIOS_128K
	MSLUG4LW_YMSND
	MSLUG4FR_SPRITES
ROM_END

ROM_START( mslug4rmd01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_rmd01.p1", 0x000000, 0x100000, CRC(5b6e2786) SHA1(65baba8be9049ce57a4cfc400768b8841107c177) )
	ROM_LOAD16_WORD_SWAP( "263_rmd01.p2", 0x100000, 0x400000, CRC(359e2ebe) SHA1(9e897bf804acfd8e8a3d6eff33ae00e82c54351c) )
    MSLUG4_CUSTOMPATCH_MODS_FILL
    MSLUG4_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
    FIX_BIOS_COIN_FILL
    AUDIOBIOS_128K
    MSLUG4FR_SFIX_128K
    MSLUG4LW_AUDIOBIOS_128K
	MSLUG4LW_YMSND
	MSLUG4FR_SPRITES
ROM_END

ROM_START( mslug4rme01 )
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263_rme01.p1", 0x000000, 0x100000, CRC(8627daf5) SHA1(b57f770ede1e7abba868655213d10663fbaef76f) )
	ROM_LOAD16_WORD_SWAP( "263_rme01.p2", 0x100000, 0x800000, CRC(2126b58e) SHA1(664ab22cbe44f226da4b6f27aab1d8579028eb71) )
    MSLUG4_CUSTOMPATCH_MODS_FILL
    MSLUG4_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
    FIX_BIOS_COIN_FILL
	AUDIOBIOS_128K
    MSLUG4HD_SFIX_128K
    MSLUG4LW_AUDIOBIOS_128K
	MSLUG4LW_YMSND
	MSLUG4LWD_SPRITES
ROM_END

ROM_START( mslug5rma01 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_rma01.p1", 0x000000, 0x200000, CRC(be572d58) SHA1(e9cc66db10e3a75a35b0ddf9ffc57b3622a359f3) )
	ROM_LOAD16_WORD_SWAP( "268_rma01.p2", 0x200000, 0x400000, CRC(b2671f9d) SHA1(6fc8834183813dcfe649c93c1ac407fc5342bf36) )
    MSLUG5HD_CUSTOMPATCH_MODS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5W_AUDIO_512K
	MSLUG5RMXE_YMSND
	MSLUG5W_SPRITES
ROM_END

ROM_START( mslug5rmb01 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_rmb01.p1", 0x000000, 0x200000, CRC(724ba6b0) SHA1(f877648eb064038eebc38aa63ef86243798bf2bb) )
	ROM_LOAD16_WORD_SWAP( "268_rmb01.p2", 0x200000, 0x400000, CRC(81aa0fed) SHA1(9bdeb734d16f8fd33e0ed0b07facd28ada383190) )
    MSLUG5HD_CUSTOMPATCH_MODS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5W_AUDIO_512K
	MSLUG5RMXE_YMSND
	MSLUG5W_SPRITES
ROM_END

ROM_START( mslug5rmc01 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_rmc01.p1", 0x000000, 0x200000, CRC(9e9b738a) SHA1(a1556458ebeb950918509a6a4857781fa3f88727) )
	ROM_LOAD16_WORD_SWAP( "268_rmc01.p2", 0x200000, 0x400000, CRC(2aa0f0a1) SHA1(1f91c6274b9aa59a4f5944293da2a866e6f1029b) )
    MSLUG5HD_CUSTOMPATCH_MODS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5W_AUDIO_512K
	MSLUG5RMXE_YMSND
	MSLUG5W_SPRITES
ROM_END

ROM_START( mslug5rmd01 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_rmd01.p1", 0x000000, 0x200000, CRC(2acd2dbe) SHA1(dafaee22605ade96f993d2fa023bcd3b85bb2f3c) )
	ROM_LOAD16_WORD_SWAP( "268_rmd01.p2", 0x200000, 0x400000, CRC(1d956047) SHA1(535be6dad8201e25207e6ffb5d45685f8d4d2558) )
    MSLUG5HD_CUSTOMPATCH_MODS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5W_AUDIO_512K
	MSLUG5RMXE_YMSND
	MSLUG5W_SPRITES
ROM_END

ROM_START( mslug5rme01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_rme01.p1", 0x000000, 0x100000, CRC(b47843f8) SHA1(e6123a69d129dee85d1c1097b0caa4ef1fa09ddb) )
	ROM_LOAD16_WORD_SWAP( "268_rme01.p2", 0x100000, 0x400000, CRC(c850f9c0) SHA1(bf997c7bc02c83e98176e572e6733f8788f17ff4) )
    MSLUG5HD_CUSTOMPATCH_MODS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5_SFIX_MT_128K
    MSLUG5W_AUDIO_512K
	MSLUG5LA_YMSND
	MSLUG5W_SPRITES
ROM_END

ROM_START( mslug5rmf01 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_rmf01.p1", 0x000000, 0x200000, CRC(3852c423) SHA1(77e60c69e7378a3c2f8bd4d2211a1242108836e1) )
	ROM_LOAD16_WORD_SWAP( "268_rma01.p2", 0x200000, 0x400000, CRC(b2671f9d) SHA1(6fc8834183813dcfe649c93c1ac407fc5342bf36) )
    MSLUG5HD_CUSTOMPATCH_MODS_FILL
    MSLUG5HD_AES_FILL
    MSLUG5D_SFIX_128K
    MSLUG5W_AUDIO_512K
	MSLUG5RMXE_YMSND
	MSLUG5W_SPRITES
ROM_END

ROM_START( mslugxrma01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_rma01.p1", 0x000000, 0x100000, CRC(8de98a10) SHA1(5da46e07b90572b1a6363627eaeaf5fe3fdf1c1c) )
	ROM_LOAD16_WORD_SWAP( "250_rma01.p2", 0x100000, 0x400000, CRC(c919382a) SHA1(2c329945be9e105a13728130d26ba349489349c8) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
    FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxrmb01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_rma01.p1", 0x000000, 0x100000, CRC(8de98a10) SHA1(5da46e07b90572b1a6363627eaeaf5fe3fdf1c1c) )
	ROM_LOAD16_WORD_SWAP( "250_rmb01.p2", 0x100000, 0x400000, CRC(2de244a2) SHA1(348d858b1552d468d4ac8ec8a3be9d719c8ad3a2) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
    FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxrmc01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_rma01.p1", 0x000000, 0x100000, CRC(8de98a10) SHA1(5da46e07b90572b1a6363627eaeaf5fe3fdf1c1c) )
	ROM_LOAD16_WORD_SWAP( "250_rmc01.p2", 0x100000, 0x400000, CRC(7b838dac) SHA1(6345fb8eaece4c802208d8e7f8e63b5bfd6a53bd) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
    FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxrmd01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_rmd01.p1", 0x000000, 0x100000, CRC(ab43a260) SHA1(c514a472f0667756d1166843bc06e553a02566fb) )
	ROM_LOAD16_WORD_SWAP( "250_rmd01.p2", 0x100000, 0x400000, CRC(5a48649d) SHA1(989037f495dba30dd9b8783f563642d043453433) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
    FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxrme01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_rme01.p1", 0x000000, 0x100000, CRC(e296f4a7) SHA1(68f5021ff82090d8bba550a11dcc0eca8718787e) )
	ROM_LOAD16_WORD_SWAP( "250_rme01.p2", 0x100000, 0x400000, CRC(5d6a60c2) SHA1(a8fd79d3972f0b7a3e3a880c8c364413494f629c) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
    FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxrmf01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_rmf01.p1", 0x000000, 0x100000, CRC(546a6f67) SHA1(80a65720f0ce3c4e0604a47947c0fa6789580725) )
	ROM_LOAD16_WORD_SWAP( "250_rmf01.p2", 0x100000, 0x400000, CRC(036cc51a) SHA1(1468ebdff637c1db6c426a04a847a7d9aaa667c6) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
    FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxrmg01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_rma01.p1", 0x000000, 0x100000, CRC(8de98a10) SHA1(5da46e07b90572b1a6363627eaeaf5fe3fdf1c1c) )
	ROM_LOAD16_WORD_SWAP( "250_rmg01.p2", 0x100000, 0x400000, CRC(c0702999) SHA1(6b4138274d35c9419c7b155051722ec3f24eae9a) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
    FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

ROM_START( mslugxrmh01 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250_rma01.p1", 0x000000, 0x100000, CRC(8de98a10) SHA1(5da46e07b90572b1a6363627eaeaf5fe3fdf1c1c) )
	ROM_LOAD16_WORD_SWAP( "250_rmh01.p2", 0x100000, 0x400000, CRC(cbaef1eb) SHA1(a5cd2b885d3e0e3faae4d56a7016a13f12cadf81) )
    MSLUGX_CUSTOMPATCH_MODS_FILL
    MSLUGX_AES_FILL
    DEFAULT_BIOS_(MSLUG_FOREVER)
    FIX_BIOS_TIME_FILL
	AUDIOBIOS_128K
    MSLUGX_SFIX_128K
    MSLUGX_AUDIOBIOS_128K
	MSLUGX_YMSND
	MSLUGXLB_SPRITES
ROM_END

/*    YEAR   NAME            PARENT       MACHINE        INPUT                     INIT        MONITOR COMPANY          FULLNAME FLAGS */
// Metal Slug (MVS AND AES VERSION)
GAME( 2003, ms5pcb,           mslug5,   neogeo_noslot, ms5pcb,  neogeo_state,    init_ms5pcbhb,   ROT0, "SNK Playmore",   "Metal Slug 5 (JAMMA PCB)", MACHINE_SUPPORTS_SAVE )
GAME( 2002, ms4plus,          mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "Bootleg",        "Metal Slug 4 Plus (Bootleg)",  MACHINE_SUPPORTS_SAVE )
GAME( 2003, ms5plus,          mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_ms5plushb,  ROT0, "Bootleg",        "Metal Slug 5 Plus (Bootleg)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, mslug,            neogeo,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "Nazca",          "Metal Slug - Super Vehicle-001", MACHINE_SUPPORTS_SAVE )
GAME( 1998, mslug2,           neogeo,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "SNK",            "Metal Slug 2 - Super Vehicle-001/II (NGM-2410)(NGH-2410)", MACHINE_SUPPORTS_SAVE )
GAME( 2000, mslug3,           neogeo,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "SNK",            "Metal Slug 3 (NGM-2560)" , MACHINE_SUPPORTS_SAVE ) /* Encrypted Code & GFX */
GAME( 2000, mslug3a,          mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3a,    ROT0, "SNK",            "Metal Slug 3 (NGM-2560, Earlier)" , MACHINE_SUPPORTS_SAVE ) /* Encrypted Code & GFX - revision Mar/17/2000 1:36 (from SMA rom) */
GAME( 2000, mslug3h,          mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "SNK",            "Metal Slug 3 (NGH-2560)" , MACHINE_SUPPORTS_SAVE ) /* Encrypted GFX */
GAME( 2000, mslug3b6,         mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3b6hb, ROT0, "Bootleg",        "Metal Slug 6 (Metal Slug 3 Bootleg)", MACHINE_SUPPORTS_SAVE ) /* real Metal Slug 6 is an Atomiswave HW game, see naomi.c ;-) */
GAME( 2002, mslug4,           neogeo,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "Mega / Playmore", "Metal Slug 4 (NGM-2630)", MACHINE_SUPPORTS_SAVE )
GAME( 2002, mslug4h,          mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "Mega / Playmore", "Metal Slug 4 (NGH-2630)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, mslug5,           neogeo,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "SNK Playmore",   "Metal Slug 5 (NGM-2680)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, mslug5h,          mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "SNK Playmore",   "Metal Slug 5 (NGH-2680)", MACHINE_SUPPORTS_SAVE ) /* Also found in later MVS carts */
GAME( 2003, mslug5b,          mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5b,    ROT0, "Bootleg",        "Metal Slug 5 (Bootleg)", MACHINE_SUPPORTS_SAVE )
GAME( 1999, mslugx,           neogeo,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "SNK",            "Metal Slug X - Super Vehicle-001 (NGM-2500)(NGH-2500)", MACHINE_SUPPORTS_SAVE )

/*********************************************************************************************************************************************
  The prototype roms that had been published by the Neoragex emulator are included, in the NeoGeo system that presented some 
   copyrighted roms in that period of the year "1999-2000-2002-2003" that could not be legally emulated, they were Looked for an alternate 
   means to be able to play this roms by making an encrypted file. 
***********************************************************************************************************************************************/

/*    YEAR       NAME        PARENT       MACHINE       INPUT                       INIT        MONITOR COMPANY           FULLNAME FLAGS */
// Metal Slug (Predecrypted)
GAME( 2002, ms4plusp,         mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "Bootleg",        "Metal Slug 4 Plus (Bootleg)(Predecrypted)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, ms5plusp,         mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "Bootleg",        "Metal Slug 5 Plus (Bootleg)(Predecrypted)", MACHINE_SUPPORTS_SAVE )
GAME( 2000, mslug3b6p,        mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "Bootleg",        "Metal Slug 6 (Metal Slug 3 Bootleg)(Predecrypted)", MACHINE_SUPPORTS_SAVE )
GAME( 2002, mslug4p,          mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4p,    ROT0, "Mega / Playmore", "Metal Slug 4 (NGM-2630)(Predecrypted)", MACHINE_SUPPORTS_SAVE )
GAME( 2002, mslug4hp,         mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4p,    ROT0, "Mega / Playmore", "Metal Slug 4 (NGH-2630)(Predecrypted)", MACHINE_SUPPORTS_SAVE )
GAME( 2002, mslug4ndp,        mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "Mega / Playmore", "Metal Slug 4 (Fully Decrypted)(Predecrypted)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, mslug5p,          mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "SNK Playmore",   "Metal Slug 5 (NGM-2680)(Predecrypted)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, mslug5hp,         mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "SNK Playmore",   "Metal Slug 5 (NGH-2680)(Predecrypted)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, mslug5np,         mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5b1,   ROT0, "SNK Playmore",   "Metal Slug 5 (Not-Encrypted)(Predecrypted)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, mslug5ndp,        mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "SNK Playmore",   "Metal Slug 5 (Fully Decrypted)(Predecrypted)", MACHINE_SUPPORTS_SAVE )
GAME( 1999, mslugxp,          mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "SNK",            "Metal Slug X (Predecrypted)", MACHINE_SUPPORTS_SAVE ) 

/*    YEAR       NAME        PARENT       MACHINE       INPUT                       INIT        MONITOR COMPANY           FULLNAME FLAGS */
// Metal Slug (Decrypter, Earlier And Bootleg)
GAME( 2005, msboot,           mslug,    neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "Bootleg",        "Metal Slug (Bootleg)", MACHINE_SUPPORTS_SAVE )
GAME( 2002, ms4boot,          mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "Bootleg",        "Metal Slug 4 (Bootleg)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, ms5boot,          mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5b1,   ROT0, "Bootleg",        "Metal Slug 5 (Bootleg)(Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, ms5pcbd,          mslug5,   neogeo_noslot, ms5pcb,  neogeo_state,    init_ms5pcbhb,   ROT0, "SNK Playmore",   "Metal Slug 5 (JAMMA PCB, Decrypted C)", MACHINE_SUPPORTS_SAVE )
GAME( 2002, ms4plusd,         mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "Bootleg",        "Metal Slug 4 Plus (Bootleg)(Decrypted C)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, ms5plusd,         mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "Bootleg",        "Metal Slug 5 Plus (Bootleg)(Decrypted C)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, ms5plusc,         mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_ms5plushb,  ROT0, "Bootleg",        "Metal Slug 5 Plus (Bootleg, Chinese)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, msluge,           mslug,    neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "Nazca",          "Metal Slug (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 2015, mslug2t,          mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "SNK",            "Metal Slug 2 Turbo", MACHINE_SUPPORTS_SAVE )
GAME( 2000, mslug3d,          mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "SNK",            "Metal Slug 3 (NGM-2560)(Decrypted C)", MACHINE_SUPPORTS_SAVE )
GAME( 2000, mslug3hd,         mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "SNK",            "Metal Slug 3 (NGH-2560)(Decrypted C)", MACHINE_SUPPORTS_SAVE )
GAME( 2000, mslug3nd,         mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "SNK",            "Metal Slug 3 (Fully Decrypted)", MACHINE_SUPPORTS_SAVE )
GAME( 2000, mslug3b6d,        mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3b6hb, ROT0, "Bootleg",        "Metal Slug 6 (Metal Slug 3 Bootleg)(Decrypted C)", MACHINE_SUPPORTS_SAVE )
GAME( 2002, mslug4d,          mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "Mega / Playmore", "Metal Slug 4 (NGM-2630)(Decrypted C)", MACHINE_SUPPORTS_SAVE )
GAME( 2002, mslug4hd,         mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "Mega / Playmore", "Metal Slug 4 (NGH-2630)(Decrypted C)", MACHINE_SUPPORTS_SAVE )
GAME( 2002, mslug4nd,         mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "Mega / Playmore", "Metal Slug 4 (Fully Decrypted)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, mslug5d,          mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "SNK Playmore",   "Metal Slug 5 (NGM-2680)(Decrypted C)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, mslug5hd,         mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "SNK Playmore",   "Metal Slug 5 (NGH-2680)(Decrypted C)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, mslug5n,          mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "SNK Playmore",   "Metal Slug 5 (Not-Encrypted)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, mslug5nd,         mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "SNK Playmore",   "Metal Slug 5 (Fully Decrypted)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, mslug5b1,         mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5b1,   ROT0, "Bootleg",        "Metal Slug 5 (Bootleg, Set 1)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, mslug5b2,         mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5b1,   ROT0, "Bootleg",        "Metal Slug 5 (Bootleg, Set 2)", MACHINE_SUPPORTS_SAVE )

/*    YEAR       NAME        PARENT       MACHINE       INPUT                       INIT        MONITOR COMPANY           FULLNAME FLAGS */
// Metal Slug (Decrypter / Darksoft)
// Non NeoGeo Titles Made For Specific Board. Do Not Work, Metal Slug 5 (JAMMA PCB)
GAME( 2002, ms4plusdd,        mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_darksoft,   ROT0, "Bootleg",        "Metal Slug 4 Plus (Bootleg)(Decrypter / Darksoft)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, ms5plusdd,        mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_darksoft,   ROT0, "Bootleg",        "Metal Slug 5 Plus (Bootleg)(Decrypter / Darksoft)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, mslugdd,          mslug,    neogeo_noslot, mslughb, neogeo_state,    init_darksoft,   ROT0, "Nazca",          "Metal Slug (Decrypter / Darksoft)", MACHINE_SUPPORTS_SAVE )
GAME( 1998, mslug2dd,         mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_darksoft,   ROT0, "SNK",            "Metal Slug 2 (Decrypter / Darksoft)", MACHINE_SUPPORTS_SAVE )
GAME( 1998, mslug2tdd,        mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_darksoft,   ROT0, "SNK",            "Metal Slug 2 Turbo (Decrypter / Darksoft)", MACHINE_SUPPORTS_SAVE )
GAME( 2000, mslug3dd,         mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3dd,   ROT0, "SNK",            "Metal Slug 3 (Decrypter / Darksoft)", MACHINE_SUPPORTS_SAVE )
GAME( 2000, mslug3b6dd,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3dd,   ROT0, "SNK",            "Metal Slug 6 (Metal Slug 3 Bootleg)(Decrypter / Darksoft)", MACHINE_SUPPORTS_SAVE )
GAME( 2002, mslug4dd,         mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4dd,   ROT0, "Mega / Playmore", "Metal Slug 4 (NGM-2630)(Decrypter / Darksoft)", MACHINE_SUPPORTS_SAVE )
GAME( 2002, mslug4hdd,        mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4dd,   ROT0, "Mega / Playmore", "Metal Slug 4 (NGH-2630)(Decrypter / Darksoft)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, mslug5dd,         mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5dd,   ROT0, "SNK Playmore",   "Metal Slug 5 (NGM-2680)(Decrypter / Darksoft)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, mslug5hdd,        mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5dd,   ROT0, "SNK Playmore",   "Metal Slug 5 (NGH-2680)(Decrypter / Darksoft)", MACHINE_SUPPORTS_SAVE )
GAME( 1999, mslugxdd,         mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugxdd,   ROT0, "SNK",            "Metal Slug X (Decrypter / Darksoft)", MACHINE_SUPPORTS_SAVE )

/*    YEAR       NAME        PARENT       MACHINE       INPUT                       INIT        MONITOR COMPANY           FULLNAME FLAGS */
// Metal Slug (Hack)
GAME( 2016, mslughc01,        mslug,    neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "DDJ",            "Metal Slug (Change Weapon 2016-03-26)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslughc02,        mslug,    neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "FBN4DROID",      "Metal Slug (Random Items Explosives 2021-06-08)", MACHINE_SUPPORTS_SAVE )
GAME( 2016, mslughc03,        mslug,    neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "DDJ",            "Metal Slug (War Chariot 2016-03-26)", MACHINE_SUPPORTS_SAVE )
GAME( 2018, mslughc04,        mslug,    neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "GOTVG",          "Metal Slug (Multi-Function Version 2018-04-30)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslughc05,        mslug,    neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "I love Nimes",   "Metal Slug (Burst Enhanced Edition 2021-09-19)", MACHINE_SUPPORTS_SAVE )
GAME( 2018, mslughc06,        mslug,    neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "hack",           "Metal Slug (Easy Mode 2018-11-26)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslughc07,        mslug,    neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "KofKill, Wang Hua, Czk", "Metal Slug (Unity Time! 2021-02-05)", MACHINE_SUPPORTS_SAVE )
GAME( 2016, mslughc08,        mslug,    neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "DDJ",            "Metal Slug (Stage Select 2016-10-17)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslughc09,        mslug,    neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "GOTVG",          "Metal Slug (1v2 Generation 2023-06-26)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslughc10,        mslug,    neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "GOTVG",          "Metal Slug (Origin 2023-03-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2017, mslughc11,        mslug,    neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "DDJ",            "Metal Slug (Jump In Mid Air 2017-08-24)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslughc12,        mslug,    neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "hack",           "Metal Slug (Enemy Speed Up 2023-03-14)", MACHINE_SUPPORTS_SAVE )

/*    YEAR       NAME         PARENT       MACHINE     INPUT                       INIT         MONITOR COMPANY            FULLNAME FLAGS */
// Metal Slug 2
GAME( 2014, mslug2hc01,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "GOTVG",           "Metal Slug 2 (Enemies Resetting Version 2014-09-14)", MACHINE_SUPPORTS_SAVE )
GAME( 2019, mslug2hc02,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "GOTVG",           "Metal Slug 2 (1V2 Generation 2019-05-11)", MACHINE_SUPPORTS_SAVE )
GAME( 2016, mslug2hc03,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "DDJ",             "Metal Slug 2 (Stage Select 2016-10-19)", MACHINE_SUPPORTS_SAVE )
GAME( 2008, mslug2hc04,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "hack",            "Metal Slug 2 (Hybrid bullets Fix Version 2008-12-04)", MACHINE_SUPPORTS_SAVE ) // This version 2023 has been fix
GAME( 2021, mslug2hc05,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "FBN4DROID",       "Metal Slug 2 (Extraction Green Turbo 2021-09-16)", MACHINE_SUPPORTS_SAVE )
GAME( 2018, mslug2hc06,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "DDJ",             "Metal Slug 2 (War Chariot 2018-01-25)", MACHINE_SUPPORTS_SAVE )
GAME( 2018, mslug2hc07,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "DDJ",             "Metal Slug 2 (Change Weapon And Mummy 2018-08-25)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslug2hc08,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "I love Nimes",    "Metal Slug 2 (Burst Enhanced Edition 2021-04-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2017, mslug2hc09,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "GOTVG",           "Metal Slug 2 (Multi-Function Version 2017-05-09)", MACHINE_SUPPORTS_SAVE )
GAME( 2018, mslug2hc10,       mslug2,   neogeo_noslot, mslughw, neogeo_state,    init_neogeo,     ROT0, "GOTVG",           "Metal Slug 2 (Survival Version 2018-07-31)", MACHINE_SUPPORTS_SAVE ) // To enable Mods random you need to apply a command you have to press the Stars + D button to change Stars + C.
GAME( 2015, mslug2hc11,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "GOTVG",           "Metal Slug 2 (Weapon Storage 2015-11-11)", MACHINE_SUPPORTS_SAVE )
GAME( 2018, mslug2hc12,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "hack",            "Metal Slug 2 (Easy Mode 2018-11-26)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslug2hc13,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "KofKill, Wang Hua, Czk", "Metal Slug 2 (Unity Time! 2021-01-22)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslug2hc14,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "GOTVG",           "Metal Slug 2 (Friendly Fire Edition 2021-04-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug2hc15,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "GOTVG",           "Metal Slug 2 (Early Summer Starry Sky 2022-05-11)", MACHINE_SUPPORTS_SAVE )
GAME( 2015, mslug2hc16,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "DDJ",             "Metal Slug 2 (Jump In Mid Air 2015-08-24)", MACHINE_SUPPORTS_SAVE )
GAME( 2006, mslug2hc17,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "hack",            "Metal Slug 2 (Traduction French)", MACHINE_SUPPORTS_SAVE )
GAME( 2011, mslug2hc18,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "hack",            "Metal Slug 2 (A Full Screen Attack 2011-01-16)", MACHINE_SUPPORTS_SAVE )
GAME( 2016, mslug2hc19,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "hack",            "Metal Slug 2 (Slug #1 Version 2016-04-12)", MACHINE_SUPPORTS_SAVE )

/*    YEAR       NAME         PARENT       MACHINE      INPUT                       INIT        MONITOR COMPANY            FULLNAME FLAGS */
// Metal Slug 3
GAME( 2000, mslug3hc01,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "HappyAsr",        "Metal Slug 3 (Super D version)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug3hc02,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "I love Nimes",    "Metal Slug 3 (Burst Enhanced Edition 2022-10-13)", MACHINE_SUPPORTS_SAVE )
GAME( 2019, mslug3hc03,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "GOTVG",           "Metal Slug 3 (Multi-Function Version 2019-03-05)" , MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug3hc04,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "GOTVG",           "Metal Slug 3 (SE Special Edition 2022-03-31)", MACHINE_SUPPORTS_SAVE ) 
GAME( 2013, mslug3hc05,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3de,   ROT0, "GOTVG",           "Metal Slug 3 (Green Blue Edition 2013-02-27)",  MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 2018, mslug3hc06,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "GOTVG",           "Metal Slug 3 (Shop Version 2017-12-16)" , MACHINE_SUPPORTS_SAVE )
GAME( 2015, mslug3hc07,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "DDJ",             "Metal Slug 3 (Jump In Mid Air 2015-08-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2018, mslug3hc08,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "GOTVG",           "Metal Slug 3 (Summon Mount Edition 2017-04-04)" , MACHINE_SUPPORTS_SAVE )
GAME( 2019, mslug3hc09,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "GOTVG",           "Metal Slug 3 (SE Special Edition 2019-07-27)(Rollback)", MACHINE_SUPPORTS_SAVE )
GAME( 2018, mslug3hc10,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "GOTVG",           "Metal Slug 3 (Onimusha Samanosuke 2018-05-29)", MACHINE_SUPPORTS_SAVE )
GAME( 2019, mslug3hc11,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "FBN4DROID",       "Metal Slug 3 (Enemy Soldiers Reset 2019-01-02)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3hc12,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "GOTVG",           "Metal Slug 3 (Ultimate Simplified Edition 2020-08-25)", MACHINE_SUPPORTS_SAVE )
GAME( 2013, mslug3hc13,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "FBN4DROID",       "Metal Slug 3 (Hybrid Bullets Version 2013-01-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2016, mslug3hc14,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "DDJ",             "Metal Slug 3 (War Chariot 2016-02-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3hc15,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "FBN4DROID",       "Metal Slug 3 (The Future 2020-09-12)", MACHINE_SUPPORTS_SAVE )
GAME( 2017, mslug3hc16,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "FBN4DROID",       "Metal Slug 3 (Enemy Remake 2017-09-27)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3hc17,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "FBN4DROID",       "Metal Slug 3 (The Last Warhead 2020-09-05)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslug3hc18,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "GOTVG",           "Metal Slug 3 (Infinite Firepower 2021-03-17)", MACHINE_SUPPORTS_SAVE )
GAME( 2019, mslug3hc19,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "GOTVG",           "Metal Slug 3 (Enemies Resetting Version 2019-07-20)" , MACHINE_SUPPORTS_SAVE )
GAME( 2017, mslug3hc20,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "FBN4DROID",       "Metal Slug 3 (Random Enemies Resetting Version 2017-12-08)" , MACHINE_SUPPORTS_SAVE )
GAME( 2017, mslug3hc21,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "Wanghua123",      "Metal Slug 3 (Slug #1 Version 2017-10-09)", MACHINE_SUPPORTS_SAVE )
GAME( 2019, mslug3hc22,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "Wanghua123",      "Metal Slug 3 (Slug #2 Version 2019-02-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2018, mslug3hc23,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "hack",            "Metal Slug 3 (Easy Mode 2018-11-16)" , MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslug3hc24,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3de,   ROT0, "KofKill, Wang Hua, Czk", "Metal Slug 3 (Unity Time! 2021-02-21)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3hc25,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "GOTVG",           "Metal Slug 3 (Legendary Edition 2023-03-01)" , MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug3hc26,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "GOTVG",           "Metal Slug 3 (Early Summer Starry Sky 2022-05-11)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug3hc27,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "GOTVG",           "Metal Slug 3 (Komorebi 2022-05-11)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3hc28,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "GOTVG",           "Metal Slug 3 (Legendary Latest Random Level Version 2023-06-01)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 2012, mslug3hc29,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "hack",            "Metal Slug 3 (Change Weapons 2012-05-22)" , MACHINE_SUPPORTS_SAVE )
GAME( 2016, mslug3hc30,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "DDJ",             "Metal Slug 3 (Change Body 2016-03-10)", MACHINE_SUPPORTS_SAVE )
GAME( 2012, mslug3hc31,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "hack",            "Metal Slug 3 (Violence Edition 2012-03-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2004, mslug3hc32,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "hack",            "Metal Slug 3 (French Traduction)", MACHINE_SUPPORTS_SAVE )
GAME( 2014, mslug3hc33,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3de,   ROT0, "hack",            "Metal Slug 3 (Green Edition 2014-10-15)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3hc34,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "GOTVG",           "Metal Slug 3 (Pigeon Slug 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3hc35,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "hack",            "Metal Slug 3 (Automatic Storage Version 2022-10-16)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3hc36,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "hack",            "Metal Slug 3 (Enemy Speed Up 2023-03-14)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3hc37,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "hack",            "Metal Slug 3 (Longest Campaign Version 2023-03-14)", MACHINE_SUPPORTS_SAVE )
GAME( 2019, mslug3hc38,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3de,   ROT0, "GOTVG",           "Metal Slug 3 (1V2 Generation 2019-05-11)" , MACHINE_SUPPORTS_SAVE )

// Metal Slug 6" is a hack/bootleg of Metal Slug 3
GAME( 2019, mslug3b6hc01,     mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3b6hb, ROT0, "hack",            "Metal Slug 6 (Enemies Resetting Version 2019-07-20)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3b6hc02,     mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3b6hb, ROT0, "hack",            "Metal Slug 6 (The Future 2020-09-29)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3b6hc03,     mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3b6hb, ROT0, "hack",            "Metal Slug 6 (Enemy Remake 2017-09-27)", MACHINE_SUPPORTS_SAVE )
GAME( 2019, mslug3b6hc04,     mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3b6hb, ROT0, "hack",            "Metal Slug 6 (Enemy Soldiers Reset 2019-01-02)", MACHINE_SUPPORTS_SAVE )
GAME( 2017, mslug3b6hc05,     mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3b6hb, ROT0, "hack",            "Metal Slug 6 (Random Enemies Resetting #1 2017-12-08)", MACHINE_SUPPORTS_SAVE )
GAME( 2017, mslug3b6hc06,     mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3b6hb, ROT0, "hack",            "Metal Slug 6 (Random Enemies Resetting #2 2017-12-08)", MACHINE_SUPPORTS_SAVE )
GAME( 2017, mslug3b6hc07,     mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3b6hb, ROT0, "hack",            "Metal Slug 6 (Random Enemies Resetting #3 2017-12-08)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3b6hc08,     mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3b6hb, ROT0, "hack",            "Metal Slug 6 (Pigeon Slug #1 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3b6hc09,     mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3b6hb, ROT0, "hack",            "Metal Slug 6 (Pigeon Slug #2 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3b6hc10,     mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3b6hb, ROT0, "hack",            "Metal Slug 6 (Pigeon Slug #3 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3b6hc11,     mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3b6hb, ROT0, "hack",            "Metal Slug 6 (Pigeon Slug #4 2023-03-28)", MACHINE_SUPPORTS_SAVE )

/*    YEAR       NAME         PARENT       MACHINE      INPUT                        INIT        MONITOR COMPANY           FULLNAME FLAGS */
// Metal Slug 4
GAME( 2007, mslug4hc01,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "HappyAsr",        "Metal Slug 4 (Super D Version)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslug4hc02,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "I love Nimes",    "Metal Slug 4 (Burst Enhanced Version 2021-04-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4hc03,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "GOTVG",           "Metal Slug 4 (Last Bullet Remix 2023-02-25)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4hc04,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "GOTVG",           "Metal Slug 4 (Ammunition Random Edition 2023-02-25)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug4hc05,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "GOTVG",           "Metal Slug 4 (Enemies Resetting Version 2020-02-10)", MACHINE_SUPPORTS_SAVE )
GAME( 2017, mslug4hc06,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "GOTVG",           "Metal Slug 4 (Multi-Function Version 2017-12-25)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslug4hc07,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "hack",            "Metal Slug 4 (Children's Version 2021-06-06)", MACHINE_SUPPORTS_SAVE )
GAME( 2015, mslug4hc08,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "DDJ",             "Metal Slug 4 (Jump In Mid Air 2015-08-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug4hc09,       mslug4,   neogeo_noslot, mslughw, neogeo_state,    init_mslug4hb,   ROT0, "GOTVG",           "Metal Slug 4 (The Longest Fight 2022-06-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2013, mslug4hc10,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "DDJ",             "Metal Slug 4 (War Chariot 2013-02-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2019, mslug4hc11,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "GOTVG",           "Metal Slug 4 (1V2 Generation 2019-05-11)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4hc12,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "GOTVG",           "Metal Slug 4 (Last Bullet Remix Bulletproof Vest Removed 2023-02-25)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4hc13,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "hack",            "Metal Slug 4 (Enemy Speed Up 2023-03-14)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslug4hc14,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "KofKill, Wang Hua, Czk", "Metal Slug 4 (Unity Time! 2021-01-30)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslug4hc15,       mslug4,   neogeo_noslot, mslughw, neogeo_state,    init_mslug4hb,   ROT0, "GOTVG",           "Metal Slug 4 (20th Anniversary Edition 2022-03-18)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug4hc16,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "GOTVG",           "Metal Slug 4 (Early Summer Starry Sky 2022-05-11)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug4hc17,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "GOTVG",           "Metal Slug 4 (Komorebi 2022-05-11)", MACHINE_SUPPORTS_SAVE )
GAME( 2010, mslug4hc18,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "DDJ",             "Metal Slug 4 (Change Weapon 2010-03-10)", MACHINE_SUPPORTS_SAVE )
GAME( 2012, mslug4hc19,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "DDJ",             "Metal Slug 4 (Change Body 2012-05-25)", MACHINE_SUPPORTS_SAVE )
GAME( 2002, mslug4hc20,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "hack",            "Metal Slug 4 (French Traduction)", MACHINE_SUPPORTS_SAVE )
GAME( 2007, mslug4hc21,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "hack",            "Metal Slug 4 (Traduction Italian)", MACHINE_SUPPORTS_SAVE )
GAME( 2018, mslug4hc22,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "hack",            "Metal Slug 4 (Easy Mode 2018-11-16)", MACHINE_SUPPORTS_SAVE ) // Fix 2023
GAME( 2019, mslug4hc23,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "GOTVG",           "Metal Slug 4 (Enemies Resetting Version 2019-02-11)(Rollback)", MACHINE_SUPPORTS_SAVE )

/*    YEAR       NAME         PARENT       MACHINE      INPUT                       INIT        MONITOR COMPANY            FULLNAME FLAGS */
// Metal Slug 5
GAME( 2016, mslug5hc01,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "DDJ",             "Metal Slug 5 (Change Weapons 2016-02-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug5hc02,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "FBN4DROID",       "Metal Slug 5 (Hybrid Bullets Version 2020-09-14)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug5hc03,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "GOTVG",           "Metal Slug 5 (Extender Ver. 2022 2022-10-02)", MACHINE_SUPPORTS_SAVE )
GAME( 2015, mslug5hc04,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "GOTVG",           "Metal Slug 5 (The New Campaign 2015-03-27)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslug5hc05,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "GOTVG",           "Metal Slug 5 (Ultimate Simplified Edition 2021-01-13)", MACHINE_SUPPORTS_SAVE )
GAME( 2016, mslug5hc06,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "GOTVG",           "Metal Slug 5 (Fierce Battle 2015-03-25)", MACHINE_SUPPORTS_SAVE )
GAME( 2018, mslug5hc07,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "hack",            "Metal Slug 5 (Easy Mode 2018-11-16)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslug5hc08,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "KofKill, Wang Hua, Czk", "Metal Slug 5 (Unity Time! 2021-04-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug5hc09,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "GOTVG",           "Metal Slug 5 (X Final 2022-06-06)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug5hc10,       mslug5,   neogeo_noslot, mslughw, neogeo_state,    init_mslug5hb,   ROT0, "GOTVG",           "Metal Slug 5 (The Longest Battle 2023-02-08)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug5hc11,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "I love Nimes",    "Metal Slug 5 (Burst Enhanced Edition 2022-10-13)", MACHINE_SUPPORTS_SAVE )
GAME( 2019, mslug5hc12,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "GOTVG",           "Metal Slug 5 (Enemies Resetting Version 2019-07-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug5hc13,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "GOTVG",           "Metal Slug 5 (Enemy Soldiers Enhanced Version 2020-04-06)",  MACHINE_SUPPORTS_SAVE )
GAME( 2019, mslug5hc14,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "GOTVG",           "Metal Slug 5 (Enemy Soldiers Magic Version 2019-12-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2019, mslug5hc15,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "GOTVG",           "Metal Slug 5 (1v2 Generation 2019-05-11)", MACHINE_SUPPORTS_SAVE )
GAME( 2018, mslug5hc16,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "GOTVG",           "Metal Slug 5 (Summon Slug Edition 2018-09-18)", MACHINE_SUPPORTS_SAVE )
GAME( 2017, mslug5hc17,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "GOTVG",           "Metal Slug 5 (Multi-Function Version 2017-05-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug5hc18,       mslug5,   neogeo_noslot, mslug5sg, neogeo_state,   init_mslug5hb,   ROT0, "GOTVG",           "Metal Slug 5 (Stone Tortoise Edition 2023-06-25)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug5hc19,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "FBN4DROID",       "Metal Slug 5 (Crazy Fire Edition 2020-09-02)", MACHINE_SUPPORTS_SAVE )
GAME( 2015, mslug5hc20,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "hack",            "Metal Slug 5 (War Chariot 2015-05-20)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug5hc21,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "GOTVG",           "Metal Slug 5 (Early Summer Starry Sky 2022-08-10)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug5hc22,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "GOTVG",           "Metal Slug 5 (Komorebi 2022-08-10)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug5hc23,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "GOTVG",           "Metal Slug 5 (Boss Edition 2023-06-25)", MACHINE_SUPPORTS_SAVE )
GAME( 2006, mslug5hc24,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "hack",            "Metal Slug 5 (Traduction French)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug5hc25,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "hack",            "Metal Slug 5 (Full Line Version 2022-08-10)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug5hc26,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "hack",            "Metal Slug 5 Plus (Hide Oh Big Mode 2023-01-27)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug5hc27,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "hack",            "Metal Slug 5 (Red Tank Expansion 2023-03-14)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug5hc28,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "GOTVG",           "Metal Slug 5 (Legendary Edition 2023-06-12)", MACHINE_SUPPORTS_SAVE )

/*    YEAR       NAME         PARENT       MACHINE      INPUT                       INIT        MONITOR COMPANY            FULLNAME FLAGS */
// Metal Slug X
GAME( 2013, mslugxhc01,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "GOTVG",           "Metal Slug X (Level Reset Special Edition 2013-10-29)", MACHINE_SUPPORTS_SAVE )
GAME( 2015, mslugxhc02,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "GOTVG",           "Metal Slug X (Extreme Space Edition 2015-04-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslugxhc03,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "GOTVG",           "Metal Slug X (Unlimited Firepower 2020-10-18)(Rollback)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslugxhc04,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "KofKill, Wang Hua, Czk", "Metal Slug X (Unity Time! 2021-01-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2013, mslugxhc05,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "GOTVG",           "Metal Slug X (Green Edition 2013-02-27)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslugxhc06,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "GOTVG",           "Metal Slug X (Infinite Firepower Edition 2021-03-20 )", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxhc07,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PlayerX China And Gaston90",   "Metal Slug X (Enemy Heavy Plate 2023-05-19)", MACHINE_SUPPORTS_SAVE )
GAME( 2018, mslugxhc08,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "DDJ",             "Metal Slug X (Change Weapon And Mummy 2018-09-26)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslugxhc09,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "GOTVG",           "Metal Slug X (SV Generation 2020-11-04)", MACHINE_SUPPORTS_SAVE )
GAME( 2016, mslugxhc10,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "DDJ",             "Metal Slug X (War Chariot 2016-03-13)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxhc11,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PlayerX China And Gaston90",   "Metal Slug X (Enemy Soldiers Remake Version 3.1 2023-05-19)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxhc12,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "GOTVG",           "Metal Slug X (Last Legendary Edition 2023-03-11)", MACHINE_SUPPORTS_SAVE )
GAME( 2018, mslugxhc13,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "hack",            "Metal Slug X (Easy Mode 2018-11-26)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslugxhc14,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "I love Nimes",    "Metal Slug X (Burst Enhanced Edition 2022-10-13)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslugxhc15,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "GOTVG",           "Metal Slug X (Enemy Soldiers Reset Version 2.7 2021-04-03)", MACHINE_SUPPORTS_SAVE )
GAME( 2014, mslugxhc16,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "hack",            "Metal Slug X (Hybrid Bullets Version 2014-11-08)", MACHINE_SUPPORTS_SAVE )
GAME( 2019, mslugxhc17,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "GOTVG",           "Metal Slug X (1V2 Generation 2019-05-11)", MACHINE_SUPPORTS_SAVE )
GAME( 2018, mslugxhc18,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "FBN4DROID",       "Metal Slug X (Big Heavy Machine Gun Flame Edition 2018-12-08)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslugxhc19,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "GOTVG",           "Metal Slug X (2R Version 2020-04-27)", MACHINE_SUPPORTS_SAVE )
GAME( 2013, mslugxhc20,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "GOTVG",           "Metal Slug X (Multi-Carrier Version 2013-05-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslugxhc21,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "GOTVG",           "Metal Slug X (Unlimited Firepower 2021-03-20)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslugxhc22,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "GOTVG",           "Metal Slug X (2R Blue Edition 2020-06-24)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslugxhc23,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "GOTVG",           "Metal Slug X (2R Generation 1V2 2020-05-18)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslugxhc24,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "GOTVG",           "Metal Slug X (Early Summer Starry Sky 2022-08-10)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxhc25,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "GOTVG",           "Metal Slug X (Legendary Origin Edition 2023-02-13)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxhc26,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "GOTVG",           "Metal Slug X (Multi-Function Version 2023-06-30)", MACHINE_SUPPORTS_SAVE )
GAME( 2015, mslugxhc27,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "DDJ",             "Metal Slug X (Jump In Mid Air 2015-08-24)", MACHINE_SUPPORTS_SAVE )
GAME( 2014, mslugxhc28,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "hack",            "Metal Slug X (Green Edition 2014-10-15)", MACHINE_SUPPORTS_SAVE )
GAME( 2012, mslugxhc29,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "hack",            "Metal Slug X (Violence Version 2012-01-08)", MACHINE_SUPPORTS_SAVE )
GAME( 2006, mslugxhc30,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "hack",            "Metal Slug X (Translator French)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, mslugxhc31,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "hack",            "Metal Slug X (Translator Italian - Beta)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxhc32,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "hack",            "Metal Slug X (Enemy Speed Up 2023-03-14)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxhc33,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "hack",            "Metal Slug X (Survival Attack 2023-03-14)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxhc34,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "hack",            "Metal Slug X (Plus v0.3 2020-07-26)", MACHINE_SUPPORTS_SAVE )

/*    YEAR   NAME             PARENT       MACHINE       INPUT                       INIT        MONITOR COMPANY           FULLNAME FLAGS */
// HomeBrew
GAME( 2022, mslug3x,          neogeo,   neogeo_noslot, neogeo,  neogeo_state,    init_neogeo,     ROT0, "CB, Willnie",     "Metal Slug HomeBrew (Mothership Armageddon Easter Egg 2022-01-10)", MACHINE_SUPPORTS_SAVE )
GAME( 2010, neopang,          mslug3x,  neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "CeL",             "Metal Slug HomeBrew (Neo Pang)", MACHINE_SUPPORTS_SAVE )

/***************
 Only exclusive
*****************/
/*********************************************************************************
* This game sector is exclusive, its modifications that load have been customized
  241.p1 and 241.p2 files. Therefore, a unique and distinctive game will be displayed 
  from the rest, we have been working to Optimize performance and avoid any type of crash 
  that occurs during the game. This it just means there are some details of the roms that 
  still need to be improved, things to add and things that could later be updated or 
  permanently removed if some kind a problem is detected that cannot be solved ...
********************************************************************************************/
/*********************************************************************************************
* They are the first hack remix roms that I have made in a basic way for the HBMAME emulator.
**************************************************************************************************/

/*    YEAR   NAME             PARENT       MACHINE       INPUT                       INIT        MONITOR COMPANY             FULLNAME FLAGS */
// Metal Slug (Version Custom)
GAME( 2023, mslugctma01,        mslug,    neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug (Multi-Function 1v2 Generation 2023-06-26)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslugctma02,        mslug,    neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug (Multi-Function Burst Enhanced Edition 2021-09-19)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslugctma03,        mslug,    neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug (Multi-Function Change Weapon 2016-03-26)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslugctma04,        mslug,    neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug (Multi-Function Easy Mode 2018-11-26)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugctma05,        mslug,    neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug (Multi-Function Enemy Speed Up 2023-03-14)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslugctma06,        mslug,    neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug (Multi-Function Random Items Explosives 2021-06-08)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslugctma07,        mslug,    neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug (Multi-Function War Chariot 2016-03-26)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug2ctma01,       mslug2,   neogeo_noslot, mslughw, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (Enemies Resetting Survival Version 2018-07-31)", MACHINE_SUPPORTS_SAVE ) // To enable Mods random you need to apply a command you have to press the Stars + D button to change Stars + C.
GAME( 2020, mslug2ctma02,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (Enemies Resetting Multi-Function Version 2017-05-09)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug2ctma03,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (Enemies Resetting 1V2 Generation 2019-05-11)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug2ctma04,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (Enemies Resetting Hybrid bullets Fix Version 2008-12-04)", MACHINE_SUPPORTS_SAVE ) // This version 2023 has been fix
GAME( 2020, mslug2ctma05,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (Enemies Resetting Burst Enhanced Edition 2021-04-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug2ctma06,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (Enemies Resetting Easy Mode 2018-11-26)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug2ctma07,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (Enemies Resetting Weapon Storage 2015-11-11)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslug2ctma08,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (Enemies Resetting Unity Time! 2021-01-22)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslug2ctma09,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (Enemies Resetting Friendly Fire Edition 2021-04-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug2ctma10,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (Enemies Resetting War Chariot 2018-01-25)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug2ctma11,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (Enemies Resetting Change Weapon And Mummy 2018-01-25)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug2ctma12,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (Enemies Resetting Early Summer Starry Sky 2022-05-11)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslug2ctma13,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (Enemies Resetting Extraction Green Turbo 2021-09-16)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctma01,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting Multi-Function Custom Version 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctma02,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting Onimusha Samanosuke Custom Version 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctma03,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting Summon Mount Custom Edition 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctma04,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting Shop Version Custom 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctma05,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting SE Special Custom Edition 2020-05-01)(Rollback)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctma06,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting Burst Enhanced Custom Edition 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctma07,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting Super D Custom version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctma08,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting Violence Custom Edition 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctma09,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting Ultimate Simplified Custom Edition 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctma10,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting Infinite Firepower Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctma11,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting Easy Mode Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctma12,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting Enemy Speed Up Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctma13,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting Automatic Storage Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctma14,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting Hybrid Bullets Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctma15,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting Early Summer Starry Sky Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmb01,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (The Future Multi-Function Custom Version 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmb02,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (The Future Onimusha Samanosuke Custom Version 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmb03,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (The Future Summon Mount Custom Edition 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmb04,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (The Future Shop Version Custom 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmb05,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (The Future SE Special Custom Edition 2020-05-01)(Rollback)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmb06,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (The Future Burst Enhanced Custom Edition 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmb07,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (The Future Super D Custom version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmb08,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (The Future Violence Custom Edition 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmb09,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (The Future Ultimate Simplified Custom Edition 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmb10,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (The Future Infinite Firepower Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmb11,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (The Future Easy Mode Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmb12,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (The Future Enemy Speed Up Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmb13,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (The Future Automatic Storage Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmb14,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (The Future Hybrid Bullets Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmb15,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (The Future Early Summer Starry Sky Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmc01,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Soldiers Reset Multi-Function Custom Version 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmc02,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Soldiers Reset Onimusha Samanosuke Custom Version 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmc03,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Soldiers Reset Summon Mount Custom Edition 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmc04,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Soldiers Reset Shop Version Custom 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmc05,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Soldiers Reset SE Special Custom Edition 2020-05-01)(Rollback)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmc06,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Soldiers Reset Burst Enhanced Custom Edition 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmc07,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Soldiers Reset Super D Custom version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmc08,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Soldiers Reset Violence Custom Edition 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmc09,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Soldiers Reset Ultimate Simplified Custom Edition 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmc10,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Soldiers Reset Infinite Firepower Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmc11,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Soldiers Reset Easy Mode Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmc12,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Soldiers Reset Enemy Speed Up Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmc13,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Soldiers Reset Automatic Storage Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmc14,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Soldiers Reset Hybrid Bullets Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmc15,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Soldiers Reset Early Summer Starry Sky Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmd01,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Remake Multi-Function Custom Version 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmd02,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Remake Onimusha Samanosuke Custom Version 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmd03,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Remake Summon Mount Custom Edition 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmd04,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Remake Shop Version Custom 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmd05,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Remake SE Special Custom Edition 2020-05-01)(Rollback)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmd06,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Remake Burst Enhanced Custom Edition 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmd07,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Remake Super D Custom version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmd08,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Remake Violence Custom Edition 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmd09,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Remake Ultimate Simplified Custom Edition 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmd10,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Remake Infinite Firepower Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmd11,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Remake Easy Mode Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmd12,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Remake Enemy Speed Up Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmd13,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Remake Automatic Storage Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmd14,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Remake Hybrid Bullets Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmd15,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemy Remake Early Summer Starry Sky Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctme01,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #1 Multi-Function Custom Version 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctme02,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #1 Onimusha Samanosuke Custom Version 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctme03,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #1 Summon Mount Custom Edition 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctme04,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #1 Shop Version Custom 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctme05,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #1 SE Special Custom Edition 2020-05-01)(Rollback)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctme06,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #1 Burst Enhanced Custom Edition 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctme07,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #1 Super D Custom version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctme08,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #1 Violence Custom Edition 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctme09,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #1 Ultimate Simplified Custom Edition 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctme10,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #1 Infinite Firepower Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctme11,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #1 Easy Mode Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctme12,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #1 Enemy Speed Up Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
//GAME( 2020, mslug3ctme13,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #1 Automatic Storage Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctme14,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #1 Hybrid Bullets Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmf01,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #2 Multi-Function Custom Version 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmf02,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #2 Onimusha Samanosuke Custom Version 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmf03,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #2 Summon Mount Custom Edition 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmf04,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #2 Shop Version Custom 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmf05,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #2 SE Special Custom Edition 2020-05-01)(Rollback)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmf06,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #2 Burst Enhanced Custom Edition 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmf07,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #2 Super D Custom version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmf08,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #2 Violence Custom Edition 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmf09,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #2 Ultimate Simplified Custom Edition 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmf10,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #2 Infinite Firepower Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmf11,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #2 Easy Mode Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmf12,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #2 Enemy Speed Up Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
//GAME( 2020, mslug3ctmf13,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #2 Automatic Storage Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmf14,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #2 Hybrid Bullets Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmg01,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #3 Multi-Function Custom Version 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmg02,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #3 Onimusha Samanosuke Custom Version 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmg03,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #3 Summon Mount Custom Edition 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmg04,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #3 Shop Version Custom 2020-05-01)" , MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmg05,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #3 SE Special Custom Edition 2020-05-01)(Rollback)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmg06,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #3 Burst Enhanced Custom Edition 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmg07,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #3 Super D Custom version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmg08,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #3 Violence Custom Edition 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmg09,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #3 Ultimate Simplified Custom Edition 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmg10,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #3 Infinite Firepower Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmg11,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #3 Easy Mode Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmg12,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #3 Enemy Speed Up Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
//GAME( 2020, mslug3ctmg13,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #3 Automatic Storage Custom Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, mslug3ctmg14,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #3 Hybrid Bullets Version 2020-05-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmh01,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #1 Multi-Function Custom Version 2023-03-28)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmh02,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #1 Onimusha Samanosuke Custom Version 2023-03-28)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmh03,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #1 Summon Mount Custom Edition 2023-03-28)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmh04,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #1 Shop Version Custom 2023-03-28)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmh05,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #1 SE Special Custom Edition 2023-03-28)(Rollback)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmh06,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #1 Burst Enhanced Custom Edition 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmh07,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #1 Super D Custom version 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmh08,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #1 Violence Custom Edition 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmh09,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #1 Ultimate Simplified Custom Edition 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmh10,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #1 Infinite Firepower Custom Version 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmh11,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #1 Easy Mode Custom Version 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmh12,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #1 Enemy Speed Up Custom Version 2023-03-28)", MACHINE_SUPPORTS_SAVE )
//GAME( 2023, mslug3ctmh13,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #1 Automatic Storage Custom Version 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmh14,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #1 Hybrid Bullets Version 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmi01,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #2 Multi-Function Custom Version 2023-03-28)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmi02,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #2 Onimusha Samanosuke Custom Version 2023-03-28)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmi03,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #2 Summon Mount Custom Edition 2023-03-28)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmi04,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #2 Shop Version Custom 2023-03-28)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmi05,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #2 SE Special Custom Edition 2023-03-28)(Rollback)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmi06,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #2 Burst Enhanced Custom Edition 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmi07,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #2 Super D Custom version 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmi08,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #2 Violence Custom Edition 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmi09,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #2 Ultimate Simplified Custom Edition 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmi10,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #2 Infinite Firepower Custom Version 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmi11,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #2 Easy Mode Custom Version 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmi12,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #2 Enemy Speed Up Custom Version 2023-03-28)", MACHINE_SUPPORTS_SAVE )
//GAME( 2023, mslug3ctmi13,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #2 Automatic Storage Custom Version 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmi14,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #2 Hybrid Bullets Version 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmj01,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #3 Multi-Function Custom Version 2023-03-28)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmj02,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #3 Onimusha Samanosuke Custom Version 2023-03-28)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmj03,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #3 Summon Mount Custom Edition 2023-03-28)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmj04,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #3 Shop Version Custom 2023-03-28)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmj05,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #3 SE Special Custom Edition 2023-03-28)(Rollback)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmj06,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #3 Burst Enhanced Custom Edition 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmj07,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #3 Super D Custom version 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmj08,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #3 Violence Custom Edition 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmj09,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #3 Ultimate Simplified Custom Edition 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmj10,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #3 Infinite Firepower Custom Version 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmj11,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #3 Easy Mode Custom Version 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmj12,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #3 Enemy Speed Up Custom Version 2023-03-28)", MACHINE_SUPPORTS_SAVE )
//GAME( 2023, mslug3ctmj13,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #3 Automatic Storage Custom Version 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmj14,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #3 Hybrid Bullets Version 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmk01,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #4 Multi-Function Custom Version 2023-03-28)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmk02,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #4 Onimusha Samanosuke Custom Version 2023-03-28)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmk03,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #4 Summon Mount Custom Edition 2023-03-28)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmk04,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #4 Shop Version Custom 2023-03-28)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmk05,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #4 SE Special Custom Edition 2023-03-28)(Rollback)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmk06,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #4 Burst Enhanced Custom Edition 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmk07,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #4 Super D Custom version 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmk08,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #4 Violence Custom Edition 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmk09,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #4 Ultimate Simplified Custom Edition 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmk10,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #4 Infinite Firepower Custom Version 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmk11,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #4 Easy Mode Custom Version 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmk12,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #4 Enemy Speed Up Custom Version 2023-03-28)", MACHINE_SUPPORTS_SAVE )
//GAME( 2023, mslug3ctmk13,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #4 Automatic Storage Custom Version 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctmk14,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug #4 Hybrid Bullets Version 2023-03-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ctml01,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Pigeon Slug Custom Version 2023-07-04)" , MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug4ctma01,       mslug4,   neogeo_noslot, mslughw, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Enemies Resetting The Longest Fight Version 2022-10-24)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug4ctma02,       mslug4,   neogeo_noslot, mslughw, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Enemies Resetting Multi-Function Version 2022-10-24)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug4ctma03,       mslug4,   neogeo_noslot, mslughw, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Enemies Resetting 1V2 Generation Version 2022-10-24)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug4ctma04,       mslug4,   neogeo_noslot, mslughw, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Enemies Resetting Change Weapon Version 2022-10-24)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug4ctma05,       mslug4,   neogeo_noslot, mslughw, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Enemies Resetting Children's Version Version 2022-10-24)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug4ctma06,       mslug4,   neogeo_noslot, mslughw, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Enemies Resetting Enemy Speed Up Version 2022-10-24)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug4ctma07,       mslug4,   neogeo_noslot, mslughw, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Enemies Resetting Unity Time! Version 2022-10-24)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug4ctma08,       mslug4,   neogeo_noslot, mslughw, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Enemies Resetting War Chariot Version 2022-10-24)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug4ctma09,       mslug4,   neogeo_noslot, mslughw, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Enemies Resetting Burst Enhanced Version 2022-10-24)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug4ctma10,       mslug4,   neogeo_noslot, mslughw, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Enemies Resetting Super D Version 2022-10-24)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug4ctma11,       mslug4,   neogeo_noslot, mslughw, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Enemies Resetting Easy Mode Version 2022-10-24)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug4ctma12,       mslug4,   neogeo_noslot, mslughw, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Enemies Resetting Early Summer Starry Sky Version 2022-10-24)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctma01,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Unlimited Firepower Infinite Firepower Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctma02,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Unlimited Firepower Easy Mode Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctma03,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Unlimited Firepower Burst Enhanced Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctma04,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Unlimited Firepower 1V2 Generation Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctma05,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Unlimited Firepower Big Heavy Machine Gun Flame Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctma06,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Unlimited Firepower Violence Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctma07,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Unlimited Firepower Enemy Speed Up Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctma08,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Unlimited Firepower Optimize Version Custom 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctma09,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Unlimited Firepower Unity Time! Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctma10,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Unlimited Firepower Survival Attack Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctma11,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Unlimited Firepower Multi-Function Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctma12,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Unlimited Firepower War Chariot Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctma13,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Unlimited Firepower Hybrid Bullets Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctma14,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Unlimited Firepower Change Weapon And Mummy Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctma15,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Unlimited Firepower Green Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctma16,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Unlimited Firepower Early Summer Starry Sky Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmb01,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Heavy Plate Infinite Firepower Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmb02,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Heavy Plate Easy Mode Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmb03,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Heavy Plate Burst Enhanced Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmb04,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Heavy Plate 1V2 Generation Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmb05,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Heavy Plate Big Heavy Machine Gun Flame Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmb06,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Heavy Plate Violence Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmb07,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Heavy Plate Enemy Speed Up Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmb08,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Heavy Plate Optimize Version Custom 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmb09,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Heavy Plate Unity Time! Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmb10,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Heavy Plate Survival Attack Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmb11,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Heavy Plate Multi-Function Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmb12,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Heavy Plate War Chariot Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmb13,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Heavy Plate Hybrid Bullets Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmb14,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Heavy Plate Change Weapon And Mummy Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmb15,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Heavy Plate Green Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmb16,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Heavy Plate Early Summer Starry Sky Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmc01,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Remake Infinite Firepower Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmc02,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Remake Easy Mode Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmc03,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Remake Burst Enhanced Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmc04,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Remake 1V2 Generation Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmc05,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Remake Big Heavy Machine Gun Flame Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmc06,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Remake Violence Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmc07,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Remake Enemy Speed Up Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmc08,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Remake Optimize Version Custom 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmc09,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Remake Unity Time! Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmc10,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Remake Survival Attack Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmc11,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Remake Multi-Function Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmc12,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Remake War Chariot Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmc13,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Remake Hybrid Bullets Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmc14,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Remake Change Weapon And Mummy Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmc15,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Remake Green Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmc16,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Remake Early Summer Starry Sky Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmd01,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Allen O'Neil See You In Hell Infinite Firepower Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmd02,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Allen O'Neil See You In Hell Easy Mode Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmd03,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Allen O'Neil See You In Hell Burst Enhanced Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmd04,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Allen O'Neil See You In Hell 1V2 Generation Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmd05,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Allen O'Neil See You In Hell Big Heavy Machine Gun Flame Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmd06,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Allen O'Neil See You In Hell Violence Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmd07,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Allen O'Neil See You In Hell Enemy Speed Up Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmd08,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Allen O'Neil See You In Hell Optimize Version Custom 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmd09,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Allen O'Neil See You In Hell Unity Time! Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmd10,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Allen O'Neil See You In Hell Survival Attack Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmd11,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Allen O'Neil See You In Hell Multi-Function Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmd12,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Allen O'Neil See You In Hell War Chariot Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmd13,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Allen O'Neil See You In Hell Hybrid Bullets Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmd14,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Allen O'Neil See You In Hell Change Weapon And Mummy Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmd15,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Allen O'Neil See You In Hell Green Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmd16,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Allen O'Neil See You In Hell Early Summer Starry Sky Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctme01,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Multi-Carrier Infinite Firepower Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctme02,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Multi-Carrier Easy Mode Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctme03,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Multi-Carrier Burst Enhanced Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctme04,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Multi-Carrier 1V2 Generation Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctme05,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Multi-Carrier Big Heavy Machine Gun Flame Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctme06,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Multi-Carrier Violence Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctme07,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Multi-Carrier Enemy Speed Up Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctme08,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Multi-Carrier Optimize Version Custom 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctme09,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Multi-Carrier Unity Time! Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctme10,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Multi-Carrier Survival Attack Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctme11,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Multi-Carrier Multi-Function Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctme12,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Multi-Carrier War Chariot Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctme13,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Multi-Carrier Hybrid Bullets Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctme14,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Multi-Carrier Change Weapon And Mummy Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctme15,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Multi-Carrier Green Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctme16,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Multi-Carrier Early Summer Starry Sky Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmf01,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Level Reset Special Infinite Firepower Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmf02,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Level Reset Special Easy Mode Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmf03,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Level Reset Special Burst Enhanced Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmf04,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Level Reset Special 1V2 Generation Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmf05,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Level Reset Special Big Heavy Machine Gun Flame Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmf06,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Level Reset Special Violence Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmf07,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Level Reset Special Enemy Speed Up Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmf08,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Level Reset Special Optimize Version Custom 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmf09,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Level Reset Special Unity Time! Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmf10,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Level Reset Special Survival Attack Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmf11,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Level Reset Special Multi-Function Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmf12,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Level Reset Special War Chariot Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmf13,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Level Reset Special Hybrid Bullets Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmf14,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Level Reset Special Change Weapon And Mummy Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmf15,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Level Reset Special Green Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmf16,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Level Reset Special Early Summer Starry Sky Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmg01,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Reset Infinite Firepower Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmg02,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Reset Easy Mode Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmg03,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Reset Burst Enhanced Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmg04,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Reset 1V2 Generation Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmg05,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Reset Big Heavy Machine Gun Flame Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmg06,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Reset Violence Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmg07,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Reset Enemy Speed Up Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmg08,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Reset Optimize Version Custom 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmg09,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Reset Unity Time! Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmg10,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Reset Survival Attack Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmg11,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Reset Multi-Function Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmg12,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Reset War Chariot Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmg13,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Reset Hybrid Bullets Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmg14,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Reset Change Weapon And Mummy Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmg15,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Reset Green Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmg16,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Reset Early Summer Starry Sky Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmh01,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Survival Enemies Resetting Infinite Firepower Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmh02,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Survival Enemies Resetting Easy Mode Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmh03,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Survival Enemies Resetting Burst Enhanced Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmh04,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Survival Enemies Resetting 1V2 Generation Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmh05,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Survival Enemies Resetting Big Heavy Machine Gun Flame Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmh06,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Survival Enemies Resetting Violence Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmh07,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Survival Enemies Resetting Enemy Speed Up Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmh08,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Survival Enemies Resetting Optimize Version Custom 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmh09,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Survival Enemies Resetting Unity Time! Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmh10,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Survival Enemies Resetting Survival Attack Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmh11,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Survival Enemies Resetting Multi-Function Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmh12,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Survival Enemies Resetting War Chariot Custom Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmh13,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Survival Enemies Resetting Hybrid Bullets Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmh14,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Survival Enemies Resetting Change Weapon And Mummy Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmh15,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Survival Enemies Resetting Green Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmh16,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Survival Enemies Resetting Early Summer Starry Sky Version 2023-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxctmi01,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Legendary Origin Edition Update 2023-02-13)", MACHINE_SUPPORTS_SAVE ) //Update last Survival 2023 (Enemy Reset)

/*    YEAR   NAME             PARENT       MACHINE       INPUT                       INIT        MONITOR COMPANY           FULLNAME FLAGS */
// Metal Slug (Version Remastering)
GAME( 2023, mslug3ly01,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Legendary Enemies Resetting #1 Remastering Edition 2023-07-07)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ly02,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Legendary Enemies Resetting #2 Remastering Edition 2023-07-07)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ly03,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Legendary Enemies Resetting #3 Remastering Edition 2023-07-07)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ly04,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Legendary Enemies Resetting #4 Remastering Edition 2023-07-07)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ly05,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Legendary Enemies Resetting #5 Remastering Edition 2023-07-07)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ly06,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Legendary Enemies Resetting #6 Remastering Edition 2023-07-07)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ly07,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Legendary Enemies Resetting #7 Remastering Edition 2023-07-07)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxer01,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Unlimited Firepower 2R Legendary Remastering Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxer02,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Heavy Plate 2R Legendary Remastering Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxer03,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Remake 2R Legendary Remastering Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxer04,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Allen O'Neil See You In Hell 2R Legendary Remastering Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxer05,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Multi-Carrier 2R Legendary Remastering Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxer06,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Level Reset Special 2R Legendary Remastering Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxer07,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Reset 2R Legendary Remastering Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )

/*    YEAR   NAME             PARENT       MACHINE       INPUT                       INIT        MONITOR COMPANY           FULLNAME FLAGS */
// Metal Slug (All Apocalyptic Time Edition)
GAME( 2021, mslug2at01,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "Gaston90",        "Metal Slug 2 Turbo (Apocalyptic Time Ports 0.2 2021-07-17)", MACHINE_SUPPORTS_SAVE ) //2023-03-21
GAME( 2020, mslugxtst01,      mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "Gaston90",        "Metal Slug X (Testing My First Level 2020-04-07)", MACHINE_SUPPORTS_SAVE ) // Update 2023-03-21
GAME( 2020, mslugxtao01,      mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "Gaston90",        "Metal Slug X (Allen O'Neil See You In Hell 1.0 2R Edition 2020-07-16)", MACHINE_SUPPORTS_SAVE ) // Update 2023-03-21 
GAME( 2020, mslugxat01,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "Gaston90",        "Metal Slug X (Apocalyptic Time 0.1 2R Edition 2020-03-22)", MACHINE_SUPPORTS_SAVE ) // Update 2023-03-21
GAME( 2020, mslugxat02,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "Gaston90",        "Metal Slug X (Apocalyptic Time 1.0 2R Edition 2020-04-20)", MACHINE_SUPPORTS_SAVE ) // Update 2023-03-21
GAME( 2020, mslugxat03,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "Gaston90",        "Metal Slug X (Apocalyptic Time 2.1 2R Edition 2020-05-01)", MACHINE_SUPPORTS_SAVE ) // Update 2023-03-21 
GAME( 2020, mslugxat04,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "Gaston90",        "Metal Slug X (Apocalyptic Time 2.2 2R Edition 2020-05-11)", MACHINE_SUPPORTS_SAVE ) // Update 2023-03-21 
GAME( 2020, mslugxat05,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "Gaston90",        "Metal Slug X (Apocalyptic Time 3.0 2R Edition 2020-05-21)", MACHINE_SUPPORTS_SAVE ) // Update 2023-03-21
GAME( 2020, mslugxat06,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "Gaston90",        "Metal Slug X (Apocalyptic Time 4.0 2R Edition 2020-06-23)", MACHINE_SUPPORTS_SAVE ) // Update 2023-03-21
GAME( 2020, mslugxat07,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "Gaston90",        "Metal Slug X (Apocalyptic Time 5.5 2R Edition 2020-08-04)", MACHINE_SUPPORTS_SAVE ) // Update 2023-03-21
GAME( 2021, mslugxat08,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "Gaston90",        "Metal Slug X (Apocalyptic Time The 1 Beginning Of The End Of Time 6.0 2R Edition 2021-04-20)", MACHINE_SUPPORTS_SAVE ) // Update 2023-03-21
GAME( 2021, mslugxat09,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "Gaston90",        "Metal Slug X (Apocalyptic Time The 2 Beginning Of The End Of Time 7.1 2R Edition 2021-12-05)", MACHINE_SUPPORTS_SAVE ) // Update 2023-03-21
GAME( 2023, mslugxat10,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "Gaston90",        "Metal Slug X (Apocalyptic Time The 3 Beginning Of The End Of Time 8.2 2R Edition 2023-04-09)", MACHINE_SUPPORTS_SAVE ) // Update 2023-03-21

/*    YEAR   NAME             PARENT       MACHINE       INPUT                       INIT        MONITOR COMPANY           FULLNAME FLAGS */
// Metal Slug (Remix Edition)
GAME( 2023, mslugla01,        mslug,    neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug (Multi-Function Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug2la01,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (XR Remix Edition 2023-03-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug2la02,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (XR Fat Remix Edition 2023-03-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug2la03,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (XR Multi-Function Remix Edition 2023-03-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug2la04,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (XR Multi-Function Fat Remix Edition 2023-03-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug2la05,       mslug2,   neogeo_noslot, mslughw, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (XR Survival Remix Edition 2023-03-21)", MACHINE_SUPPORTS_SAVE )//To enable Mods random you need to apply a command you have to press the Stars + D button to change Stars + C.
GAME( 2023, mslug2la06,       mslug2,   neogeo_noslot, mslughw, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (XR Survival Fat Remix Edition 2023-03-21)", MACHINE_SUPPORTS_SAVE )//To enable Mods random you need to apply a command you have to press the Stars + D button to change Stars + C.
GAME( 2023, mslug2la07,       mslug2,   neogeo_noslot, mslughw, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (XR Survival Hybrid Bullets Remix Edition 2023-03-21)", MACHINE_SUPPORTS_SAVE )//To enable Mods random you need to apply a command you have to press the Stars + D button to change Stars + C.
GAME( 2023, mslug2la08,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (XR Hybrid Bullets Remix Edition 2023-03-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug2lb01,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (Enemies Resetting XR Remix Edition 2023-03-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug2lb02,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (Enemies Resetting XR Fat Remix Edition 2023-03-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug2lb03,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (Enemies Resetting XR Multi-Function Remix Edition 2023-03-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug2lb04,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (Enemies Resetting XR Multi-Function Fat Remix Edition 2023-03-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug2lb05,       mslug2,   neogeo_noslot, mslughw, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (Enemies Resetting XR Survival Remix Edition 2023-03-21)", MACHINE_SUPPORTS_SAVE )//To enable Mods random you need to apply a command you have to press the Stars + D button to change Stars + C.
GAME( 2023, mslug2lb06,       mslug2,   neogeo_noslot, mslughw, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (Enemies Resetting XR Survival Fat Remix Edition 2023-03-21)", MACHINE_SUPPORTS_SAVE )//To enable Mods random you need to apply a command you have to press the Stars + D button to change Stars + C.
GAME( 2023, mslug2lb07,       mslug2,   neogeo_noslot, mslughw, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (Enemies Resetting XR Survival Hybrid Bullets Remix Edition 2023-03-21)", MACHINE_SUPPORTS_SAVE )//To enable Mods random you need to apply a command you have to press the Stars + D button to change Stars + C.
GAME( 2023, mslug2lb08,       mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (Enemies Resetting XR Hybrid Bullets Remix Edition 2023-03-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3la01,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Multi-Function Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3la02,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Multi-Function Fat Players Mode Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3la03,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Multi-Function Zombie Players Mode Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3la04,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Multi-Function Mummy Players Mode Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3la05,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Multi-Function Hybrid Bullets Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3la06,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Summon Mount Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lb01,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #1 Multi-Function Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lb02,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #1 Multi-Function Fat Players Mode Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lb03,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #1 Multi-Function Zombie Players Mode Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lb04,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #1 Multi-Function Mummy Players Mode Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lb05,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #1 Multi-Function Hybrid Bullets Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lb06,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #1 Summon Mount Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lc01,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #2 Multi-Function Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lc02,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #2 Multi-Function Fat Players Mode Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lc03,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #2 Multi-Function Zombie Players Mode Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lc04,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #2 Multi-Function Mummy Players Mode Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lc05,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #2 Multi-Function Hybrid Bullets Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lc06,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #2 Summon Mount Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ld01,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #3 Multi-Function Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ld02,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #3 Multi-Function Fat Players Mode Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ld03,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #3 Multi-Function Zombie Players Mode Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ld04,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #3 Multi-Function Mummy Players Mode Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ld05,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #3 Multi-Function Hybrid Bullets Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3ld06,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #3 Summon Mount Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3le01,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #4 Multi-Function Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3le02,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #4 Multi-Function Fat Players Mode Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3le03,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #4 Multi-Function Zombie Players Mode Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3le04,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #4 Multi-Function Mummy Players Mode Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3le05,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #4 Multi-Function Hybrid Bullets Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3le06,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #4 Summon Mount Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lf01,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #5 Multi-Function Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lf02,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #5 Multi-Function Fat Players Mode Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lf03,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #5 Multi-Function Zombie Players Mode Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lf04,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #5 Multi-Function Mummy Players Mode Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lf05,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #5 Multi-Function Hybrid Bullets Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lf06,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #5 Summon Mount Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lg01,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #6 Multi-Function Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lg02,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #6 Multi-Function Fat Players Mode Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lg03,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #6 Multi-Function Zombie Players Mode Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lg04,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #6 Multi-Function Mummy Players Mode Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lg05,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #6 Multi-Function Hybrid Bullets Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lg06,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #6 Summon Mount Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lh01,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #7 Multi-Function Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lh02,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #7 Multi-Function Fat Players Mode Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lh03,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #7 Multi-Function Zombie Players Mode Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lh04,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #7 Multi-Function Mummy Players Mode Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lh05,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #7 Multi-Function Hybrid Bullets Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3lh06,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #7 Summon Mount Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3li01,       mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Random Enemies Resetting Remix Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4la01,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Plus Style Model Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4la02,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Plus Style Model Fat Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4la03,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Plus Style Model Zombie Players Mode Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4la04,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Plus Style Model Mummy Players Mode Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4la05,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Plus Style Model Monkeys Players Mode Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4lb01,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Enemies Resetting Plus Style Model Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4lb02,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Enemies Resetting Plus Style Model Fat Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4lb03,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Enemies Resetting Plus Style Model Zombie Players Mode Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4lb04,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Enemies Resetting Plus Style Model Mummy Players Mode Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4lb05,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Enemies Resetting Plus Style Model Monkeys Players Mode Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4lc01,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Multi-Function Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4lc02,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Multi-Function Fat Players Mode Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4lc03,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Multi-Function Zombie Players Mode Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4lc04,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Multi-Function Mummy Players Mode Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4lc05,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Multi-Function Monkeys Players Mode Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4ld01,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Enemies Resetting Multi-Function Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4ld02,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Enemies Resetting Multi-Function Fat Players Mode Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4ld03,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Enemies Resetting Multi-Function Zombie Players Mode Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE ) 
GAME( 2023, mslug4ld04,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Enemies Resetting Multi-Function Mummy Players Mode Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4ld05,       mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Enemies Resetting Multi-Function Monkeys Players Mode Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug5la01,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "PSMSlugForever",  "Metal Slug 5 (Enemy Soldiers Enhanced Multi-Function Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug5lb01,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "PSMSlugForever",  "Metal Slug 5 (Enemies Resetting Multi-Function Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug5lc01,       mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "PSMSlugForever",  "Metal Slug 5 (Enemies Resetting Hybrid bullets Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxla01,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Unlimited Firepower 2R Extreme Space Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxla02,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Unlimited Firepower 2R Extreme Space Big Heavy Machine Gun Flame Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxla03,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Unlimited Firepower 2R Extreme Space Hybrid Bullets Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxlb01,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Heavy Plate 2R Extreme Space Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxlb02,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Heavy Plate 2R Extreme Space Big Heavy Machine Gun Flame Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxlb03,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Heavy Plate 2R Extreme Space Hybrid Bullets Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxlc01,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Remake 2R Extreme Space Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxlc02,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Remake 2R Extreme Space Big Heavy Machine Gun Flame Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxlc03,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Remake 2R Extreme Space Hybrid Bullets Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxld01,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Apocalyptic Time The 3 Beginning Of The End Of Time 2R Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxld02,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Apocalyptic Time The 3 Beginning Of The End Of Time 2R Big Heavy Machine Gun Flame Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxld03,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Apocalyptic Time The 3 Beginning Of The End Of Time 2R Hybrid Bullets Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxle01,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Allen O'Neil See You In Hell 2R Extreme Space Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxle02,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Allen O'Neil See You In Hell 2R Extreme Space Big Heavy Machine Gun Flame Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxle03,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Allen O'Neil See You In Hell 2R Extreme Space Hybrid Bullets Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxlf01,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Multi-Carrier 2R Extreme Space Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxlf02,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Multi-Carrier 2R Extreme Space Big Heavy Machine Gun Flame Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxlf03,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Multi-Carrier 2R Extreme Space Hybrid Bullets Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxlg01,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Extreme Space 2R Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxlg02,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Extreme Space 2R Big Heavy Machine Gun Flame Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxlg03,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Extreme Space 2R Hybrid Bullets Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxlh01,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Reset 2R Extreme Space Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxlh02,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Reset 2R Extreme Space Big Heavy Machine Gun Flame Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxlh03,       mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Reset 2R Extreme Space Hybrid Bullets Remix Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )

/*    YEAR   NAME             PARENT       MACHINE       INPUT                       INIT        MONITOR COMPANY           FULLNAME FLAGS */
// Metal Slug (Remix Extreme Edition)
GAME( 2023, mslugrma01,       mslug,    neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug (Multi-Function Heavy Machine Gun Extreme Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug2rma01,      mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (XR Heavy Machine Gun Extreme Edition 2023-03-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug2rma02,      mslug2,   neogeo_noslot, mslughw, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (XR Survival Heavy Machine Gun Extreme Edition 2023-03-21)", MACHINE_SUPPORTS_SAVE )//To enable Mods random you need to apply a command you have to press the Stars + D button to change Stars + C.
GAME( 2023, mslug2rmb01,      mslug2,   neogeo_noslot, mslughb, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (Enemies Resetting XR Heavy Machine Gun Extreme Edition 2023-03-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug2rmb02,      mslug2,   neogeo_noslot, mslughw, neogeo_state,    init_neogeo,     ROT0, "PSMSlugForever",  "Metal Slug 2 Turbo (Enemies Resetting XR Survival Heavy Machine Gun Extreme Edition 2023-03-21)", MACHINE_SUPPORTS_SAVE ) //To enable Mods random you need to apply a command you have to press the Stars + D button to change Stars + C.
GAME( 2023, mslug3rma01,      mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Multi-Function Big Heavy Machine Gun Extreme Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3rmb01,      mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #1 Multi-Function Big Heavy Machine Gun Extreme Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3rmc01,      mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #2 Multi-Function Big Heavy Machine Gun Extreme Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3rmd01,      mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #3 Multi-Function Big Heavy Machine Gun Extreme Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3rme01,      mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #4 Multi-Function Big Heavy Machine Gun Extreme Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3rmf01,      mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #5 Multi-Function Big Heavy Machine Gun Extreme Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3rmg01,      mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #6 Multi-Function Big Heavy Machine Gun Extreme Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3rmh01,      mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Enemies Resetting #7 Multi-Function Big Heavy Machine Gun Extreme Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug3rmi01,      mslug3,   neogeo_noslot, mslughb, neogeo_state,    init_mslug3hb,   ROT0, "PSMSlugForever",  "Metal Slug 3 (Random Enemies Resetting Big Heavy Machine Gun Extreme Edition 2023-07-07)" , MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4rma01,      mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Plus Style Model Big Heavy Machine Gun Extreme Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4rmb01,      mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Enemies Resetting Plus Style Model Big Heavy Machine Gun Extreme Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4rmc01,      mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Multi-Function Big Heavy Machine Gun Extreme Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4rmd01,      mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Enemies Resetting Multi-Function Big Heavy Machine Gun Extreme Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug4rme01,      mslug4,   neogeo_noslot, mslughb, neogeo_state,    init_mslug4hb,   ROT0, "PSMSlugForever",  "Metal Slug 4 (Last Bullet Big Heavy Machine Gun Extreme Edition 2023-02-25)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug5rma01,      mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "PSMSlugForever",  "Metal Slug 5 (Big Heavy Machine Gun Extreme Edition 2020-12-24)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug5rmb01,      mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "PSMSlugForever",  "Metal Slug 5 (Multi-Function Enemy Soldiers Enhanced Big Heavy Machine Gun Extreme Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug5rmc01,      mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "PSMSlugForever",  "Metal Slug 5 (Enemy Soldiers Enhanced Big Heavy Machine Gun Extreme Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug5rmd01,      mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "PSMSlugForever",  "Metal Slug 5 (Enemy Soldiers Magic Big Heavy Machine Gun Extreme Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug5rme01,      mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "PSMSlugForever",  "Metal Slug 5 (Fighting Machine Latest Big Heavy Machine Gun Extreme Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslug5rmf01,      mslug5,   neogeo_noslot, mslughb, neogeo_state,    init_mslug5hb,   ROT0, "PSMSlugForever",  "Metal Slug 5 (Enemies Resetting Big Heavy Machine Gun Extreme Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxrma01,      mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Unlimited Firepower 2R Extreme Space Big Heavy Machine Gun Extreme Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxrmb01,      mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Heavy Plate 2R Extreme Space Big Heavy Machine Gun Extreme Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxrmc01,      mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Remake 2R Extreme Space Big Heavy Machine Gun Extreme Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxrmd01,      mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Apocalyptic Time The 3 Beginning Of The End Of Time 2R Big Heavy Machine Gun Extreme Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxrme01,      mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Allen O'Neil See You In Hell 2R Extreme Space Big Heavy Machine Gun Extreme Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxrmf01,      mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Multi-Carrier 2R Extreme Space Big Heavy Machine Gun Extreme Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxrmg01,      mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Extreme Space 2R Big Heavy Machine Gun Extreme Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, mslugxrmh01,      mslugx,   neogeo_noslot, mslughb, neogeo_state,    init_mslugx,     ROT0, "PSMSlugForever",  "Metal Slug X (Enemy Soldiers Reset 2R Extreme Space Big Heavy Machine Gun Extreme Edition 2023-07-23)", MACHINE_SUPPORTS_SAVE )
